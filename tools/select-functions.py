#!/usr/bin/env python3
"""Choose the functions of a stage's C rebuild from a Ghidra export: everything reachable from the stage's main by
name (calls and function addresses passed as values) plus every application function whose address the stock data
holds (dispatch tables), stopping at the CRT routines the rebuild takes from the host CRT (--shim, the names
src/_crt_shim.c defines) and at import thunks.

Usage: python tools/select-functions.py <stage> --export <reports dir> --root <addr> --crt <first CRT addr>
                                        [--shim NAME ...] [--write]
--write creates rebuild/<stage>/src/<addr>_<name>.c placeholders for the chosen functions (regen fills them) and
removes 0*.c files of functions no longer chosen.
"""
import argparse, csv, re, struct
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def c_part(t):
    return t.split("// --- disassembly ---")[0]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("stage"); ap.add_argument("--export", required=True); ap.add_argument("--root", required=True)
    ap.add_argument("--crt", required=True); ap.add_argument("--shim", nargs="*", default=[])
    ap.add_argument("--write", action="store_true")
    a = ap.parse_args()
    rep = ROOT / "ghidra/reports" / a.export
    funcs = {}                                   # addr -> (name as in C, file)
    by_name = defaultdict(list)
    ext = {r["name"] for r in csv.DictReader(open(rep / "externals.tsv"), delimiter="\t")}
    for r in csv.DictReader(open(rep / "functions.tsv"), delimiter="\t"):
        addr = int(r["entry"], 16)
        cname = r["name"].replace(":", "_")
        f = next((rep / "decomp").glob(f"{r['entry']}_*.c"))
        if by_name[cname]:
            continue                             # a second copy under the same name (FID: _strncnt): callers link to the first
        funcs[addr] = (cname, f)
        by_name[cname].append(addr)
    crt = int(a.crt, 16)
    shim = set(a.shim)
    # function addresses in the stock data (.reloc sites in .rdata/.data pointing into .text)
    d = (ROOT / "extracted/bin" / f"{a.stage}.exe").read_bytes()
    pe = struct.unpack_from("<I", d, 0x3C)[0]
    n = struct.unpack_from("<H", d, pe + 6)[0]
    opt = struct.unpack_from("<H", d, pe + 20)[0]
    base = struct.unpack_from("<I", d, pe + 24 + 28)[0]
    secs = []
    for i in range(n):
        nm, vs, va, rs, ra = struct.unpack_from("<8sIIII", d, pe + 24 + opt + 40 * i)
        secs.append((nm.rstrip(b"\0").decode(), base + va, vs, rs, ra))
    rrva, rsize = struct.unpack_from("<II", d, pe + 24 + 96 + 5 * 8)

    def fo(v):
        return next(ra + v - va for _, va, vs, rs, ra in secs if va <= v < va + max(vs, rs))
    data = [s for s in secs if s[0] in (".rdata", ".data")]
    p = fo(base + rrva); end = p + rsize; roots = set()
    while p < end:
        page, bs = struct.unpack_from("<II", d, p)
        if bs == 0:
            break
        for k in range((bs - 8) // 2):
            e = struct.unpack_from("<H", d, p + 8 + 2 * k)[0]
            site = base + page + (e & 0xFFF)
            if e >> 12 == 3 and any(va <= site < va + vs for _, va, vs, _, _ in data):
                v = struct.unpack_from("<I", d, fo(site))[0]
                if v in funcs and v < crt:
                    roots.add(v)
        p += bs
    ident = re.compile(r"\b[A-Za-z_]\w*\b")
    seen, todo = set(), [int(a.root, 16)] + sorted(roots)
    while todo:
        x = todo.pop()
        if x in seen:
            continue
        name, f = funcs[x]
        if name in shim or name in ext or name == "entry":
            continue
        seen.add(x)
        for w in set(ident.findall(c_part(f.read_text(encoding="utf-8", errors="replace")))):
            for y in by_name.get(w, ()):
                if y != x:
                    todo.append(y)
    app = sorted(x for x in seen if x < crt)
    lib = sorted(x for x in seen if x >= crt)
    print(f"{len(seen)} functions: {len(app)} application, {len(lib)} CRT; {len(roots)} data roots; "
          f"{sum(1 for x in funcs if x < crt) - len(app)} application functions unreached")
    print("CRT:", " ".join(f"{x:08x}:{funcs[x][0]}" for x in lib))
    if a.write:
        S = ROOT / "rebuild" / a.stage / "src"; S.mkdir(parents=True, exist_ok=True)
        want = {f"{x:08x}_{funcs[x][1].stem.split('_', 1)[1]}.c" for x in seen}
        for f in S.glob("0*.c"):
            if f.name not in want:
                f.unlink()
        for w in want:
            if not (S / w).exists():
                (S / w).write_text("")


if __name__ == "__main__":
    main()
