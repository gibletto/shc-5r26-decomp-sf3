# Compiler tests

`ready_wave.py` exercises the default-off `ASM_READY_WAVES` scheduler mode.
It compiles and links generic dependency joins, volatile accesses, overlapping
pointers, multiplies, branches, indirect calls and windows longer than 32 entries,
then executes them with the SH2 interpreter. Installed/unset/0 complete objects
must agree; mode1 must change scheduling while preserving results, memory and
callee saves. The optional profile supplies existing stage settings; omit the
new setting from it.

```
python tests/ready_wave.py --trial build/msvc/shcasm/shcasm.exe --production PATH_TO_COMPLETE_TOOLS --matchlab PATH_TO_GAME/tools/matchlab --work FRESH_PRIVATE_DIRECTORY [--profile SETTINGS.json]
```

Missing tool arguments skip cleanly. A supplied work directory must be fresh.

`narrow_const.py` is a separate native SH2 semantic test for
`GEN_NARROW_CONST`. Give it `--trial` (the new GEN executable),
`--production` and `--r26` (complete tool directories), `--matchlab`, and a fresh
`--work` directory. It compiles six settings once: stock, all rules zero, previous
GEN, unset, explicit zero, and one. Disabled native objects and date-normalized
listings must match; signed/unsigned byte/short ADDs must change, while wide and
address controls must not. Boundary inputs check return values, memory and saved
registers. SUB fixtures execute but do not trigger this choice and are not claimed
as SUB policy coverage. `--readback` repeats checks on retained outputs without
compiling or linking. `--diagnostic-work` also checks the new default against
retained enabled output of a default-off diagnostic. This does not change the
existing byte-parity inventory.

`python tests/parity.py` checks all rule settings at zero against Release 26 and
the default rules against `expected.tsv`. `sf3-expected.tsv` is refreshed only
with the separately authorized game/compiler export.

The switch-chain scratch test compiles and links native SH2 code, then checks its
returns, volatile stores and callee-saved registers with the companion game's
existing interpreter:

```
python tests/chain_scratch.py --matchlab PATH_TO_GAME/tools/matchlab --work FRESH_PRIVATE_DIRECTORY
```

The default stage directory is `build/msvc`; `--exes` and `--r26` can override it
and the original tool directory. All outputs and temporary files stay under the
fresh work directory. Six fixtures cover a reused selector, a selector assigned
from a call, default-only and absent-default switches, large case constants,
short branches, medium BRA expansion and genuine far indirect jumps. Both
settings of `GEN_CHAIN_SCRATCH_R0` are run. The long case
bodies use volatile increments so their distances cannot disappear through
constant folding. The test also checks which branch forms actually appeared.

These are SH2/PIC0 controls. They do not claim dynamic coverage of PIC expansion
or ordinary C case fallthrough. The standalone semantic test does not change
the existing 48-case byte-parity inventory.

The default-rule expectations changed only for `chainjump` (the r1 constant
enters the first conditional slot) and `switch`/`switch_sh1` (the default-only
selector load stays before its jump, leaving a NOP and changing pool alignment).

The nested-switch boundary controls run separately:

```
python tests/switch_end.py --work-dir FRESH_PRIVATE_DIRECTORY
```

They compare complete date-normalized objects for `PEP_SWITCH_END` modes 0, 1,
2 and 3. Bit 2 changes the adjacent nested-end fixture; inserting a call between
the ends leaves the object unchanged. Existing bit 1 remains independent.


Terminal-return scheduling controls (`PEP_RETURN_EXIT`, default 0):

```
python tests/return_exit_native.py --work FRESH_NATIVE_DIRECTORY
python tests/return_exit.py --trial NEW/shcpep.exe --production OLD_BIN --matchlab GAME/tools/matchlab --profile STAGE_SETTINGS.json --work FRESH_EXECUTION_DIRECTORY
```

The native test compiles the actual finder, its block-local scanner and stack-add
check, plus the verbatim helper/setting reader from `_pep_rules.c`. It runs 27
structural cases with stock/rules builds and unset/0/1: literal values and GPRs,
15-record continuation boundaries, outgoing targets, strict adjacency, extra
labels/exits/real records, operand kinds and stack-add consumers.

The SH2 test compares installed, candidate-unset, zero and one. All disabled
objects must match. Eight C controls execute both arms and the early return,
including negative/positive literals, 32/160-byte frames, an arm operand
dependency, a call and an extra join predecessor. The latter three objects must
stay unchanged. Return values, all caller memory and callee-saved registers are
checked in 1,536 executions. The observer call is modeled as memory-preserving
and clobbering caller registers/T. These are SH2/PIC0 controls.

`--profile` is optional JSON of the existing stage settings and must exclude
`PEP_RETURN_EXIT`, which the runner controls. Inputs and proof artifacts stay in
the fresh work directory; no tool is installed. With no tool arguments the SH2
runner skips, like the other optional native tests.

`imm_expr.py` tests the default-off `MDL_IMM_REG` bit 128 with native SH2
execution. Pass `--trial` (candidate shcmdl.exe), `--production`, `--r26`,
`--matchlab` and a fresh `--work`. Seven arithmetic cases cover sums,
differences, products, casts and cached constants 1, 7, -3 and 16. Six controls
cover a direct global read, local-only expression, indirect reads, calls, zero
and a constant outside imm8. It compares disabled objects/listings with the
previous stages and Release26, checks which function bodies changed, then
executes all seven compiler modes over signed-byte boundary inputs. Returns,
argument stores, untouched inputs and callee-saved registers are checked.
The byte-parity case inventory and default expectations are unchanged.
