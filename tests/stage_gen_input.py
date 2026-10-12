"""Portable codec tests; no compiler or retained capture is required."""
from pathlib import Path
import importlib.util
import struct
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("gen_input_codec", ROOT / "tools/stage_gen_input.py")
c = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(c)


def node(op, sym=None):
    return bytes([op]) + (struct.pack("<h", sym) if sym is not None else b"") + bytes(6) + (b"\1" if op in (8, 9) else b"")


def symbol(number, name, scope):
    raw = struct.pack("<hBB", number, 1, len(name)) + name.encode() + b"\x48" + bytes(5) + b"\xff"
    return raw + bytes([0x14, 0, 0]) + struct.pack("<hh", 1, scope)


def scope(number):
    return struct.pack("<hBB", number, 10, 0) + bytes(6) + b"\xff" + bytes(4)


class GenInputTests(unittest.TestCase):
    def setUp(self):
        # TMP/TEMP can point at the caller's private scratch directory.
        self.temp = tempfile.TemporaryDirectory(prefix="gen-input-test-")
        self.root = Path(self.temp.name)
        self.snapshot = self.root / "snapshot"
        self.snapshot.mkdir()
        self.first = node(4, 1) + node(8, 2) + node(27, 3) + node(28, 3) + node(15) + node(9)
        self.second = node(4, 4) + node(8, 5) + node(9)
        reg = struct.pack("<hBBhhBHhhIIhh", 1, 0, 0, 1, 4, 0x14, 1, 3, 1, 5, 6, 0, 1)
        files = {"unit.ilb": self.first + self.second,
                 "unit.sym": symbol(1, "demo", 2) + scope(2) + symbol(4, "other", 5) + scope(5),
                 "unit.reg": reg, "unit.cmn": b"opaque request", "unit.int": b"", "unit.swi": b"",
                 "unit.ila": b"upstream IL is opaque", "unknown.sidecar": b"\0\xffopaque\x80"}
        for name, data in files.items():
            (self.snapshot / name).write_bytes(data)
        self.packet = self.root / "packet"
        c.dump(self.snapshot, "demo", self.packet)

    def tearDown(self):
        self.temp.cleanup()

    def test_complete_roundtrip_with_unknown_sidecar_and_other_function(self):
        out = self.root / "out"
        c.encode(self.packet, out)
        for f in self.snapshot.iterdir():
            self.assertEqual(f.read_bytes(), (out / f.name).read_bytes(), f.name)

    def test_one_signed_typed_field_edit(self):
        rows = c.read_tsv(self.packet / "fields.tsv")
        row = next(r for r in rows if r["field"] == "lreg[0].preg")
        row["value"] = "-1"
        c.write_tsv(self.packet / "fields.tsv", c.COLUMNS, rows)
        out = self.root / "out"
        c.encode(self.packet, out)
        expected = bytearray((self.snapshot / "unit.reg").read_bytes())
        struct.pack_into("<h", expected, int(row["offset"]), -1)
        self.assertEqual(expected, (out / "unit.reg").read_bytes())
        self.assertEqual((out / "unit.ilb").read_bytes(), self.first + self.second)

    def test_structural_leaf_deletion_preserves_following_function(self):
        order = (self.packet / "ilb_order.txt").read_text().splitlines()
        order.remove("node:2")
        (self.packet / "ilb_order.txt").write_text("\n".join(order) + "\n")
        out = self.root / "out"
        c.encode(self.packet, out)
        expected = node(4, 1) + node(8, 2) + node(28, 3) + node(15) + node(9) + self.second
        self.assertEqual(expected, (out / "unit.ilb").read_bytes())

    def test_mutated_sidecar_rejected_before_output(self):
        (self.packet / "original/unknown.sidecar").write_bytes(b"changed")
        out = self.root / "out"
        with self.assertRaisesRegex(ValueError, "modified original"):
            c.encode(self.packet, out)
        self.assertFalse(out.exists())

    def test_missing_block_end_rejected_before_output(self):
        order = (self.packet / "ilb_order.txt").read_text().splitlines()
        order.remove("node:5")
        (self.packet / "ilb_order.txt").write_text("\n".join(order) + "\n")
        out = self.root / "out"
        with self.assertRaises(ValueError):
            c.encode(self.packet, out)
        self.assertFalse(out.exists())

    def test_unknown_opcode_explicit_opaque_roundtrip(self):
        raw = b"\xfeunknown\0\xff"
        (self.snapshot / "unit.ilb").write_bytes(raw)
        with self.assertRaisesRegex(ValueError, "unsupported ILB op"):
            c.dump(self.snapshot, "demo", self.root / "semantic")
        packet = self.root / "opaque"
        c.dump(self.snapshot, "demo", packet, opaque=True)
        out = self.root / "out"
        c.encode(packet, out)
        self.assertEqual(raw, (out / "unit.ilb").read_bytes())
        self.assertEqual([], c.read_tsv(packet / "fields.tsv"))

    def test_typed_node_clone_and_shape_change(self):
        rows = c.read_tsv(self.packet / "ilb_records.tsv")
        edited = []
        for row in rows:
            if row["record"] == "node:2":
                if row["field"] == "sym":
                    continue
                if row["field"] == "op":
                    row["value"] = "15"
            edited.append(row)
        cloned = [dict(row, record="inserted-null") for row in edited if row["record"] == "node:2"]
        position = next(i for i, row in enumerate(edited) if row["record"] == "node:3")
        edited[position:position] = cloned
        table = self.packet / "edited.tsv"
        c.write_tsv(table, ["record", "field", "type", "value"], edited)
        out = self.root / "out"
        c.encode(self.packet, out, table)
        expected = node(4, 1) + node(8, 2) + node(15) + node(15) + node(28, 3) + node(15) + node(9) + self.second
        self.assertEqual(expected, (out / "unit.ilb").read_bytes())

    def test_typed_node_field_mislabel_rejected(self):
        rows = c.read_tsv(self.packet / "ilb_records.tsv")
        next(row for row in rows if row["field"] == "line")["field"] = "invented"
        table = self.packet / "edited.tsv"
        c.write_tsv(table, ["record", "field", "type", "value"], rows)
        out = self.root / "out"
        with self.assertRaisesRegex(ValueError, "serialization grammar"):
            c.encode(self.packet, out, table)
        self.assertFalse(out.exists())

    def test_nested_sidecars_rejected_not_dropped(self):
        (self.snapshot / "nested").mkdir()
        with self.assertRaisesRegex(ValueError, "directories/symlinks"):
            c.dump(self.snapshot, "demo", self.root / "new_packet")


if __name__ == "__main__":
    unittest.main()
