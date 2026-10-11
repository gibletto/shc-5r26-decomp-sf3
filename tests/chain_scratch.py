"""Execute switch-selector controls with the companion game's SH2 interpreter.

Requires native SHC tools, the rebuilt stages, and --matchlab pointing to
tools/matchlab in cps3-sf3iii. Every output/temp stays in a fresh --work directory.
The fixture is deliberately separate from byte-parity cases: its assertions are
C-level return/store/callee-save semantics and realized near/far branch forms.
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
NAMES = ('live_selector', 'call_selector', 'default_only', 'no_default',
         'far_selector', 'mid_selector')


def expected(name, x, y):
    k = x ^ 85
    if name == 'live_selector':
        r = {0: 17, 1: 23, 1000: 31, -300: 41}.get(x, 53)
        return r + x + y, r
    if name == 'call_selector':
        r = {0: 61, 1: 67, 1000: 71}.get(k, 73)
        return r + k + x + y, k
    if name == 'default_only':
        return k + x + y, k + y
    if name == 'no_default':
        return x + y, {0: 83, 1: 89}.get(x, 123)
    increments = 1450 if name == 'far_selector' else 80
    return {0: 97, 1: 101, 1000: 103}.get(x, 107) + x + y, increments if x == 0 else 123


def write_table(path, header, rows):
    with path.open('w', newline='') as f:
        writer = csv.writer(f, delimiter='\t')
        writer.writerow(header)
        writer.writerows(rows)


def run(command, work, env, name):
    (work / (name + '.command.txt')).write_text(subprocess.list2cmdline(command) + '\n')
    with (work / (name + '.log')).open('w') as log:
        process = subprocess.Popen(command, cwd=work, env=env, stdout=log,
                                   stderr=subprocess.STDOUT, creationflags=0x08000000)
        try:
            code = process.wait(timeout=180)
        except subprocess.TimeoutExpired:
            subprocess.run(['taskkill', '/PID', str(process.pid), '/T', '/F'],
                           capture_output=True, creationflags=0x08000000)
            raise
    assert code == 0, (name, code, work)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exes', type=Path, default=ROOT / 'build/msvc')
    parser.add_argument('--r26', type=Path, default=ROOT / 'extracted/bin')
    parser.add_argument('--matchlab', type=Path, required=True)
    parser.add_argument('--work', type=Path, required=True)
    args = parser.parse_args()
    work = args.work.resolve()
    assert not work.exists(), 'use a fresh work directory'
    work.mkdir(parents=True)
    sys.dont_write_bytecode = True
    sys.path.insert(0, str(args.matchlab.resolve()))
    import diff_exec as dx
    binary = work / 'bin'
    shutil.copytree(args.r26, binary)
    for stage in ('shcmdl', 'shcgen', 'shcpep', 'shcasm'):
        shutil.copyfile(args.exes / stage / (stage + '.exe'), binary / (stage + '.exe'))
    source = ROOT / 'tests/cases/chain_scratch.c'
    rows = []
    for old in (0, 1):
        for flag in (0, 1):
            case = work / (str(old) + str(flag))
            case.mkdir()
            (case / 'tmp').mkdir()
            shutil.copyfile(source, case / 'fixture.c')
            env = {k: v for k, v in os.environ.items()
                   if not k.startswith(('GEN_', 'PEP_', 'MDL_', 'ASM_', 'SWITCH_', 'XJUMP', 'SLOT_'))}
            env.update(SHC_LIB=str(binary), SHC_TMP=str(case / 'tmp'),
                       TMP=str(case / 'tmp'), TEMP=str(case / 'tmp'),
                       GEN_CHAIN_JUMP=str(old), GEN_CHAIN_SCRATCH_R0=str(flag))
            recorded = {k: v for k, v in env.items()
                        if k.startswith(('GEN_', 'PEP_', 'MDL_', 'ASM_', 'SWITCH_', 'XJUMP', 'SLOT_'))
                        or k in ('SHC_LIB', 'SHC_TMP', 'TMP', 'TEMP')}
            write_table(case / 'environment.tsv', ['name', 'value'], sorted(recorded.items()))
            run([str(binary / 'shc.exe'), 'fixture.c', *OPTIONS, '-object=fixture.obj',
                 '-listfile=fixture.lst', '-show=object'], case, env, 'compile')
            (case / 'fixture.sub').write_text('START P(06000000),B(02000000)\nINPUT fixture.obj\n'
                                            'OUTPUT fixture.abs\nPRINT fixture.map\nFORM A\nEXIT\n')
            run([str(binary / 'lnk.exe'), '-SUBCOMMAND=fixture.sub'], case, env, 'link')
            run([str(binary / 'rof2bin.exe'), '-s=06000000', '-e=06010000', '-v=00',
                 'fixture.abs'], case, env, 'image')
            listing = (case / 'fixture.lst').read_text()
            far = listing.split('_far_selector:')[1].split('_mid_selector:')[0]
            assert len(re.findall(r'JMP\s+@R' + str(0 if flag else 1), far)) == 3
            assert re.search(r'BT\s+', far) and re.search(r'CMP/EQ\s+R1,R0', far)
            middle = listing.split('_mid_selector:')[1]
            assert re.search(r'BF\s+', middle) and re.search(r'BRA\s+', middle)
            assert not re.search(r'JMP\s+', middle)
            symbols = {n: int(a, 16) for n, a in re.findall(
                r"^_(\w+)\s+H'([0-9A-F]+)", (case / 'fixture.map').read_text(), re.M)}
            image = dx.Image((case / 'fixture.bin').read_bytes())
            dx.G = {}
            live = dx.LiveIn(image)
            for name in NAMES:
                for x in (-300, -1, 0, 1, 2, 85, 84, 1000, 1000 ^ 85):
                    for y in (-17, 0, 211):
                        machine = dx.Machine(image, symbols[name], dx.BASE, image.hi,
                                             0, [], live, lambda value: value)
                        machine.R[4], machine.R[5] = x & 0xffffffff, y & 0xffffffff
                        machine.wr(symbols['sink'], 4, 123)
                        machine.trace, machine.seg = [], []
                        machine.run()
                        assert machine.trace and machine.trace[-1][0] == 'ret', (old, flag, name, x, y)
                        result, store = expected(name, x, y)
                        assert machine.trace[-1][1] == result & 0xffffffff, (old, flag, name, x, y, 'return')
                        assert machine.rd(symbols['sink'], 4) == store & 0xffffffff, (old, flag, name, x, y, 'store')
                        assert machine.trace[-1][2], (old, flag, name, x, y, 'callee-saved registers')
                        assert not any(event[0] == 'call' for event in machine.trace), 'simulated external call'
                        rows.append([old, flag, name, x, y, result & 0xffffffff, store & 0xffffffff, 'PASS'])
            print('PASS old/new settings', old, flag, '162 executions', flush=True)
    write_table(work / 'results.tsv', ['GEN_CHAIN_JUMP', 'GEN_CHAIN_SCRATCH_R0', 'name', 'x', 'y',
                                      'result', 'sink', 'status'], rows)
    paths = [Path(__file__).resolve(), source, Path(dx.__file__).resolve()]
    paths += [p for p in work.rglob('*') if p.is_file() and 'tmp' not in p.relative_to(work).parts]
    write_table(work / 'bindings.tsv', ['path', 'sha256'],
                [(str(p), hashlib.sha256(p.read_bytes()).hexdigest()) for p in sorted(paths)])
    print('PASS', len(rows), 'semantic executions; near/BRA/JMP forms verified', flush=True)


if __name__ == '__main__':
    main()
