"""Execute arithmetic constant-reuse controls and check disabled output parity.

All tools, inputs and outputs are copied into a fresh private work directory.
The byte-parity inventory stays unchanged; this test covers explicit bit 128 (which covers the retired bit 64:
63 against 191, and the previous bundle's 255 against 255 and 191).
"""
import argparse
import hashlib
import os
from pathlib import Path
import re
import shutil
import sys

import narrow_const as support
import parity

ROOT = Path(__file__).resolve().parent.parent
CHANGED = ('difference', 'sum', 'product', 'cast_difference', 'difference_seven',
           'difference_negative', 'product_sixteen', 'local_sum')
CONTROLS = ('plain_global', 'indirect_difference', 'call_difference',
            'outside_imm8', 'zero_offset')
NAMES = CHANGED + CONTROLS
SEEDS = (-128, -127, -1, 0, 1, 126, 127)


def expected(name, a, b):
    if name in ('product', 'product_sixteen'):
        value = a * b
    elif name in ('sum', 'local_sum'):
        value = a + b
    elif name == 'plain_global':
        value = a
    else:
        value = a - b
    constant = {'difference_seven': 7, 'difference_negative': -3,
                'product_sixteen': 16, 'outside_imm8': 128, 'zero_offset': 0}.get(name, 1)
    return (value + constant) * 3 + 65, constant * 28


