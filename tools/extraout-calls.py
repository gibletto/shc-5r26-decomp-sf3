#!/usr/bin/env python3
"""Give Ghidra's extraout_EAX* variables their value: the EAX a call left behind.

When a caller uses the return value of a function whose call site Ghidra models as returning nothing, the
decompiler shows the value as extraout_EAX (extraout_EAX_00, ...) right after the call:
    read_next_backend_record(local_1c,1);
    local_24 = extraout_EAX;
In the rebuild extraout_EAX is an uninitialised local. This wraps the nearest call before each use of the
variable into an assignment, (extraout_EAX = (T)read_next_backend_record(local_1c,1)), T its declared type.

Usage: python tools/extraout-calls.py <stage> [--apply]
"""
import re, sys
from pathlib import Path

R = Path(__file__).resolve().parent.parent / "rebuild" / sys.argv[1] / "src"
KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof"}
total = 0
for f in sorted(R.glob("0*.c")):
    s = f.read_bytes().decode("latin-1")
    decl = {m.group(2): m.group(1).strip() for m in re.finditer(r"^\s+([\w ]+?\s*\**)\s*\b(extraout_EAX\w*);", s, re.M)}
    if not decl:
        continue
    n = 0
    for var, typ in decl.items():
        while True:
            uses = [m for m in re.finditer(r"\b" + var + r"\b", s) if not re.match(r"\s*=[^=]", s[m.end():])]
            uses = [m for m in uses if not re.match(r"^\s+[\w ]+?\s*\**\s*$", s[s.rfind("\n", 0, m.start()) + 1:m.start()])]
            # the first use not yet fed by an assignment
            todo = None
            for u in uses:
                prev = s[:u.start()]
                calls = [c for c in re.finditer(r"\b(\w+)\(", prev) if c.group(1) not in KEYWORDS
                         and not re.match(r"\(\w+ = \(", prev[c.start() - len(var) - 5:c.start()])]
                if not calls:
                    continue
                c = calls[-1]
                if prev[max(0, c.start() - len(var) - 40):c.start()].rstrip().endswith(f"({var} = ({typ})"):
                    continue
                todo = c
                break
            if not todo:
                break
            i, depth = todo.end(), 1
            while depth:
                depth += {"(": 1, ")": -1}.get(s[i], 0)
                i += 1
            s = s[:todo.start()] + f"({var} = ({typ}){s[todo.start():i]})" + s[i:]
            n += 1
    if n:
        total += n
        print(f"{f.name}: {n}")
        if "--apply" in sys.argv:
            f.write_bytes(s.encode("latin-1"))
print(f"{total} calls feeding extraout_EAX" + (" rewritten" if "--apply" in sys.argv else ""))
