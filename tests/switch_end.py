#!/usr/bin/env python3
"""Check nested switch-end boundaries and a control with intervening code."""
import argparse
import shutil
from pathlib import Path

from parity import ROOT, Runner, create_work_dir


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--exes', type=Path, default=ROOT / 'build/msvc')
    ap.add_argument('--r26', type=Path, default=ROOT / 'extracted/bin')
    ap.add_argument('--work-dir')
    args = ap.parse_args()
    inputs = [('nested' + str(control), ROOT / 'tests/cases', 'switch_end.c',
               '-cpu=sh2 -division=cpu -endian=big -pic=0 -nortnext -optimize=1 -speed '
               '-define=WITH_CODE=' + str(control), False) for control in (0, 1)]
    work = create_work_dir(args.work_dir, inputs)
    try:
        run = Runner(work, args.r26, args.exes, None)
        for control, inp in enumerate(inputs):
            results = {mode: run.outputs(run.ours, {'PEP_SWITCH_END': str(mode)}, inp, 0)
                       for mode in (0, 1, 2, 3)}
            assert results[0] == results[1], 'existing modes changed the control fixture'
            assert results[2] == results[3], 'the two bits interfered in the control fixture'
            changed = results[1] != results[3]
            assert changed == (control == 0), 'unexpected nested-boundary scope'
            print(('consecutive ends' if control == 0 else 'intervening code') + ': PASS')
    except Exception:
        print('work retained at', work)
        raise
    shutil.rmtree(work)
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
