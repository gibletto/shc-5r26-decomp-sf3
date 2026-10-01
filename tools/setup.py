#!/usr/bin/env python3
"""Unpack SHC 5.0 Release 26 into extracted/ and make each rebuilt stage's src/_stockdata.c from it.

Usage: python tools/setup.py [shc-v5.0r26.tar.gz]

Without an argument the archive decomp.me hosts is downloaded. Either way its SHA-256 must be the one below.
"""
import hashlib, io, sys, tarfile, urllib.request
from importlib import import_module
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
URL = "https://github.com/decompme/compilers/releases/download/compilers/shc-v5.0r26.tar.gz"
SHA256 = "a065c9b6bfe60af986c72c2d863b0b067fe839605b1131460ff786a8e0badc0d"
STAGES = ["shcmdl", "shcgen", "shcpep", "shcasm"]


def main():
    if len(sys.argv) > 1:
        data = Path(sys.argv[1]).read_bytes()
    else:
        print(f"downloading {URL}")
        data = urllib.request.urlopen(URL).read()
    h = hashlib.sha256(data).hexdigest()
    if h != SHA256:
        sys.exit(f"SHA-256 {h}: not the Release 26 archive ({SHA256})")
    with tarfile.open(fileobj=io.BytesIO(data)) as t:
        for m in t.getmembers():
            if m.isdir() and m.name.rstrip("/") == "bin":
                continue
            if not m.isfile() or not m.name.startswith("bin/") or "/" in m.name[4:]:
                sys.exit(f"unexpected member {m.name}")
        t.extractall(ROOT / "extracted", **({"filter": "data"} if hasattr(tarfile, "data_filter") else {}))
    print(f"Release 26 in {ROOT / 'extracted/bin'}")
    sys.path.insert(0, str(ROOT / "tools"))
    gen = import_module("gen-stockdata")
    for s in STAGES:
        lo, hi, n = gen.write_stockdata(s)
        print(f"{s}: src/_stockdata.c, data {lo:#x}..{hi:#x}, {n} pointer sites")


if __name__ == "__main__":
    main()
