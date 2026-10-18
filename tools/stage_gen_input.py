#!/usr/bin/env python3
"""Lossless, routine-scoped SHC GEN input editor (stage-2 optimized ILB).

dump SNAPSHOT --function NAME --out PACKET
encode PACKET --out SNAPSHOT
encode PACKET --out SNAPSHOT --ilb-records PACKET/ilb_records.tsv

Edit the value column of fields.tsv. ILB order/deletion uses ilb_order.txt.
Original files are immutable sidecars.
For ILB node insertion or payload-shape changes, edit ilb_records.tsv and pass
--ilb-records explicitly. Each contiguous record group is one complete typed
node. Names may be cloned to new unique record IDs. The entire module is parsed
again and every supplied field must agree with the native serialization grammar.
All numeric serialization is little endian. V1 deliberately preserves field and
record layouts; counts, type changes and opcodes must still parse identically.
No compiler is invoked. CMN relocation belongs to the staged runner.
For unknown grammar, dump --opaque preserves the entire boundary without
claiming routine selection or exposing guessed semantic fields.

Grammar: shcgen read_ilb_node/read_symbol_table/read_reg_file_lreg_table,
and the retained r28 ilb_tree_reader.py/r29 read_symbols.py decoders.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import json
from pathlib import Path
import re
import struct

ROOT = Path(__file__).resolve().parents[1]
UNTYPED = {0, 1, 9, 15, 18, 20, 22, 23, 25, 26, 111, 120, 121}
SYMBOL = {4, 8, 16, 27, 28, 29, 30, 112}
FR0 = {80, 81, 84, 86, 95, 108}
TYPED = {24, 32, 36, 37, 40, 41, 44, 45, 64, 65, 68, 70, 71, 72,
         73, 76, 77, 78, 80, 81, 84, 86, 87, 88, 89, 92, 93, 94,
         95, 96, 97, 100, 101, 102, 103, 104, 105, 108, 127}
FORMATS = {"u8": "B", "s8": "b", "u16": "H", "s16": "h", "u32": "I"}
COLUMNS = ["file", "record", "offset", "field", "type", "value", "annotation"]


def stock_tables():
    source = (ROOT / "rebuild/shcmdl/src/_stockdata.c").read_text()
    body = source.split("= {", 1)[1].split("};", 1)[0]
    raw = bytes(int(s, 16) for s in re.findall(r"0x([0-9a-fA-F]{2})\b", body))
    if len(raw) != 0x28468:
        raise ValueError("unexpected MDL stock-data size")
    arity = struct.unpack_from("<128h", raw, 0x14f8)
    source = (ROOT / "rebuild/shcgen/include/stage_types.h").read_text()
    names = {int(v, 16): k for k, v in re.findall(r"\b(IL_\w+)\s*=\s*(0x[0-9a-fA-F]+)", source)}
    return arity, names


class Reader:
    def __init__(self, data, filename):
        self.data, self.filename, self.pos = data, filename, 0
        self.fields = []
        self.record = ""

    def get(self, name, kind):
        size = int(kind[7:]) if kind.startswith("latin1:") else struct.calcsize(FORMATS[kind])
        if self.pos + size > len(self.data):
            raise ValueError(f"{self.filename}: truncated {name} at {self.pos}")
        raw = self.data[self.pos:self.pos + size]
        value = raw.decode("latin1") if kind.startswith("latin1:") else struct.unpack("<" + FORMATS[kind], raw)[0]
        self.fields.append(dict(file=self.filename, record=self.record, offset=self.pos,
                                field=name, type=kind, value=value, annotation=""))
        self.pos += size
        return value

    def count(self, name, kind):
        value = self.get(name, kind)
        if value < 0:
            raise ValueError(f"negative {name}: {value}")
        return value


def parse_ilb(data, filename, arity):
    r, nodes, stack = Reader(data, filename), [], []
    while r.pos < len(data):
        start = r.pos
        r.record = f"node:{len(nodes)}"
        op = r.get("op", "u8")
        n = dict(index=len(nodes), offset=start, op=op, parent=-1, children=[], funcsym=0, sym=0, lreg=0)

        def typed():
            t = r.get("type", "u8")
            n["type"] = t
            if t & 0xe0 in (0x60, 0x80):
                n["aggregate_size"] = r.get("aggregate_size", "u32")
            return t

        if op in UNTYPED:
            pass
        elif op in SYMBOL:
            n["sym"] = r.get("sym", "s16")
        elif op == 5:
            r.get("val", "u32"); r.get("val2", "u32")
        elif op == 48:
            typed(); r.get("call_extra", "u8"); r.get("call_flags", "u8")
        elif op in (52, 53):
            typed(); r.get("val2", "u32")
            if op == 53:
                r.get("bit_offset", "u8"); r.get("bit_width", "u8")
        elif op in (56, 57, 60, 61):
            typed(); r.get("val", "u32")
        elif op == 113:
            t = typed()
            if t & 0xe0 == 0x40:
                n["lreg"] = r.get("pointer_lreg", "s16")
            r.get("val", "u32")
            if t & 0xf8 in (0x30, 0x38):
                r.get("val2", "u32")
            if t & 0xf8 == 0x38:
                r.get("val3", "u32")
        elif op in TYPED:
            typed()
        else:
            raise ValueError(f"unsupported ILB op {op:02x} at {start}")
        r.get("filn", "s16"); n["line"] = r.get("line", "u16"); r.get("listno", "s16")
        if op == 112:
            n["lreg"] = r.get("lreg", "s16")
        if op in (8, 9):
            r.get("block_flag", "u8")
        if op == 112 or op in FR0:
            r.get("fr0", "u8")
        while stack and stack[-1][1] == 0:
            stack.pop()
        if stack:
            p = nodes[stack[-1][0]]
            n["parent"], n["funcsym"] = p["index"], p["funcsym"]
            p["children"].append(n["index"])
            if stack[-1][1] > 0:
                stack[-1][1] -= 1
            if (p["op"], op) in ((8, 9), (120, 121)):
                stack[-1][1] = 0
        if op == 4:
            n["funcsym"] = n["sym"]
        n["end"] = r.pos
        nodes.append(n)
        if op >= len(arity) or arity[op] < 0 and op not in (8, 120):
            raise ValueError(f"unsupported arity for {op}")
        if arity[op]:
            stack.append([n["index"], arity[op]])
    while stack and stack[-1][1] == 0:
        stack.pop()
    if stack:
        raise ValueError(f"incomplete ILB tree: {stack[-5:]}")
    return r.fields, nodes


def parse_reg(data, filename):
    r, records = Reader(data, filename), []
    while r.pos < len(data):
        start = r.pos
        r.record = f"function:{len(records)}"
        fn = r.get("function_sym", "s16")
        r.get("flag", "u8"); r.get("no_ranges", "u8")
        syms, lregs, i = [], [], 0
        while True:
            prefix = f"lreg[{i}]."
            lreg = r.get(prefix + "id", "s16")
            if not lreg:
                break
            lregs.append(lreg)
            r.get(prefix + "preg", "s16"); r.get(prefix + "type", "u8")
            for j in range(r.count(prefix + "symbol_count", "u16")):
                syms.append(r.get(prefix + f"symbols[{j}]", "s16"))
            for j in range(r.count(prefix + "range_count", "s16")):
                r.get(prefix + f"ranges[{j}].start", "u32")
                r.get(prefix + f"ranges[{j}].end", "u32")
            i += 1
        trailer = r.get("trailer_sym", "s16")
        if trailer != fn:
            raise ValueError(f"REG function header/trailer mismatch at {start}")
        records.append(dict(record=r.record, sym=fn, refs=syms, lregs=lregs, offset=start, end=r.pos))
    return r.fields, records


def parse_sym(data, filename):
    r, records = Reader(data, filename), []
    while r.pos < len(data):
        start = r.pos
        r.record = f"symbol:{len(records)}"
        sym = r.get("sym", "s16")
        sc = r.get("sclass", "u8")
        if sc in (3, 4, 9, 11):
            r.get("skipped", "s16")
        length = r.get("name_length", "u8")
        name = r.get("name", f"latin1:{length}")
        ty = r.get("type", "u8")
        if ty & 0xe0 in (0x60, 0x80):
            r.get("size", "u32")
        r.get("byte03", "u8"); flags = r.get("flags", "u8")
        r.get("attr", "u8"); r.get("short06", "u16"); r.get("reg", "s8")
        refs = []
        if ty & 0xf8 == 0x48 and sc in (1, 3):
            ret = r.get("ret_type", "u8")
            if ret & 0xe0 == 0x60:
                r.get("ret_size", "u32")
            r.get("ret19", "u8")
            for j in range(r.count("parameter_count", "u8")):
                refs.append(r.get(f"params[{j}].sym", "s16"))
                r.get(f"params[{j}].flag", "u8")
            for j in range(r.count("scope_count", "s16")):
                refs.append(r.get(f"scopes[{j}]", "s16"))
            if flags & 0x10:
                ext = r.get("extension_flags", "u8")
                if ext & 2:
                    v = r.get("extension_value", "s16" if ext & 4 else "u32")
                    if ext & 4:
                        refs.append(v)
                if ext & 1:
                    r.get("extension_value2", "u32")
        if sc == 10:
            for j in range(r.count("child_count", "s16")):
                refs.append(r.get(f"children[{j}]", "s16"))
            for j in range(r.count("member_count", "s16")):
                refs.append(r.get(f"members[{j}].sym", "s16"))
                r.get(f"members[{j}].flag", "u8")
        elif sc == 9:
            r.get("other", "u32")
        records.append(dict(record=r.record, sym=sym, name=name, refs=refs, offset=start, end=r.pos))
    return r.fields, records


def one(files, suffix, required=True):
    found = [n for n in files if Path(n).suffix.lower() == suffix]
    if not found and not required:
        return None
    if len(found) != 1:
        raise ValueError(f"expected one {suffix} file, found {found}")
    return found[0]


def decode(files, function):
    arity, names = stock_tables()
    ilb, sym, reg = one(files, ".ilb"), one(files, ".sym"), one(files, ".reg", False)
    sf, symbols = parse_sym(files[sym], sym)
    matches = [s for s in symbols if s["name"] == function]
    if len(matches) != 1:
        raise ValueError(f"function name has {len(matches)} symbols: {function}")
    fn = matches[0]["sym"]
    nf, nodes = parse_ilb(files[ilb], ilb, arity)
    selected_nodes = [n for n in nodes if n["funcsym"] == fn]
    if not selected_nodes:
        raise ValueError(f"no ILB routine for symbol {fn}")
    rf, registers = parse_reg(files[reg], reg) if reg else ([], [])
    selected_regs = [r for r in registers if r["sym"] == fn]
    wanted = {fn} | {n["sym"] for n in selected_nodes if n["sym"]}
    for record in selected_regs:
        wanted.update(record["refs"])
    bysym = {s["sym"]: s for s in symbols}
    pending = list(wanted)
    while pending:
        for ref in bysym.get(pending.pop(), {}).get("refs", []):
            if ref not in wanted:
                wanted.add(ref); pending.append(ref)
    selected_symbols = [s for s in symbols if s["sym"] in wanted]
    nrecs = {f"node:{n['index']}": n for n in selected_nodes}
    srecs = {s["record"]: s for s in selected_symbols}
    rrecs = {r["record"]: r for r in selected_regs}
    fields = []
    for collection, selected in ((nf, nrecs), (rf, rrecs), (sf, srecs)):
        for f in collection:
            if f["record"] not in selected:
                continue
            item = selected[f["record"]]
            if collection is nf:
                label = bysym.get(item["sym"], {}).get("name", "")
                f["annotation"] = f"{names.get(item['op'], str(item['op']))} line={item['line']} parent={item['parent']} children={item['children']} sym={label}"
            else:
                f["annotation"] = f"sym={item['sym']} name={item.get('name', function)}"
            fields.append(f)
    meta = dict(sym=fn, nodes=selected_nodes, symbols=selected_symbols, registers=selected_regs)
    return fields, meta


def sha(data):
    return hashlib.sha256(data).hexdigest()


def write_tsv(path, columns, rows):
    with path.open("w", encoding="utf8", newline="") as f:
        writer = csv.DictWriter(f, columns, delimiter="\t", lineterminator="\n")
        writer.writeheader(); writer.writerows(rows)


def read_tsv(path):
    with path.open(encoding="utf8", newline="") as f:
        return list(csv.DictReader(f, delimiter="\t"))


def dump(snapshot, function, out, opaque=False):
    if out.exists():
        raise ValueError(f"output already exists: {out}")
    entries = sorted(snapshot.iterdir())
    if any(p.is_symlink() or not p.is_file() for p in entries):
        raise ValueError("snapshot must contain only regular files; directories/symlinks are not silently omitted")
    files = {p.name: p.read_bytes() for p in entries}
    for suffix in (".cmn", ".ilb", ".sym", ".swi", ".int"):
        one(files, suffix)
    fields, meta = ([], None) if opaque else decode(files, function)
    (out / "original").mkdir(parents=True)
    for name, data in files.items():
        (out / "original" / name).write_bytes(data)
    write_tsv(out / "FILES.tsv", ["name", "bytes", "sha256"],
              [dict(name=n, bytes=len(d), sha256=sha(d)) for n, d in files.items()])
    write_tsv(out / "fields.tsv", COLUMNS,
              [dict(f, value=json.dumps(f["value"], ensure_ascii=True)) for f in fields])
    (out / "function.txt").write_text(function + "\n", encoding="utf8")
    (out / "mode.txt").write_text("opaque\n" if opaque else "records\n", encoding="utf8")
    if opaque:
        (out / "ilb_order.txt").write_text("", encoding="utf8")
        (out / "routine.txt").write_text("OPAQUE boundary: all complete files preserved. No routine selection or semantic fields decoded.\n", encoding="utf8")
        print(f"dumped OPAQUE boundary: {len(files)} complete sidecars -> {out}")
        return
    (out / "ilb_order.txt").write_text("".join(f"node:{n['index']}\n" for n in meta["nodes"]), encoding="utf8")
    write_tsv(out / "ilb_records.tsv", ["record", "field", "type", "value"],
              [dict(record=f["record"], field=f["field"], type=f["type"], value=json.dumps(f["value"]))
               for f in fields if Path(f["file"]).suffix.lower() == ".ilb"])
    _, names = stock_tables()
    bysym = {s["sym"]: s["name"] for s in meta["symbols"]}
    lines = [f"GEN INPUT v1 function={function} symbol={meta['sym']}",
             "Edit fields.tsv value cells. Scalar edits must preserve record layouts/counts.",
             "ILB reorder/delete: edit ilb_order.txt; use each original selected node at most once. Result must parse as a complete tree.",
             "ILB insert/clone/shape change: edit ilb_records.tsv and encode --ilb-records FILE; leave ILB fields.tsv values/order unchanged.",
             "ILA is preserved upstream; GEN reads ILB. Integers are serialized little endian.",
             "SYM records can be shared with other routines; edits to shared symbols affect the whole module.",
             f"nodes={len(meta['nodes'])} symbols={len(meta['symbols'])} reg_functions={len(meta['registers'])} fields={len(fields)}"]
    for n in meta["nodes"]:
        lines.append(f"node:{n['index']} @{n['offset']}..{n['end']} {names.get(n['op'], n['op'])} line={n['line']} parent={n['parent']} children={n['children']} sym={n['sym']}:{bysym.get(n['sym'], '')} lreg={n['lreg']}")
    (out / "routine.txt").write_text("\n".join(lines) + "\n", encoding="utf8")
    print(f"dumped {function}: {len(fields)} fields, {len(files)} complete sidecars -> {out}")


def key(field):
    return tuple(str(field[c]) for c in ("file", "record", "offset", "field", "type"))


def pack_value(kind, value):
    if kind.startswith("latin1:"):
        if not isinstance(value, str):
            raise ValueError("expected string")
        raw = value.encode("latin1")
        if len(raw) != int(kind[7:]):
            raise ValueError("string length edits change layout")
        return raw
    if type(value) is not int:
        raise ValueError("expected integer")
    return struct.pack("<" + FORMATS[kind], value)


def replace_ilb_records(files, function, meta, table):
    rows = read_tsv(table)
    groups, seen = [], set()
    for row in rows:
        if set(row) != {"record", "field", "type", "value"}:
            raise ValueError("ILB records need record/field/type/value columns")
        ident = row["record"]
        if not groups or groups[-1][0] != ident:
            if ident in seen or not ident:
                raise ValueError("ILB record groups must be contiguous and uniquely named")
            seen.add(ident); groups.append((ident, []))
        value = json.loads(row["value"])
        groups[-1][1].append((row["field"], row["type"], value))
    if not groups:
        raise ValueError("ILB function cannot be empty")
    raw_groups = [b"".join(pack_value(kind, value) for _, kind, value in fields) for _, fields in groups]
    ilb = one(files, ".ilb")
    nodes = meta["nodes"]
    start, end = nodes[0]["offset"], nodes[-1]["end"]
    if any(a["end"] != b["offset"] for a, b in zip(nodes, nodes[1:])):
        raise ValueError("selected routine is not contiguous")
    candidate = dict(files)
    candidate[ilb] = files[ilb][:start] + b"".join(raw_groups) + files[ilb][end:]
    new_fields, new_meta = decode(candidate, function)
    if len(new_meta["nodes"]) != len(groups) or sum(n["op"] == 4 for n in new_meta["nodes"]) != 1:
        raise ValueError("ILB records change routine identity or boundary")
    byrecord = {}
    for field in new_fields:
        if field["file"] == ilb:
            byrecord.setdefault(field["record"], []).append((field["field"], field["type"], field["value"]))
    if list(byrecord.values()) != [fields for _, fields in groups]:
        raise ValueError("ILB typed record fields disagree with serialization grammar")
    if [n["end"]-n["offset"] for n in new_meta["nodes"]] != list(map(len, raw_groups)):
        raise ValueError("ILB serialized record boundaries differ")
    return candidate[ilb]


def encode(packet, out, ilb_records=None):
    if out.exists():
        raise ValueError(f"output already exists: {out}")
    files = {}
    for row in read_tsv(packet / "FILES.tsv"):
        name = row["name"]
        if Path(name).name != name or name in files:
            raise ValueError(f"invalid or duplicate sidecar name: {name}")
        data = (packet / "original" / name).read_bytes()
        if str(len(data)) != row["bytes"] or sha(data) != row["sha256"]:
            raise ValueError(f"modified original sidecar: {name}")
        files[name] = data
    function = (packet / "function.txt").read_text(encoding="utf8").strip()
    mode_path = packet / "mode.txt"
    mode = mode_path.read_text(encoding="utf8").strip() if mode_path.exists() else "records"
    if mode not in ("records", "opaque"):
        raise ValueError("unknown packet mode")
    if mode == "opaque":
        if ilb_records or read_tsv(packet / "fields.tsv") or (packet / "ilb_order.txt").read_text().strip():
            raise ValueError("opaque packet cannot claim semantic field or node edits")
        out.mkdir(parents=True)
        for name, data in files.items():
            (out / name).write_bytes(data)
        write_tsv(out / "ENCODED.tsv", ["name", "bytes", "sha256", "unchanged"],
                  [dict(name=n, bytes=len(d), sha256=sha(d), unchanged=1) for n, d in files.items()])
        print(f"encoded OPAQUE boundary: {len(files)} unchanged files -> {out}")
        return
    original, original_meta = decode(files, function)
    edited = read_tsv(packet / "fields.tsv")
    if [key(f) for f in edited] != [key(f) for f in original]:
        raise ValueError("field identity/order changed; edit only value cells")
    updated = {n: bytearray(d) for n, d in files.items()}
    changes = []
    values = []
    for old, row in zip(original, edited):
        value = json.loads(row["value"])
        kind = old["type"]
        raw = pack_value(kind, value)
        if ilb_records and Path(old["file"]).suffix.lower() == ".ilb" and value != old["value"]:
            raise ValueError("--ilb-records owns ILB edits; leave ILB fields.tsv values unchanged")
        start = old["offset"]
        updated[old["file"]][start:start + len(raw)] = raw
        values.append(value)
        if value != old["value"]:
            changes.append(dict(file=old["file"], offset=start, field=old["field"], old=repr(old["value"]), new=repr(value)))
    new_fields, _ = decode(updated, function)
    if [key(f) for f in new_fields] != [key(f) for f in original]:
        raise ValueError("edit changes selected record layout, scope, or identity")
    if [f["value"] for f in new_fields] != values:
        raise ValueError("encoded field readback differs")
    # Same field layout is not enough if an opcode changes tree arity.
    arity, _ = stock_tables()
    for old, new in zip(original, new_fields):
        if old["field"] == "op" and arity[old["value"]] != arity[new["value"]]:
            raise ValueError("opcode edit changes tree arity")
    nodes = original_meta["nodes"]
    sequence = [line.strip() for line in (packet / "ilb_order.txt").read_text(encoding="utf8").splitlines() if line.strip()]
    node_map = {f"node:{n['index']}": n for n in nodes}
    if len(sequence) != len(set(sequence)) or set(sequence) - node_map.keys():
        raise ValueError("ILB order contains duplicate or nonselected node")
    original_sequence = list(node_map)
    if ilb_records and sequence != original_sequence:
        raise ValueError("--ilb-records owns ILB order; leave ilb_order.txt unchanged")
    if ilb_records:
        ilb = one(updated, ".ilb")
        old = updated[ilb]
        updated[ilb] = replace_ilb_records(updated, function, original_meta, ilb_records)
        if updated[ilb] != old:
            changes.append(dict(file=ilb, offset=nodes[0]["offset"], field="ILB typed records", old=sha(old), new=sha(updated[ilb])))
    if sequence != original_sequence:
        ilb = one(updated, ".ilb")
        if any(a["end"] != b["offset"] for a, b in zip(nodes, nodes[1:])):
            raise ValueError("selected routine is not contiguous")
        data = updated[ilb]
        start, end = nodes[0]["offset"], nodes[-1]["end"]
        body = b"".join(data[node_map[k]["offset"]:node_map[k]["end"]] for k in sequence)
        updated[ilb] = data[:start] + body + data[end:]
        # Reparse the entire module, including all following functions.
        _, structural_meta = decode(updated, function)
        if len(structural_meta["nodes"]) != len(sequence):
            raise ValueError("ILB edit moves nodes across the routine boundary")
        changes.append(dict(file=ilb, offset=start, field="ILB node order", old=repr(original_sequence), new=repr(sequence)))
    out.mkdir(parents=True)
    for name, data in updated.items():
        (out / name).write_bytes(data)
    write_tsv(out / "CHANGES.tsv", ["file", "offset", "field", "old", "new"], changes)
    write_tsv(out / "ENCODED.tsv", ["name", "bytes", "sha256", "unchanged"],
              [dict(name=n, bytes=len(d), sha256=sha(d), unchanged=int(d == files[n])) for n, d in updated.items()])
    print(f"encoded {len(updated)} files, {len(changes)} typed field changes -> {out}")


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="command", required=True)
    d = sub.add_parser("dump"); d.add_argument("snapshot", type=Path)
    d.add_argument("--function", required=True); d.add_argument("--out", type=Path, required=True)
    d.add_argument("--opaque", action="store_true", help="preserve unknown boundary grammar without semantic decoding")
    e = sub.add_parser("encode"); e.add_argument("packet", type=Path)
    e.add_argument("--out", type=Path, required=True)
    e.add_argument("--ilb-records", type=Path, help="replacement routine typed node table; permits insertion, deletion and shape edits")
    a = p.parse_args()
    try:
        if a.command == "dump":
            dump(a.snapshot, a.function, a.out, a.opaque)
        else:
            encode(a.packet, a.out, a.ilb_records)
    except (ValueError, KeyError, struct.error, UnicodeError, OSError) as exc:
        p.exit(2, f"error: {exc}\n")


if __name__ == "__main__":
    main()
