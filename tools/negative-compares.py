#!/usr/bin/env python3
"""Find (and with --apply, fix) == / != comparisons of an unsigned 1- or 2-byte value with a negative constant.

Ghidra prints an 'undefined' (untyped) byte or halfword compared with 0xff as `== -1` (it compares the bits); in C
the value is an unsigned char / unsigned short (ghidra_stubs.h: undefined, undefined1, undefined2; decls.h: an
untyped DAT_ global) and is promoted to int, so the comparison is never true. --apply writes the constant as the
unsigned value of the same bits (-1 -> 0xff, -0x73 -> 0x8d; 0xffff for 2 bytes).

Operands recognised: a data global NAME or (&NAME)[...] whose macro (decls.h, or the file's per-function override
block from apply-global-types.py) is unsigned char / unsigned short, and a local or parameter declared
undefined / undefined1 / undefined2 / byte / ushort (VAR or VAR[...]).

Usage: python tools/negative-compares.py <stage> [--apply]
"""
import re, sys
from pathlib import Path

R = Path(__file__).resolve().parent.parent / "rebuild" / sys.argv[1]
MACRO = re.compile(r"^#define (\w+) \(\*\((unsigned char|unsigned short|[\w ]+?) \*\)\(g_sd \+ 0x[0-9a-f]+\)\)", re.M)
WIDTH = {"unsigned char": 0x100, "unsigned short": 0x10000, "undefined": 0x100, "undefined1": 0x100, "byte": 0x100,
         "uchar": 0x100, "undefined2": 0x10000, "ushort": 0x10000, "word": 0x10000}
glob = {m.group(1): m.group(2) for m in MACRO.finditer((R / "include/decls.h").read_text(errors="replace"))}
LOCAL = re.compile(r"\b(undefined[12]?|byte|uchar|ushort|word)\s+(\w+)(?:\s*\[\d+\])?\s*[;,)]")
CMP = re.compile(r"(?P<lhs>\(&(?P<g1>\w+)\)\s*\[|(?<![\w&.>])(?P<n>\w+)\s*\[|(?<![\w&.>*])(?P<g2>\w+))")
NEG = re.compile(r"\s*(==|!=)\s*-(0x[0-9a-fA-F]+|\d+)\b")


def close(s, i):
    """index after the ] matching the [ at s[i-1]"""
    depth = 1
    while i < len(s) and depth:
        depth += {"[": 1, "]": -1}.get(s[i], 0)
        i += 1
    return i


total = 0
for f in sorted((R / "src").glob("0*.c")):
    s = f.read_bytes().decode("latin-1")
    g = dict(glob)
    g.update({m.group(1): m.group(2) for m in MACRO.finditer(s)})          # the file's own overrides win
    loc = {m.group(2): m.group(1) for m in LOCAL.finditer(s)}
    out, pos, changed = [], 0, 0
    for m in CMP.finditer(s):
        if m.start() < pos:
            continue
        name = m.group("g1") or m.group("n") or m.group("g2")
        if m.group("g1"):
            w = WIDTH.get(g.get(name, ""))
        elif m.group("n"):
            w = WIDTH.get(loc.get(name, ""))
        else:
            w = WIDTH.get(loc.get(name, "")) if name in loc else WIDTH.get(g.get(name, ""))
        if not w:
            continue
        end = close(s, m.end()) if m.group("g1") or m.group("n") else m.end()
        k = NEG.match(s, end)
        if not k:
            continue
        v = int(k.group(2), 0)
        if v > w // 2:
            continue
        out.append(s[pos:k.start(2) - 1] + f"0x{w - v:x}")
        pos = k.end()
        changed += 1
        line = s.count("\n", 0, m.start()) + 1
        print(f"{f.name}:{line}: {s[m.start():k.end()]}")
    if changed:
        out.append(s[pos:])
        total += changed
        if "--apply" in sys.argv:
            f.write_bytes("".join(out).encode("latin-1"))
print(f"{total} comparisons of unsigned bytes/halfwords with negative constants" + (" rewritten" if "--apply" in sys.argv else ""))
