"""Constraint and preservation checks; no compiler is run."""
import struct
import sys
import unittest
from pathlib import Path

sys.dont_write_bytecode = True
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import stage_asa
import stage_asa_remap as remap


def asa(entries=()):
    # AUX header, typed ranges, optional flags, name, ASB tail, END.
    return (struct.pack("<BHIIIHHBBB", 12, 1, 0, 0, 0, 0, 0, 0, 0, len(entries))
            + b"".join(struct.pack("<bbII", *entry) for entry in entries)
            + struct.pack("<HBBB", 0, 0, 0, 1) + b"f" + bytes(29) + struct.pack("<BH", 13, 2))


def label():
    return struct.pack("<BHi", 0x1b, 1, 0)


def mov(src, dst, exp=1):
    return struct.pack("<BHHIBBBBBBB", 0x40, 1, 1, exp, 2, 0, 2, 1, src, 1, dst)


def branch(tmp, exp=1, opcode=0x25):
    head = struct.pack("<BHHI", opcode, 1, 1, exp)
    return head + (b"\0" if opcode == 0x23 else b"") + struct.pack("<HB", 2, tmp)


class PlannerTests(unittest.TestCase):
    def test_no_edit_lossless(self):
        original = label() + mov(2, 4)
        result, _, binary = remap.plan(asa(), original, original)
        self.assertEqual(result["status"], "no_edit")
        self.assertEqual(binary, asa())

    def test_adjacent_expression_merge(self):
        old = label() + mov(2, 4, 1) + mov(2, 4, 2)
        new = label() + mov(1, 4, 1) + mov(1, 4, 2)
        result, _, _ = remap.plan(asa(), old, new)
        self.assertEqual(result["additions"], {1: [(2, 1, 1, 2)]})

    def test_swap_simultaneous(self):
        result, _, _ = remap.plan(asa(), label() + mov(1, 2), label() + mov(2, 1))
        self.assertEqual(result["additions"], {1: [(1, 2, 1, 1), (2, 1, 1, 1)]})

    def test_unchanged_real_lifetime_conflict(self):
        old = label() + mov(2, 4) + mov(2, 5)
        new = label() + mov(1, 4) + mov(2, 5)
        result, _, binary = remap.plan(asa(), old, new, True)
        self.assertEqual(result["status"], "rejected")
        self.assertIsNone(binary)
        self.assertEqual(result["conflicts"][0]["wanted"], [1, 2])

    def test_branch_tmp_only_deferred_not_proven(self):
        old = label() + mov(2, 4) + branch(2)
        new = label() + mov(1, 4) + branch(2)
        self.assertEqual(remap.plan(asa(), old, new)[0]["status"], "rejected")
        result, _, _ = remap.plan(asa(), old, new, True)
        self.assertEqual(result["status"], "candidate")
        self.assertFalse(result["native_verified"])
        self.assertEqual(result["deferred_differences"][0]["planned"], 1)

    def test_call_tmp_is_hard_constraint(self):
        old = label() + mov(2, 4) + branch(2, opcode=0x23)
        new = label() + mov(1, 4) + branch(2, opcode=0x23)
        self.assertEqual(remap.plan(asa(), old, new, True)[0]["status"], "rejected")

    def test_compose_existing_and_preserve_all_ranges(self):
        entries = [(8, 2, 1, 1), (9, 3, 1, 1), (14, 1, 10, 20)]
        result, _, binary = remap.plan(asa(entries), label() + mov(8, 4), label() + mov(9, 4))
        self.assertEqual(result["additions"], {1: [(8, 3, 1, 1)]})
        parsed = remap.groups(stage_asa.parse(binary))[1]
        self.assertEqual(remap.ranges(parsed), [(8, 3, 1, 1)] + entries)
        self.assertEqual(remap.mapped(8, 1, remap.ranges(parsed)), 3)

    def test_packed_address_base_and_index(self):
        head = struct.pack("<BHHIBBB", 0x40, 1, 1, 1, 2, 0, 2)
        old = label() + head + bytes([9, 0x24, 1, 5])
        new = label() + head + bytes([9, 0x34, 1, 5])
        result, constraints, _ = remap.plan(asa(), old, new)
        self.assertEqual(result["additions"], {1: [(2, 3, 1, 1)]})
        self.assertTrue(any(row["component"] == "index" and row["before"] == 4 for row in constraints))

    def test_nonregister_and_record_structure_reject(self):
        old = label() + mov(2, 4)
        with self.assertRaisesRegex(ValueError, "non-register"):
            remap.plan(asa(), old, label() + mov(2, 4, 2))
        with self.assertRaisesRegex(ValueError, "record count"):
            remap.plan(asa(), old, old + mov(1, 2))

    def test_unknown_stream_reject(self):
        with self.assertRaises(ValueError):
            remap.plan(asa(), label() + b"\xff", label() + b"\xff")


if __name__ == "__main__":
    unittest.main()
