#!/usr/bin/env python3
"""Make each function of a C rebuild see the globals with the types Ghidra's decompiler used in that function.

Usage: python tools/apply-global-types.py <stage> <global_types.tsv>

global_types.tsv (ghidra/scripts/ExportGlobalTypes.java) lists, per function, every global and the type the
decompiler gave it there. decls.h declares each global once (a macro into the stock image), but the decompiler infers
an untyped global's type per function, so the same name is an int in one function and a short * in another:
  - a pointer type in this function: the file redefines the macro with that type after the includes
  - undefinedN used with [] or unary * (Ghidra prints an undefinedN used as a pointer with N-byte elements): those
    uses become ((intN *)NAME)[...] / *(intN *)NAME
Run it on sources exported in the same Ghidra session as the tsv.
"""
import csv, re, sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
stage, tsv = sys.argv[1], Path(sys.argv[2])
# --underscore: the decompiler's type for DAT_x also applies to _DAT_x (Ghidra's name for a wider access at the
# same address, which the C uses while global_types.tsv names the symbol DAT_x)
UNDERSCORE = "--underscore" in sys.argv
R = ROOT / "rebuild" / stage
dh = (R / "include/decls.h").read_text(errors="replace")
macro = {m.group(1): (m.group(2), m.group(3)) for m in re.finditer(r"^#define (\w+) \(\*\((.+?) \*\)\(g_sd \+ (0x[0-9a-f]+)\)\)", dh, re.M)}
per = defaultdict(dict)
# the stage's own types (include/stage_types.h, tools/gen-stage-types.py) are kept as they are
_names = R / "include/stage_types.names"
STAGE = set(_names.read_text().split()) if _names.exists() else set()
for r in csv.DictReader(open(tsv, errors="replace"), delimiter="\t"):
    # a global the tables gave a struct or array type keeps it (its htype is the type of the field accessed)
    if "[" in r["type"] or r["type"].strip() in STAGE:
        continue
    # htype (the type the decompiler inferred in this function, which the printed C follows) wins over the stored type
    per[r["function"].lower().zfill(8)][r["name"]] = ((r.get("htype") or r["type"]).strip(), int(r["size"] or 0),
                                                      bool(r.get("htype")))
ELEM = {1: "unsigned char", 2: "short", 4: "int", 8: "__int64"}
CT = {"undefined4": "int", "undefined2": "short", "undefined1": "unsigned char", "undefined": "unsigned char",
      "uint": "unsigned int", "ushort": "unsigned short", "byte": "unsigned char", "char": "char", "int": "int",
      "short": "short", "dword": "unsigned int", "word": "unsigned short", "bool": "unsigned char", "void": "void",
      "code": "unsigned char"}


def cptr(t):
    """Ghidra pointer type 'X *' / 'X * *' -> C"""
    base = t.rstrip(" *")
    stars = t.count("*")
    b = CT.get(base, base if re.fullmatch(r"[A-Za-z_]\w*", base) and (base in ("FILE", "GhFILE") or base in STAGE) else "unsigned char")
    return b + " " + "*" * stars


def unary_deref(s, name, elem):
    out, i = [], 0
    for m in re.finditer(r"\*\s*" + re.escape(name) + r"\b", s):
        j = m.start() - 1
        while j >= 0 and s[j] in " \t":
            j -= 1
        if j >= 0 and s[j] == ")":                    # a cast before the * makes it unary: (uint)*X
            k, depth = j, 0
            while k >= 0:
                depth += s[k] == ")"
                depth -= s[k] == "("
                if depth == 0:
                    break
                k -= 1
            if not re.fullmatch(r"\(\s*(unsigned |signed )?[A-Za-z_]\w*(\s*\*)*\s*\)", s[k:j + 1]):
                continue
        elif j >= 0 and (s[j].isalnum() or s[j] in "_]"):
            continue                                   # a multiplication
        out.append(s[i:m.start()] + f"*({elem} *){name}")
        i = m.end()
    out.append(s[i:])
    return "".join(out)


OVR_BLOCK = r"\n/\* the types Ghidra's decompiler used for these globals in this function \*/\n(#undef \w+\n#define [^\n]*\n)*"
n_over = n_rw = 0
for f in sorted((R / "src").glob("0*.c")):
    types = per.get(f.name[:8])
    if not types:
        continue
    s = f.read_bytes().decode("latin-1")
    s = re.sub(OVR_BLOCK, "", s)
    overrides = []
    items = list(types.items())
    if UNDERSCORE:
        items += [("_" + n, v) for n, v in types.items() if ("_" + n) in macro and ("_" + n) not in types
                  and re.search(r"\b_" + re.escape(n) + r"\b", s)]
    for name, (t, size, inferred) in items:
        if name not in macro:
            continue
        off = macro[name][1]
        called = re.search(r"\(\s*\*\s*" + re.escape(name) + r"\s*\)\s*\(", s)
        if t.replace(" ", "") == "code*" or (called and t.endswith("*")):
            overrides.append(f"#undef {name}\n#define {name} (*(int (**)())(g_sd + {off}))")
            n_over += 1
        elif t.endswith("*"):
            overrides.append(f"#undef {name}\n#define {name} (*({cptr(t)} *)(g_sd + {off}))")
            n_over += 1
        elif inferred:
            # a scalar: the width and signedness the decompiler used here (an undefined4 global read as a byte,
            # a byte global read as 4 bytes)
            ct = {"undefined4": "int", "undefined2": "short", "undefined1": "unsigned char",
                  "undefined": "unsigned char", "undefined8": "__int64", "longlong": "__int64",
                  "ulonglong": "unsigned __int64", "long": "int", "ulong": "unsigned int"}.get(t, CT.get(t))
            if ct and ct != macro[name][0]:
                overrides.append(f"#undef {name}\n#define {name} (*({ct} *)(g_sd + {off}))")
                n_over += 1
                # Ghidra steps a pointer to the global (&X)[i] / &X + n in elements of the type stored at that address
                # (an undefined1 DAT_x is indexed by bytes even where its value is read as an int): keep that element
                if size in ELEM and size != {"char": 1, "unsigned char": 1, "short": 2, "unsigned short": 2}.get(ct, 4):
                    el = ELEM[size]
                    s2 = re.sub(r"\(&" + re.escape(name) + r"\)\[", f"(({el} *)&{name})[", s)
                    s2 = re.sub(r"(?<!\))&" + re.escape(name) + r"(\s*[+-]\s)", rf"({el} *)&{name}\1", s2)  # not cast
                    if s2 != s:
                        n_rw += 1
                        s = s2
        elif re.fullmatch(r"undefined\d?", t):
            elem = ELEM.get(size or 4, "int")
            s2 = re.sub(r"\(\s*\*\s*" + re.escape(name) + r"\s*\)\s*\(", f"((int (*)()){name})(", s)   # a call through it
            s2 = re.sub(r"\b" + re.escape(name) + r"\[", f"(({elem} *){name})[", s2)
            s2 = unary_deref(s2, name, elem)
            if s2 != s:
                n_rw += 1
                s = s2
    if overrides:
        k = s.index('#include "imports.h"') + len('#include "imports.h"')
        s = s[:k] + "\n/* the types Ghidra's decompiler used for these globals in this function */\n" + "\n".join(sorted(overrides)) + "\n" + s[k:]
    f.write_bytes(s.encode("latin-1"))
print(f"{n_over} per-function pointer views, {n_rw} files with undefinedN pointer uses rewritten")
