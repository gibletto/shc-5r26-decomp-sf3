"""Execute narrow constant-reuse controls and compare disabled native output.

Uses the game's existing SH2 interpreter. No installed tools or sources change;
all native compiler/linker outputs stay in a fresh --work directory.
"""
import argparse
import csv
import hashlib
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parent.parent
OPTIONS = ['-cpu=sh2', '-division=cpu', '-endian=big', '-pic=0',
           '-extra=m=8,a=8', '-nortnext', '-optimize=1', '-speed', '-noinline']
NAMES = ['narrow_' + t + '_' + op for t in ('s8', 'u8', 's16', 'u16') for op in ('add', 'sub')]
NAMES += ['wide_sum', 'folded_address', 'unequal_constant', 'changed_base', 'signed_constant']
PREFIXES = ('GEN_', 'PEP_', 'MDL_', 'ASM_', 'SWITCH_', 'XJUMP', 'SLOT_')


def signed(value, bits):
    value &= (1 << bits) - 1
    return value - (1 << bits) if value & (1 << (bits - 1)) else value


def table(path, header, rows):
    with path.open('w', newline='') as f:
        w = csv.writer(f, delimiter='\t', lineterminator='\n')
        w.writerow(header)
        w.writerows(rows)


def run(command, cwd, env, name):
    (cwd / (name + '.command.txt')).write_text(subprocess.list2cmdline(command) + '\n')
    with (cwd / (name + '.log')).open('w') as log:
        p = subprocess.run(command, cwd=cwd, env=env, stdout=log, stderr=subprocess.STDOUT,
                           timeout=180, creationflags=0x08000000)
    assert p.returncode == 0, (name, p.returncode, cwd)


def listing(text):
    return re.sub(r'\d\d-[A-Za-z]{3}-\d{4} \d\d:\d\d:\d\d', '<compile-date>', text)


def body(module, name):
    start = module.starts[name]
    end = min([value for value in module.starts.values() if value > start] + [module.sizes['P']])
    relocations = tuple((offset - start, width, expression) for section, offset, width, expression
                        in module.relocations if section == 'P' and start <= offset < end)
    return (end - start, module.words[name], relocations)


