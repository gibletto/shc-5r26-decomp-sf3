#!/usr/bin/env python3
"""Rename a C rebuild's function sources (rebuild/<stage>/src/<addr>_<name>.c) after the names in a Ghidra export
(ghidra/reports/<export>/decomp/<addr>_<name>.c), so a function renamed in the stage's tables gets its new file
name before the regen imports its code. Built objects keep the old name until the next build.

Usage: python tools/rename-rebuild-sources.py <stage> <export>
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
stage, exp = sys.argv[1], sys.argv[2]
src = ROOT / "rebuild" / stage / "src"
names = {p.name[:8]: p.name for p in (ROOT / "ghidra/reports" / exp / "decomp").glob("0*.c")}
n = 0
for f in sorted(src.glob("0*.c")):
    want = names.get(f.name[:8])
    if want and want != f.name:
        f.rename(src / want)
        n += 1
print(f"{n} sources renamed")
