#!/usr/bin/env python3
"""Rejoin stack records Ghidra split into separate locals.

Usage: python tools/frame-records.py <stage> [--dry]

Ghidra names a stack local by its frame offset (local_8 = [ebp-8] in its numbering) and splits a record that the
code reads or writes whole into one local per field: `FUN_0041bff0(f, (char *)&local_8, 4)` fills local_8
(a 2-byte short) and local_6 (the next 2 bytes). In the rebuild each is its own variable, so the call writes over
memory that is not the second field. This finds every call that passes &local_X with a literal length larger than
local_X, and gives the function one byte buffer covering the whole record (the largest such length over all the
calls, merged across overlapping records); every local inside it becomes a view into the buffer at its offset:
    unsigned char _frec_8[4];
    #define local_8 (*(undefined2 *)(_frec_8 + 0))
    #define local_6 (*(short *)(_frec_8 + 2))
(and #undef at the end of the function). --all instead makes the whole stock frame one buffer in every function
with an array local or an address-taken local. An array local keeps its element type: local_100[N] becomes
((T *)(_frec + off)).
"""
import argparse, re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ALL = False
SIZE = {"char": 1, "byte": 1, "uchar": 1, "undefined1": 1, "undefined": 1, "bool": 1, "cVar": 1,
        "short": 2, "ushort": 2, "undefined2": 2, "wchar_t": 2, "word": 2,
        "int": 4, "uint": 4, "undefined4": 4, "dword": 4, "long": 4, "ulong": 4, "float": 4, "LPSTR": 4, "HANDLE": 4,
        "undefined8": 8, "longlong": 8, "ulonglong": 8, "double": 8, "__int64": 8}
DECL = re.compile(r"^([ \t]+)((?:unsigned |signed )?[A-Za-z_]\w*(?:\s*\*+)?)\s+(\**)([A-Za-z_]\w*)(?:\s*\[(\d+)\])?;[ \t]*\r?\n", re.M)
CALL_ARG = re.compile(r"&([A-Za-z_]\w*)\s*(?:\[0\])?\s*,\s*(?:\([^()]*\)\s*)?(0x[0-9a-f]+|\d+)\s*[,)]")
# a stack local's frame offset: local_N names it in hex; a local_N the naming tables renamed (locals.tsv) keeps
# the offset of its old name
RENAMED = {}


STACK_NAMES = False      # --stack-names / --stack-arrays: Ghidra's acStack_N / auStack_N / uStack_N ... (the same offset scheme) too


def frame_offset(fn, name):
    # Ghidra names stack arrays and other stack variables by their offset too (acStack_10b, auStack_9: the frame's
    # bytes at -0x10b, -9, as local_N would be); emit_line_comment's base name follows its length byte, and
    # get_source_file_basename writes the two as one record
    m = re.fullmatch(r"(?:local|[a-z]+Stack)_([0-9a-f]+)" if STACK_NAMES else r"local_([0-9a-f]+)",
                     RENAMED.get((fn, name), name))
    return int(m.group(1), 16) if m else None


def tsize(t, stars):
    if stars or t.rstrip().endswith("*"):
        return 4
    return SIZE.get(t.strip(), 4)


