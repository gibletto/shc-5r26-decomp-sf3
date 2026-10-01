# SHC 5.0 Release 26 compiler stages in C

C source for four stages of Hitachi's SH C compiler, SHC 5.0 Release 26: `shcmdl` (optimizer), `shcgen` (code
generator), `shcpep` (peephole optimizer) and `shcasm` (scheduler and assembler). The C is generated from Ghidra's
decompilation of the original programs, using the name and type tables in `ghidra/names`.

With every rule setting at 0, the stages give the same output as Release 26. By default they also follow the
rules of the compiler that built the arcade game Street Fighter III 3rd Strike: see [SF3.md](SF3.md).

No Renesas files are included. The stages' data and the rest of the compiler come from your copy of Release 26,
the archive decomp.me hosts.

## Requirements

- Windows and Python 3.8+
- Visual Studio 2017 or later with the C++ x86/x64 build tools (the Build Tools are enough), or Visual C++ 6
- To regenerate the C: Ghidra 12.0.4, a JDK 21 and Git Bash

## Build and check

    python tools/setup.py
    python build.py
    python tests/parity.py

`setup.py` downloads `shc-v5.0r26.tar.gz` (or takes its path), checks its SHA-256 and unpacks it into `extracted/`.
`build.py` writes `build/msvc/<stage>/<stage>.exe`; `--toolchain vc6` uses Visual C++ 6 (`VC6_DIR` = the folder
holding `VC98`). `parity.py` compiles `tests/cases` with Release 26 and with the rebuilt stages: with the rules at
0 every output must be identical, with the rules on it must match `tests/expected.tsv`. `--sf3 <checkout of
sfIII3-cps3-decomp>` does the same for the game's 824 C modules.

To use the stages, copy them over the ones in a copy of `extracted/bin` and point `SHC_LIB` at it. SHC rejects
an option value containing `-`, such as `-object=C:\my-dir\x.obj`.

## Regenerate the C

    export GHIDRA_HOME=<Ghidra 12.0.4> JAVA_HOME=<JDK 21>
    sh tools/regen-all.sh

This imports the four executables into a new Ghidra project (`ghidra/project`, default analysis), then for each
stage applies `ghidra/names/<stage>`, exports and rewrites `rebuild/<stage>`, reproducing the committed sources
exactly. Generated files (`src/0*.c`, `_relocs.c`, `_stubs.c`, `decls.h`, `stage_types.h`) aren't edited by hand:
change the tables or `tools/<stage>-fixes.py` and regenerate.

## Layout

    rebuild/<stage>   src/: a generated file per function and the hand-written _*.c; include/: headers
    ghidra/           names/: the tables; scripts/: the Ghidra scripts the export runs
    tools/            setup, export and regeneration
    tests/            parity.py, test sources, expected outputs

## Thanks

To decomp.me for hosting the compilers, and to DrewDos for his matching work and help.
