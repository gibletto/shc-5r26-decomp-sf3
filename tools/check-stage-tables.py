#!/usr/bin/env python3
"""Check a stage's naming tables (ghidra/names/<stage>/) against a Ghidra export before applying them.

Usage: python tools/check-stage-tables.py <stage> [--export <stage>-now] [--tables DIR]

functions.tsv: every address is a function of the export; names are unique C identifiers; a signature names its
own function and keeps the export's parameter count and each parameter's width (1/2/4/8 bytes: a different width
changes what the rebuilt callee reads; a note with "WIDTH:" and the reason, from the machine code, allows one; a
note with "PARAMS:" gives parameters to a function Ghidra left as (void)); a return type keeps the export's width, except that an unlocked
'undefined' return may get any type (its callers decide; see the ret4 export) and a return may be narrowed when
the note says the callers use only its low byte / low half (then check the callers' decompilation gains no
extraout_ / CONCAT: that would mean one reads more), or with "RETURN:" and the machine-code reason when Ghidra
locked a void return the callers do use (a function called through a table).
globals.tsv: names unique, not also function names.
locals.tsv: the function and its old variable name exist in the export (variables.tsv); the new name is a C
identifier that is not a keyword, a type, a Win32 macro, a global or function name (decls.h makes those macros)
or another variable of the function; a variable named by a source-fix anchor (PROTECTED_BY_STAGE) keeps its name.
Prints one line per problem; exit status 1 if there are any.
"""
import argparse, csv, re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
KEYWORDS = set("auto break case char const continue default do double else enum extern float for goto if int long "
               "register return short signed sizeof static struct switch typedef union unsigned void volatile while".split())
# names a parameter must not take: the decompiler's type names (include/ghidra_stubs.h) and Win32/CRT types it prints
RESERVED = KEYWORDS | set("byte word dword qword code uint ushort ulong uchar sbyte bool pointer longlong ulonglong "
                          "undefined undefined1 undefined2 undefined3 undefined4 undefined5 undefined6 undefined7 "
                          "undefined8 FILE HANDLE DWORD WORD BYTE BOOL LPSTR LPCSTR LPVOID UINT LONG SIZE_T size_t "
                          "true false NULL".split())
# windows.h / VC6 CRT macros a variable name would collide with
WIN32 = set("min max near far small IN OUT OPTIONAL CONST VOID TRUE FALSE interface pascal cdecl PASCAL CDECL "
            "WINAPI CALLBACK errno stdin stdout stderr EOF BUFSIZ FILENAME_MAX getc putc getchar putchar".split())
# per stage, the variables its source fixes (tools/<stage>-fixes.py) name literally: renaming one needs the anchor
# changed too
PROTECTED_BY_STAGE = {"shcpep": {("00401fb0", "block_00"), ("00401fb0", "local_14"), ("00401fb0", "edges"), ("004028f0", "local_44"),
             ("004028f0", "bVar15"), ("0040f4e0", "local_2c"), ("0040f4e0", "local_c"), ("0040f4e0", "local_14"),
             ("00413850", "local_c"), ("00413850", "local_8"), ("004179a0", "local_4"), ("004179a0", "local_8"),
             ("004179a0", "local_9")},
                      "shcmdl": {("00414030", "local_2")}}
GH = {"undefined": 0, "void": 0, "undefined1": 1, "byte": 1, "char": 1, "uchar": 1, "bool": 1, "sbyte": 1,
      "undefined2": 2, "short": 2, "ushort": 2, "word": 2, "wchar_t": 2,
      "undefined4": 4, "int": 4, "uint": 4, "dword": 4, "long": 4, "ulong": 4, "float": 4, "LPVOID": 4, "HANDLE": 4,
      "SIZE_T": 4, "size_t": 4, "intptr_t": 4, "UINT": 4, "DWORD": 4, "LONG": 4, "LPSTR": 4, "LPCSTR": 4, "LCID": 4, "BOOL": 4,
      "undefined8": 8, "longlong": 8, "ulonglong": 8, "double": 8, "qword": 8}
