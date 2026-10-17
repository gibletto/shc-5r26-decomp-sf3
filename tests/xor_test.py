"""Check XOR/self-test proofs using the actual production PEP helper objects.

Build shcpep first, then use a fresh private --work directory. No installed
stage, build object or source is modified. The fixture checks candidate proofs;
the full compiler witness separately exercises deletion of allocated records.
"""
import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import shutil
import subprocess

ROOT = Path(__file__).resolve().parent.parent


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--work', required=True, help='fresh private output directory')
    parser.add_argument('--objects', default=str(ROOT / 'build/msvc/shcpep'))
    args = parser.parse_args()
    work = Path(args.work).resolve()
    if work.exists():
        parser.error('--work must not exist')
    objects = Path(args.objects).resolve()
    if not (objects / '_relocs.c').is_file() or not (objects / '_xortest.obj').is_file():
        parser.error('build shcpep before running this test')
    work.mkdir()
    spec = importlib.util.spec_from_file_location('xor_build', ROOT / 'build.py')
    build = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(build)
    tc = build.toolchain('msvc')
    env, cc, cflags, linker, lflags = tc
    include = ROOT / 'rebuild/shcpep/include'
    source = ROOT / 'tests/xor_test_native.c'
    name, rc, message = build.compile_one(tc, source, work / 'fixture.obj', include, 1)
    if rc:
        raise RuntimeError(message)
    shutil.copy2(objects / '_relocs.c', work / '_relocs.c')
    linked = [p for p in sorted(objects.glob('*.obj')) if p.stem not in ('_stubs', '_relocs')]
    response = [str(p) for p in linked] + [str(work / 'fixture.obj'), str(work / '_relocs.obj')]
    (work / 'link.rsp').write_text('\n'.join(response + build.LIBS) + '\n')
    for attempt in range(8):
        name, rc, message = build.compile_one(tc, work / '_relocs.c', work / '_relocs.obj', include, 1)
        if rc:
            raise RuntimeError(message)
        command = linker + ['/nologo', '/out:fixture.exe', '/subsystem:console', '/machine:x86',
                            *lflags, '/map:fixture.map', '@link.rsp']
        (work / 'link.command.txt').write_text(subprocess.list2cmdline(command) + '\n')
        result = subprocess.run(command, cwd=work, env=env, capture_output=True, text=True)
        (work / 'link.log').write_text(result.stdout + result.stderr)
        if result.returncode:
            raise RuntimeError(result.stdout + result.stderr)
        moved = build.resync_relocs(work / 'fixture.map', work / '_relocs.c')
        if not moved:
            break
    else:
        raise RuntimeError('test relocation map did not settle')
    result = subprocess.run([str(work / 'fixture.exe')], capture_output=True, text=True)
    (work / 'results.log').write_text(result.stdout + result.stderr)
    hashes = {str(p): hashlib.sha256(p.read_bytes()).hexdigest()
              for p in [source, work / 'fixture.exe', *linked]}
    (work / 'input_hashes.json').write_text(json.dumps(hashes, indent=2))
    print(result.stdout, end='')
    if result.returncode:
        raise RuntimeError(result.stdout + result.stderr)


if __name__ == '__main__':
    main()
