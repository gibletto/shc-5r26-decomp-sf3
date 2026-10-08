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
| `PEP_RET_R0=15` | shcpep | keeps r1 free at a `return` (the register a far jump to the function's exit would use), so two returns share every instruction they end with, `mov #0,r0` included, and an instruction that uses r1 cannot fill the delay slot of the jump to the exit; when every return has become a tail call the unreached exit is dropped | bit 1: keeps r0 free instead: returns share their ending only as far back as it leaves r0 alone (never the `mov #K,r0` of `return K;`, but the store or call in front of a plain `return;`), and an instruction that uses r0 leaves a `nop` behind the jump to the shared code. Bit 2: inside a `switch`, a `return` whose shared part would be its whole block, starting at a label, keeps its own copy (an observed class, seven sites, reason unknown). Bit 4: after two returns were shared the exit stays, so a function whose paths all end in tail calls still has its epilogue and `rts` behind the last jump. Bit 8: when code that cannot be reached is deleted behind a jump, the label it jumped to stays counted as used (Release 26 takes the jump off the label's count), and if that label is the function's exit the exit stays too: `if (c) f(); else g(); break;` at the end of a function, both calls made tail calls, leaves the `break` unreachable and the epilogue and `rts` behind the last jump |
| `PEP_R0_FORGET=3` | shcpep | keeps a constant in r0 across a conditional branch | loads it again in both successors |
| `SLOT_NO_STACK=1` | shcpep | may fill a delay slot with a stack load or store | never does (pushes and pops still can) |
| `PEP_NO_THREAD=28` | shcpep | threads jumps through labels made by merging identical code | doesn't |
| `PEP_AUTOINC=3` | shcpep | folds a load through a pointer and a later `add` to the pointer into a post-increment load (`mov.l @r5+,r6`), and an `add` of minus the size to a pointer and a later store through it into a pre-decrement store (`mov.l r1,@-r4`) | leaves both apart; post-increments come only from `*p++` in the source, and `*--p = x` is a pre-decrement store only while `p` is used again (the last one of a run is `add #-4,r4` and `mov.l r1,@r4`) |
| `GEN_TST_R0=1` | shcgen | gives a value that is only tested the highest free register of r0-r3 | gives it the lowest |
| `GEN_MUL_L=7` | shcgen | multiplies a `short` or `char` by a 16-bit constant with `muls.w`, which extends its operands itself, so the operand's cast to `int` is dropped | keeps `mul.l` (bits 1 and 2), and keeps the cast with it (bit 4): a `short` parameter is extended before it is multiplied (`exts.w r4,r1`, `mov #21,r3`, `mul.l r3,r1`) |
| `GEN_CHAIN_JUMP=1` | shcgen | counts r1 as used by a switch's compare chain (the register a far jump would need), so a value live from the switch head into its cases cannot move from r13/r14 to r1 at the end of the function | leaves r1 free there: the value moves to r1 and r13/r14 is not saved |
| `GEN_JUMP_TEMP=3` | shcgen | charges the scratch register a `break` or a `continue` picks for its jump to the statement in front of it, so a value that lives through that statement (the copy of a stepped pointer in a loop body that ends in `continue`, a counter tested just before a `break`) cannot move to that scratch register at the end of the function and keeps a saved register (`mov.l r10,@-r15`, `mov r5,r10`) | does not: the value moves to the scratch register (`mov r5,r1`) and the register is not saved; `goto`, the jumps of `for` and `while` and the jump over an `else` are charged as in Release 26 |
| `GEN_POOL_MOVLOC=4` | shcgen | without optimization, counts a load or store of a local as 6 bytes when deciding where a literal pool goes | counts it as 4, so the pools of unoptimized files come later |
| `GEN_RELOAD=1` | shcgen | reads a variable kept in the frame from the scratch register an assignment or load left it in, whichever reference it is (`exts.w r0,r7` next to the store of a `short`) | does not for the variable's last reference, which reads the frame slot again (`mov.w r0,@(12,r15)`, `mov.w @(12,r15),r0`, `mov r0,r7`); earlier references, globals and locals whose address is taken still take the register |
| `GEN_EVICT_ORDER=1` | shcgen | when a register that is noted as holding a constant is noted as holding a variable instead (an array's address just loaded), forgets the register's own note first, so the note of one other register always survives | first forgets the older of the two notes when another register has one, so after an array's address is loaded the register that held an earlier address or constant counts as free |
| `GEN_MEM_INDEX=11` | shcgen | when the address of an access is the sum of an operand that is still in memory and one that is not, loads an operand so that the access is indexed: a pointer read from memory (a row of a table of pointers, `table[a]` in `table[a][b]`; a pointer kept in the frame or in a global) beside an index in a register goes to r0 (`mov.l @(r0,r3),r0`, `mov.l @(r0,r2),r3`); a scaled index kept in the frame beside an array's address is loaded and the address goes to r0 (`mov.l @r15,r2`, `mov.l left,r0`, `mov.w @(r0,r2),r1`); a pointer read from memory beside an index already in r0 goes to a scratch register (`mov.l @r2,r3`, `mov.w @(r0,r3),r1`) | leaves the sum to an add in all three (bits 1, 2 and 8): `mov.l @(r0,r3),r3`, `add r3,r2`, `mov.l @r2,r1`; `mov.l left,r2`, `mov.l @r15,r1`, `add r2,r1`, `mov.w @r1,r3`; `add r3,r0`, `mov.w @r0,r1`. The access is still indexed when the pointer lands in r0 because the value is wanted there. Two operands both in memory (bit 4) stay as in Release 26: no place in the game decides it |
| `GEN_R0VAR=2` | shcgen | when one variable is the index of several arrays in a statement, copies it into r0 once and uses every array as a base (`exts.w r14,r0`, `mov.b @(r0,r8),r3`, `mov.b r3,@(r0,r9)`) | has no such variable: the index stays where it is, and each access either takes its array's address into r0 (`mov r8,r0`, `mov.b @(r0,r4),r3`) or adds (`add r4,r2`, `mov.b r3,@r2`) |
| `MDL_ARG_CONST=b` | shcmdl | doesn't count constants passed to calls when choosing register variables | counts them, so a constant used by several calls is kept in a register |
| `MDL_MUL_CONST=3` | shcmdl | never lets a `char` or `short` multiply read a constant from a register, so `c *= 16` is two `shll2` even with 16 in r12; sets the 16-bit constant of an `int` multiply of a `char` or `short` aside for `muls.w`, so it is loaded at every multiply | once the constant is in a register for its other uses, a `char` or `short` multiply reads it (`muls.w r12,r3`, `sts macl,r3`); the constant of an `int` multiply of a `char` or `short` counts like any other, so `s * 100` three times keeps 100 in a register (`mul.l r14,r1`) |
| `MDL_IMM_REG=15` | shcmdl | when it weighs a constant for a register and when it makes the uses read that register, passes over every use the operator can take as an immediate: the zero of `a[0]` (an add of zero in the tree) and the constant of `v & 3` stay in place (`mov.w r14,@r3`, `and #3,r0`) | does not pass over a zero that is added or subtracted, nor the constant of a bit-and: with zero in r14, `a[0] = 0` is `mov.w r14,@(r0,r14)` and a counter's start `x + 0` is `add r14,r12`; with 3 in r4, `v & 3` is `and r4,r0`. Bit 4: nor a nonzero constant added to or subtracted from a local variable (`(ix + 1) & 1` with 1 in r12 is `add r12,r2`, `and r12,r2`), while an add to a value first loaded from memory keeps its immediate (`p->code[n] + 1` is `add #1,r7`). Bit 8: nor the constant of an add- or subtract-assignment (`y -= 1` with 1 in r8 is `sub r8,r1`), which then also counts toward keeping the constant in a register. Which constants are candidates is as in Release 26 |
| `MDL_MASK_AND=3` | shcmdl | turns a mask by 0xff into casts, `(T)(unsigned char)x`, for `x & 0xFF` and for `v &= 0xFF` on a variable, so the code extends (`extu.b r5,r5`) | leaves the mask an and (`and #255,r0`, or `mov.w` of H'00FF and `and r1,r5`); `extu.b` comes from a cast or an `unsigned char`. 0xffff is converted as before |
| `MDL_CAST_CSE=7` | shcmdl | takes an integer cast of an array or function name, `(u32)table`, as widening, so computes it once and keeps it across calls | loads it at each use, as Release 26 already does for `(u32)&x`; pointer casts are unaffected |
| `MDL_ARG_CAST=6` | shcmdl | keeps a variable in its argument register across a call only when the call is passed the variable itself | also when it is passed `&p->m` with m at offset 0, so `f(&p->first)` no longer moves p to a callee-saved register |
| `MDL_CAST_MUL=1` | shcmdl | leaves `(long)ix` of a `short` or `char` variable alone when its first use is scaled (`shorts[ix]`), but then keeps `(long)ix * 1`, the index of a `char` array, in a register across blocks (`exts.w r5,r4` once) | makes no temporary of that product either, so each `chars[ix]` extends `ix` again (`exts.w r5,r0`); when the first use of `ix` is not scaled the temporary stays |
| `MDL_GCSE=11` | shcmdl | lets later uses of a global variable read a copy that an earlier use in a dominating block kept in a register or on the stack; when the first of several equal expressions cannot share its value with the others (something on the way changes it), still computes the others once, in the block that dominates them; when the first can share with some of the others but not all (a call or a store comes between), shares the rest among themselves a second time (`&table[id]` once before a call and once more after it) | loads the global again at each use; in the second case leaves the others alone, so each use computes the expression itself; in the third only the uses reached from the first share, and each use after the call computes the expression again |
| `MDL_IV=3` | shcmdl | forgets that a cast to `char` of an induction variable's multiple, `(char)(i * 6)`, is derived from the variable, so multiplies afresh on each pass | keeps the derivation, so the value steps by 6 like `i * 6` (a cast to `short` is still forgotten: the arcade does not reduce those) |
| `MDL_IV_BASE=3` | shcmdl | when it looks for induction variables, takes the address of a member reached through a pointer, `p->a`, as unchanging in the loop, so `p->a[i]` becomes a pointer that steps by the element size | takes it as it does when it moves expressions out of loops, as possibly changing: only `i * size` is stepped, and `p` and the member offset are added to it on each pass; the element of a static array, `a[i]`, still becomes a stepping pointer |
| `MDL_IV_TEMP=117` | shcmdl | when an expression derived from the loop variable is used more than once and so already sits in a temporary (`t = i * 2`, `t = &a[i]`), always makes that temporary the one that steps | does so only for an address that another argument of the same call takes again (`f(a[i].x, a[i].y)`) or that is used again in the same test, and for an address that a later statement uses while the variable counts down by one (`b[i].x = b[i - 1].x; b[i].y = b[i - 1].y;`); for a scaled index, whichever way the variable counts (`p->a[i] = p->b[i]`, `t[0][i] = t[0][i - 1]; t[1][i] = t[1][i - 1];`), for an address used again by a later statement while the variable counts up (`a[i].x = 0; a[i].y = 0;`) and for an address used again inside the assignment that first takes it (`r[j + 1] = r[j]` for a record, `x[i].m = k ^ x[i].n`) steps a new temporary and copies it into the first on each pass (`mov r4,r7`): the first use reads the new one, later uses the copy; the index of a `char` array, `(long)i * 1`, is not stepped at all (`exts.w r4,r6` on each pass, `i` stays the counter) |
| `MDL_TEST_REPLACE=13` | shcmdl | keeps the counter of a loop beside the pointers it steps (`add #1,r14`, `cmp/hs r13,r14`): the code that rewrites the loop's test is there but no option switches it on | when every use of an `int` or `long` counter has become a stepped address (at most three) and the test reads the counter, compares one of the addresses with the end of the table (`mov.w` of the size and `add` before the loop, `cmp/hs r14,r4` in it) and drops the counter; a `short` or `char` counter, and a loop where only an integer multiple of the counter is stepped, keep the counter |
| `MDL_LOOP_INV=31` | shcmdl | with `-speed`, copies the test of every loop whose trip count it does not know in front of the loop (`for`/`while` become `if (c) do ... while (c)`) | does so only where it would without `-speed`: when the test compares two local variables or constants and the loop holds no other loop; every other loop keeps one test, at the bottom, entered by a jump |
| `ASM_SPECREG=1` | shcasm | can schedule `sts macl` above the multiply it reads (a bug) | never does |
| `ASM_MULWAIT=3` | shcasm | holds `sts macl` back for two instructions after a multiply, and when nothing can issue without a stall issues the first ready instruction | holds it back for one, and a forced issue skips instructions waiting on the multiplier |

0 gives Release 26 for each; the value shown is the default. `ASM_SPECREG` fixes a fault in Release 26 itself:
since SH-4 support moved the special registers' numbers, its scheduler sees no dependency through MACL, so for
example `x = (x * 60) / 100` can read MACL before the `mul.l` that sets it. `tests/cases/macl.c` shows it.

Of the game's 10,063 C routines (sfIII3-cps3-decomp), 3,785 compile to the arcade's instructions with
Release 26 and 9,338 with the rules; byte for byte, literal pools included, 1,846 and 8,900.

The rules' code is in `rebuild/shcpep/src/_pep_rules.c`, `rebuild/shcgen/src/_regknobs.c`, `rebuild/shcgen/src/_remaprules.c`,
`rebuild/shcgen/src/_poolrules.c`, `rebuild/shcgen/src/_reloadrules.c`, `rebuild/shcgen/src/_evictrules.c`,
`rebuild/shcgen/src/_memindexrules.c`, `rebuild/shcgen/src/_r0varrules.c`,
`rebuild/shcmdl/src/_argconst.c`, `rebuild/shcmdl/src/_castrules.c`, `rebuild/shcmdl/src/_castmulrules.c`, `rebuild/shcmdl/src/_gcserules.c`,
`rebuild/shcmdl/src/_ivrules.c`, `rebuild/shcmdl/src/_looprules.c`, `rebuild/shcmdl/src/_maskrules.c`,
`rebuild/shcasm/src/_mulrules.c` and `tools/shcasm-fixes.py`;
`tools/<stage>-fixes.py` puts the calls into the generated functions. `python tests/parity.py --each-rule` lists which test cases each rule changes.

## Diagnostics

Off unless set.

| Setting | Stage | |
|---|---|---|
| `PEP_SKIP`, `PEP_POST_SKIP=<mask>` | shcpep | leave out optimization passes |
| `PEP_LOG=<file>`, `XJUMP_LOG=<file>` | shcpep | log literal-pool and tail-merging decisions (a line per decision, with the function) |
| `XJUMP_OFF=<mask>`, `XJUMP_FLIP=<function>:<n>` | shcpep | refuse kinds of tail merging (2: every `return` tail, the default when `PEP_RET_R0=0`; this was the rule before `PEP_RET_R0`), or turn one logged decision round |
| `PEP_DUMP=<file>` | shcpep | write each function's blocks and records after loading and after each pass |
| `SHCGEN_REGTRACE=<file>` | shcgen | log every register choice |
| `GEN_REMAP_LOG=<file>` | shcgen | log what the end-of-function move of register variables to r0-r3 sees |
| `GEN_RELOAD_LOG=<file>` | shcgen | log each last reference that reads its frame slot again although a register holds the variable |
| `GEN_MEM_INDEX_LOG=<file>` | shcgen | log each address sum with an operand in memory that `GEN_MEM_INDEX` is asked about: the class of the other operand and whether the sum is left to an `add` |
| `MDL_MUL_ONE=<bits>` | shcmdl | a measured lead, off by default: folds a product by 1 although the game's `-extra=m=8` keeps it (1: of a converted value read from memory; see `rebuild/shcmdl/src/_castmulrules.c`) |
| `MDL_REGVAR_LOG=<file>` | shcmdl | log the register variables chosen and why |
| `MDL_LOOP_LOG=<file>` | shcmdl | log each loop the inversion pass looks at, what it asked and whether it inverted the loop |
| `MDL_IMM_LOG=<file>`, `MDL_MASK_LOG=<file>` | shcmdl | log each use `MDL_IMM_REG` no longer takes as an immediate, and each mask by 0xff the simplifier meets |
| `ASM_NOSCHED=1` | shcasm | issue each scheduling window in input order |
| `SHC_ALIGN_FILE=<file>` | shcasm | move named functions as if earlier code were longer |
