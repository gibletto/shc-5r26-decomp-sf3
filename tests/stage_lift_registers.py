"""Adversarial register-lift matching tests; no compiler/capture dependency."""
from pathlib import Path
import importlib.util
from types import SimpleNamespace as NS
import unittest

spec = importlib.util.spec_from_file_location("lift_registers", Path(__file__).resolve().parents[1] / "tools/stage_lift_registers.py")
lift = importlib.util.module_from_spec(spec); spec.loader.exec_module(lift)


def record(index, name="MOV", function=None, dst=2, kind=1, field="ea2.base"):
    pairs = [("opcode", "u8", 0x1b if function is not None else 0x40)]
    if function is not None:
        name = "FLABEL"; pairs += [("raw_ea1", "u16", function), ("sptravel", "i32", 0)]
    else:
        pairs += [("file", "u16", 1), ("line", "u16", 50), ("expression", "u32", 3),
                  ("flags_raw", "u8", 2), ("operand_count", "u8", 2),
                  ("ea1.type_raw", "u8", 1), ("ea1.base", "u8", 12),
                  ("ea2.type_raw", "u8", kind), (field, "u8", dst)]
    sizes = {"u8": 1, "u16": 2, "u32": 4, "i32": 4}
    fields, offset = [], 0
    for key, typ, value in pairs:
        fields.append(NS(offset=offset, name=key, kind=typ, value=value)); offset += sizes[typ]
    return NS(index=index, offset=index * 30, name=name, format=5 if function is not None else 8,
              fields=fields, warning="")


class LiftTests(unittest.TestCase):
    def test_exact_unique_mapping_with_record_numbers_changed(self):
        original = [record(0, function=7), record(1)]
        edited = [record(0, function=7), record(1, dst=3)]
        source = [record(0, function=7), record(2)]
        rows = lift.plan_records(original, edited, source, {7: "any_name"})
        self.assertEqual([(1, 2, "ea2.base", 2, 3)], [(r["sub_record"], r["sua_record"], r["field"], r["old"], r["new"]) for r in rows])

    def test_repeated_sua_payload_rejected(self):
        with self.assertRaisesRegex(lift.LiftError, "SUA candidates \\[1, 2\\]"):
            lift.plan_records([record(0, function=7), record(1)],
                              [record(0, function=7), record(1, dst=3)],
                              [record(0, function=7), record(1), record(2)], {7: "f"})

    def test_repeated_sub_payload_rejected_even_one_sua(self):
        with self.assertRaisesRegex(lift.LiftError, "SUB candidates \\[1, 2\\]"):
            lift.plan_records([record(0, function=7), record(1), record(2)],
                              [record(0, function=7), record(1, dst=3), record(2)],
                              [record(0, function=7), record(1)], {7: "f"})

    def test_cross_function_identical_payload_uses_function_identity(self):
        original = [record(0, function=7), record(1), record(2, function=8), record(3)]
        edited = [record(0, function=7), record(1), record(2, function=8), record(3, dst=3)]
        rows = lift.plan_records(original, edited, original, {7: "f", 8: "g"})
        self.assertEqual((8, 3), (rows[0]["function_symbol"], rows[0]["sua_record"]))

    def test_transformed_or_eliminated_source_rejected(self):
        with self.assertRaisesRegex(lift.LiftError, "SUA candidates \\[\\]"):
            lift.plan_records([record(0, function=7), record(1)],
                              [record(0, function=7), record(1, dst=3)],
                              [record(0, function=7), record(1, dst=4)], {7: "f"})

    def test_system_register_offset_rejected(self):
        with self.assertRaisesRegex(lift.LiftError, "non-register"):
            lift.changed_fields([record(1, kind=5, field="ea2.system_reg_offset")],
                                [record(1, kind=5, field="ea2.system_reg_offset", dst=3)])

    def test_incorrectly_named_control_operand_rejected(self):
        with self.assertRaisesRegex(lift.LiftError, "operand kind"):
            lift.changed_fields([record(1, kind=5)], [record(1, kind=5, dst=3)])

    def test_floating_or_special_register_number_rejected(self):
        with self.assertRaisesRegex(lift.LiftError, "not a GPR value"):
            lift.changed_fields([record(1, dst=16)], [record(1, dst=17)])

    def test_operand_expansion_rejected(self):
        expanded = record(1)
        expanded.fields.append(NS(offset=99, name="extra", kind="u8", value=3))
        with self.assertRaisesRegex(lift.LiftError, "expansion/layout"):
            lift.changed_fields([record(1)], [expanded])

    def test_packed_gpr_pair_allowed(self):
        changes = lift.changed_fields([record(1, dst=0x23, kind=9, field="ea2.base_index_packed")],
                                     [record(1, dst=0x32, kind=9, field="ea2.base_index_packed")])
        self.assertEqual(1, len(changes))


if __name__ == "__main__":
    unittest.main()
