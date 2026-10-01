#!/usr/bin/env python3
"""Turn Ghidra's stack0xN references (addresses in the caller's part of the stack, relative to the entry stack
pointer) into C, after frame-records.py:

- &stack0x00000000 (the end of the frame: a loop over a local array up to the return address) -> the end of the
  function's frame buffer, (_frec_T + T) for the largest frame record T
- stack0x0000000N, N >= 4 (a parameter slot Ghidra left out of the signature, or a part of one) -> param_K
  (K = (N - 4) / 4 + 1, plus the byte offset); missing parameters are added to the signature as int
- in_stack_0000000N (a local Ghidra made of a parameter slot it left out of the signature) -> that parameter
  (a whole slot: the parameter takes the local's type; part of one: a view into it)

Usage: python tools/stack-refs.py <stage>
"""
import re, sys
from pathlib import Path

R = Path(__file__).resolve().parent.parent / "rebuild" / sys.argv[1] / "src"
IN_DECL = re.compile(r"^[ \t]+((?:unsigned )?\w+(?:\s*\*+)?)\s+in_stack_([0-9a-f]{8});[ \t]*\r?\n", re.M)
tot = 0
for f in sorted(R.glob("0*.c")):
    s = f.read_bytes().decode("latin-1")
    if "stack0x" not in s and "in_stack_" not in s:
        continue
    o = s
    ins = {int(d.group(2), 16): d.group(1) for d in IN_DECL.finditer(s)}
    s = IN_DECL.sub("", s)
    recs = [int(x, 16) for x in re.findall(r"unsigned char _frec_([0-9a-f]+)\[", s)]
    if "&stack0x00000000" in s:
        if not recs:
            sys.exit(f"stack-refs: {f.name}: &stack0x00000000 without a frame record")
        t = max(recs)
        s = s.replace("&stack0x00000000", f"(void *)(_frec_{t:x} + {t:#x})")
    offs = sorted({int(x, 16) for x in re.findall(r"stack0x([0-9a-f]{8})", s)} | set(ins))
    if offs:
        m = re.search(r"^(\w[\w \*]*?__cdecl\s+\w+)\(([^)]*)\)\s*\r?\n\{", s, re.M)
        params = [] if m.group(2).strip() in ("", "void") else [p.strip() for p in m.group(2).split(",")]
        need = max((x - 4) // 4 + 1 for x in offs)
        for k in range(len(params) + 1, need + 1):
            params.append(f"{ins.get(4 * k, 'int')} param_{k}")
        s = s[:m.start()] + f"{m.group(1)}({','.join(params)})\n{{" + s[m.end():]

        def rep(mm):
            x = int(mm.group(2), 16)
            k, b = (x - 4) // 4 + 1, (x - 4) % 4
            if mm.group(1):
                return f"&param_{k}" if not b else f"((char *)&param_{k} + {b})"
            return f"param_{k}" if not b else f"*((char *)&param_{k} + {b})"
        s = re.sub(r"(&?)stack0x([0-9a-f]{8})", rep, s)

        def rep_in(mm):
            x = int(mm.group(1), 16)
            k, b = (x - 4) // 4 + 1, (x - 4) % 4
            return f"param_{k}" if not b else f"(*({ins[x]} *)((char *)&param_{k} + {b}))"
        s = re.sub(r"\bin_stack_([0-9a-f]{8})\b", rep_in, s)
    if s != o:
        tot += 1
        f.write_bytes(s.encode("latin-1"))
        print(f.name)
print(tot, "files with stack references rewritten")