def execute(dx, image, symbols, label, rows):
    dx.G = {}
    live = dx.LiveIn(image)
    for name in NAMES:
        for a in SEEDS:
            for b in SEEDS:
                machine = dx.Machine(image, symbols[name], dx.BASE, image.hi,
                                     0, [], live, lambda value: value)
                machine.wr(symbols['left_value'], 1, a & 255)
                machine.wr(symbols['right_value'], 1, b & 255)
                machine.wr(symbols['result'], 4, 0)
                machine.wr(symbols['checksum'], 4, 0)
                if name == 'local_sum':
                    machine.R[4], machine.R[5] = a & 0xffffffff, b & 0xffffffff
                elif name == 'indirect_difference':
                    machine.R[4], machine.R[5] = symbols['left_value'], symbols['right_value']
                machine.trace, machine.seg = [], []
                machine.run()
                context = (label, name, a, b)
                assert machine.trace and machine.trace[-1][0] == 'ret', context
                assert machine.trace[-1][2], (context, 'callee-saved')
                assert not any(event[0] == 'call' for event in machine.trace), (context, 'external call')
                value, checksum = expected(name, a, b)
                assert machine.rd(symbols['result'], 4) == value & 0xffffffff, (context, 'result')
                assert machine.rd(symbols['checksum'], 4) == checksum & 0xffffffff, (context, 'arguments')
                assert machine.rd(symbols['left_value'], 1) == a & 255, (context, 'left input')
                assert machine.rd(symbols['right_value'], 1) == b & 255, (context, 'right input')
                rows.append([label, name, a, b, value & 0xffffffff, checksum & 0xffffffff, 'PASS'])


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--trial', type=Path, help='candidate shcmdl.exe')
    ap.add_argument('--production', type=Path, help='previous complete tool bundle')
    ap.add_argument('--r26', type=Path, help='original Release26 tool bundle')
    ap.add_argument('--matchlab', type=Path, help="the game's tools/matchlab directory")
    ap.add_argument('--work', type=Path, help='fresh private work directory')
    args = ap.parse_args()
    if not (args.trial and args.production and args.r26 and args.matchlab):
        print('SKIP: needs --trial, --production, --r26 and --matchlab (tests/README.md)')
        return 0
    if not args.work:
        ap.error('--work is required')
    assert (args.matchlab / 'diff_exec.py').is_file(), 'missing SH2 interpreter'
    work = args.work.resolve()
    assert not work.exists(), 'fresh work path required'
    work.mkdir(parents=True)
    sys.dont_write_bytecode = True
    sys.path.insert(0, str(args.matchlab.resolve()))
    import diff_exec as dx
    import msearch_module as mm
    bins = {}
    for label, origin in [('stock', args.r26), ('old', args.production), ('trial', args.production)]:
        bins[label] = work / ('bin_' + label)
        shutil.copytree(origin, bins[label])
        if label == 'trial':
            shutil.copyfile(args.trial, bins[label] / 'shcmdl.exe')
    modes = [('stock', 'stock', {}), ('alloff', 'trial', dict.fromkeys(parity.RULES, '0')),
             ('old63', 'old', {}), ('unset', 'trial', {}),
             ('old255', 'old', {'MDL_IMM_REG': '255'}),
             ('on255', 'trial', {'MDL_IMM_REG': '255'}),
             ('on191', 'trial', {'MDL_IMM_REG': '191'})]
    outputs, parsed, rows = {}, {}, []
    source = ROOT / 'tests/cases/imm_expr.c'
    for label, bundle, settings in modes:
        case = work / label
        case.mkdir()
        (case / 'tmp').mkdir()
        shutil.copyfile(source, case / 'fixture.c')
        env = {k: v for k, v in os.environ.items() if not parity.SETTING.fullmatch(k)}
        env.update(settings, SHC_LIB=str(bins[bundle]), SHC_TMP=str(case / 'tmp'),
                   TMP=str(case / 'tmp'), TEMP=str(case / 'tmp'))
        support.table(case / 'environment.tsv', ['name', 'value'], sorted(
            (k, v) for k, v in env.items() if parity.SETTING.fullmatch(k)
            or k in ('SHC_LIB', 'SHC_TMP', 'TMP', 'TEMP')))
        support.run([str(bins[bundle] / 'shc.exe'), 'fixture.c', *support.OPTIONS,
                     '-object=fixture.obj', '-listfile=fixture.lst', '-show=object'], case, env, 'compile')
        outputs[label] = (parity.normalize((case / 'fixture.obj').read_bytes()),
                          support.listing((case / 'fixture.lst').read_text()))
        parsed[label] = mm.parse_listing(case / 'fixture.lst')
        (case / 'fixture.sub').write_text('START P(06000000),C(06008000),D(02008000),B(02009000)\n'
                                        'INPUT fixture.obj\nOUTPUT fixture.abs\nPRINT fixture.map\nFORM A\nEXIT\n')
        support.run([str(bins[bundle] / 'lnk.exe'), '-SUBCOMMAND=fixture.sub'], case, env, 'link')
        support.run([str(bins[bundle] / 'rof2bin.exe'), '-s=06000000', '-e=06010000',
                     '-v=00', 'fixture.abs'], case, env, 'image')
        symbols = {n: int(a, 16) for n, a in re.findall(
            r"^_(\w+)\s+H'([0-9A-F]+)", (case / 'fixture.map').read_text(), re.M)}
        execute(dx, dx.Image((case / 'fixture.bin').read_bytes()), symbols, label, rows)
        print('PASS semantic', label, flush=True)
    # 255 held the retired bit 64 beside 128 in the previous bundle; 128 covers it, so 255 and 191 give its output
    for a, b in [('stock', 'alloff'), ('old63', 'unset'), ('old255', 'on255'), ('old255', 'on191')]:
        assert outputs[a] == outputs[b], ('disabled native/listing parity', a, b)
    off, on = parsed['unset'], parsed['on191']
    assert off.frozen_data() == on.frozen_data(), 'non-code data changed'
    changes = []
    for name in NAMES:
        changed = support.body(off, name) != support.body(on, name)
        assert changed == (name in CHANGED), ('eligibility control', name, changed)
        changes.append([name, int(changed)])
    support.table(work / 'changes.tsv', ['function', 'changed'], changes)
    support.table(work / 'results.tsv', ['mode', 'function', 'left', 'right', 'result', 'checksum', 'status'], rows)
    paths = [Path(__file__).resolve(), source, Path(dx.__file__).resolve(), args.trial]
    paths += [p for p in work.rglob('*') if p.is_file() and 'tmp' not in p.relative_to(work).parts]
    support.table(work / 'bindings.tsv', ['path', 'sha256'],
                  [(str(p), hashlib.sha256(p.read_bytes()).hexdigest()) for p in sorted(set(paths))])
    print('PASS', len(rows), 'executions; disabled output identical; eight arithmetic changes, five controls', flush=True)
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
