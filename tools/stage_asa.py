#!/usr/bin/env python3
"""Lossless, editable SHC GEN symbol/auxiliary (.asa) stream.

Schema follows shcpep/00409d30_load_symbol_aux_record_stream.c. No compiler
policy is applied. Every serialized byte, including unused bits and bytes after
END, is represented. Offsets are within each record; complete record blocks may
move, but fields must remain contiguous inside each block. Count fields are explicit.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import io
import re
import struct
from dataclasses import dataclass
from pathlib import Path


MAGIC = "# stage-asa-v1"
HEADER = ["record", "offset", "field", "type", "value"]
FORMATS = {"u8": "B", "i8": "b", "u16": "H", "u32": "I"}
NAMES = {0: "ZERO", 6: "BREAK", 12: "AUX", 13: "END", 14: "EXTRA"}


class AsaError(ValueError):
    pass


@dataclass(frozen=True)
class Atom:
    record: int
    offset: int
    field: str
    kind: str
    value: int | bytes

    def packed(self) -> bytes:
        if self.kind in FORMATS:
            try:
                return struct.pack("<" + FORMATS[self.kind], self.value)
            except (struct.error, TypeError) as exc:
                raise AsaError(f"{self.field}: {self.value!r} outside {self.kind}") from exc
        if self.kind in ("hex", "latin1") and isinstance(self.value, bytes):
            return self.value
        raise AsaError(f"unknown atom type {self.kind!r}")


def escaped(data: bytes) -> str:
    return "".join(chr(b) if 32 <= b <= 126 and b != 92 else f"\\x{b:02x}" for b in data)


def unescaped(text: str) -> bytes:
    out = bytearray()
    i = 0
    while i < len(text):
        if text[i] == "\\":
            if not re.fullmatch(r"\\x[0-9a-fA-F]{2}", text[i:i + 4]):
                raise AsaError("Latin-1 text uses only \\xHH escapes")
            out.append(int(text[i + 2:i + 4], 16))
            i += 4
        else:
            if not 32 <= ord(text[i]) <= 126:
                raise AsaError("non-ASCII name byte must be written as \\xHH")
            out.append(ord(text[i]))
            i += 1
    return bytes(out)


def parse(data: bytes) -> list[Atom]:
    atoms: list[Atom] = []
    pos = 0
    record = 0
    record_start = 0

    def take(field: str, kind: str, size: int | None = None):
        nonlocal pos
        if kind in FORMATS:
            size = struct.calcsize(FORMATS[kind])
        assert size is not None
        if pos + size > len(data):
            raise AsaError(f"truncated record {record} field {field} at {pos:#x}: needs {size} bytes")
        raw = data[pos:pos + size]
        value = struct.unpack("<" + FORMATS[kind], raw)[0] if kind in FORMATS else raw
        atoms.append(Atom(record, pos - record_start, field, kind, value))
        pos += size
        return value

    def name():
        size = take("name_length", "u8")
        take("name", "latin1", size)

    ended = False
    while pos < len(data):
        record += 1
        record_start = pos
        tag = take("tag", "u8")
        typ = tag & 31
        if typ in (0, 6):
            pass
        elif 1 <= typ <= 11:
            take("symbol", "u16")
            take("header_word", "u16")
            take("value", "u32")
            if typ > 4:
                name()
            if typ > 6:
                take("attr", "u8")
                take("attr2", "u8")
        elif typ == 12:
            take("symbol", "u16")
            take("aux_00", "u32")
            take("max_stack", "u32")
            take("sp_adjust", "u32")
            take("saved_regs2", "u16")
            take("saved_regs", "u16")
            take("saved_mac", "u8")
            take("saved_sys", "u8")
            count = take("range_count", "u8")
            for n in range(count):
                take(f"range[{n}].before_reg", "i8")
                take(f"range[{n}].after_reg", "i8")
                take(f"range[{n}].start_expno", "u32")
                take(f"range[{n}].end_expno", "u32")
            take("flags16", "u16")
            opt1 = take("opt1", "u8")
            if opt1 & 128:
                # The reader consumes four bytes for supported opt1 modes 0,1,3.
                if opt1 & 3 == 2:
                    raise AsaError(f"unsupported opt1 mode2 at record {record}")
                take("opt1_arg", "u32")
            opt2 = take("opt2", "u8")
            if opt2 & 128:
                take("opt2_arg", "u8")
            name()
            take("asb_word", "u32")
            take("attr", "u8")
            take("asb_bytes", "hex", 23)
            take("reg28", "u8")
        elif typ == 13:
            take("last_label", "u16")
            ended = True
            if pos < len(data):
                record += 1
                record_start = pos
                take("trailing_bytes", "hex", len(data) - pos)
            break
        elif typ == 14:
            take("trailer_value1", "u16")
            take("trailer_value2", "u16")
            take("trailer_bytes", "hex", 32)
        else:
            raise AsaError(f"unknown ASA record type {typ} at {pos - 1:#x}")
    if not ended:
        raise AsaError("missing ASA END record")
    return atoms


def dumps(data: bytes, opaque: bool = False) -> str:
    atoms = [Atom(1, 0, "opaque_bytes", "hex", data)] if opaque else parse(data)
    out = io.StringIO(newline="")
    out.write(MAGIC + "\n")
    out.write("# mode=" + ("opaque" if opaque else "records") + "\n")
    out.write(f"# bytes={len(data)} sha256={hashlib.sha256(data).hexdigest()}\n")
    writer = csv.writer(out, delimiter="\t", lineterminator="\n")
    writer.writerow(HEADER)
    last = 0
    absolute = 0
    for atom in atoms:
        if atom.record != last:
            if atom.field == "tag":
                typ = atom.value & 31
                name = NAMES.get(typ, f"SYM{typ}")
                out.write(f"# record={atom.record} original_offset={absolute:#x} {name} tag={atom.value:#04x}\n")
            elif atom.field == "trailing_bytes":
                out.write(f"# record={atom.record} trailing bytes after END\n")
            else:
                out.write(f"# record={atom.record} opaque stream; no semantic decoding claimed\n")
            last = atom.record
        value = atom.value
        if atom.kind == "hex":
            value = value.hex()
        elif atom.kind == "latin1":
            value = escaped(value)
        elif atom.field in ("tag", "flags16", "attr", "attr2", "opt1", "opt2"):
            value = hex(value)
        writer.writerow([atom.record, hex(atom.offset), atom.field, atom.kind, value])
        absolute += len(atom.packed())
    return out.getvalue()


def encode(text: str) -> bytes:
    if not text.splitlines() or text.splitlines()[0] != MAGIC:
        raise AsaError("missing stage-asa-v1 header")
    modes = [line for line in text.splitlines() if line.startswith("# mode=")]
    if len(modes) > 1 or modes and modes[0] not in ("# mode=records", "# mode=opaque"):
        raise AsaError("unsupported or duplicate dump mode")
    opaque = modes == ["# mode=opaque"]
    reader = csv.reader((line for line in text.splitlines() if line and not line.startswith("#")), delimiter="\t")
    if next(reader, None) != HEADER:
        raise AsaError("unexpected TSV column header")
    atoms = []
    seen = set()
    record = None
    offset = 0
    for row in reader:
        if len(row) != 5:
            raise AsaError(f"expected five columns, got {len(row)}")
        rid, off, field, kind, value = row
        try:
            rid, off = int(rid), int(off, 0)
            if kind in FORMATS:
                value = int(value, 0)
            elif kind == "hex":
                value = bytes.fromhex(value)
            elif kind == "latin1":
                value = unescaped(value)
            else:
                raise AsaError(f"unknown atom type {kind!r}")
        except ValueError as exc:
            raise AsaError(f"invalid field {field}: {exc}") from exc
        if rid <= 0 or off < 0:
            raise AsaError("record IDs must be positive and offsets nonnegative")
        if rid != record:
            if rid in seen:
                raise AsaError(f"record {rid} appears in multiple blocks")
            seen.add(rid)
            record, offset = rid, 0
        if off != offset:
            raise AsaError(f"noncontiguous offset in record {rid}: {off:#x}, expected {offset:#x}")
        atom = Atom(rid, off, field, kind, value)
        offset += len(atom.packed())
        atoms.append(atom)
    binary = b"".join(atom.packed() for atom in atoms)
    if opaque:
        if len(atoms) != 1 or atoms[0].field != "opaque_bytes" or atoms[0].kind != "hex":
            raise AsaError("opaque mode requires exactly one opaque_bytes hex atom")
        return binary
    actual = parse(binary)
    # Parsing alone is insufficient: a wrong count could reinterpret following
    # bytes as plausible fields. Require every semantic field boundary to agree.
    expected_fields = [(a.field, a.kind, a.value) for a in atoms]
    actual_fields = [(a.field, a.kind, a.value) for a in actual]
    expected_groups = [i for i, a in enumerate(atoms) if i == 0 or a.record != atoms[i - 1].record]
    actual_groups = [i for i, a in enumerate(actual) if i == 0 or a.record != actual[i - 1].record]
    if expected_fields != actual_fields or expected_groups != actual_groups:
        raise AsaError("field layout disagrees with ASA grammar; check tags, lengths, range counts and optional fields")
    return binary


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    for verb in ("dump", "encode"):
        cmd = sub.add_parser(verb)
        cmd.add_argument("input", type=Path)
        cmd.add_argument("output", type=Path)
        if verb == "dump":
            cmd.add_argument("--opaque", action="store_true", help="preserve an unsupported stream as exact opaque bytes")
    args = parser.parse_args(argv)
    try:
        if args.input.resolve() == args.output.resolve():
            raise AsaError("input and output must differ")
        if args.command == "dump":
            data = dumps(args.input.read_bytes(), opaque=args.opaque)
            args.output.write_text(data, encoding="utf-8", newline="\n")
        else:
            args.output.write_bytes(encode(args.input.read_text(encoding="utf-8")))
    except (AsaError, OSError) as exc:
        parser.exit(2, f"stage_asa: {exc}\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
