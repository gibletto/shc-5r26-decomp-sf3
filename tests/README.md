# Compiler tests

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
