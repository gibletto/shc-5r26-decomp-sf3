#!/usr/bin/env python3
"""Find (and with --apply, wrap in SD()) numeric literals in a C rebuild's code that are stock data addresses.

Usage: python tools/raw-data-literals.py <stage> [--apply]

Ghidra leaves an address as a number where it had no symbol there (table + index*8, (T *)0x44xxxx). With the stock
data image (gen-stockdata.py) such a number must become SD(0x...), the image's copy of that address. The data range
comes from the stock exe's .rdata/.data sections. Comment lines, 'case' labels and literals already inside SD( are
left alone; the rest are listed with their line, and --apply rewrites them.
"""
import re, struct, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
stage = sys.argv[1]
d = (ROOT / "extracted/bin" / f"{stage}.exe").read_bytes()
pe = struct.unpack_from("<I", d, 0x3C)[0]
n = struct.unpack_from("<H", d, pe + 6)[0]
opt = struct.unpack_from("<H", d, pe + 20)[0]
base = struct.unpack_from("<I", d, pe + 24 + 28)[0]
lo = hi = None
for i in range(n):
    name, vs, va, rs, ra = struct.unpack_from("<8sIIII", d, pe + 24 + opt + 40 * i)
    if name.rstrip(b"\0") in (b".rdata", b".data"):
        lo = base + va if lo is None else min(lo, base + va)
        hi = base + va + vs if hi is None else max(hi, base + va + vs)
lit = re.compile(r"(?<![\w])(?<!SD\()0x0*([0-9a-fA-F]{5,8})u?\b")
total = 0
for f in sorted((ROOT / "rebuild" / stage / "src").glob("0*.c")):
    s = f.read_bytes().decode("latin-1")
    out, changed = [], False
    for no, line in enumerate(s.splitlines(keepends=True), 1):
        st = line.lstrip()
        # a comment line; a wrapped statement may start with a dereference, *(uint *)(i * 0x30 + 0x448ca8 + ...)
        if st.startswith(("/*", "//", "case ", "#")) or re.match(r"\*(\s|/|$)", st):
            out.append(line); continue

        def rep(m):
            global total
            v = int(m.group(1), 16)
            if lo <= v < hi:
                total += 1
                print(f"{f.name}:{no}: {line.strip()[:110]}")
                return f"SD(0x{v:08x})"
            return m.group(0)
        new = lit.sub(rep, line)
        changed |= new != line
        out.append(new)
    if changed and "--apply" in sys.argv:
        f.write_bytes("".join(out).encode("latin-1"))
print(f"{total} literals in {lo:#x}..{hi:#x}" + (" wrapped in SD()" if "--apply" in sys.argv else ""))
