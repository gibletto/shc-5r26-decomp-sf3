#!/usr/bin/env python3
"""Lossless SHC5 assembler-input (.sub/.sud) dump and encoder.

The TSV contains editable serialized fields, not a lossy reconstruction of the
assembler's in-memory PSD. In particular, flags the reader masks out, relocation
label chains, and unused bytes remain present. Unknown grammar preserves the
entire remaining stream as explicitly opaque data; --require-complete rejects it.

Rows are record, offset-within-record, field, type, value. Records are emitted in
file order, so complete record groups may be reordered. Offset annotations in
comments are informational. Field offsets must remain contiguous. Integers are
little endian. u8/i8/u16/i16/u32/i32 and hex are supported. Packed base/index
bytes keep base in the high nibble; raw flags/type bytes retain all bits.

Schema: rebuild/shcasm/src/{00402b00_read_backend_record_payload,
004030aa_read_pseudo_op_record_payload,00403e5d_read_record_operand}.c.
Opcode tables come from the checked-in stock data, not an installed executable.
This module imports no compiler runner and never executes a stage.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import io
import re
import struct
import sys
from dataclasses import dataclass
from pathlib import Path

FORMATS = {"u8": "B", "i8": "b", "u16": "H", "i16": "h", "u32": "I", "i32": "i"}
HEADER = ["record", "offset", "field", "type", "value"]
MAGIC = "# stage-sub-v1"


@dataclass
class Field:
    offset: int
    name: str
    kind: str
    value: int | bytes


@dataclass
class Record:
    index: int
    offset: int
    name: str
    format: int
    fields: list[Field]
    warning: str = ""


def load_tables(stock_path: Path | None = None):
    if stock_path is None:
        stock_path = Path(__file__).resolve().parents[1] / "rebuild/shcasm/src/_stockdata.c"
    source = Path(stock_path).read_text(encoding="utf-8")
    base_match = re.search(r"stock data image (0x[0-9a-fA-F]+)", source)
    body_match = re.search(r"unsigned char g_sd\[[^]]+\] = \{(.*?)\};", source, re.S)
    if not base_match or not body_match:
        raise ValueError(f"unrecognized stock data source: {stock_path}")
    base = int(base_match[1], 16)
    data = bytes(int(x, 16) for x in re.findall(r"0x([0-9a-fA-F]{2})\b", body_match[1]))
    formats = struct.unpack_from("<256H", data, 0x43C048 - base)
    names = []
    for i in range(256):
        pointer = struct.unpack_from("<I", data, 0x440D88 - base + 4 * i)[0]
        if base <= pointer < base + len(data):
            raw = data[pointer-base:pointer-base+40].split(b"\0", 1)[0]
            name = raw.decode("ascii", errors="replace").strip()
            if not name.isprintable():
                name = ""
        else:
            name = ""
        names.append(name or f"op_{i:02x}")
    return formats, names


class Reader:
    def __init__(self, data: bytes):
        self.data = data
        self.pos = 0
        self.start = 0
        self.fields: list[Field] = []

    def read(self, name: str, kind: str, size: int | None = None):
        length = size if kind == "hex" else struct.calcsize("<" + FORMATS[kind])
        if length is None or self.pos + length > len(self.data):
            raise ValueError(f"truncated {name} at 0x{self.pos:x}: need {length} bytes")
        raw = self.data[self.pos:self.pos+length]
        value = raw if kind == "hex" else struct.unpack("<" + FORMATS[kind], raw)[0]
        self.fields.append(Field(self.pos-self.start, name, kind, value))
        self.pos += length
        return value

    def refs(self, prefix: str):
        count = self.read(prefix + ".count", "u32")
        if count > (len(self.data)-self.pos)//2:
            raise ValueError(f"impossible label count {count} at 0x{self.pos-4:x}")
        for i in range(count):
            self.read(f"{prefix}[{i}]", "u16")

    def operand(self, prefix: str, flags: int):
        kind = self.read(prefix + ".type_raw", "u8") & 0x1f
        if kind == 0:
            return
        if kind in (1, 2, 3, 4, 15, 16):
            self.read(prefix + ".base", "u8")
        elif kind in (5, 6):
            # Assembler adds REG_SR (0x61) or REG_MACH (0x64).
            self.read(prefix + ".system_reg_offset", "u8")
        elif kind == 7:
            if flags & 3 == 3:
                raise ValueError(f"invalid immediate size selector at 0x{self.pos:x}")
            self.read(prefix + ".immediate", ("i8", "i16", "i32")[flags & 3])
            self.refs(prefix + ".labels")
        elif kind == 8:
            self.read(prefix + ".base", "u8")
            self.read(prefix + ".displacement", "i16")
        elif kind == 9:
            self.read(prefix + ".base_index_packed", "u8")
        elif kind == 10:
            self.read(prefix + ".pc_displacement", "i16")
        elif kind == 11:
            self.read(prefix + ".gbr_displacement", "i32")
            self.refs(prefix + ".labels")
        elif kind == 12:
            self.read(prefix + ".gbr_index", "u8")
        else:
            raise ValueError(f"unknown operand kind {kind} at 0x{self.pos-1:x}")

    def location(self):
        self.read("file", "u16")
        self.read("line", "u16")

    def pseudo(self, opcode: int):
        self.location()
        self.read("expression", "u32")
        if opcode == 0x22:
            self.read("branch_label", "u16")
        elif opcode in (0x23, 0x24, 0x25, 0x26):
            if opcode == 0x23:
                self.read("misc_raw", "u8")
            self.read("branch_label", "u16")
            self.read("tmp", "u8")
        elif opcode == 0x27:
            self.read("flags_raw", "u8")
            self.read("misc_raw", "u8")
            self.read("register", "u8")
            self.read("tmp", "u8")
            self.read("unused_size", "u8")
            self.read("frame_displacement", "i32")
            self.read("unused_word", "u32")
            self.read("sptravel", "i32")
        elif opcode == 0x28:
            self.read("flags_raw", "u8")
            self.read("destination", "u8")
            self.read("unused_size", "u8")
            self.read("frame_displacement", "i32")
            self.read("unused_word", "u32")
            self.read("sptravel", "i32")
        elif opcode == 0x29:
            self.read("destination", "u8")
            self.read("unused_size", "u8")
            self.read("immediate", "i32")
            self.refs("labels")
        elif opcode in (0x2a, 0x2b, 0x2c):
            self.read("flags_raw", "u8")
            if opcode == 0x2b:
                self.read("destination_tmp_packed", "u8")
            else:
                self.read("misc_raw", "u8")
                self.read("destination", "u8")
                if opcode == 0x2c:
                    self.read("tmp", "u8")
            self.read("unused_size", "u8")
            self.read("immediate", "i32")
            self.refs("labels")
        elif opcode == 0x2e:
            self.read("flags_raw", "u8")
            self.read("source", "u8")
            self.read("destination", "u8")
        elif opcode in (0x30, 0x31):
            self.read("register", "u8")
        else:
            raise ValueError(f"unknown pseudo opcode 0x{opcode:02x}")


def decode(data: bytes, stock_path: Path | None = None, opaque: bool = False) -> list[Record]:
    if opaque:
        fields = [Field(i, f"bytes_{i:08x}", "hex", data[i:i+32]) for i in range(0, len(data), 32)]
        return [Record(0, 0, "OPAQUE_SIDECAR", -1, fields)]
    formats, names = load_tables(stock_path)
    reader = Reader(data)
    records = []
    while reader.pos < len(data):
        reader.start = reader.pos
        reader.fields = []
        try:
            opcode = reader.read("opcode", "u8")
            fmt = formats[opcode]
            if fmt in (1, 7):
                pass
            elif fmt == 2:
                reader.read("expression", "u32")
                reader.location()
                reader.read("raw_ea1", "u32")
                reader.read("raw_ea2", "u32")
            elif fmt in (3, 10):
                reader.location()
            elif fmt == 4:
                reader.read("raw_ea1", "u16")
            elif fmt == 5:
                reader.read("raw_ea1", "u16")
                reader.read("sptravel", "i32")
            elif fmt == 6:
                reader.location()
                reader.read("raw_ea1", "u8")
            elif fmt == 8:
                reader.location()
                reader.read("expression", "u32")
                flags = reader.read("flags_raw", "u8")
                reader.read("misc_raw", "u8")
                count = reader.read("operand_count", "u8")
                if count > 2:
                    raise ValueError(f"unsupported operand count {count}")
                for i in range(count):
                    reader.operand(f"ea{i+1}", flags)
            elif fmt == 9:
                reader.pseudo(opcode)
            elif fmt == 11:
                reader.location()
                reader.read("raw_ea1", "u32")
                reader.read("raw_ea2", "u32")
            elif fmt == 12:
                reader.read("file", "u16")
            else:
                raise ValueError(f"unknown record format {fmt} for opcode 0x{opcode:02x}")
        except ValueError as error:
            # No guessed resynchronization: retain the failing record and all
            # later bytes, including any partial header, exactly once.
            fields = [Field(0, "opaque_remainder", "hex", data[reader.start:])]
            records.append(Record(len(records), reader.start, "OPAQUE_REMAINDER", -1, fields, str(error)))
            break
        records.append(Record(len(records), reader.start, names[opcode], fmt, reader.fields))
    return records


def dumps(data: bytes, stock_path: Path | None = None, opaque: bool = False) -> str:
    records = decode(data, stock_path, opaque)
    output = io.StringIO(newline="")
    output.write(MAGIC + "\n")
    output.write("# mode=" + ("opaque" if opaque else "records") + "\n")
    output.write(f"# original_bytes={len(data)} sha256={hashlib.sha256(data).hexdigest()}\n")
    output.write("# offsets are within each record; integers little endian; full raw flags retained\n")
    writer = csv.writer(output, delimiter="\t", lineterminator="\n")
    writer.writerow(HEADER)
    for record in records:
        output.write(f"# record={record.index} original_offset=0x{record.offset:x} name={record.name} format={record.format}\n")
        if record.warning:
            output.write("# WARNING " + record.warning + "\n")
        for field in record.fields:
            if field.kind == "hex":
                value = field.value.hex()
            elif field.kind.startswith("i"):
                value = str(field.value)
            else:
                value = f"0x{field.value:0{int(field.kind[1:])//4}x}"
            writer.writerow([record.index, f"0x{field.offset:x}", field.name, field.kind, value])
    return output.getvalue()


def encode(text: str, stock_path: Path | None = None) -> bytes:
    if text.splitlines()[:1] != [MAGIC]:
        raise ValueError("missing stage-sub-v1 signature")
    rows = csv.DictReader((line for line in text.splitlines() if not line.startswith("#")), delimiter="\t")
    if rows.fieldnames != HEADER:
        raise ValueError(f"expected columns {HEADER}")
    result = bytearray()
    seen = set()
    names = set()
    record = None
    offset = 0
    shapes = []
    mode = [line for line in text.splitlines() if line.startswith("# mode=")]
    if len(mode) > 1 or (mode and mode[0] not in ("# mode=records", "# mode=opaque")):
        raise ValueError("unsupported or duplicate dump mode")
    opaque = mode == ["# mode=opaque"]
    for row in rows:
        if None in row or any(value is None for value in row.values()):
            raise ValueError(f"malformed TSV row: {row}")
        if row["record"] != record:
            record = row["record"]
            if record in seen:
                raise ValueError(f"record {record} occurs in noncontiguous groups")
            seen.add(record)
            names = set()
            offset = 0
            shapes.append([])
        if row["field"] in names:
            raise ValueError(f"duplicate field {record}:{row['field']}")
        names.add(row["field"])
        if int(row["offset"], 0) != offset:
            raise ValueError(f"noncontiguous field {record}:{row['field']}; expected offset 0x{offset:x}")
        kind = row["type"]
        if opaque and (kind != "hex" or not row["field"].startswith("bytes_")):
            raise ValueError("opaque sidecars permit only raw bytes_* hex atoms")
        if kind == "hex":
            raw = bytes.fromhex(row["value"])
        elif kind in FORMATS:
            try:
                raw = struct.pack("<" + FORMATS[kind], int(row["value"], 0))
            except struct.error as error:
                raise ValueError(f"out-of-range {record}:{row['field']} {kind}: {row['value']}") from error
        else:
            raise ValueError(f"unsupported atom type {kind}")
        result.extend(raw)
        shapes[-1].append((offset, row["field"], kind, len(raw)))
        offset += len(raw)
    data = bytes(result)
    if not opaque:
        actual = []
        for parsed in decode(data, stock_path):
            actual.append([(field.offset, field.name, field.kind,
                            len(field.value) if field.kind == "hex" else struct.calcsize("<" + FORMATS[field.kind]))
                           for field in parsed.fields])
        if actual != shapes:
            mismatch = next((i for i in range(min(len(actual), len(shapes))) if actual[i] != shapes[i]),
                            min(len(actual), len(shapes)))
            raise ValueError(f"encoded grammar differs from typed fields at record group {mismatch}; "
                             "update all affected operands/fields for a form or count edit")
    return data


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    commands = parser.add_subparsers(dest="command", required=True)
    dump = commands.add_parser("dump", help="binary to readable lossless TSV")
    dump.add_argument("input", type=Path)
    dump.add_argument("output", type=Path)
    dump.add_argument("--stock-data", type=Path)
    dump.add_argument("--opaque", action="store_true", help="carry an unknown sidecar as exact raw atoms")
    dump.add_argument("--require-complete", action="store_true", help="reject any undecoded remainder")
    dump.add_argument("--force", action="store_true", help="replace an existing distinct output file")
    pack = commands.add_parser("encode", help="edited TSV to binary")
    pack.add_argument("input", type=Path)
    pack.add_argument("output", type=Path)
    pack.add_argument("--stock-data", type=Path)
    pack.add_argument("--force", action="store_true", help="replace an existing distinct output file")
    check = commands.add_parser("check", help="prove binary equality after dump/encode; never runs compiler")
    check.add_argument("input", type=Path)
    check.add_argument("--stock-data", type=Path)
    check.add_argument("--opaque", action="store_true")
    check.add_argument("--require-complete", action="store_true")
    args = parser.parse_args(argv)
    if args.command in ("dump", "encode"):
        if args.input.resolve() == args.output.resolve():
            raise ValueError("input and output must be different files")
        if args.output.exists() and not args.force:
            raise ValueError("output already exists; choose a new path or explicitly use --force")
    if args.command == "encode":
        data = encode(args.input.read_text(encoding="utf-8-sig"), args.stock_data)
        args.output.write_bytes(data)
        print(f"encoded bytes={len(data)} sha256={hashlib.sha256(data).hexdigest()}")
        return 0
    data = args.input.read_bytes()
    text = dumps(data, args.stock_data, args.opaque)
    warnings = [record.warning for record in decode(data, args.stock_data, args.opaque) if record.warning]
    for warning in warnings:
        print("WARNING: " + warning, file=sys.stderr)
    if args.require_complete and warnings:
        raise ValueError("undecoded remainder: completeness required")
    encoded = encode(text, args.stock_data)
    if encoded != data:
        raise AssertionError("dump/encode changed input bytes")
    if args.command == "dump":
        args.output.write_text(text, encoding="utf-8", newline="")
    print(f"roundtrip=identical bytes={len(data)} records={len(decode(data, args.stock_data, args.opaque))} "
          f"opaque_remainders={len(warnings)} sha256={hashlib.sha256(data).hexdigest()}")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (ValueError, OSError, struct.error) as error:
        raise SystemExit(f"stage_sub: {error}")
