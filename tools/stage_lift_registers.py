#!/usr/bin/env python3
"""Conservatively lift a typed SUB GPR edit to GEN-output SUA.

An original record must have identical opcode, operands, labels, raw flags and
file/line/expression provenance in SUA, under the same FLABEL. Both sides must
contain exactly one such record. No occurrence-order guess, opcode conversion,
flag normalization, label remap or expanded-record inference is attempted.

The helper checks serialization, not semantic equivalence. Run unchanged PEP
and ASM, then compare the complete native object with the validated SUB witness.
Unknown/ambiguous/expanded records fail closed; no partial SUA patch is emitted.
"""
from __future__ import annotations

import argparse
from collections import defaultdict
import csv
import hashlib
import importlib
from pathlib import Path
import re
import struct
import sys

REGISTER = re.compile(r"(?:ea[12]\.(?:base|base_index_packed)|destination|source|destination_tmp_packed|tmp|register)\Z")
MAPPING_COLUMNS = ["sub_record", "sua_record", "function_symbol", "function_name", "opcode",
                   "field", "type", "old", "new", "file", "line", "expression",
                   "sub_offset", "sua_offset"]


class LiftError(ValueError):
    pass


def values(record):
    return {field.name: field.value for field in record.fields}


def signature(record):
    return (record.name, record.format,
            tuple((f.offset, f.name, f.kind, f.value) for f in record.fields))


def scopes(records):
    result = {}
    function = None
    seen = set()
    for record in records:
        if record.warning:
            raise LiftError(f"undecoded record {record.index}: {record.warning}")
        if record.name == "FLABEL":
            function = values(record).get("raw_ea1")
            if not isinstance(function, int) or function in seen:
                raise LiftError(f"missing or repeated FLABEL identity at record {record.index}")
            seen.add(function)
        result[record.index] = function
    return result


def changed_fields(original, edited):
    if len(original) != len(edited):
        raise LiftError("SUB record insertion/deletion is not a register-only edit")
    changes = []
    for a, b in zip(original, edited):
        if (a.index, a.offset, a.name, a.format) != (b.index, b.offset, b.name, b.format):
            raise LiftError(f"SUB record identity/layout changed at {a.index}")
        shape_a = [(f.offset, f.name, f.kind) for f in a.fields]
        shape_b = [(f.offset, f.name, f.kind) for f in b.fields]
        if shape_a != shape_b:
            raise LiftError(f"SUB operand expansion/layout change at {a.index}")
        for old, new in zip(a.fields, b.fields):
            if old.value == new.value:
                continue
            if not REGISTER.fullmatch(old.name) or old.kind != "u8":
                raise LiftError(f"non-register field changed: record {a.index} {old.name}")
            payload = values(a)
            if old.name.startswith("ea"):
                prefix = old.name.split(".", 1)[0]
                kind = payload.get(prefix + ".type_raw", -1) & 0x1f
                allowed = {9} if old.name.endswith("base_index_packed") else {1, 2, 3, 4, 8}
                if kind not in allowed:
                    raise LiftError(f"not a supported GPR operand kind: record {a.index} {old.name} kind={kind}")
            else:
                opcodes = {"tmp": {0x23, 0x24, 0x25, 0x26, 0x27, 0x2c},
                           "register": {0x27, 0x30, 0x31}, "source": {0x2e},
                           "destination": {0x28, 0x29, 0x2a, 0x2c, 0x2e},
                           "destination_tmp_packed": {0x2b}}
                if payload.get("opcode") not in opcodes[old.name]:
                    raise LiftError(f"unsupported pseudo-register field: record {a.index} {old.name}")
            limit = 255 if old.name.endswith("packed") else 15
            if not (isinstance(old.value, int) and isinstance(new.value, int) and
                    0 <= old.value <= limit and 0 <= new.value <= limit):
                raise LiftError(f"not a GPR value: record {a.index} {old.name}")
            changes.append((a, old, new.value))
    return changes


def plan_records(original, edited, source, function_names):
    original_scope, source_scope = scopes(original), scopes(source)
    scopes(edited)
    changes = changed_fields(original, edited)
    sub_index, sua_index = defaultdict(list), defaultdict(list)
    for record in original:
        sub_index[(original_scope[record.index], signature(record))].append(record)
    for record in source:
        sua_index[(source_scope[record.index], signature(record))].append(record)
    mapping = []
    for record, field, new_value in changes:
        function = original_scope[record.index]
        if function is None or function not in function_names:
            raise LiftError(f"changed SUB record {record.index} lacks an ASA-named function")
        key = function, signature(record)
        sub_matches, sua_matches = sub_index[key], sua_index[key]
        if len(sub_matches) != 1 or len(sua_matches) != 1:
            raise LiftError(f"unresolved record {record.index} ({record.name}, function {function}): "
                            f"SUB candidates {[r.index for r in sub_matches]}, "
                            f"SUA candidates {[r.index for r in sua_matches]}; "
                            "missing, repeated or transformed record")
        match = sua_matches[0]
        provenance = values(record)
        mapping.append(dict(sub_record=record.index, sua_record=match.index,
                            function_symbol=function, function_name=function_names[function],
                            opcode=record.name, field=field.name, type=field.kind,
                            old=field.value, new=new_value, file=provenance.get("file", ""),
                            line=provenance.get("line", ""), expression=provenance.get("expression", ""),
                            sub_offset=record.offset + field.offset,
                            sua_offset=match.offset + field.offset))
    return mapping


