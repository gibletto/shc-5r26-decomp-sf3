#!/usr/bin/env python3
"""Plan an ASA-only alternative to a full-module SUA register-field edit.

This is an intermediate-file experiment, not compiler policy. All real serialized
operand occurrences, including unchanged ones, constrain a simultaneous mapping
per function/expression. Existing ASA mappings are composed with the edited SUA
values and retained verbatim. New overriding ranges precede them: the PEP reader
prepends ranges, so the earliest serialized overlapping range wins.

`plan` never runs a compiler and never claims native sufficiency. `verify` runs
unchanged PEP+ASM twice through stage_pipeline.py and requires full native object
byte equality. --allow-branch-tmp only defers unchanged JUMP/JUMPT/JUMPF tmp
constraints; it does not declare those fields inert. A native check is mandatory.
Unknown grammar, structural/non-register edits and mapping contradictions reject.
Only GPR0..15 mappings are synthesized. Other existing mappings are preserved.

Sources: shcpep 00406760/00407220 readers, 00409d30 range loading,
0040f720 apply_function_register_remap, 0040f810/0040fac0 register shifting.
"""
from __future__ import annotations

import argparse
import ast
import csv
import hashlib
import io
import pprint
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

sys.dont_write_bytecode = True
import stage_asa
import stage_sua


def digest(data):
    return hashlib.sha256(data).hexdigest()


def groups(atoms):
    result = {}
    for atom in atoms:
        result.setdefault(atom.record, {})[atom.field] = atom.value
    return result


def ranges(aux):
    return [tuple(aux[f"range[{i}].{field}"] for field in
                  ("before_reg", "after_reg", "start_expno", "end_expno"))
            for i in range(aux["range_count"])]


def mapped(reg, expression, entries):
    # First serialized match wins, because the reader reverses list order.
    for before, after, start, end in entries:
        if before == reg and start <= expression <= end:
            return after
    return reg


def register_fields(record):
    """Return semantic components keyed by (serialized field, component).

    Only real operands are constraints: zero-filled unused EA base/index members
    are not live register uses. PEP's effects on unused members/misc flags remain
    covered by mandatory native verification. No implicit ABI use is renamed in
    this model; it is also covered by that check, not assumed safe.
    """
    data = {field.name: field.value for field in record.fields}
    result = {}
    for name, value in data.items():
        if name in ("source", "destination", "register", "tmp") or name.endswith(".base"):
            if value != 255:
                result[(name, "register")] = value
        elif name.endswith(".base_index_packed"):
            result[(name, "base")] = value >> 4
            result[(name, "index")] = value & 15
        elif name == "destination_tmp_packed":
            result[(name, "destination")] = value >> 4
            result[(name, "tmp")] = value & 15
        elif name.endswith(".gbr_index"):
            result[(name, "index")] = value
        elif name.endswith(".system_reg_offset"):
            kind = data[name.rsplit(".", 1)[0] + ".type_raw"] & 31
            result[(name, "register")] = value + (97 if kind == 5 else 100)
    return result


def rewrite_ranges(asa, additions):
    """Preserve every original atom except count and reindexed range names."""
    atoms = stage_asa.parse(asa)
    output = []
    offsets = defaultdict(int)
    for atom in atoms:
        rid = atom.record
        extra = additions.get(rid, [])
        name, value = atom.field, atom.value
        if name == "range_count":
            value += len(extra)
            if value > 255:
                raise ValueError(f"AUX record {rid} exceeds 255 ranges")
        elif name.startswith("range[") and extra:
            index, suffix = name[6:].split("]", 1)
            name = f"range[{int(index) + len(extra)}]" + suffix
        new = stage_asa.Atom(rid, offsets[rid], name, atom.kind, value)
        output.append(new)
        offsets[rid] += len(new.packed())
        if name == "range_count":
            for index, entry in enumerate(extra):
                for field, kind, item in zip(
                        ("before_reg", "after_reg", "start_expno", "end_expno"),
                        ("i8", "i8", "u32", "u32"), entry):
                    new = stage_asa.Atom(rid, offsets[rid], f"range[{index}].{field}", kind, item)
                    output.append(new)
                    offsets[rid] += len(new.packed())
    binary = b"".join(atom.packed() for atom in output)
    # Validate byte layout against the independent codec parser.
    actual = stage_asa.parse(binary)
    if output != actual:
        raise ValueError("rewritten ASA grammar differs from intended fields")
    return binary


