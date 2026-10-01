#!/usr/bin/env python3
"""Give every row of a stage's locals.tsv the first-use address and storage of its variable (columns 5 and 6),
from an export's variables.tsv, so ApplyStageTables.java still finds the variable after the decompiler renumbers
its temporaries (a signature or type change elsewhere turns iVar6 into iVar5).

Usage: python tools/key-locals.py <stage> [--export <stage>-now]

Run it on an export made with the current tables: a row's variable is found there under its new name (the tables
were applied) or its old one. Rows already keyed are left alone; a row whose variable can't be found is reported.
"""
import argparse, csv, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("stage"); ap.add_argument("--export")
    a = ap.parse_args()
    E = ROOT / "ghidra/reports" / (a.export or f"{a.stage}-now")
    T = ROOT / "ghidra/names" / a.stage / "locals.tsv"
    var = {}
    for r in csv.DictReader(open(E / "variables.tsv", errors="replace"), delimiter="\t"):
        var[(r["entry"].zfill(8), r["name"])] = (r.get("pc") or "", r.get("storage") or "")
    out, n, missing = [], 0, 0
    for l in open(T, encoding="utf-8"):
        r = l.rstrip("\n").split("\t")
        if l.startswith("#") or len(r) < 3:
            out.append(l.rstrip("\n"))
            continue
        r += [""] * (6 - len(r))
        if not r[4]:
            k = var.get((r[0], r[2])) or var.get((r[0], r[1]))
            if k and k[0]:
                r[4], r[5] = k
                n += 1
            elif not k:
                missing += 1
                print(f"{r[0]} {r[1]} -> {r[2]}: not in the export")
        out.append("\t".join(r[:6]).rstrip("\t"))
    T.write_bytes(("\n".join(out) + "\n").encode("utf-8"))     # LF line endings whatever the platform
    print(f"{n} rows keyed, {missing} not found")
    sys.exit(1 if missing else 0)


if __name__ == "__main__":
    main()