C = {"void": 0, "char": 1, "signed char": 1, "unsigned char": 1, "short": 2, "unsigned short": 2, "int": 4,
     "unsigned int": 4, "long": 4, "unsigned long": 4, "unsigned": 4, "float": 4, "double": 8, "__int64": 8}


def width(t, table):
    t = re.sub(r"\b(const|volatile|struct|union|enum)\b", "", t).strip()
    t = re.sub(r"\s+", " ", t)
    if t.endswith("*") or "[" in t:
        return 4
    if t in table:
        return table[t]
    return None


def split_sig(sig):
    """'ret name(params)' -> (ret, name, [param types])"""
    sig = sig.replace("FID_conflict:", "")
    m = re.match(r"\s*(.*?)\b(\w+)\s*\((.*)\)\s*;?\s*$", sig)
    if not m:
        return None
    ret, name, ps = m.group(1).strip(), m.group(2), m.group(3).strip()
    params = []
    if ps and ps != "void":
        for p in ps.split(","):
            p = p.strip()
            if p == "...":
                params.append("...")
                continue
            q = re.match(r"(.*?)(\w+)\s*(\[\d*\])?$", p)
            t = (q.group(1) + ("*" if q.group(3) else "")).strip() if q and q.group(1).strip() else p
            params.append(t)
    return ret, name, params


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("stage"); ap.add_argument("--export"); ap.add_argument("--tables")
    a = ap.parse_args()
    T = Path(a.tables) if a.tables else ROOT / "ghidra/names" / a.stage
    E = ROOT / "ghidra/reports" / (a.export or f"{a.stage}-now")
    types = set()
    for f in ("stage_types.names",):
        p = ROOT / "rebuild" / a.stage / "include" / f
        if p.exists():
            types |= set(p.read_text().split())
    # an enum of the tables is an integer of its size (enums.tsv): a struct field or parameter of that type keeps it
    enum_w = {}
    if (T / "enums.tsv").exists():
        for l in (T / "enums.tsv").read_text().splitlines():
            if l.strip() and not l.startswith("#"):
                enum_w[l.split("	")[0].strip()] = int(l.split("	")[1], 0)
    C.update(enum_w)
    exp = {}
    for f in (E / "decomp").glob("0*.c"):
        s = f.read_text(errors="replace")
        m = re.search(r"^// sig  : (.*)$", s, re.M)
        exp[f.name[:8]] = m.group(1) if m else ""
    bad = 0

    def problem(msg):
        nonlocal bad
        bad += 1
        print(msg)

    names = {}
    for r in csv.reader(open(T / "functions.tsv", encoding="utf-8"), delimiter="\t"):
        if not r or r[0].startswith("#") or not r[0].strip():
            continue
        r += [""] * (4 - len(r))
        addr, name, sig, note = (x.strip() for x in r[:4])
        if addr not in exp:
            problem(f"{addr}: not a function of the export")
            continue
        if not re.fullmatch(r"[A-Za-z_]\w*", name) or name in KEYWORDS:
            problem(f"{addr}: bad name {name!r}")
        if re.match(r"(FUN|DAT|LAB|sub)_[0-9a-f]+$", name):
            problem(f"{addr}: placeholder name {name}")
        if name in names:
            problem(f"{addr}: name {name} also at {names[name]}")
        names[name] = addr
        if not sig:
            continue
        for pn in re.findall(r"(\w+)\s*(?:\[\d*\])?\s*(?:,|\)\s*;?\s*$)", sig.split("(", 1)[1]):
            if pn != "void" and (pn in RESERVED or pn in types):
                problem(f"{addr} {name}: parameter name {pn} is a type or keyword")
        ours, theirs = split_sig(sig), split_sig(exp[addr].replace(" * ", " *"))
        if not ours or not theirs:
            problem(f"{addr}: cannot parse signature {sig!r} / export {exp[addr]!r}")
            continue
        if ours[1] != name:
            problem(f"{addr}: signature names {ours[1]}, not {name}")
        if len(ours[2]) != len(theirs[2]):
            # Ghidra's '(void)' for a function that reads stack arguments: a note with "PARAMS:" and the machine
            # code's evidence gives the real list
            if not (theirs[2] == [] and "PARAMS:" in note):
                problem(f"{addr} {name}: {len(ours[2])} parameters, the export has {len(theirs[2])}: {exp[addr]}")
            continue
        for i, (p, q) in enumerate(zip(ours[2], theirs[2])):
            if p == q == "...":
                continue
            wp, wq = width(p, {**C, **enum_w}), width(q, {**GH, **C, **enum_w})
            if wp is None and p.rstrip("* ") in types:
                wp = 4 if p.endswith("*") else None
            if wp is None or wq is None:
                problem(f"{addr} {name}: parameter {i + 1} type {p!r} / export {q!r}: unknown width")
            elif wp != wq and "WIDTH:" not in note:
                problem(f"{addr} {name}: parameter {i + 1} is {wp} bytes ({p}), the export's {wq} ({q})")
        rp, rq = width(ours[0], {**C, **enum_w}), width(theirs[0], {**GH, **C, **enum_w})
        if rp is None and ours[0].rstrip("* ") in types:
            rp = 4 if ours[0].endswith("*") else None
        if rp is None or rq is None:
            problem(f"{addr} {name}: return type {ours[0]!r} / export {theirs[0]!r}: unknown width")
        elif theirs[0] == "undefined":
            pass
        elif rp != rq and not (rp < rq and ("low byte" in note or "low half" in note)) and "RETURN:" not in note:
            problem(f"{addr} {name}: returns {rp} bytes ({ours[0]}), the export {rq} ({theirs[0]})")
    gnames = {}
    if (T / "globals.tsv").exists():
        for r in csv.reader(open(T / "globals.tsv", encoding="utf-8"), delimiter="\t"):
            if not r or r[0].startswith("#") or not r[0].strip():
                continue
            addr, name = r[0].strip(), r[1].strip()
            if not re.fullmatch(r"[A-Za-z_]\w*", name) or name in KEYWORDS:
                problem(f"global {addr}: bad name {name!r}")
            if name in gnames:
                problem(f"global {addr}: name {name} also at {gnames[name]}")
            if name in names:
                problem(f"global {addr}: name {name} is also a function")
            gnames[name] = addr
    nloc = 0
    FIELDS = set()
    if (T / "types.h").exists():
        FIELDS = set(re.findall(r"(\w+)\s*(?:\[[^\]]*\])?;", re.sub(r"/\*.*?\*/", "", (T / "types.h").read_text(), flags=re.S)))
    if (T / "locals.tsv").exists():
        variables = {}
        for r in csv.DictReader(open(E / "variables.tsv", errors="replace"), delimiter="\t"):
            variables.setdefault(r["entry"].zfill(8), set()).add(r["name"])
        seen = {}
        for r in csv.reader(open(T / "locals.tsv", encoding="utf-8"), delimiter="\t"):
            if not r or r[0].startswith("#") or not r[0].strip():
                continue
            fn, old, new = (x.strip() for x in r[:3])
            nloc += 1
            vs = variables.get(fn)
            if vs is None:
                problem(f"locals {fn}: no such function in the export")
                continue
            applied = old not in vs and new in vs       # an export made with this table already has the new name
            if old not in vs and not applied:
                problem(f"locals {fn}: no variable {old}")
            if (fn, old) in PROTECTED_BY_STAGE.get(a.stage, set()):
                problem(f"locals {fn}: {old} is named by a shcpep-fixes anchor")
            if not re.fullmatch(r"[A-Za-z_]\w*", new) or new in RESERVED or new in types or new in WIN32 \
                    or new in names or new in gnames or ("_" + new) in gnames:
                problem(f"locals {fn}: bad new name {new!r} for {old}")
            # a stack local may become a frame-record view (#define NAME ...): it must not be a struct field name
            if re.fullmatch(r"local_[0-9a-f]+", old) and new in FIELDS:
                problem(f"locals {fn}: {new} (for {old}) is a struct field name")
            taken = seen.setdefault(fn, set())
            if new in taken or (new in vs and new != old and not applied and old not in vs):
                problem(f"locals {fn}: {new} is already a variable of the function")
            taken.add(new)
    print(f"{len(names)} functions, {len(gnames)} globals, {nloc} locals, {bad} problems")
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
