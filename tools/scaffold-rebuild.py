#!/usr/bin/env python3
"""Give a stage's C rebuild (the decompiled functions in src/) what it needs to link and run against the stock
program's data image.

Usage: python tools/scaffold-rebuild.py <stage> [--main NAME] [--heap GLOBAL] [--heap-create]

Writes:
  include/ghidra_stubs.h, imports.h   copied from rebuild/shcgen (for Visual C++, with Ghidra's SUBPIECE macros)
  include/decls.h    every function (its return type from its definition, unprototyped) and every data global
                     the sources name, as a macro for the lvalue at its stock offset in g_sd. Types follow Ghidra:
                     globals.tsv where the global is typed; else DAT_x is a byte (Ghidra's 'undefined'), _DAT_x a
                     4-byte int (Ghidra's prefix for a wider access at the same address), PTR_ a pointer, s_ a string
  src/_stockdata.c   g_sd (the stock .rdata/.data bytes), the stock .reloc sites in it and _stockdata_relocate()
                     (tools/gen-stockdata.py)
  src/_relocs.c      _text_reloc (stock function entry -> rebuild address; build.py fills it in from the link map)
                     and _translate_text_va()
  src/_stubs.c       main(): relocate, the heap global = GetProcessHeap() (--heap-create: a private heap as the stock
                     CRT startup makes it, HeapCreate(1, 0x1000, 0): no low-fragmentation heap, so blocks come in
                     address order run after run), then --main (default <stage>_main)
"""
import argparse, csv, re, shutil, struct, sys
from importlib import import_module
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))

CTYPE = {"undefined4": "int", "undefined2": "short", "undefined1": "unsigned char", "undefined": "unsigned char",
         "dword": "unsigned int", "word": "unsigned short", "byte": "unsigned char", "char": "char", "uchar": "unsigned char",
         "int": "int", "uint": "unsigned int", "short": "short", "ushort": "unsigned short", "long": "int", "ulong": "unsigned int",
         "bool": "unsigned char", "pointer": "char *", "undefined8": "__int64", "float": "float", "double": "double",
         "string": "char", "TerminatedCString": "char", "ImageBaseOffset32": "int", "LPSTR": "char *", "LPCSTR": "char *",
         "LPVOID": "void *", "HANDLE": "void *", "FARPROC": "void *", "DWORD": "unsigned int", "UINT": "unsigned int",
         "WORD": "unsigned short", "BYTE": "unsigned char", "LONG": "int", "BOOL": "int", "code": "unsigned char"}


STAGE_TYPES = set()       # names include/stage_types.h defines (tools/gen-stage-types.py): kept as they are


def ctype(t, length):
    """Ghidra type name -> (C base type, array length or None)"""
    t = t.strip()
    m = re.fullmatch(r"(.+?)\s*\[(\d+)\]", t)
    if m:
        base, _ = ctype(m.group(1), None)
        return base, int(m.group(2))
    if t.endswith("*"):
        base, _ = ctype(t[:-1].strip(), None)
        return (base if base != "unsigned char[]" else "unsigned char") + " *", None
    if t in ("string", "TerminatedCString", "unicode"):
        return "char", max(1, length or 1)
    if t in CTYPE:
        return CTYPE[t], None
    if t in STAGE_TYPES:
        return t, None
    return "unsigned char", max(1, length or 1)          # a struct or an unknown type: its bytes


