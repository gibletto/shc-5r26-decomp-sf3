#!/usr/bin/env python3
"""Build the four rebuilt stages: build/<toolchain>/<stage>.exe (with the rules; see SF3.md).

Usage: python build.py [stage ...] [--toolchain msvc|vc6] [--msvc-version V] [--stock] [--jobs N]

msvc: Visual Studio (Build Tools are enough) with the x86 C compiler: the newest install vswhere finds, or VS_DIR.
vc6: Visual C++ 6, VC6_DIR = the directory holding VC98 and COMMON.
--stock builds without the rules' code (SHC_REBUILD_UPDATED=0): the stages are then Release 26 only.

Each stage needs src/_stockdata.c, made from your Release 26 by tools/setup.py. src/_relocs.c maps stock
function addresses to the rebuild's; it is copied into the build directory, filled in from the link map and
relinked until no address moves.
"""
import argparse, os, re, shutil, subprocess, sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent
STAGES = ["shcmdl", "shcgen", "shcpep", "shcasm"]
LIBS = ["kernel32.lib", "user32.lib", "advapi32.lib", "shell32.lib"]


def env_from_bat(bat, arg=""):
    out = subprocess.run(f'"{bat}" {arg} >nul && set', shell=True, capture_output=True, text=True).stdout
    env = dict(l.split("=", 1) for l in out.splitlines() if "=" in l)
    if "INCLUDE" not in env:
        sys.exit(f"{bat} did not set up a compiler environment")
    return env


def find_vs():
    if os.environ.get("VS_DIR"):                         # a Visual Studio install other than the newest
        return Path(os.environ["VS_DIR"])
    vswhere = Path(os.environ.get("ProgramFiles(x86)", r"C:\Program Files (x86)")) / "Microsoft Visual Studio/Installer/vswhere.exe"
    if not vswhere.exists():
        sys.exit("vswhere.exe not found: install Visual Studio Build Tools with the C++ x86/x64 build tools")
    p = subprocess.run([str(vswhere), "-latest", "-products", "*", "-requires",
                        "Microsoft.VisualStudio.Component.VC.Tools.x86.x64", "-property", "installationPath"],
                       capture_output=True, text=True).stdout.strip().splitlines()
    if not p:
        sys.exit("no Visual Studio install with the C++ x86/x64 build tools")
    return Path(p[0])


def toolchain(name, msvc_version=None):
    """(environment, compiler command, compiler flags, linker command, linker flags)"""
    if name == "vc6":
        vs6 = os.environ.get("VC6_DIR")
        if not vs6 or not (Path(vs6) / "VC98/BIN/CL.EXE").exists():
            sys.exit("set VC6_DIR to the Visual C++ 6 directory that holds VC98 and COMMON")
        vs6 = Path(vs6)
        env = dict(os.environ)
        env["PATH"] = f"{vs6 / 'VC98/BIN'};{vs6 / 'COMMON/MSDEV98/BIN'};" + env.get("PATH", "")
        env["INCLUDE"] = str(vs6 / "VC98/INCLUDE")
        env["LIB"] = str(vs6 / "VC98/LIB")
        return env, [str(vs6 / "VC98/BIN/CL.EXE")], [], [str(vs6 / "VC98/BIN/LINK.EXE")], []
    vs = find_vs()
    env = env_from_bat(vs / "VC/Auxiliary/Build/vcvars32.bat", f"-vcvars_ver={msvc_version}" if msvc_version else "")
    # VC6 had no security cookies and linked at a fixed base: _relocs.c holds absolute addresses
    cflags = ["/GS-"]
    lflags = ["/DYNAMICBASE:NO", "/FIXED", "/SAFESEH:NO"]
    path = next(v for k, v in env.items() if k.upper() == "PATH")
    cl, ln = shutil.which("cl.exe", path=path), shutil.which("link.exe", path=path)
    return env, [cl], cflags, [ln], lflags


def compile_one(tc, src, obj, inc, mode):
    env, cc, cflags, _, _ = tc
    p = subprocess.run(cc + ["/nologo", "/c", "/W0", "/MT", "/Od", *cflags, "/I", str(inc),
                             f"/DSHC_REBUILD_UPDATED={mode}", f"/Fo{obj}", str(src)],
                       capture_output=True, text=True, env=env)
    return src.name, p.returncode, (p.stdout + p.stderr).strip()


