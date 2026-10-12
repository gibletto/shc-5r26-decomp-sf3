#!/usr/bin/env python3
"""Compile with Release 26 and with the rebuilt stages, and compare the outputs.

Usage:
  python tests/parity.py [--exes build/msvc] [--sf3 DIR] [--jobs N] [--work-dir DIR] [--each-rule] [--write-expected]

Inputs: tests/cases.txt (a source in tests/cases and its options per line), and with --sf3 every C module of a
Street Fighter III 3rd Strike tree (the shc lines of its build.bat). Every input is compiled to an object and,
for tests/cases, to assembler source:

  off   Release 26 (extracted/bin) against the rebuilt stages with every rule set to 0: must be identical
  on    the rebuilt stages with the rules unset (the defaults), against tests/expected.tsv (tests/cases) or
        tests/sf3-expected.tsv (--sf3; the tree's commit is in its first line)

--each-rule lists, for each rule, the inputs whose output it changes on its own. --write-expected rewrites the
expected file of the inputs run from the 'on' outputs. An object's compile date (and the checksum of each
record holding it) is masked before comparing.

--work-dir must name a fresh private directory. Otherwise a fresh directory is made under the configured
temporary directory; there is no drive-root fallback. Unsafe SHC output paths fail before compilation.
Work is removed on success and retained on compilation/setup failure. A failed or empty output never passes.
"""
import argparse, hashlib, os, re, shutil, subprocess, sys, tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
STAGES = ["shcmdl", "shcgen", "shcpep", "shcasm"]
RULES = ["SWITCH_ARCADE_BRANCH", "SWITCH_ARCADE_JUMP", "XJUMP_OFF", "PEP_R0_FORGET", "SLOT_NO_STACK",
         "PEP_NO_THREAD", "GEN_TST_R0", "GEN_MUL_L", "MDL_ARG_CONST", "MDL_CAST_CSE", "MDL_ARG_CAST", "MDL_GCSE", "GEN_CHAIN_JUMP", "ASM_SPECREG", "ASM_MULWAIT",
         "PEP_AUTOINC", "MDL_IV", "GEN_POOL_MOVLOC", "MDL_LOOP_INV", "GEN_RELOAD", "GEN_EVICT_ORDER", "MDL_CAST_MUL", "MDL_MUL_CONST",
         "GEN_MEM_INDEX", "GEN_R0VAR", "PEP_RET_R0", "MDL_IMM_REG", "MDL_MASK_AND", "MDL_IV_BASE", "MDL_IV_TEMP", "GEN_JUMP_TEMP", "MDL_TEST_REPLACE", "MDL_MUL_ONE", "MDL_TEMP_EXPR", "GEN_CHAIN_SCRATCH_R0", "GEN_NARROW_CONST", "GEN_OR_INDEX_EARLY"]


def normalize(obj):
    """An object with its compile date (yymmddhhmmss, first in the 0x84 header record) zeroed, and the checksum of
    every record that holds it."""
    d, p, date = bytearray(obj), 0, None
    while p + 1 < len(d) and d[p + 1] >= 2:
        t, n = d[p], d[p + 1]
        if t == 0x84 and date is None:
            m = re.search(rb"\d{12}", bytes(d[p:p + n]))
            date = m.group(0) if m else b"-"
        if date and date in d[p:p + n - 1]:
            d[p:p + n] = bytes(d[p:p + n - 1]).replace(date, b"0" * 12) + bytes(1)
        p += n
    return bytes(d)


LOCAL = set()      # cases whose output holds the source's full path (-debug): compared with Release 26 only


def cases():
    out = []
    for line in (ROOT / "tests/cases.txt").read_text().splitlines():
        if line.strip() and not line.startswith("#"):
            name, src, opts = line.split(None, 2)
            if name.startswith("!"):
                name = name[1:]
                LOCAL.add(name)
            out.append((name, ROOT / "tests/cases", src, opts, True))
    return out


def sf3_inputs(tree):
    out = []
    for line in (Path(tree) / "build.bat").read_text().splitlines():
        m = re.match(r"\s*shc\s+(\S+\.c)\s+(.*?)\s+-object=\S+", line)
        if m:
            out.append((Path(m.group(1).replace("\\", "/")).stem, Path(tree), m.group(1), m.group(2), False))
    return out


def output_argument(out, cwd):
    """SHC rejects '-' in option values; a relative path may avoid a shared ancestor containing it."""
    out, cwd = Path(out).resolve(), Path(cwd).resolve()
    value = str(out)
    if "-" in value:
        try:
            value = os.path.relpath(out, cwd)
        except ValueError as error:  # Windows paths on different drives cannot be relative.
            raise ValueError(f"cannot express SHC output path from {cwd}: {out}") from error
    if "-" in value:
        raise ValueError(f"SHC output path still contains '-': {value}; choose a different --work-dir")
    return value


