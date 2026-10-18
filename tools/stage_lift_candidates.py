"""Opt-in bounded duplicate-payload SUB-to-SUA candidate enumeration.

This is serialization inversion, not a historical mapping or a semantic proof.
Every candidate needs unchanged PEP+ASM and complete native-object equality to
the validated SUB witness. The default delegates to the strict unique mapper.
"""
from __future__ import annotations

import argparse
from collections import defaultdict
import hashlib
import itertools
from pathlib import Path
import struct

import stage_lift_registers as unique

HARD_BARRIERS = frozenset({
    "LABEL", "CLABEL", "DLABEL", "FLABEL", "ENTER", "EXIT", "CALL", "RETURN",
    "JUMP", "BRA", "JMP", "JSR", "BSR", "BRAF", "BSRF", "RTS", "RTE", "TRAPA",
    "SWBGN", "SWEND", "CASEJMP", "PROGRAM", "PRGRAM", "END",
})


def check_span(records, members):
    """Duplicate groups cannot bridge labels, calls, transfers or expressions."""
    positions = {r.index: i for i, r in enumerate(records)}
    lo, hi = min(positions[r.index] for r in members), max(positions[r.index] for r in members)
    expected = unique.values(members[0]).get("expression")
    if not isinstance(expected, int) or expected <= 0:
        raise unique.LiftError("duplicate group lacks a positive expression identity")
    for rec in records[lo:hi + 1]:
        if rec.name in HARD_BARRIERS:
            raise unique.LiftError(f"duplicate group crosses hard barrier {rec.index} {rec.name}")
        expression = unique.values(rec).get("expression")
        if expression is not None and expression != expected:
            raise unique.LiftError(f"duplicate group crosses expression at record {rec.index}")


def plan_candidates(original, edited, source, names, *, allow_duplicates=False, max_candidates=32):
    if not 1 <= max_candidates <= 32:
        raise unique.LiftError("candidate cap must be between 1 and 32")
    if not allow_duplicates:
        return [dict(mapping=unique.plan_records(original, edited, source, names), bijections=[])]
    old_scope, src_scope = unique.scopes(original), unique.scopes(source)
    unique.scopes(edited)
    changes = unique.changed_fields(original, edited)
    if not changes:
        raise unique.LiftError("no register delta supplied")
    functions = {old_scope[r.index] for r, _, _ in changes}
    if len(functions) != 1 or None in functions or not functions <= names.keys():
        raise unique.LiftError("enumeration requires one ASA-named function scope")
    old_groups, src_groups = defaultdict(list), defaultdict(list)
    for rec in original:
        old_groups[(old_scope[rec.index], unique.signature(rec))].append(rec)
    for rec in source:
        src_groups[(src_scope[rec.index], unique.signature(rec))].append(rec)
    affected = {}
    for rec, field, value in changes:
        key = old_scope[rec.index], unique.signature(rec)
        affected.setdefault(key, []).append((rec, field, value))
    choices, total = [], 1
    for key, deltas in affected.items():
        old, src = old_groups[key], src_groups[key]
        if len(old) != len(src) or not src:
            raise unique.LiftError(f"group count mismatch: SUB {len(old)}, SUA {len(src)}")
        if len(old) > 1:
            check_span(original, old)
            check_span(source, src)
        # Limit assignments before materializing permutations, including equal-output ones.
        for factor in range(2, len(old) + 1):
            total *= factor
            if total > max_candidates:
                raise unique.LiftError(f"bijection count exceeds cap {max_candidates}")
        choices.append((key, deltas, old, src))
    candidates = []
    for permutations in itertools.product(*(itertools.permutations(group[3]) for group in choices)):
        mapping, pairs = [], []
        for (key, deltas, old, _), permutation in zip(choices, permutations):
            assigned = {a.index: b for a, b in zip(old, permutation)}
            pairs += [dict(function_symbol=key[0], sub_record=a.index, sua_record=b.index,
                           opcode=a.name, expression=unique.values(a).get("expression", ""))
                      for a, b in zip(old, permutation)]
            for rec, field, value in deltas:
                match = assigned[rec.index]
                provenance = unique.values(rec)
                mapping.append(dict(sub_record=rec.index, sua_record=match.index,
                    function_symbol=key[0], function_name=names[key[0]], opcode=rec.name,
                    field=field.name, type=field.kind, old=field.value, new=value,
                    file=provenance.get("file", ""), line=provenance.get("line", ""),
                    expression=provenance.get("expression", ""),
                    sub_offset=rec.offset + field.offset, sua_offset=match.offset + field.offset))
        candidates.append(dict(mapping=mapping, bijections=pairs))
    return candidates


