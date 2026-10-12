"""Portable adversarial checks for opt-in duplicate-payload enumeration."""
from pathlib import Path
import copy
import sys
from types import SimpleNamespace as NS
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import stage_lift_candidates as tool


def record(index, *, function=None, dst=0, expression=2, name="TST"):
    pairs = [("opcode", "u8", 0x1b if function is not None else 0x85)]
    if function is not None:
        name = "FLABEL"
        pairs += [("raw_ea1", "u16", function), ("sptravel", "i32", 0)]
    else:
        pairs += [("file", "u16", 1), ("line", "u16", 30), ("expression", "u32", expression),
                  ("flags_raw", "u8", 2), ("operand_count", "u8", 2),
                  ("ea1.type_raw", "u8", 1), ("ea1.base", "u8", 0),
                  ("ea2.type_raw", "u8", 1), ("ea2.base", "u8", dst)]
    sizes = {"u8": 1, "u16": 2, "u32": 4, "i32": 4}
    fields, offset = [], 0
    for key, typ, value in pairs:
        fields.append(NS(offset=offset, name=key, kind=typ, value=value)); offset += sizes[typ]
    return NS(index=index, offset=index * 30, name=name, format=5 if function is not None else 8,
              fields=fields, warning="")


def change(records, index, value=1):
    edited = copy.deepcopy(records)
    for rec in edited:
        if rec.index == index:
            next(f for f in rec.fields if f.name == "ea2.base").value = value
    return edited


def plan(original, edited, source=None, **kwargs):
    return tool.plan_candidates(original, edited, original if source is None else source,
                                {7: "arbitrary", 8: "other"}, **kwargs)


class CandidateTests(unittest.TestCase):
    def setUp(self):
        self.original = [record(0, function=7), record(1), record(2)]

    def test_default_retains_unique_mapper_rejection(self):
        with self.assertRaisesRegex(tool.unique.LiftError, "SUB candidates"):
            plan(self.original, change(self.original, 1))

    def test_unique_default_still_passes(self):
        original = self.original[:2]
        self.assertEqual(1, len(plan(original, change(original, 1))))

    def test_two_by_two_enumerates_full_bijections(self):
        plans = plan(self.original, change(self.original, 1), allow_duplicates=True)
        self.assertEqual([1, 2], [p["mapping"][0]["sua_record"] for p in plans])
        self.assertTrue(all(len(p["bijections"]) == 2 for p in plans))

    def test_unchanged_member_count_is_required(self):
        with self.assertRaisesRegex(tool.unique.LiftError, "count mismatch"):
            plan(self.original, change(self.original, 1), self.original[:2], allow_duplicates=True)

    def test_extra_source_duplicate_rejects(self):
        with self.assertRaisesRegex(tool.unique.LiftError, "count mismatch"):
            plan(self.original, change(self.original, 1), self.original + [record(3)], allow_duplicates=True)

    def test_different_expression_is_not_a_matching_candidate(self):
        source = [record(0, function=7), record(1), record(2, expression=3)]
        with self.assertRaisesRegex(tool.unique.LiftError, "count mismatch"):
            plan(self.original, change(self.original, 1), source, allow_duplicates=True)

    def test_intervening_expression_change_rejects(self):
        original = [record(0, function=7), record(1), record(2, expression=3), record(3)]
        with self.assertRaisesRegex(tool.unique.LiftError, "crosses expression"):
            plan(original, change(original, 1), allow_duplicates=True)

    def test_source_barrier_rejects(self):
        source = [record(0, function=7), record(1), record(2, name="CALL"), record(3)]
        with self.assertRaisesRegex(tool.unique.LiftError, "hard barrier"):
            plan(self.original, change(self.original, 1), source, allow_duplicates=True)

    def test_original_label_barrier_rejects(self):
        original = [record(0, function=7), record(1), record(2, name="LABEL"), record(3)]
        with self.assertRaisesRegex(tool.unique.LiftError, "hard barrier"):
            plan(original, change(original, 1), allow_duplicates=True)

    def test_conditional_branch_inside_expression_is_allowed(self):
        original = [record(0, function=7), record(1), record(2, name="JUMPF"), record(3)]
        self.assertEqual(2, len(plan(original, change(original, 1), allow_duplicates=True)))

    def test_scope_prevents_cross_function_assignment(self):
        original = self.original + [record(3, function=8), record(4)]
        plans = plan(original, change(original, 1), allow_duplicates=True)
        self.assertEqual(2, len(plans))
        self.assertTrue(all(r["function_symbol"] == 7 for p in plans for r in p["mapping"]))

    def test_multiple_changed_functions_reject(self):
        original = self.original + [record(3, function=8), record(4)]
        edited = change(change(original, 1), 4)
        with self.assertRaisesRegex(tool.unique.LiftError, "one ASA-named"):
            plan(original, edited, allow_duplicates=True)

    def test_factorial_and_global_cap(self):
        original = [record(0, function=7)] + [record(i) for i in range(1, 6)]
        with self.assertRaisesRegex(tool.unique.LiftError, "exceeds cap"):
            plan(original, change(original, 1), allow_duplicates=True)
        with self.assertRaisesRegex(tool.unique.LiftError, "between 1 and 32"):
            plan(self.original, change(self.original, 1), allow_duplicates=True, max_candidates=33)

    def test_non_gpr_delta_rejects(self):
        with self.assertRaisesRegex(tool.unique.LiftError, "not a GPR"):
            plan(self.original, change(self.original, 1, 16), allow_duplicates=True)

    def test_product_cap_across_independent_groups(self):
        original = [record(0, function=7)] + [record(i) for i in range(1, 4)] + [record(i, expression=3) for i in range(4, 7)]
        edited = change(change(original, 1), 4)
        with self.assertRaisesRegex(tool.unique.LiftError, "exceeds cap"):
            plan(original, edited, allow_duplicates=True)

    def test_decoded_native_branch_and_program_barriers(self):
        for name in ("BRA", "PRGRAM"):
            with self.subTest(name=name):
                source = [record(0, function=7), record(1), record(2, name=name), record(3)]
                with self.assertRaisesRegex(tool.unique.LiftError, "hard barrier"):
                    plan(self.original, change(self.original, 1), source, allow_duplicates=True)


if __name__ == "__main__":
    unittest.main()