def plan(asa: bytes, original_sua: bytes, edited_sua: bytes, allow_branch_tmp=False):
    """Return (result dict, constraints rows, new ASA or None), without I/O."""
    auxes = {rid: aux for rid, aux in groups(stage_asa.parse(asa)).items()
             if aux.get("tag", 0) & 31 == 12}
    by_symbol = {}
    for rid, aux in auxes.items():
        if aux["symbol"] in by_symbol:
            raise ValueError("duplicate function AUX symbol")
        by_symbol[aux["symbol"]] = rid
    original, edited = stage_sua.decode(original_sua), stage_sua.decode(edited_sua)
    if len(original) != len(edited):
        raise ValueError("record count changed; only register-field edits are supported")
    constraints, changed_functions = [], set()
    active = None
    changed_fields = 0
    for old_record, new_record in zip(original, edited):
        old = {f.name: f.value for f in old_record.fields}
        new = {f.name: f.value for f in new_record.fields}
        if [(f.name, f.kind, f.offset) for f in old_record.fields] != [
                (f.name, f.kind, f.offset) for f in new_record.fields]:
            raise ValueError(f"record {old_record.index}: field layout changed")
        before, after = register_fields(old_record), register_fields(new_record)
        if before.keys() != after.keys():
            raise ValueError(f"record {old_record.index}: register shape changed")
        register_names = {name for name, _ in before}
        for name in old:
            if old[name] != new[name]:
                if name not in register_names:
                    raise ValueError(f"record {old_record.index}: non-register edit {name}")
                changed_fields += 1
        if old["opcode"] == 0x1b:  # OP_FLABEL, its raw_ea1 is the AUX symbol.
            active = by_symbol.get(old["raw_ea1"])
        if old != new:
            if active is None:
                raise ValueError(f"record {old_record.index}: no function AUX")
            changed_functions.add(active)
        if not before:
            continue
        if "expression" not in old:
            raise ValueError(f"record {old_record.index}: register without expression")
        if active is None:
            if old != new:
                raise ValueError("register edit outside function")
            continue
        expression = old["expression"]
        entries = ranges(auxes[active])
        for (name, component), reg in before.items():
            wanted = after[(name, component)]
            if not (0 <= reg <= 108 and 0 <= wanted <= 108):
                raise ValueError(f"record {old_record.index}: invalid register")
            deferred = bool(allow_branch_tmp and name == "tmp" and reg == wanted
                            and old["opcode"] in (0x24, 0x25, 0x26))
            constraints.append(dict(aux_record=active, function=auxes[active]["name"].decode("latin1"),
                record=old_record.index, opcode=old_record.name, expression=expression,
                field=name, component=component, before=reg, edited=wanted,
                baseline=mapped(reg, expression, entries), wanted=mapped(wanted, expression, entries),
                deferred=deferred))
    constraints = [row for row in constraints if row["aux_record"] in changed_functions]
    demands = defaultdict(set)
    for row in constraints:
        if not row["deferred"]:
            demands[(row["aux_record"], row["expression"], row["before"])].add(row["wanted"])
    conflicts = [dict(aux_record=rid, expression=exp, before=reg, wanted=sorted(values))
                 for (rid, exp, reg), values in sorted(demands.items()) if len(values) > 1]
    result = dict(status="rejected" if conflicts else "candidate", native_verified=False,
                  changed_fields=changed_fields, allow_branch_tmp=allow_branch_tmp, conflicts=conflicts,
                  functions=[auxes[rid]["name"].decode("latin1") for rid in sorted(changed_functions)])
    if conflicts:
        return result, constraints, None
    points = defaultdict(list)
    for (rid, exp, reg), values in sorted(demands.items()):
        wanted = next(iter(values))
        if wanted != mapped(reg, exp, ranges(auxes[rid])):
            if not (0 <= reg < 16 and 0 <= wanted < 16):
                raise ValueError("only GPR0..15 new mappings are supported")
            points[(rid, reg, wanted)].append(exp)
    additions = defaultdict(list)
    for (rid, reg, wanted), expressions in sorted(points.items()):
        start = end = expressions[0]
        for expression in expressions[1:]:
            if expression == end + 1:
                end = expression
            else:
                additions[rid].append((reg, wanted, start, end))
                start = end = expression
        additions[rid].append((reg, wanted, start, end))
    binary = rewrite_ranges(asa, additions)
    combined = groups(stage_asa.parse(binary))
    collateral = []
    for row in constraints:
        actual = mapped(row["before"], row["expression"], ranges(combined[row["aux_record"]]))
        row["planned"] = actual
        if actual != row["wanted"]:
            if not row["deferred"]:
                raise AssertionError("planned mapping violates a hard constraint")
            collateral.append({key: row[key] for key in
                               ("function", "record", "expression", "field", "before", "wanted", "planned")})
    result.update(additions=dict(additions), deferred_differences=collateral,
                  asa_before_bytes=len(asa), asa_after_bytes=len(binary))
    if not changed_fields:
        result["status"] = "no_edit"
    return result, constraints, binary


