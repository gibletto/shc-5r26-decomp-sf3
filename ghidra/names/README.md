# Naming tables

`ghidra/names/<stage>/` holds everything a stage's C rebuild knows about names and types beyond Ghidra's own
analysis. The Ghidra project is never edited: `tools/export-stage-now.sh <stage>` opens it read-only, applies the
tables with `ghidra/scripts/ApplyStageTables.java`, and exports; `tools/regen-<stage>.sh` turns the export into
`rebuild/<stage>/src`. A name lives in exactly one place, a table row, and the next regen reproduces it
(`tools/regen-all.sh` does all four stages).

## Files

| File | Columns | Applied as |
|---|---|---|
| `entries.tsv` | address, note | code Ghidra's analysis left without a function (a dispatch-table target, a handler passed as a number): disassembled and made a function first, in the read-only session |
| `ret4-list.txt` | address | functions Ghidra left with an unlocked `undefined` return whose callers use the value: decompiled again with the return locked to 4 bytes |
| `enums.tsv` | enum, size, member, value | an enum of that size (a struct field of that type keeps its width). Give every value a member: the decompiler spells an unnamed value as an expression of others (`~(OP_AND\|OP_MUL)`), which C evaluates as an int |
| `types.h` | C struct definitions | parsed into the program (category `/stage`). Natural alignment only, so Ghidra's packing and Visual C++'s agree; `// @size name 0xNN` lines are checked by the script and become compile-time checks in the rebuild |
| `functions.tsv` | address, name, signature, note | the function's name, then the C prototype (if any). The note is the evidence; it is not applied |
| `globals.tsv` | address, name, type, note | a label, and data of that C type (`symbol *`, `symbol *[0x3fd]`, `literal_table`) when the type column is set |
| `locals.tsv` | function, old name, new name, type, first use, storage | a decompiler local renamed (and retyped). `first use`/`storage` (filled by `tools/key-locals.py`) find the variable when the decompiler has renumbered its temporaries |

`tools/gen-stage-types.py` writes `rebuild/<stage>/include/stage_types.h` from `enums.tsv` and `types.h` (a typedef
per struct, since Ghidra prints `psd *` not `struct psd *`; enum constants; the size checks); `decls.h` includes it.

## The loop

```sh
python tools/check-stage-tables.py <stage>            # widths, names, reserved words, collisions
tools/export-stage-now.sh <stage>                     # GHIDRA_HOME, GHIDRA_PROJECT
python tools/key-locals.py <stage>                    # after new locals rows: key them from the export
tools/regen-<stage>.sh
python build.py <stage>
python tests/parity.py                                # and with --sf3 <tree>
```

`export-stage-now.sh` takes `NAMES_DIR=<dir>` to try a variant of the tables without touching these.

## Rules the tools enforce, and why

- **Widths.** A signature keeps each parameter's width and the return's (the rebuild calls through unprototyped
  declarations, so the callee reads what its own C says). A return may be narrowed when every caller reads only
  its low byte/half (say so in the note: `low byte` / `low half`); then check the callers' decompilation gains no
  `extraout_`/`CONCAT`. A parameter width may change only with a `WIDTH:` note giving the machine-code reason
  (shcpep's .ofb writers copy the whole stack slot of their location argument). A function Ghidra left as `(void)` that reads stack
  arguments gets its parameters with a `PARAMS:` note giving the instructions that read them. An enum of
  `enums.tsv` is as wide as its size column. A variable the decompiler types as an enum but masks (`& 0xe0`) gets
  spelled with members (`& ~IL_NON_1F`, an int): retype it in locals.tsv (shcgen's read_ilb_node).
- **Names that would break the C.** Parameters and locals must not be type names (`code`, `byte`, `psd`), keywords
  or Win32 macros (`min`, `near`). A local must not be a global or function name: `decls.h` makes every global a
  macro. A renamed stack local must not be a struct field name: `frame-records.py` turns it into a `#define` view of
  the stock frame, which would rewrite `p->len`.
- **Stock CRT.** Statically linked C runtime routines compiled in the rebuild are `stock_<crt name>`, and CRT
  globals `stock_<name>`: the rebuild links the host CRT too, and a global macro named `_iob` would capture
  `stdout`.
- **Source fixes.** `tools/<stage>-fixes.py` anchors match table names and capture temporaries; a single space in
  a literal anchor matches a re-wrapped line. Variables an anchor names literally are listed in
  `check-stage-tables.py` (PROTECTED_BY_STAGE) so a locals row can't rename them.

## Naming a stage

Start with the records: a stage's own debug dumps often print field and function names (shcpep's `psdtbl->psdop`,
`eabase`, `dc_cmp start!`), and its opcode name table gives an enum. Then functions, signatures and globals, each
row with its evidence in the note column; then locals. Re-export, regenerate and check parity after each step.
A name the code does not support stays out of the tables.
