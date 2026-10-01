#!/usr/bin/env python3
"""List the functions of a Ghidra export whose return type is an unlocked 'undefined' (Ghidra printed a bare return;)
while some caller uses the value (the call is not a statement of its own): they are to be decompiled again with the
return locked (DecompileAddresses.java <list> <out> ret4). After that run, --use <ret4 dir> writes <ret4 dir>/use.txt:
the functions whose locked decompile does not return a leftover EAX (in_EAX: really void).

Usage: python tools/ret4-candidates.py <export> > list.txt
       python tools/ret4-candidates.py <export> --use <ret4 export dir>
"""
import re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
rep = ROOT / "ghidra/reports" / sys.argv[1] / "decomp"
if "--use" in sys.argv:
    d = ROOT / "ghidra/reports" / sys.argv[sys.argv.index("--use") + 1]
    # in_EAX only as the upper part of a narrower result (CONCAT22((short)((uint)in_EAX >> 0x10), x): a function
    # returning a short in AX) still returns a value
    def void(t):
        t = re.sub(r"^\s*\w+ in_EAX;\s*$", "", t, flags=re.M)
        t = re.sub(r"CONCAT\d\d\(\(\w+\)\(\(uint\)in_EAX >> 0x[0-9a-f]+\)", "", t)
        return "in_EAX" in t
    use = [f.name[:8] for f in sorted(d.glob("0*.c")) if not void(f.read_text(encoding="utf-8", errors="replace"))]
    (d / "use.txt").write_bytes(("\n".join(use) + "\n").encode())
    print(len(use), "of", len(list(d.glob("0*.c"))), "return a value")
    sys.exit()
cands = {}
texts = {}
for f in sorted(rep.glob("*.c")):
    t = f.read_text(encoding="utf-8", errors="replace")
    texts[f.name] = t.split("// --- disassembly ---")[0]
    m = re.search(r"^// sig  : undefined (\w+)\(", t, re.M)
    if m:
        cands[m.group(1)] = f.name[:8]
used = set()
for name, t in texts.items():
    for line in t.splitlines():
        for m in re.finditer(r"\b(\w+)\(", line):
            if m.group(1) in cands and not re.match(r"\s*" + re.escape(m.group(1)) + r"\(", line[:m.end()]) \
               and not line.lstrip().startswith(("//", "/*")) and not re.match(r"^\S", line):
                used.add(m.group(1))
for n in sorted(used, key=lambda n: cands[n]):
    print("0x" + cands[n])
