#!/usr/bin/env python3
"""Fill a rebuild's function sources from a Ghidra export: the C part of ghidra/reports/$EXPORT/decomp/<addr>_*.c,
with the rebuild's includes, an 'undefined' or void return as int, and __cdecl.

Usage: EXPORT=<stage>-now python tools/import-ghidra-function.py <stage> <address> [<address> ...]
"""
import os, re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
stage = sys.argv[1]
for a in sys.argv[2:]:
    a = a.lower().replace("0x", "").zfill(8)
    g = next((ROOT / "ghidra/reports" / os.environ["EXPORT"] / "decomp").glob(f"{a}_*.c"))
    dst = next((ROOT / "rebuild" / stage / "src").glob(f"{a}_*.c"))
    t = g.read_text(encoding="utf-8", errors="replace")
    i = re.search(r"^[0-9a-f]{8}\t", t, re.M)
    if i:
        t = t[:i.start()]
    t = re.sub(r"\n// --- disassembly ---\s*$", "\n", t.rstrip() + "\n")
    name = dst.stem.split("_", 1)[1]
    t, k = re.subn(r"^(undefined\w*|void|int|uint|short|ushort|char|byte|bool)(\s*\*?\s*)(?:__cdecl\s+)?(" + re.escape(name) + r")\(",
                   lambda m: ("int" if m.group(1) in ("undefined", "void") else m.group(1)) + m.group(2) + "__cdecl " + m.group(3) + "(",
                   t, count=1, flags=re.M)
    if not k:
        # a long prototype printed over three lines ("void __cdecl" / name / "          (params"): its return type too
        t = re.sub(r"^(undefined|void)(\s+__cdecl\s+" + re.escape(name) + r"\s*\()", r"int\2", t, count=1, flags=re.M)
    dst.write_text('#include "decls.h"\n#include "imports.h"\n\n' + t)
    print(dst.name, "<-", g.name)
