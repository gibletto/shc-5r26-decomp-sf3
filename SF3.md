# The Street Fighter III rules

Street Fighter III 3rd Strike's arcade program was built with an SHC of the same family as Release 26, but not the
same compiler: compiled with Release 26, the game's decompiled C differs from the arcade's code in ways that no
change to the C removes. Each difference below was traced to the stage that makes it and turned into a rule. The
rules are on by default; setting one to 0 in the environment gives Release 26's behaviour.

## An example

```c
int pick(int n, int a, int b)
{
    switch (n) {
    case 0:  return a;
    default: return b;
    }
}
```

Release 26, with the game's options and `-code=asmcode`:

```
_pick:                           ; function: pick
                                 ; frame size=0
          MOV         R4,R0
          CMP/EQ      #0,R0
          BF          L239
L238:                            ; case label
          RTS
          MOV         R5,R0
L239:                            ; default label
          MOV         R6,R0
L241:
          RTS
          NOP
```

These stages with the rules on, the shape the arcade's compiler uses for every switch case:

```
_pick:                           ; function: pick
                                 ; frame size=0
          MOV         R4,R0
          CMP/EQ      #0,R0
          BT          L238
          BRA         L239
          NOP
L238:                            ; case label
          RTS
          MOV         R5,R0
L239:                            ; default label
          MOV         R6,R0
L241:
          RTS
          NOP
```

Release 26's peephole stage folds the `bt`/`bra` pair into one `bf`. This is `pick` in `tests/cases/switch.c`.

## The rules

| Setting | Stage | Release 26 | With the rule |
|---|---|---|---|
| `SWITCH_ARCADE_BRANCH=2` | shcpep | folds a switch case's `bt case; bra default` into `bf default` | keeps the pair |
| `SWITCH_ARCADE_JUMP=1` | shcpep | deletes a `bra` to the next block | keeps it when that block is a case or default label |
| `XJUMP_OFF=2` | shcpep | merges identical `return` tails into one block the others jump to | each `return` keeps its own `rts`; jump and label tails still merge |
| `PEP_R0_FORGET=3` | shcpep | keeps a constant in r0 across a conditional branch | loads it again in both successors |
| `SLOT_NO_STACK=1` | shcpep | may fill a delay slot with a stack load or store | never does (pushes and pops still can) |
| `PEP_NO_THREAD=28` | shcpep | threads jumps through labels made by merging identical code | doesn't |
| `PEP_AUTOINC=1` | shcpep | folds a load through a pointer and a later `add` to the pointer into a post-increment load (`mov.l @r5+,r6`) | leaves them apart; post-increments come only from `*p++` in the source |
| `GEN_TST_R0=1` | shcgen | gives a value that is only tested the highest free register of r0-r3 | gives it the lowest |
| `GEN_MUL_L=3` | shcgen | multiplies a `short` or `char` by a 16-bit constant with `muls.w` | keeps `mul.l` |
| `GEN_CHAIN_JUMP=1` | shcgen | counts r1 as used by a switch's compare chain (the register a far jump would need), so a value live from the switch head into its cases cannot move from r13/r14 to r1 at the end of the function | leaves r1 free there: the value moves to r1 and r13/r14 is not saved |
| `MDL_ARG_CONST=b` | shcmdl | doesn't count constants passed to calls when choosing register variables | counts them, so a constant used by several calls is kept in a register |
| `MDL_CAST_CSE=7` | shcmdl | takes an integer cast of an array or function name, `(u32)table`, as widening, so computes it once and keeps it across calls | loads it at each use, as Release 26 already does for `(u32)&x`; pointer casts are unaffected |
| `MDL_ARG_CAST=6` | shcmdl | keeps a variable in its argument register across a call only when the call is passed the variable itself | also when it is passed `&p->m` with m at offset 0, so `f(&p->first)` no longer moves p to a callee-saved register |
| `MDL_GCSE=1` | shcmdl | lets later uses of a global variable read a copy that an earlier use in a dominating block kept in a register or on the stack | loads the global again at each use |
| `MDL_IV=3` | shcmdl | forgets that a cast to `char` of an induction variable's multiple, `(char)(i * 6)`, is derived from the variable, so multiplies afresh on each pass | keeps the derivation, so the value steps by 6 like `i * 6` (a cast to `short` is still forgotten: the arcade does not reduce those) |
| `ASM_SPECREG=1` | shcasm | can schedule `sts macl` above the multiply it reads (a bug) | never does |
| `ASM_MULWAIT=3` | shcasm | holds `sts macl` back for two instructions after a multiply, and when nothing can issue without a stall issues the first ready instruction | holds it back for one, and a forced issue skips instructions waiting on the multiplier |

The seventeen settings implement sixteen rules: the switch rule has two (`SWITCH_ARCADE_BRANCH` and `SWITCH_ARCADE_JUMP`).

0 gives Release 26 for each; the value shown is the default. `ASM_SPECREG` fixes a fault in Release 26 itself:
since SH-4 support moved the special registers' numbers, its scheduler sees no dependency through MACL, so for
example `x = (x * 60) / 100` can read MACL before the `mul.l` that sets it. `tests/cases/macl.c` shows it.

Of the game's 10,048 C routines (sfIII3-cps3-decomp as published), 3,684 compile to the arcade's instructions with
Release 26 and 8,623 with the rules; byte for byte, literal pools included, 1,745 and 7,958.

The rules' code is in `rebuild/shcpep/src/_pep_rules.c`, `rebuild/shcgen/src/_regknobs.c`, `rebuild/shcgen/src/_remaprules.c`,
`rebuild/shcmdl/src/_argconst.c`, `rebuild/shcmdl/src/_castrules.c`, `rebuild/shcmdl/src/_gcserules.c`,
`rebuild/shcasm/src/_mulrules.c` and `tools/shcasm-fixes.py`;
`tools/<stage>-fixes.py` puts the calls into the generated functions. `python tests/parity.py --each-rule` lists which test cases each rule changes.

## Diagnostics

Off unless set.

| Setting | Stage | |
|---|---|---|
| `PEP_SKIP`, `PEP_POST_SKIP=<mask>` | shcpep | leave out optimization passes |
| `PEP_LOG=<file>`, `XJUMP_LOG=<file>` | shcpep | log literal-pool and tail-merging decisions (a line per decision, with the function) |
| `PEP_DUMP=<file>` | shcpep | write each function's blocks and records after loading and after each pass |
| `SHCGEN_REGTRACE=<file>` | shcgen | log every register choice |
| `GEN_REMAP_LOG=<file>` | shcgen | log what the end-of-function move of register variables to r0-r3 sees |
| `MDL_REGVAR_LOG=<file>` | shcmdl | log the register variables chosen and why |
| `ASM_NOSCHED=1` | shcasm | issue each scheduling window in input order |
| `SHC_ALIGN_FILE=<file>` | shcasm | move named functions as if earlier code were longer |