def create_work_dir(requested, inputs):
    if requested:
        path = Path(requested)
        if path.exists() or path.is_symlink():
            raise ValueError(f"--work-dir must not exist: {path}")
        work = path.resolve()
        work.mkdir()  # Require an existing parent; do not silently choose another location.
    else:
        work = Path(tempfile.mkdtemp(prefix="shcpar", dir=tempfile.gettempdir())).resolve()
    try:
        for name, cwd, _, _, with_asm in inputs:
            for suffix in (["obj", "src"] if with_asm else ["obj"]):
                out = (work / "out0" / f"{name}.{suffix}").resolve()
                if not out.is_relative_to(work):
                    raise ValueError(f"output escaped the private work directory: {out}")
                output_argument(out, cwd)
    except Exception:
        work.rmdir()  # It is still the empty directory this call created.
        raise
    return work


class CompilationError(RuntimeError):
    pass


class Runner:
    def __init__(self, work, r26, exes, against):
        self.work = work
        self.stock = work / "lib-r26"
        self.ours = work / "lib-rebuild"
        self.other = work / "lib-against" if against else None
        for lib in (self.stock, self.ours, self.other):
            if lib:
                shutil.copytree(r26, lib)
        for s in STAGES:
            shutil.copy(exes / s / f"{s}.exe", self.ours / f"{s}.exe")
            if against:
                shutil.copy(Path(against) / f"{s}.exe", self.other / f"{s}.exe")

    def compile(self, lib, rules, cwd, src, opts, out, asm, slot):
        if out.is_symlink():
            raise ValueError(f"output must not be a symbolic link: {out}")
        out = out.resolve()
        if not out.is_relative_to(self.work.resolve()):
            raise ValueError(f"output escaped the private work directory: {out}")
        object_arg = output_argument(out, cwd)
        out.unlink(missing_ok=True)  # Never accept a stale file after a failed invocation.
        tmp = self.work / f"tmp{slot}"
        if tmp.is_symlink() or not tmp.resolve().is_relative_to(self.work.resolve()):
            raise ValueError(f"temporary directory escaped the private work directory: {tmp}")
        shutil.rmtree(tmp, ignore_errors=True)
        tmp.mkdir()
        env = {k: v for k, v in os.environ.items() if k not in RULES}
        env.update(rules, SHC_LIB=str(lib), SHC_TMP=str(tmp) + "\\", TMP=str(tmp), TEMP=str(tmp))
        args = [str(lib / "shc.exe"), src, *opts.split(), "-object=" + object_arg]
        if asm:
            args.insert(-1, "-code=asmcode")
        try:
            rc = subprocess.run(args, cwd=str(cwd), env=env, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                                timeout=600).returncode
        except subprocess.TimeoutExpired:
            rc = "timeout"
        data = out.read_bytes() if out.exists() else b""
        if out.exists():
            out.unlink()
        return rc, data if asm else normalize(data)

    def outputs(self, lib, rules, inp, slot):
        name, cwd, src, opts, with_asm = inp
        res = {}
        for asm in ([False, True] if with_asm else [False]):
            out = self.work / f"out{slot}" / (f"{name}.src" if asm else f"{name}.obj")
            if not out.resolve().is_relative_to(self.work.resolve()):
                raise ValueError(f"output escaped the private work directory: {out}")
            out.parent.mkdir(exist_ok=True)
            rc, data = self.compile(lib, rules, cwd, src, opts, out, asm, slot)
            if rc != 0 or not data:
                raise CompilationError(f"{name}: {lib.name} {'assembler source' if asm else 'object'} "
                                       f"failed (exit {rc}, {len(data)} output bytes)")
            res["src" if asm else "obj"] = (rc, data)
        return res