def asa_function_names(atoms):
    groups = defaultdict(dict)
    for atom in atoms:
        groups[atom.record][atom.field] = atom.value
    names = {}
    for fields in groups.values():
        if fields.get("tag", 0) & 31 != 12:
            continue
        symbol, name = fields.get("symbol"), fields.get("name")
        if not isinstance(symbol, int) or not isinstance(name, bytes):
            raise LiftError("malformed ASA function AUX name")
        if symbol in names:
            raise LiftError(f"duplicate ASA AUX function symbol {symbol}")
        names[symbol] = name.decode("latin1")
    return names


def load_codecs(directory):
    directory = Path(directory).resolve()
    for name in ("stage_sub", "stage_sua", "stage_asa"):
        if not (directory / (name + ".py")).is_file():
            raise LiftError(f"missing codec {name} in {directory}; use --codec-dir")
    sys.path.insert(0, str(directory))
    try:
        modules = tuple(importlib.import_module(name) for name in ("stage_sub", "stage_sua", "stage_asa"))
        if any(Path(mod.__file__).resolve().parent != directory for mod in modules):
            raise LiftError("another codec directory is already imported in this process")
        return modules
    finally:
        sys.path.pop(0)


def lift(original_sub, edited_sub, original_sua, original_asa, codecs):
    sub, sua, asa = codecs
    original = sub.decode(original_sub)
    edited = sub.decode(edited_sub)
    source = sua.decode(original_sua)
    names = asa_function_names(asa.parse(original_asa))
    mapping = plan_records(original, edited, source, names)
    lifted = bytearray(original_sua)
    for row in mapping:
        if lifted[row["sua_offset"]] != row["old"]:
            raise LiftError("serialized register byte disagrees with typed source field")
        struct.pack_into("B", lifted, row["sua_offset"], row["new"])
    lifted = bytes(lifted)
    new_records = sua.decode(lifted)
    actual = changed_fields(source, new_records)
    wanted = [(m["sua_record"], m["field"], m["old"], m["new"]) for m in mapping]
    found = [(r.index, f.name, f.value, v) for r, f, v in actual]
    if sorted(wanted) != sorted(found):
        raise LiftError("typed SUA edit readback differs from mapping")
    text = sua.dumps(lifted)
    if sua.encode(text) != lifted:
        raise LiftError("lifted SUA codec roundtrip differs")
    return lifted, text, mapping


def write_tsv(path, columns, rows):
    with Path(path).open("w", encoding="utf8", newline="") as stream:
        writer = csv.DictWriter(stream, columns, delimiter="\t", lineterminator="\n")
        writer.writeheader(); writer.writerows(rows)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--sub-original", type=Path, required=True)
    parser.add_argument("--sub-edited", type=Path, required=True)
    parser.add_argument("--sua", type=Path, required=True)
    parser.add_argument("--asa", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True, help="fresh output directory")
    parser.add_argument("--codec-dir", type=Path, default=Path(__file__).resolve().parent)
    args = parser.parse_args(argv)
    if args.out.exists():
        parser.exit(2, "output already exists\n")
    try:
        paths = (args.sub_original, args.sub_edited, args.sua, args.asa)
        blobs = [path.read_bytes() for path in paths]
        codecs = load_codecs(args.codec_dir)
        lifted, text, mapping = lift(*blobs, codecs)
        args.out.mkdir(parents=True)
        (args.out / "lifted.sua").write_bytes(lifted)
        (args.out / "lifted.sua.tsv").write_text(text, encoding="utf8")
        write_tsv(args.out / "MAPPING.tsv", MAPPING_COLUMNS, mapping)
        write_tsv(args.out / "INPUTS.tsv", ["role", "path", "bytes", "sha256"],
                  [dict(role=role, path=str(path.resolve()), bytes=len(data), sha256=hashlib.sha256(data).hexdigest())
                   for role, path, data in zip(("original_sub", "edited_sub", "original_sua", "original_asa"), paths, blobs)])
        (args.out / "REPORT.txt").write_text(
            f"REGISTER LIFT SERIALIZATION PASS: {len(mapping)} fields across {len({r['sub_record'] for r in mapping})} records.\n"
            "Matching used exact original typed records and function identity, with uniqueness on both sides.\n"
            "All unrelated SUA bytes and the ASA input remain unchanged. No stage was executed by this helper.\n"
            "Unchanged PEP+ASM and full native-object comparison with the SUB witness remain required.\n", encoding="utf8")
        print(f"lifted {len(mapping)} register fields -> {args.out / 'lifted.sua'}; native validation required")
    except (ValueError, OSError, struct.error) as exc:
        parser.exit(2, f"unresolved: {exc}\n")


if __name__ == "__main__":
    main()
