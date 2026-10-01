#!/usr/bin/env python3
"""Fold a field copied byte by byte between two records back into one field assignment.

Usage: python tools/fold-byte-copies.py <stage> [--dry]

Where the stage copies a record field with byte moves, the decompiler shows one line per byte:
    *(char *)&dst->filno = (char)src->filno;
    *(undefined1 *)((int)&dst->filno + 1) = *(undefined1 *)((int)&src->filno + 1);
and this writes `dst->filno = src->filno;`. Only when the lines cover the whole field (its size from the stage's
types.h; a name two structs give different sizes is left alone), in order, with nothing between them, and both sides
are the same field of a record pointer: the bytes written are the same, as two records' fields are either the
same object or do not overlap.
"""
import re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SIZES = {"char": 1, "unsigned char": 1, "signed char": 1, "short": 2, "unsigned short": 2, "int": 4,
         "unsigned int": 4, "long": 4, "unsigned long": 4}
BYTE = r"(?:char|undefined1|byte|uchar)"


def field_sizes(stage):
    t = (ROOT / "ghidra/names" / stage / "types.h").read_text()
    t = re.sub(r"/\*.*?\*/", "", t, flags=re.S)
    enums = set()
    e = ROOT / "ghidra/names" / stage / "enums.tsv"
    if e.exists():
        for l in e.read_text().splitlines():
            if l and not l.startswith("#"):
                enums.add((l.split("\t")[0], int(l.split("\t")[1], 0)))
    out = {}
    for m in re.finditer(r"^\s*((?:struct\s+)?[\w ]+?)\s*(\*?)\s*(\w+)\s*(\[[^\]]*\])?;", t, re.M):
        typ, star, name, arr = m.group(1).strip(), m.group(2), m.group(3), m.group(4)
        if arr:
            continue
        size = 4 if star else SIZES.get(typ, next((s for n, s in enums if n == typ), None))
        if size is None:
            continue
        out.setdefault(name, set()).add(size)
    return {k: next(iter(v)) for k, v in out.items() if len(v) == 1}


def main():
    stage = sys.argv[1]
    sizes = field_sizes(stage)
    first = re.compile(r"^(\s*)\*\(" + BYTE + r" \*\)&(\w+)->(\w+) = (?:\(" + BYTE + r"\)(\w+)->(\w+)|\*\(" + BYTE +
                       r" \*\)&(\w+)->(\w+));\n", re.M)
    total = 0
    for f in sorted((ROOT / "rebuild" / stage / "src").glob("0*.c")):
        s = f.read_text(encoding="latin-1")
        out, pos, n = [], 0, 0
        for m in first.finditer(s):
            if m.start() < pos:
                continue
            ind, d, fd = m.group(1), m.group(2), m.group(3)
            sv, fs = (m.group(4), m.group(5)) if m.group(4) else (m.group(6), m.group(7))
            size = sizes.get(fd)
            if fd != fs or not size or size == 1:
                continue
            end, ok = m.end(), True
            for k in range(1, size):
                nxt = re.compile(re.escape(ind) + r"\*\(" + BYTE + r" \*\)\(\(int\)&" + re.escape(d) + "->" + re.escape(fd) +
                                 r" \+ " + str(k) + r"\) = \*\(" + BYTE + r" \*\)\(\(int\)&" + re.escape(sv) + "->" +
                                 re.escape(fs) + r" \+ " + str(k) + r"\);\n").match(s, end)
                if not nxt:
                    ok = False
                    break
                end = nxt.end()
            if not ok:
                continue
            out.append(s[pos:m.start()] + f"{ind}{d}->{fd} = {sv}->{fs};\n")
            pos = end
            n += 1
        if n:
            out.append(s[pos:])
            total += n
            if "--dry" not in sys.argv:
                f.write_text("".join(out), encoding="latin-1")
    print(f"{total} byte-wise field copies folded")


if __name__ == "__main__":
    main()