def sections(d):
    pe = struct.unpack_from("<I", d, 0x3C)[0]
    n = struct.unpack_from("<H", d, pe + 6)[0]
    opt = struct.unpack_from("<H", d, pe + 20)[0]
    base = struct.unpack_from("<I", d, pe + 24 + 28)[0]
    secs = []
    for i in range(n):
        name, vs, va, rs, ra = struct.unpack_from("<8sIIII", d, pe + 24 + opt + 40 * i)
        secs.append((name.rstrip(b"\0").decode(), base + va, vs, rs, ra))
    rva, size = struct.unpack_from("<II", d, pe + 24 + 96 + 5 * 8)
    return base, secs, rva, size


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("stage"); ap.add_argument("--main"); ap.add_argument("--heap"); ap.add_argument("--heap-create", action="store_true")
    ap.add_argument("--reports", required=True,
                    help="ghidra/reports/<dir> holding symbols.tsv/globals.tsv: the export the sources came from")
    a = ap.parse_args()
    R = ROOT / "rebuild" / a.stage
    (R / "include").mkdir(exist_ok=True)
    names = R / "include/stage_types.names"
    if names.exists():
        STAGE_TYPES.update(names.read_text().split())
    for h in ("ghidra_stubs.h", "imports.h"):
        if a.stage != "shcgen":                          # shcgen's are the originals
            shutil.copy(ROOT / "rebuild/shcgen/include" / h, R / "include" / h)
    d = (ROOT / "extracted/bin" / f"{a.stage}.exe").read_bytes()
    base, secs, rrva, rsize = sections(d)
    data = [s for s in secs if s[0] in (".rdata", ".data")]
    lo, hi = min(s[1] for s in data), max(s[1] + s[2] for s in data)

    # names -> addresses and Ghidra types
    rep = ROOT / "ghidra/reports" / a.reports
    sym, typ = {}, {}
    for r in csv.reader(open(rep / "symbols.tsv", errors="replace"), delimiter="\t"):
        if len(r) >= 2 and re.fullmatch(r"[0-9a-f]{8}", r[0]):
            sym.setdefault(r[1], int(r[0], 16))
    for r in csv.DictReader(open(rep / "globals.tsv", errors="replace"), delimiter="\t"):
        if re.fullmatch(r"[0-9a-f]{8}", r["addr"]):
            typ[int(r["addr"], 16)] = (r["type"], int(r["len"] or 0))
            if r["name"]:
                sym.setdefault(r["name"], int(r["addr"], 16))

    # functions: name -> return type from the definition
    funcs = {}
    for f in sorted((R / "src").glob("0*.c")):
        s = f.read_text(errors="replace")
        name = f.stem.split("_", 1)[1]
        m = re.search(r"^([A-Za-z_][\w ]*?[\s\*]+)(?:__cdecl\s+|__stdcall\s+)?" + re.escape(name) + r"\s*\(", s, re.M)
        rt = (m.group(1).strip() if m else "int")
        if rt in ("undefined", "void"):
            rt = "int"
        funcs[name] = rt
    idents = set()
    for f in (R / "src").glob("0*.c"):
        idents |= set(re.findall(r"\b[A-Za-z_]\w*\b", f.read_text(errors="replace")))

    out = ["#ifndef DECLS_H", "#define DECLS_H", '#include "ghidra_stubs.h"'] +           (['#include "stage_types.h"'] if STAGE_TYPES else []) + ["",
           "/* the stock data image (scaffold-rebuild.py): data globals are lvalues at their stock offsets */",
           "extern unsigned char g_sd[];", f"#define SD(a) ((unsigned int)(g_sd + ((unsigned int)(a) - {lo:#x}u)))", ""]
    for name, rt in sorted(funcs.items()):
        out.append(f"extern {rt} {name}();")
    out.append("")
    n_glob = 0
    for name in sorted(idents):
        if name in funcs:
            continue
        m = re.fullmatch(r"(_?)(DAT|PTR_\w+|s_\w+|u_\w+|switchdataD|BYTE|WORD|DWORD|QWORD)_([0-9a-f]{8})", name)
        addr = int(m.group(3), 16) if m else sym.get(name)
        # _NAME: Ghidra's name for a wider access at a named global NAME (as _DAT_x for DAT_x)
        wide = bool(m and m.group(1) == "_") or (addr is None and name.startswith("_") and name[1:] in sym)
        if addr is None and wide:
            addr = sym[name[1:]]
        if addr is None or not (lo <= addr < hi):
            continue
        if addr in typ and not wide:
            t, ln = ctype(*typ[addr])
        elif wide:
            t, ln = "int", None
        elif m and m.group(2).startswith("PTR_"):
            t, ln = "char *", None
        elif m and m.group(2).startswith(("s_", "u_")):
            t, ln = "char", (typ.get(addr, ("", 1))[1] or 1)
        else:
            t, ln = "unsigned char", None
        off = addr - lo
        if ln:
            out.append(f"#define {name} (*({t} (*)[{ln}])(g_sd + {off:#x}))")
        else:
            out.append(f"#define {name} (*({t} *)(g_sd + {off:#x}))")
        n_glob += 1
    out += ["", "#endif", ""]
    (R / "include/decls.h").write_text("\n".join(out))

    # _stockdata.c
    _, _, n_sites = import_module("gen-stockdata").write_stockdata(a.stage)

    # _relocs.c: function entries (build.py fills in the rebuild addresses)
    ents = sorted(int(f.name[:8], 16) for f in (R / "src").glob("0*.c"))
    rel = ["/* stock function entry -> rebuild address (build.py fills in the second column from the link map) */", "",
           "static const struct { unsigned int stock_va; unsigned int rebuild_va; } _text_reloc[] = {"]
    rel += [f"    {{ 0x{e:08X}u, 0x00000000u }}," for e in ents]
    rel += ["};", f"static const int _text_reloc_count = {len(ents)};", "",
            "unsigned int _translate_text_va(unsigned int va) {", "    int lo = 0, hi = _text_reloc_count, mid;",
            "    while (lo < hi) {", "        mid = (lo + hi) >> 1;", "        if (_text_reloc[mid].stock_va < va) lo = mid + 1;",
            "        else if (_text_reloc[mid].stock_va > va) hi = mid;", "        else return _text_reloc[mid].rebuild_va;",
            "    }", "    return 0;", "}", ""]
    (R / "src/_relocs.c").write_text("\n".join(rel))

    # _stubs.c
    mn = a.main or f"{a.stage}_main"
    st = ['#include "decls.h"', '#include "imports.h"', "", "extern void _stockdata_relocate(void);", "",
          "int main(int argc, char **argv) {", "    _stockdata_relocate();"]
    if a.heap:
        st.append(f"    {a.heap} = (int)HeapCreate(1, 0x1000, 0);" if a.heap_create else f"    {a.heap} = (int)GetProcessHeap();")
    st += [f"    {mn}(argc, (int)argv);", "    return 0;", "}", ""]
    (R / "src/_stubs.c").write_text("\n".join(st))
    print(f"{len(funcs)} functions, {n_glob} data globals, {n_sites} pointer sites; data {lo:#x}..{hi:#x}")


if __name__ == "__main__":
    main()
