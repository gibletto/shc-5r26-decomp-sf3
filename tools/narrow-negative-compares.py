#!/usr/bin/env python3
"""Find (and with --apply, fix) == / != comparisons of an unsigned 1- or 2-byte value with a negative constant in a
C rebuild. Ghidra compares at the value's width (undefined2 x == -1 is a 16-bit compare with 0xffff); C promotes the
unsigned short to int, so the comparison is never true. --apply writes the constant at the operand's width
(-1 -> 0xffff / 0xff).

Operands recognised: a variable, *ptr, ptr[i] (typed from the function's declarations) and *(T *)(...) casts.
Usage: python tools/narrow-negative-compares.py <stage> [--apply]
"""
import re, sys
from pathlib import Path

R = Path(__file__).resolve().parent.parent / "rebuild" / sys.argv[1] / "src"
W = {"undefined2": 2, "ushort": 2, "word": 2, "unsigned short": 2, "uint16_t": 2,
     "undefined1": 1, "undefined": 1, "byte": 1, "uchar": 1, "unsigned char": 1, "bool": 1}
DECL = re.compile(r"\b((?:unsigned )?\w+)\s*(\*?)\s*\b([A-Za-z_]\w*)\s*(?:\[\d+\])?\s*[;,)]")
CMP = re.compile(r"(==|!=)\s*(-(?:0x[0-9a-fA-F]+|\d+))\b")


def operand_before(s, i):
    """the operand text ending just before index i (whitespace skipped) -> (start, text)"""
    j = i
    while j > 0 and s[j - 1] in " \t":
        j -= 1
    end = j
    if j and s[j - 1] == ")":                          # a parenthesised group, maybe after *(T *)
        depth, k = 0, j - 1
        while k >= 0:
            depth += s[k] == ")"
            depth -= s[k] == "("
            if depth == 0:
                break
            k -= 1
        m = re.search(r"\*\s*\(\s*([\w ]+?)\s*\*\s*\)\s*$", s[:k])
        if m:
            return m.start(), s[m.start():end], m.group(1)
        return k, s[k:end], None
    m = re.search(r"(\*\s*)?([A-Za-z_]\w*)(\s*\[[^\[\]]+\])?$", s[:j])
    if not m:
        return None
    return m.start(), m.group(0), None


tot = 0
for f in sorted(R.glob("0*.c")):
    s = f.read_bytes().decode("latin-1")
    types = {m.group(3): (m.group(1), m.group(2) == "*") for m in DECL.finditer(s)}
    out, pos, hits = [], 0, []
    for m in CMP.finditer(s):
        op = operand_before(s, m.start())
        if not op:
            continue
        st, text, cast = op
        w = None
        if cast:
            w = W.get(cast.strip())
        else:
            mm = re.fullmatch(r"(\*\s*)?([A-Za-z_]\w*)(\s*\[[^\[\]]+\])?", text)
            if mm:
                t = types.get(mm.group(2))
                if t:
                    deref = bool(mm.group(1) or mm.group(3))
                    if deref == t[1]:                # *p / p[i] of a pointer, or a plain variable
                        w = W.get(t[0])
        if not w:
            continue
        v = int(m.group(2), 0) & ((1 << (8 * w)) - 1)
        hits.append(f"{text} {m.group(1)} {m.group(2)}")
        out.append(s[pos:m.start()] + f"{m.group(1)} {v:#x}")
        pos = m.end()
    if hits:
        out.append(s[pos:])
        tot += len(hits)
        print(f.name, hits[:3])
        if "--apply" in sys.argv:
            f.write_bytes("".join(out).encode("latin-1"))
print(tot, "narrow unsigned compares with a negative constant" + (" fixed" if "--apply" in sys.argv else ""))