def digest(res):
    return " ".join(f"{k}:{rc}:{hashlib.sha256(d).hexdigest()[:16]}" for k, (rc, d) in sorted(res.items()))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--exes", default=str(ROOT / "build/msvc"), help="directory holding <stage>/<stage>.exe")
    ap.add_argument("--r26", default=str(ROOT / "extracted/bin"))
    ap.add_argument("--sf3", help="a Street Fighter III 3rd Strike tree (sfIII3-cps3-decomp) instead of tests/cases")
    ap.add_argument("--jobs", type=int, default=min(8, os.cpu_count() or 4))
    ap.add_argument("--work-dir", help="fresh private work directory (parent must exist)")
    ap.add_argument("--each-rule", action="store_true")
    ap.add_argument("--write-expected", action="store_true")
    ap.add_argument("--against", help="compare 'on' with these stages (<dir>/<stage>.exe, such as the game's bin) "
                                      "instead of the expected file")
    ap.add_argument("--only", nargs="*")
    a = ap.parse_args()
    inputs = sf3_inputs(a.sf3) if a.sf3 else cases()
    if a.only:
        inputs = [i for i in inputs if i[0] in a.only]
    if a.jobs < 1 or not inputs:
        ap.error("--jobs must be positive and at least one input must be selected")
    exp_file = ROOT / ("tests/sf3-expected.tsv" if a.sf3 else "tests/expected.tsv")
    expected = {}
    if exp_file.exists():
        for line in exp_file.read_text().splitlines():
            if line and not line.startswith("#"):
                k, v = line.split("\t")
                expected[k] = v
    if a.sf3:
        head = subprocess.run(["git", "-C", a.sf3, "rev-parse", "HEAD"], capture_output=True, text=True).stdout.strip()
        want = exp_file.read_text().split("\n")[0][2:].strip() if exp_file.exists() else ""
        if want and head and head != want:
            print(f"note: tests/sf3-expected.tsv is for commit {want}, the tree is at {head}: 'on' rows may differ")

    try:
        work = create_work_dir(a.work_dir, inputs)
    except (OSError, ValueError) as error:
        print(f"parity setup failed: {error}", file=sys.stderr)
        return 1
    try:
        run = Runner(work, Path(a.r26), Path(a.exes), a.against)
    except OSError as error:
        print(f"parity setup failed: {error}; work retained at {work}", file=sys.stderr)
        return 1
    off = {r: "0" for r in RULES}

    def one(i, slot):
        stock = run.outputs(run.stock, {}, i, slot)
        res = {"off": run.outputs(run.ours, off, i, slot), "on": run.outputs(run.ours, {}, i, slot)}
        if run.other:
            res["against"] = run.outputs(run.other, {}, i, slot)
        if a.each_rule:
            for r in RULES:                     # this rule at its default, the others 0
                res[r] = run.outputs(run.ours, {k: v for k, v in off.items() if k != r}, i, slot)
        return i[0], stock, res

    chunks = [inputs[k::a.jobs] for k in range(a.jobs)]
    results = []
    try:
        with ThreadPoolExecutor(a.jobs) as ex:
            for part in ex.map(lambda k: [one(i, k) for i in chunks[k]], range(a.jobs)):
                results += part
    except (CompilationError, OSError, ValueError) as error:
        print(f"parity failed: {error}; work retained at {work}", file=sys.stderr)
        return 1
    shutil.rmtree(work)

    off_bad = on_bad = 0
    changed = {r: [] for r in RULES}
    for name, stock, res in sorted(results):
        if res["off"] != stock:
            off_bad += 1
            print(f"{name:20} off: differs from Release 26 ({digest(stock)} / {digest(res['off'])})")
        got = digest(res["on"])
        if a.against:
            if res["on"] != res["against"]:
                on_bad += 1
                print(f"{name:20} on: {got}, {a.against}: {digest(res['against'])}")
        elif not a.write_expected and name not in LOCAL and expected.get(name) != got:
            on_bad += 1
            print(f"{name:20} on: {got} expected {expected.get(name)}")
        if a.each_rule:
            for r in RULES:
                if res[r] != res["off"]:
                    changed[r].append(name)
    n = len(results)
    print(f"off (rules 0 = Release 26): {n - off_bad}/{n} identical")
    if a.against:
        print(f"on (rules unset): {n - on_bad}/{n} identical to {a.against}")
    elif not a.write_expected:
        m = n - len(LOCAL & {name for name, _, _ in results})
        print(f"on (rules unset): {m - on_bad}/{m} as expected")
    if a.each_rule:
        for r in RULES:
            print(f"{r:22} changes {len(changed[r])}: {' '.join(changed[r])}")
    if a.write_expected:
        if off_bad or on_bad:
            print("expected file not written: parity failed", file=sys.stderr)
            return 1
        lines = [f"# {head}"] if a.sf3 else ["# tests/cases outputs with the default rules (tests/parity.py)"]
        lines += [f"{name}\t{digest(res['on'])}" for name, _, res in sorted(results) if name not in LOCAL]
        with open(exp_file, "w", newline="\n") as f:
            f.write("\n".join(lines) + "\n")
        print(f"wrote {exp_file.relative_to(ROOT)}")
    return 1 if off_bad or on_bad else 0


if __name__ == "__main__":
    sys.exit(main())