def process(s, fn):
    out, pos, n = [], 0, 0
    # functions: a line starting with a type and a name followed by (, then { ... } at column 0
    for fm in re.finditer(r"^[A-Za-z_][^\n;]*\([^;{]*\)\s*\r?\n\{\r?\n(.*?)^\}", s, re.S | re.M):
        body, b0 = fm.group(1), fm.start(1)
        decls, by_name = {}, {}
        # only the declaration block (Ghidra ends it with a blank line): a wrapped statement line such as
        # "           unit_bytes * unit_count;" would otherwise read as a declaration
        blank = re.search(r"^[ \t]*\r?\n", body, re.M)
        for d in DECL.finditer(body, 0, blank.start() if blank else len(body)):
            if d.group(2).split()[0] in ("return", "goto", "case", "else", "do", "sizeof"):
                continue
            off = frame_offset(fn, d.group(4))
            if off is None:
                continue
            by_name[d.group(4)] = off
            elem = tsize(d.group(2), d.group(3))
            cnt = int(d.group(5)) if d.group(5) else 0
            decls[off] = (d, d.group(2).strip() + (" " + d.group(3) if d.group(3) else ""), elem, cnt)
        recs = []
        for c in CALL_ARG.finditer(body):
            x, ln = by_name.get(c.group(1)), int(c.group(2), 0)
            if x not in decls or ln > 0x400:
                continue
            d, t, elem, cnt = decls[x]
            if ln > elem * max(cnt, 1):
                recs.append([x, ln])
        if ALL and decls and (any(re.search(r"&" + re.escape(nm) + r"\b", body) for nm in by_name)
                              or any(v[3] for v in decls.values())):
            # the whole stock frame: every local_X is a view at its stock offset (arrays copied past their
            # declared length, records walked by pointer, address-taken neighbours behave as in stock)
            recs = [[max(decls), max(decls)]]
        if not recs:
            continue
        recs.sort(key=lambda r: -r[0])                        # higher local number = lower address
        merged = []
        for x, ln in recs:
            if merged and merged[-1][0] - merged[-1][1] < x:  # overlaps the previous record
                top, mln = merged[-1]
                merged[-1][1] = max(mln, top - x + ln)
            else:
                merged.append([x, ln])
        new_body = body
        defs, undefs, drop = [], [], []
        for top, ln in merged:
            buf = f"_frec_{top:x}"
            inside = [o for o in decls if top - ln < o <= top]
            hi = max(top - o + decls[o][2] * max(decls[o][3], 1) for o in inside)
            defs.append(f"  unsigned char {buf}[{max(ln, hi)}];")
            for o in sorted(inside, reverse=True):
                d, t, elem, cnt = decls[o]
                drop.append(d)
                k = top - o
                nm = d.group(4)
                if cnt:
                    defs.append(f"#define {nm} (*({t} (*)[{cnt}])({buf} + {k}))")
                else:
                    defs.append(f"#define {nm} (*({t} *)({buf} + {k}))")
                undefs.append(f"#undef {nm}")
        for d in sorted(drop, key=lambda d: -d.start()):
            new_body = new_body[:d.start()] + new_body[d.end():]
        first = DECL.search(new_body)
        ins = 0                                           # C89: the buffer and views open the function body
        new_body = new_body[:ins] + "\n".join(defs) + "\n" + new_body[ins:]
        new_body = new_body.rstrip() + "\n" + "\n".join(undefs) + "\n"
        out.append(s[pos:b0] + new_body)
        pos = fm.end(1)
        n += len(merged)
    out.append(s[pos:])
    return "".join(out), n


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("stage"); ap.add_argument("--dry", action="store_true"); ap.add_argument("--only")
    ap.add_argument("--all", action="store_true", help="the whole stock frame of every function with an array local or &local_")
    ap.add_argument("--locals", help="the stage's locals.tsv (renamed locals: function, old name, new name)")
    ap.add_argument("--stack-names", action="store_true",
                    help="also Ghidra's xStack_N locals (auStack_9 is the frame's bytes at -9, as local_9 would be)")
    ap.add_argument("--stack-arrays", action="store_true", help="the same as --stack-names (shcasm's regen spells it so)")
    a = ap.parse_args()
    global STACK_NAMES
    STACK_NAMES = a.stack_names or a.stack_arrays
    if a.locals and Path(a.locals).exists():
        for l in open(a.locals, encoding="utf-8"):
            r = l.rstrip("\n").split("\t")
            if len(r) >= 3 and not l.startswith("#"):
                RENAMED[(r[0].strip().zfill(8), r[2].strip())] = r[1].strip()
    global ALL
    ALL = a.all
    tot = 0
    for f in sorted((ROOT / "rebuild" / a.stage / "src").glob("0*.c")):
        if a.only and a.only not in f.name:
            continue
        s = f.read_bytes().decode("latin-1")
        if "_frec_" in s:
            continue
        s2, n = process(s, f.name[:8])
        if n:
            tot += n
            print(f"{f.name}: {n}")
            if not a.dry:
                f.write_bytes(s2.encode("latin-1"))
    print(tot, "records")


if __name__ == "__main__":
    main()
