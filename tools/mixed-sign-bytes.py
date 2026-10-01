#!/usr/bin/env python3
"""Find (and with --apply, fix) == / != comparisons between a signed char and an unsigned byte in a C rebuild.

Ghidra compares 1-byte values as bytes; C promotes both sides to int, so `char` 0x95 (-107) != `byte` 0x95 (149).
Operands recognised: a variable, *ptr, ptr[i] and param_N[i], typed from the function's declarations (locals and
parameters). --apply casts the char side to (byte), which is what the stock byte compare means.

Usage: python tools/mixed-sign-bytes.py <stage> [--apply]
"""
import re, sys
from pathlib import Path

R = Path(__file__).resolve().parent.parent / "rebuild" / sys.argv[1] / "src"
SIGNED = {"char"}
UNSIGNED = {"byte", "uchar", "unsigned char", "undefined1", "bool"}
DECL = re.compile(r"\b((?:unsigned )?\w+)\s*(\*?)\s*\b((?:[a-z]Var\d+|param_\d+|local_\w+))\b\s*[;,)]")
OPND = r"(\*\s*\w+|\w+\s*\[[^\]]+\]|\w+)"
CMP = re.compile(OPND + r"\s*(==|!=)\s*" + OPND)


def vartype(types, e):
    e = e.strip()
    m = re.fullmatch(r"\*\s*(\w+)", e) or re.fullmatch(r"(\w+)\s*\[[^\]]+\]", e)
    if m:
        t = types.get(m.group(1))
        return t[0] if t and t[1] else None           # the pointee of a pointer
    t = types.get(e)
    return t[0] if t and not t[1] else None


tot = 0
for f in sorted(R.glob("0*.c")):
    s = f.read_bytes().decode("latin-1")
    types = {m.group(3): (m.group(1), m.group(2) == "*") for m in DECL.finditer(s)}
    hits = []

    def rep(m):
        a, op, b = m.group(1), m.group(2), m.group(3)
        ta, tb = vartype(types, a), vartype(types, b)
        if ta in SIGNED and tb in UNSIGNED:
            hits.append(m.group(0)); return f"(byte){a} {op} {b}"
        if tb in SIGNED and ta in UNSIGNED:
            hits.append(m.group(0)); return f"{a} {op} (byte){b}"
        return m.group(0)
    s2 = CMP.sub(rep, s)
    if hits:
        tot += len(hits)
        print(f.name, hits[:4])
        if "--apply" in sys.argv:
            f.write_bytes(s2.encode("latin-1"))
print(tot, "mixed-sign byte comparisons" + (" cast" if "--apply" in sys.argv else ""))