def enumerate_lifts(original_sub, edited_sub, original_sua, original_asa, codecs,
                    *, allow_duplicates=False, max_candidates=32):
    sub, sua, asa = codecs
    source = sua.decode(original_sua)
    plans = plan_candidates(sub.decode(original_sub), sub.decode(edited_sub), source,
                            unique.asa_function_names(asa.parse(original_asa)),
                            allow_duplicates=allow_duplicates, max_candidates=max_candidates)
    results = []
    for plan in plans:
        raw = bytearray(original_sua)
        for row in plan["mapping"]:
            if raw[row["sua_offset"]] != row["old"]:
                raise unique.LiftError("source typed field differs from serialized byte")
            struct.pack_into("B", raw, row["sua_offset"], row["new"])
        raw = bytes(raw)
        actual = unique.changed_fields(source, sua.decode(raw))
        wanted = sorted((r["sua_record"], r["field"], r["old"], r["new"]) for r in plan["mapping"])
        found = sorted((r.index, f.name, f.value, new) for r, f, new in actual)
        if wanted != found:
            raise unique.LiftError("candidate contains changes beyond the original typed GPR delta")
        text = sua.dumps(raw)
        if sua.encode(text) != raw:
            raise unique.LiftError("candidate roundtrip differs")
        results.append(dict(data=raw, text=text, **plan))
    return results


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--sub-original", type=Path, required=True)
    parser.add_argument("--sub-edited", type=Path, required=True)
    parser.add_argument("--sua", type=Path, required=True)
    parser.add_argument("--asa", type=Path, required=True)
    parser.add_argument("--function", required=True)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--codec-dir", type=Path, default=Path(__file__).resolve().parent)
    parser.add_argument("--enumerate-duplicates", action="store_true")
    parser.add_argument("--max-candidates", type=int, default=32)
    args = parser.parse_args()
    try:
        if args.out.exists():
            raise unique.LiftError("output already exists")
        paths = [args.sub_original, args.sub_edited, args.sua, args.asa]
        data = [p.read_bytes() for p in paths]
        candidates = enumerate_lifts(*data, unique.load_codecs(args.codec_dir),
            allow_duplicates=args.enumerate_duplicates, max_candidates=args.max_candidates)
        if any({r["function_name"] for r in c["mapping"]} != {args.function} for c in candidates):
            raise unique.LiftError("edited function identity differs from --function")
        args.out.mkdir(parents=True)
        unique.write_tsv(args.out / "INPUTS.tsv", ["role", "path", "bytes", "sha256"],
            [dict(role=role, path=str(path.resolve()), bytes=len(blob), sha256=hashlib.sha256(blob).hexdigest())
             for role, path, blob in zip(("original_sub", "edited_sub", "original_sua", "original_asa"), paths, data)])
        ledger = []
        for index, candidate in enumerate(candidates):
            folder = args.out / f"candidate{index:02d}"
            folder.mkdir()
            (folder / "edited.sua").write_bytes(candidate["data"])
            (folder / "edited.sua.tsv").write_text(candidate["text"], encoding="utf8")
            unique.write_tsv(folder / "MAPPING.tsv", unique.MAPPING_COLUMNS, candidate["mapping"])
            unique.write_tsv(folder / "BIJECTION.tsv",
                ["function_symbol", "sub_record", "sua_record", "opcode", "expression"], candidate["bijections"])
            ledger.append(dict(candidate=index, sua=str((folder / "edited.sua").resolve()),
                fields=len(candidate["mapping"]), sha256=hashlib.sha256(candidate["data"]).hexdigest()))
        unique.write_tsv(args.out / "CANDIDATES.tsv", ["candidate", "sua", "fields", "sha256"], ledger)
        (args.out / "REPORT.txt").write_text(
            f"Serialized candidates: {len(candidates)}; cap {args.max_candidates}. No stage executed.\n"
            "Each candidate requires unchanged PEP+ASM and complete native-object equality to the validated SUB witness.\n"
            "Identical accepted outputs can leave the historical bijection nonunique.\n", encoding="utf8")
        print(f"wrote {len(candidates)} candidates; native validation required")
    except (ValueError, OSError, struct.error) as exc:
        parser.exit(2, f"unresolved: {exc}\n")


if __name__ == "__main__":
    main()
