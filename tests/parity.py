#!/usr/bin/env python3
"""Compile with Release 26 and with the rebuilt stages, and compare the outputs.

Usage:
  python tests/parity.py [--exes build/msvc] [--sf3 DIR] [--jobs N] [--each-rule] [--write-expected]

Inputs: tests/cases.txt (a source in tests/cases and its options per line), and with --sf3 every C module of a
Street Fighter III 3rd Strike tree (the shc lines of its build.bat). Every input is compiled to an object and,
for tests/cases, to assembler source:

  off   Release 26 (extracted/bin) against the rebuilt stages with every rule set to 0: must be identical
  on    the rebuilt stages with the rules unset (the defaults), against tests/expected.tsv (tests/cases) or
        tests/sf3-expected.tsv (--sf3; the tree's commit is in its first line)

--each-rule lists, for each rule, the inputs whose output it changes on its own. --write-expected rewrites the
expected file of the inputs run from the 'on' outputs. An object's compile date (and the checksum of each
record holding it) is masked before comparing.
"""
import argparse, hashlib, os, re, shutil, subprocess, sys, tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
STAGES = ["shcmdl", "shcgen", "shcpep", "shcasm"]
RULES = ["SWITCH_ARCADE_BRANCH", "SWITCH_ARCADE_JUMP", "XJUMP_OFF", "PEP_R0_FORGET", "SLOT_NO_STACK",
         "PEP_NO_THREAD", "GEN_TST_R0", "GEN_MUL_L", "MDL_ARG_CONST", "MDL_CAST_CSE", "MDL_ARG_CAST", "MDL_GCSE", "GEN_CHAIN_JUMP", "ASM_SPECREG", "ASM_MULWAIT",
         "PEP_AUTOINC", "MDL_IV", "GEN_POOL_MOVLOC", "MDL_LOOP_INV"]


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
        tmp = self.work / f"tmp{slot}"
        shutil.rmtree(tmp, ignore_errors=True)
        tmp.mkdir()
        env = {k: v for k, v in os.environ.items() if k not in RULES}
        env.update(rules, SHC_LIB=str(lib), SHC_TMP=str(tmp) + "\\")
        args = [str(lib / "shc.exe"), src, *opts.split(), "-object=" + str(out)]
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
            out.parent.mkdir(exist_ok=True)
            rc, data = self.compile(lib, rules, cwd, src, opts, out, asm, slot)
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
    ap.add_argument("--each-rule", action="store_true")
    ap.add_argument("--write-expected", action="store_true")
    ap.add_argument("--against", help="compare 'on' with these stages (<dir>/<stage>.exe, such as the game's bin) "
                                      "instead of the expected file")
    ap.add_argument("--only", nargs="*")
    a = ap.parse_args()
    inputs = sf3_inputs(a.sf3) if a.sf3 else cases()
    if a.only:
        inputs = [i for i in inputs if i[0] in a.only]
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

    # SHC rejects an option value holding '-' (-object=C:/my-dir/x.obj): outputs go where the path has none
    tmp = tempfile.gettempdir()
    work = Path(tempfile.mkdtemp(prefix="shcpar", dir=tmp if "-" not in tmp else os.environ.get("SystemDrive", "C:") + "/"))
    run = Runner(work, Path(a.r26), Path(a.exes), a.against)
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
    with ThreadPoolExecutor(a.jobs) as ex:
        for part in ex.map(lambda k: [one(i, k) for i in chunks[k]], range(a.jobs)):
            results += part
    shutil.rmtree(work, ignore_errors=True)

    off_bad = on_bad = 0
    changed = {r: [] for r in RULES}
    for name, stock, res in sorted(results):
        if res["off"] != stock:
            off_bad += 1
            print(f"{name:20} off: differs from Release 26 ({digest(stock)} / {digest(res['off'])})")
        if any(rc != 0 for rc, _ in stock.values()):
            print(f"{name:20} Release 26 exit status {[rc for rc, _ in stock.values()]}")
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
        lines = [f"# {head}"] if a.sf3 else ["# tests/cases outputs with the default rules (tests/parity.py)"]
        lines += [f"{name}\t{digest(res['on'])}" for name, _, res in sorted(results) if name not in LOCAL]
        with open(exp_file, "w", newline="\n") as f:
            f.write("\n".join(lines) + "\n")
        print(f"wrote {exp_file.relative_to(ROOT)}")
    sys.exit(1 if off_bad or on_bad else 0)


if __name__ == "__main__":
    main()