def execute(dx, image, symbols, setting, rows):
    base = 0x02010000
    dx.G = {}
    live = dx.LiveIn(image)
    for name in NAMES:
        xs = (0, 1, 2, 3) if name == 'folded_address' else (-65537, -32768, -129, -1, 0, 1, 127, 32767, 65536)
        for seed in (0, 1, 127, 128, 255, 256, 32767, 32768, 65534, 65535):
            for x in xs:
                initial = bytearray([0x5a] * 160)
                def put(offset, width, value):
                    initial[offset:offset + width] = (value & ((1 << (width * 8)) - 1)).to_bytes(width, 'big')
                for index in range(4):
                    put(index * 36 + 32, 2, seed + index)
                    put(index * 36 + 34, 2, 65535 - seed - index)
                width = 1 if name.startswith(('narrow_s8', 'narrow_u8')) else 2
                if name == 'wide_sum':
                    width = 4
                put(32, width, seed)
                expected = bytearray(initial)
                a = signed(seed, width * 8)
                b = int.from_bytes(initial[34:36], 'big')
                if name.startswith('narrow_'):
                    unsigned = name.split('_')[1].startswith('u')
                    a = seed & ((1 << (width * 8)) - 1) if unsigned else a
                    value = a + x + (32 if name.endswith('_add') else -32)
                    stored = value & ((1 << (width * 8)) - 1)
                    result = stored if unsigned else signed(stored, width * 8)
                    expected[32:32 + width] = stored.to_bytes(width, 'big')
                elif name == 'wide_sum':
                    result = a + x + 32
                    expected[32:36] = (result & 0xffffffff).to_bytes(4, 'big')
                elif name == 'folded_address':
                    off = x * 36
                    result = signed(int.from_bytes(initial[off + 32:off + 34], 'big'), 16)
                    result += int.from_bytes(initial[off + 34:off + 36], 'big')
                else:
                    if name == 'unequal_constant':
                        value = a + x + 31
                    elif name == 'changed_base':
                        value = a + b + x + 32
                    else:
                        value = a + x - 1
                        b = (b + 65535) & 65535
                        expected[34:36] = b.to_bytes(2, 'big')
                    expected[32:34] = (value & 65535).to_bytes(2, 'big')
                    result = signed(value, 16) + (0 if name == 'unequal_constant' else b)
                machine = dx.Machine(image, symbols[name], dx.BASE, image.hi, 0, [], live, lambda value: value)
                machine.R[4], machine.R[5] = base, x & 0xffffffff
                for offset, value in enumerate(initial):
                    machine.wr(base + offset, 1, value)
                machine.trace, machine.seg = [], []
                machine.run()
                context = (setting, name, seed, x)
                assert machine.trace and machine.trace[-1][0] == 'ret', context
                assert machine.trace[-1][1] == result & 0xffffffff, (context, 'return', machine.trace[-1], result)
                assert machine.trace[-1][2], (context, 'callee-saved')
                assert not any(event[0] == 'call' for event in machine.trace), (context, 'external call')
                actual = bytes(machine.rd(base + offset, 1) for offset in range(len(initial)))
                assert actual == bytes(expected), (context, 'memory')
                rows.append([setting, name, seed, x, result & 0xffffffff, 'PASS'])


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--trial', type=Path, help='new shcgen.exe only')
    ap.add_argument('--production', type=Path, help='old complete tool bundle')
    ap.add_argument('--r26', type=Path, help='original Release26 tool bundle')
    ap.add_argument('--matchlab', type=Path, help="the game tree's tools/matchlab (its SH2 interpreter)")
    ap.add_argument('--work', type=Path, required=True)
    ap.add_argument('--readback', action='store_true', help='audit retained compiles without invoking any native tool')
    ap.add_argument('--diagnostic-work', type=Path, help='retained default-off trial fixture output, for default-vs-enabled parity')
    args = ap.parse_args()
    if not (args.trial and args.production and args.r26):
        print('SKIP: needs --trial, --production and --r26 (see tests/README.md)')
        return 0
    if not args.matchlab or not (args.matchlab / 'diff_exec.py').is_file() \
            or not (args.matchlab / 'msearch_module.py').is_file():
        print('SKIP: needs --matchlab, the tools/matchlab directory of the game development tree '
              '(diff_exec.py, msearch_module.py)')
        return 0
    work = args.work.resolve()
    if args.readback:
        assert work.is_dir(), 'retained work path required'
    else:
        assert not work.exists(), 'fresh work path required'
        work.mkdir(parents=True)
    sys.dont_write_bytecode = True
    sys.path.insert(0, str(args.matchlab.resolve()))
    sys.path.insert(0, str(ROOT / 'tests'))
    import diff_exec as dx
    import parity
    import msearch_module as mm
    bins = {}
    for label, origin in [('stock', args.r26), ('old', args.production), ('trial', args.production)]:
        bins[label] = work / ('bin_' + label)
        if not args.readback:
            shutil.copytree(origin, bins[label])
        for stage in ('shcmdl', 'shcgen', 'shcpep', 'shcasm', 'shc'):
            source = args.trial if label == 'trial' and stage == 'shcgen' else origin / (stage + '.exe')
            if not args.readback and label == 'trial' and stage == 'shcgen':
                shutil.copyfile(source, bins[label] / (stage + '.exe'))
            assert (bins[label] / (stage + '.exe')).read_bytes() == source.read_bytes(), (label, stage)
    modes = [('stock', 'stock', {}), ('alloff', 'trial', dict.fromkeys(parity.RULES, '0')),
             ('old', 'old', {}), ('unset', 'trial', {}),
             ('zero', 'trial', {'GEN_NARROW_CONST': '0'}), ('one', 'trial', {'GEN_NARROW_CONST': '1'})]
    outputs = {}
    parsed = {}
    executions = []
    for label, bundle, settings in modes:
        case = work / label
        if not args.readback:
            case.mkdir()
            (case / 'tmp').mkdir()
            shutil.copyfile(ROOT / 'tests/cases/narrow_const.c', case / 'fixture.c')
        assert (case / 'fixture.c').read_bytes() == (ROOT / 'tests/cases/narrow_const.c').read_bytes()
        env = {k: v for k, v in os.environ.items() if not k.startswith(PREFIXES)}
        env.update(settings, SHC_LIB=str(bins[bundle]), SHC_TMP=str(case / 'tmp'),
                   TMP=str(case / 'tmp'), TEMP=str(case / 'tmp'))
        recorded = {k: v for k, v in env.items()
                    if k.startswith(PREFIXES) or k in ('SHC_LIB', 'SHC_TMP', 'TMP', 'TEMP')}
        if not args.readback:
            table(case / 'environment.tsv', ['name', 'value'], sorted(recorded.items()))
            run([str(bins[bundle] / 'shc.exe'), 'fixture.c', *OPTIONS, '-object=fixture.obj',
                 '-listfile=fixture.lst', '-show=object'], case, env, 'compile')
        else:
            with (case / 'environment.tsv').open(newline='') as f:
                assert {r['name']: r['value'] for r in csv.DictReader(f, delimiter='\t')} == recorded
        outputs[label] = (parity.normalize((case / 'fixture.obj').read_bytes()), listing((case / 'fixture.lst').read_text()))
        parsed[label] = mm.parse_listing(case / 'fixture.lst')
        if not args.readback:
            (case / 'fixture.sub').write_text('START P(06000000),C(06008000),D(02008000),B(02009000)\n'
                                            'INPUT fixture.obj\nOUTPUT fixture.abs\nPRINT fixture.map\nFORM A\nEXIT\n')
            run([str(bins[bundle] / 'lnk.exe'), '-SUBCOMMAND=fixture.sub'], case, env, 'link')
            run([str(bins[bundle] / 'rof2bin.exe'), '-s=06000000', '-e=06010000', '-v=00', 'fixture.abs'], case, env, 'image')
        symbols = {n: int(a, 16) for n, a in re.findall(r"^_(\w+)\s+H'([0-9A-F]+)", (case / 'fixture.map').read_text(), re.M)}
        execute(dx, dx.Image((case / 'fixture.bin').read_bytes()), symbols, label, executions)
        print('PASS semantic', label, flush=True)
    assert outputs['stock'] == outputs['alloff'], 'flag0 with all rules zero differs from Release26'
    assert outputs['old'] == outputs['zero'], 'zero differs from previous GEN'
    assert outputs['unset'] == outputs['one'], 'default differs from explicit one'
    if args.diagnostic_work:
        for now, then in [('unset', 'one'), ('zero', 'zero')]:
            oldcase = args.diagnostic_work / then
            assert (oldcase / 'fixture.c').read_bytes() == (ROOT / 'tests/cases/narrow_const.c').read_bytes()
            old = (parity.normalize((oldcase / 'fixture.obj').read_bytes()), listing((oldcase / 'fixture.lst').read_text()))
            assert outputs[now] == old, ('diagnostic native/listing parity', now, then)
    off, on = parsed['zero'], parsed['one']
    changes = []
    assert off.frozen_data() == on.frozen_data(), 'non-P data changed'
    # Function-relative listing words and declared relocation expression records.
    for name in NAMES:
        a = body(off, name)
        b = body(on, name)
        changed = a != b
        changes.append([name, int(changed), str(a), str(b)])
    assert outputs['one'] != outputs['zero'], 'fixture did not exercise the rule'
    for name in ('wide_sum', 'folded_address', 'unequal_constant', 'signed_constant'):
        assert body(off, name) == body(on, name), ('control changed', name)
    for t in ('s8', 'u8', 's16', 'u16'):
        name = 'narrow_' + t + '_add'
        assert body(off, name) != body(on, name), ('narrow ADD did not exercise rule', name)
    print('SUB controls execute but do not trigger a changed reuse choice; not claimed as SUB policy coverage.', flush=True)
    table(work / 'changes.tsv', ['name', 'changed', 'zero', 'one'], changes)
    table(work / 'results.tsv', ['mode', 'name', 'seed', 'x', 'return', 'status'], executions)
    paths = [Path(__file__).resolve(), ROOT / 'tests/cases/narrow_const.c', Path(dx.__file__).resolve(), args.trial]
    if args.diagnostic_work:
        paths += [args.diagnostic_work / case / name for case in ('one', 'zero')
                  for name in ('fixture.c', 'fixture.obj', 'fixture.lst')]
    paths += [p for p in work.rglob('*') if p.is_file() and 'tmp' not in p.relative_to(work).parts]
    table(work / 'bindings.tsv', ['path', 'sha256'], [(str(p), hashlib.sha256(p.read_bytes()).hexdigest()) for p in sorted(set(paths))])
    print('PASS', len(executions), 'executions; disabled native/listing parity and enabled change verified', flush=True)


if __name__ == '__main__':
    main()
