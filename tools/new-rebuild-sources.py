#!/usr/bin/env python3
"""Start a C rebuild's src/ from a Ghidra export: one placeholder <addr>_<name>.c per exported function (the file
names of ghidra/reports/<export>/decomp), for import-ghidra-function.py to fill. Existing 0*.c files are removed.

Usage: python tools/new-rebuild-sources.py <stage> <export> [--skip ADDR ...] [--crt ADDR ...]
--skip: left out (a second copy of a library function under the same name); --crt: written to src/_crt_excluded/
(stock CRT stdio that src/_crt_shim.c replaces with the host CRT) instead of src/.
"""
import argparse
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ap = argparse.ArgumentParser()
ap.add_argument("stage"); ap.add_argument("export")
ap.add_argument("--skip", nargs="*", default=[]); ap.add_argument("--crt", nargs="*", default=[])
a = ap.parse_args()
S = ROOT / "rebuild" / a.stage / "src"
S.mkdir(parents=True, exist_ok=True)
X = S / "_crt_excluded"
for d in (S, X):
    if d.exists():
        for f in d.glob("0*.c"):
            f.unlink()
norm = lambda x: x.lower().replace("0x", "").zfill(8)
skip, crt = {norm(x) for x in a.skip}, {norm(x) for x in a.crt}
n = 0
for g in sorted((ROOT / "ghidra/reports" / a.export / "decomp").glob("0*.c")):
    addr = g.name[:8]
    if addr in skip:
        continue
    d = X if addr in crt else S
    d.mkdir(exist_ok=True)
    (d / g.name).write_text("")
    n += 1
print(n, "sources")