def table(path, rows, columns=None):
    with path.open("w", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=columns or list(rows[0]), delimiter="\t", lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)


def write_result(path, value):
    path.write_text(pprint.pformat(value, sort_dicts=False, width=110) + "\n", encoding="utf-8")


def one_file(folder, suffix):
    matches = list(folder.glob("*" + suffix))
    if len(matches) != 1:
        raise ValueError(f"expected one {suffix} in {folder}, got {len(matches)}")
    return matches[0]


def plan_command(args):
    capture = args.capture.resolve()
    if args.out.resolve().is_relative_to(capture):
        raise ValueError("output must be outside the immutable capture")
    folder = capture / "before_shcpep/files"
    if not folder.is_dir():
        raise ValueError("not applicable: capture has no PEP input boundary")
    source_asa, source_sua = one_file(folder, ".asa"), one_file(folder, ".sua")
    asa, original, edited = source_asa.read_bytes(), source_sua.read_bytes(), args.edited_sua.read_bytes()
    result, constraints, binary = plan(asa, original, edited, args.allow_branch_tmp)
    args.out.mkdir(parents=True, exist_ok=False)
    for name, data in (("original.asa", asa), ("original.sua", original), ("edited.sua", edited)):
        (args.out / name).write_bytes(data)
    (args.out / "before.asa.tsv").write_text(stage_asa.dumps(asa), encoding="utf-8")
    if binary is not None:
        (args.out / "edit.asa").write_bytes(binary)
        (args.out / "after.asa.tsv").write_text(stage_asa.dumps(binary), encoding="utf-8")
    table(args.out / "CONSTRAINTS.tsv", constraints,
          ["aux_record", "function", "record", "opcode", "expression", "field", "component",
           "before", "edited", "baseline", "wanted", "deferred", "planned"])
    files = [dict(path=str(path.resolve()), bytes=path.stat().st_size, sha256=digest(path.read_bytes()))
             for path in sorted(folder.iterdir()) if path.is_file()]
    files.append(dict(path=str(capture / "manifest.txt"), bytes=(capture / "manifest.txt").stat().st_size,
                      sha256=digest((capture / "manifest.txt").read_bytes())))
    table(args.out / "CAPTURE_FILES.tsv", files)
    result.update(capture=str(capture), edited_sua_source=str(args.edited_sua.resolve()),
                  scope="ASA-only relative to this captured boundary; any inherited interventions remain.",
                  packet_hashes={path.name: digest(path.read_bytes()) for path in args.out.iterdir()
                                 if path.is_file()})
    write_result(args.out / "result.txt", result)
    print(f"{result['status']}: fields={result['changed_fields']} conflicts={len(result['conflicts'])}; native_verified=False")
    return 3 if result["status"] == "rejected" else 0


def native_object(run):
    manifest = ast.literal_eval((run / "manifest.txt").read_text(encoding="utf-8"))
    obj = Path(manifest["object"])
    if not obj.is_absolute():
        obj = run / "work" / obj
    if not obj.is_file():
        raise ValueError("replay did not retain the native object")
    return obj