def link(tc, stage, out):
    env, _, _, ld, lflags = tc
    objs = sorted(o.name for o in out.glob("*.obj"))
    (out / "link.rsp").write_text("\n".join(objs + LIBS) + "\n")
    p = subprocess.run(ld + ["/nologo", f"/out:{stage}.exe", "/subsystem:console", "/machine:x86", *lflags,
                             f"/map:{stage}.map", "@link.rsp"], capture_output=True, text=True, env=env, cwd=str(out))
    return p.returncode, (p.stdout + p.stderr).strip()


def resync_relocs(map_path, relocs):
    """Point each stock address in _relocs.c at the rebuild address the map gives; return how many moved."""
    addr = {}
    for line in map_path.read_text(errors="ignore").splitlines():
        m = re.search(r"\b_([A-Za-z0-9_]+)\s+([0-9A-Fa-f]{8})\b", line)
        if m:
            for s in re.finditer(r"004[0-9A-Fa-f]{5}", m.group(1)):
                addr[int(s.group(0), 16)] = int(m.group(2), 16)
        # a source file is named after its function's stock address: the lowest address of its object
        m = re.search(r"^\s*[0-9A-Fa-f]{4}:[0-9A-Fa-f]{8}\s+\S+\s+([0-9A-Fa-f]{8})(?:\s+\S+)?\s+(\S+\.obj)\b", line)
        if m:
            s = re.search(r"004[0-9A-Fa-f]{5}", m.group(2))
            if s:
                k, v = int(s.group(0), 16), int(m.group(1), 16)
                if k not in addr or v < addr[k]:
                    addr[k] = v
    moved = 0

    def repl(m):
        nonlocal moved
        new = addr.get(int(m.group(1), 16))
        if new is None or new == int(m.group(2), 16):
            return m.group(0)
        moved += 1
        return "{ 0x%08Xu, 0x%08Xu }" % (int(m.group(1), 16), new)
    text = re.sub(r"\{\s*0x(004[0-9A-Fa-f]{5})u,\s*0x([0-9A-Fa-f]{8})u\s*\}", repl, relocs.read_text())
    relocs.write_text(text)
    return moved


def build_stage(tc, stage, out, mode, jobs):
    R = ROOT / "rebuild" / stage
    if not (R / "src/_stockdata.c").exists():
        sys.exit(f"{stage}: src/_stockdata.c is missing: run python tools/setup.py first")
    out.mkdir(parents=True, exist_ok=True)
    for o in out.glob("*.obj"):
        o.unlink()
    shutil.copy(R / "src/_relocs.c", out / "_relocs.c")
    srcs = [s for s in sorted((R / "src").glob("*.c")) if s.name != "_relocs.c"] + [out / "_relocs.c"]
    with ThreadPoolExecutor(jobs) as ex:
        res = list(ex.map(lambda s: compile_one(tc, s, out / (s.stem + ".obj"), R / "include", mode), srcs))
    bad = [(n, msg) for n, rc, msg in res if rc]
    for n, msg in bad[:10]:
        print(f"{stage}: {n} failed:\n{msg[-1500:]}")
    if bad:
        sys.exit(f"{stage}: {len(bad)} of {len(srcs)} files failed to compile")
    for _ in range(8):
        rc, msg = link(tc, stage, out)
        if rc:
            sys.exit(f"{stage}: link failed\n" + "\n".join(l for l in msg.splitlines() if "error" in l.lower())[:3000])
        if resync_relocs(out / f"{stage}.map", out / "_relocs.c") == 0:
            break
        n, rc, msg = compile_one(tc, out / "_relocs.c", out / "_relocs.obj", R / "include", mode)
        if rc:
            sys.exit(msg)
    else:
        sys.exit(f"{stage}: _relocs.c did not settle")
    print(f"{stage}: {out / (stage + '.exe')}")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("stages", nargs="*", default=STAGES)
    ap.add_argument("--toolchain", default="msvc", choices=["msvc", "vc6"])
    ap.add_argument("--stock", action="store_true")
    ap.add_argument("--msvc-version", help="an installed MSVC toolset other than the newest (vcvars -vcvars_ver, e.g. 14.16)")
    ap.add_argument("--jobs", type=int, default=os.cpu_count() or 4)
    a = ap.parse_args()
    tc = toolchain(a.toolchain, a.msvc_version)
    for s in a.stages:
        if s not in STAGES:
            sys.exit(f"unknown stage {s}")
        build_stage(tc, s, ROOT / "build" / (a.toolchain + (a.msvc_version or "") + ("-stock" if a.stock else "")) / s, 0 if a.stock else 1, a.jobs)


if __name__ == "__main__":
    main()
