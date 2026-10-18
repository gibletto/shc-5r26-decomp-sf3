#!/usr/bin/env python3
"""Lossless editable GEN output / PEP input (.sua), sharing the SUB PSD codec.

All 256 PEP format-table entries are checked against the shared ASM table.
The TSV records expose opcodes, registers, immediates, labels, flags and unused
bytes. Full record groups may be reordered. ASA and the request/other sidecars
are separate files and must be retained when resuming PEP.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import re
import struct
import sys
from functools import lru_cache
from pathlib import Path

sys.dont_write_bytecode = True
import stage_sub

MAGIC = "# stage-sua-v1"


@lru_cache(maxsize=1)
def verify_tables():
    path = Path(__file__).resolve().parents[1] / "rebuild/shcpep/src/_stockdata.c"
    source = path.read_text(encoding="utf-8")
    body = re.search(r"unsigned char g_sd\[[^]]+\] = \{(.*?)\};", source, re.S)
    if not body:
        raise ValueError(f"unrecognized PEP stock data: {path}")
    raw = bytes(int(x, 16) for x in re.findall(r"0x([0-9a-fA-F]{2})\b", body[1]))
    pep_formats = struct.unpack_from("<256H", raw, 0x1118)
    asm_formats, _ = stage_sub.load_tables()
    if pep_formats != asm_formats:
        raise ValueError("PEP and ASM serialized record format tables differ")
    return True


def decode(data: bytes):
    verify_tables()
    records = stage_sub.decode(data)
    warnings = [record.warning for record in records if record.warning]
    if warnings:
        raise ValueError("SUA is not completely decoded: " + "; ".join(warnings))
    return records


def dumps(data: bytes, opaque: bool = False) -> str:
    if not opaque:
        decode(data)
    return stage_sub.dumps(data, opaque=opaque).replace(stage_sub.MAGIC, MAGIC, 1)


def encode(text: str) -> bytes:
    if text.splitlines()[:1] != [MAGIC]:
        raise ValueError("missing stage-sua-v1 signature")
    binary = stage_sub.encode(text.replace(MAGIC, stage_sub.MAGIC, 1))
    if "# mode=opaque" in text.splitlines():
        return binary
    actual = decode(binary)
    expected = []
    group = -1
    previous = None
    for row in csv.DictReader((line for line in text.splitlines() if not line.startswith("#")), delimiter="\t"):
        if row["record"] != previous:
            group += 1
            previous = row["record"]
        kind = row["type"]
        value = bytes.fromhex(row["value"]) if kind == "hex" else int(row["value"], 0)
        expected.append((group, row["field"], kind, value))
    decoded = [(i, field.name, field.kind, field.value)
               for i, record in enumerate(actual) for field in record.fields]
    if expected != decoded:
        raise ValueError("edited field layout disagrees with SUA grammar; check operand kinds, flags, counts and lengths")
    return binary


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest="command", required=True)
    for verb in ("dump", "encode"):
        command = commands.add_parser(verb)
        command.add_argument("input", type=Path)
        command.add_argument("output", type=Path)
        if verb == "dump":
            command.add_argument("--opaque", action="store_true", help="preserve an unsupported stream as exact opaque bytes")
    check = commands.add_parser("check")
    check.add_argument("input", type=Path)
    args = parser.parse_args(argv)
    try:
        if args.command == "check":
            binary = args.input.read_bytes()
            if encode(dumps(binary)) != binary:
                raise ValueError("roundtrip changed bytes")
            print(f"roundtrip=identical bytes={len(binary)} records={len(decode(binary))} opaque_remainders=0 sha256={hashlib.sha256(binary).hexdigest()}")
        else:
            if args.input.resolve() == args.output.resolve():
                raise ValueError("input and output must differ")
            if args.command == "dump":
                args.output.write_text(dumps(args.input.read_bytes(), opaque=args.opaque), encoding="utf-8", newline="\n")
            else:
                args.output.write_bytes(encode(args.input.read_text(encoding="utf-8")))
    except (ValueError, OSError) as exc:
        parser.exit(2, f"stage_sua: {exc}\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