def verify_command(args):
    packet = args.plan.resolve()
    result = ast.literal_eval((packet / "result.txt").read_text(encoding="utf-8"))
    if result["status"] != "candidate":
        raise ValueError("verify requires a candidate plan")
    for name, expected in result["packet_hashes"].items():
        if digest((packet / name).read_bytes()) != expected:
            raise ValueError(f"changed plan input: {name}")
    capture = Path(result["capture"])
    if args.out.resolve().is_relative_to(capture):
        raise ValueError("output must be outside the immutable capture")
    with (packet / "CAPTURE_FILES.tsv").open(encoding="utf-8", newline="") as stream:
        capture_rows = list(csv.DictReader(stream, delimiter="\t"))
        for row in capture_rows:
            if digest(Path(row["path"]).read_bytes()) != row["sha256"]:
                raise ValueError(f"changed capture input: {row['path']}")
    expected_paths = {str(Path(row["path"]).resolve()) for row in capture_rows}
    actual_paths = {str(path.resolve()) for path in (capture / "before_shcpep/files").iterdir() if path.is_file()}
    actual_paths.add(str((capture / "manifest.txt").resolve()))
    if expected_paths != actual_paths:
        raise ValueError("capture input file inventory changed")
    args.out.mkdir(parents=True, exist_ok=False)
    driver = args.driver.resolve()
    verification = dict(status="running", native_verified=False, plan=str(packet),
                        driver=str(driver), driver_sha256=digest(driver.read_bytes()),
                        scope="Alternative relative to the selected capture, including its inherited interventions.")
    write_result(args.out / "result.txt", verification)
    try:
        objects = []
        for name, replacement in (("sua_witness", "sua=edited.sua"), ("asa_alternative", "asa=edit.asa")):
            if digest(driver.read_bytes()) != verification["driver_sha256"]:
                raise ValueError("driver changed during verification")
            suffix, filename = replacement.split("=")
            run = args.out / name
            command = [sys.executable, "-B", str(driver), "replay", "--capture", result["capture"],
                       "--from-stage", "shcpep", "--out", str(run), "--replace", f"{suffix}={packet / filename}"]
            with (args.out / (name + ".log")).open("w", encoding="utf-8") as stream:
                subprocess.run(command, stdout=stream, stderr=subprocess.STDOUT, check=True)
            objects.append(native_object(run))
        if digest(driver.read_bytes()) != verification["driver_sha256"]:
            raise ValueError("driver changed during verification")
        blobs = [path.read_bytes() for path in objects]
        equal = blobs[0] == blobs[1]
        verification.update(status="verified_alternative" if equal else "native_mismatch", native_verified=equal,
                            full_native_objects_equal=equal,
                            objects=[dict(path=str(path), bytes=len(data), sha256=digest(data))
                                     for path, data in zip(objects, blobs)],
                            deferred_differences=result["deferred_differences"],
                            claim="Equality to the SUA witness only; no independent arcade-exact claim.")
    except (OSError, ValueError, subprocess.CalledProcessError) as exc:
        verification.update(status="verification_failed", error=str(exc))
    write_result(args.out / "result.txt", verification)
    print(verification["status"])
    return 0 if verification["native_verified"] else 4


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest="command", required=True)
    command = commands.add_parser("plan")
    command.add_argument("--capture", type=Path, required=True)
    command.add_argument("--edited-sua", type=Path, required=True)
    command.add_argument("--out", type=Path, required=True)
    command.add_argument("--allow-branch-tmp", action="store_true")
    command = commands.add_parser("verify")
    command.add_argument("--plan", type=Path, required=True)
    command.add_argument("--driver", type=Path, required=True)
    command.add_argument("--out", type=Path, required=True)
    args = parser.parse_args(argv)
    try:
        return plan_command(args) if args.command == "plan" else verify_command(args)
    except (OSError, ValueError) as exc:
        parser.exit(2, f"stage_asa_remap: {exc}\n")


if __name__ == "__main__":
    raise SystemExit(main())
