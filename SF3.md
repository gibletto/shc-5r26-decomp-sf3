# The Street Fighter III rules

Street Fighter III 3rd Strike's arcade program was built with an SHC of the same family as Release 26, but not the
same compiler: compiled with Release 26, the game's decompiled C differs from the arcade's code in ways that no
change to the C removes. Each difference below was traced to the stage that makes it and turned into a rule. The
rules are on by default. The new optimization (`GEN_NARROW_NORMALIZE`) has a general safety argument and whole-program tests;
its single observed application does not establish the historical compiler's implementation.
Setting all 42 settings listed by `tests/parity.py` to 0 in the environment gives
Release 26's behaviour; individual switches select the decisions described below.

`ASM_READY_WAVES` is an additional optional scheduler mode, **off by default**.
Value 1 uses stable dependency-ready frontiers with FIFO promotion on predecessor
retirement; the existing phase/hazard chooser operates within each frontier.
It applies to the whole invocation, has no routine selectors, and is available
in normal updated builds. Leave it unset or 0 for existing game profiles. The
observed decoder result does not identify the historical compiler revision;
the model also changes a held pitch routine adversely. See `notes/shcasm.md` and
the separate native execution controls in `tests/ready_wave.py`.

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
| `SWITCH_ARCADE_BRANCH=1` | shcpep | folds a switch case's `bt case; bra default` into `bf default`, and every other `bt L; bra D; L:` into `bf D` | keeps the pair (value 2, which kept it only in front of a case or default label, is retired: no module of 3rd Strike, 2nd Impact or New Generation has the pair anywhere else) |
| `SWITCH_ARCADE_JUMP=3` | shcpep | deletes every `bra` to the next block in its flow pass | keeps it (`bra` to the next instruction, `nop`) unless all that stood between the jump and its label when the function was loaded was a bare jump under a label nothing referred to: the jump of a then arm in front of `else break;` (or `continue`, `goto`) still goes, as it does for a plain label that arrives while the function is loaded. Kept: the jump to a switch's case or default label (value 1, the rule before: a switch whose only label is `default`), the jump over an else arm that was shared with a later identical block, the jump in front of `else return;`, and the end of the compare chain of a switch whose cases are all `goto` |
| `PEP_RET_R0=15` | shcpep | keeps r1 free at a `return` (the register a far jump to the function's exit would use), so two returns share every instruction they end with, `mov #0,r0` included, and an instruction that uses r1 cannot fill the delay slot of the jump to the exit; when every return has become a tail call the unreached exit is dropped | bit 1: keeps r0 free instead: returns share their ending only as far back as it leaves r0 alone (never the `mov #K,r0` of `return K;`, but the store or call in front of a plain `return;`), and an instruction that uses r0 leaves a `nop` behind the jump to the shared code. Bit 2: inside a `switch`, a `return` whose shared part would be its whole block, starting at a label, keeps its own copy (an observed class, seven sites, reason unknown). Bit 4: after two returns were shared the exit stays, so a function whose paths all end in tail calls still has its epilogue and `rts` behind the last jump. Bit 8: when code that cannot be reached is deleted behind a jump, the label it jumped to stays counted as used (Release 26 takes the jump off the label's count), and if that label is the function's exit the exit stays too: `if (c) f(); else g(); break;` at the end of a function, both calls made tail calls, leaves the `break` unreachable and the epilogue and `rts` behind the last jump |
| `PEP_R0_FORGET=3` | shcpep | keeps a constant in r0 across a conditional branch | loads it again in both successors |
| `SLOT_NO_STACK=1` | shcpep | may fill a delay slot with a stack load or store | never does (pushes and pops still can) |
| `PEP_NO_THREAD=20` | shcpep | threads jumps through labels made by merging identical code | doesn't |
| `PEP_AUTOINC=3` | shcpep | folds a load through a pointer and a later `add` to the pointer into a post-increment load (`mov.l @r5+,r6`), and an `add` of minus the size to a pointer and a later store through it into a pre-decrement store (`mov.l r1,@-r4`) | leaves both apart; post-increments come only from `*p++` in the source, and `*--p = x` is a pre-decrement store only while `p` is used again (the last one of a run is `add #-4,r4` and `mov.l r1,@r4`) |
| `PEP_CASE_WORD=1` | shcpep | at a switch jump table, forgets that the code before it loaded a word literal, so the next literal pool is placed by the long reach | keeps the short reach until the first branch after the table (ten routines of `end_main.c`) |
| `PEP_RET_MAC=1` | shcpep | counts a saved MACH or MACL among the saved registers when it decides whether a `return` may need the exit label as a literal (the literal pool estimate) | leaves them out, so a function that saves one register and MACL estimates no literal for its returns (`check_combo_end`) |
| `GEN_TST_R0=1` | shcgen | gives a value that is only tested the highest free register of r0-r3 | gives it the lowest |
| `GEN_MUL_L=5` | shcgen | multiplies a `short` or `char` by a 16-bit constant with `muls.w`, which extends its operands itself, so the operand's cast to `int` is dropped | keeps `mul.l` (bit 1), and keeps the cast with it (bit 4): a `short` parameter is extended before it is multiplied (`exts.w r4,r1`, `mov #21,r3`, `mul.l r3,r1`) |
| `GEN_CHAIN_SCRATCH_R0=3` | shcgen | uses r1 as the possible far-jump scratch register for each case and default edge of a switch compare chain | uses the selector register r0, whose value is dead on those edges; reserves its actual use before case-state restoration, including a default-only switch. The ordinary branch producers and all delay-slot dependency checks stay unchanged (bit 1). Bit 2: a switch inside a loop body whose default edge is its own end (no `default` label) keeps Release 26's r1, so a value that lives through the loop is not moved to r1 at the end of the function (fade_cont_init's loop bound `num` stays in r10, saved, as in all three games; with bit 1 alone it moved to r1). No other routine of the three games decides: the full 3rd Strike, 2nd Impact and New Generation builds are byte-identical with 1 and with 3 |
| `GEN_JUMP_TEMP=2` | shcgen | charges the scratch register a `break` picks for its jump to the statement in front of it, so a value that lives through that statement (a counter tested just before a `break`) cannot move to that scratch register at the end of the function and keeps a saved register (`mov.l r10,@-r15`, `mov r5,r10`) | does not: the value moves to the scratch register (`mov r5,r1`) and the register is not saved; `continue`, `goto`, the jumps of `for` and `while` and the jump over an `else` are charged as in Release 26 (bit 1, `continue`, retired in round 52: no game module decides) |
| `GEN_POOL_MOVLOC=4` | shcgen | without optimization, counts a load or store of a local as 6 bytes when deciding where a literal pool goes | counts it as 4, so the pools of unoptimized files come later |
| `GEN_RELOAD=1` | shcgen | reads a variable kept in the frame from the scratch register an assignment or load left it in, whichever reference it is (`exts.w r0,r7` next to the store of a `short`) | does not for the variable's last reference, which reads the frame slot again (`mov.w r0,@(12,r15)`, `mov.w @(12,r15),r0`, `mov r0,r7`); earlier references, globals and locals whose address is taken still take the register |
| `GEN_EVICT_ORDER=1` | shcgen | when a register that is noted as holding a constant is noted as holding a variable instead (an array's address just loaded), forgets the register's own note first, so the note of one other register always survives | first forgets the older of the two notes when another register has one, so after an array's address is loaded the register that held an earlier address or constant counts as free |
| `GEN_RIGHT_FIRST_DROP=1` | shcgen | when an operator evaluates its right operand first, forgets at once the notes of the registers the left operand works in | forgets them after the operator's own template, so a base address the template loads for `@(r0,Rn)` still counts the right operand's note and pushes out an older note: `G = A[i] + B[i][0];` then stores through the register that held an earlier global's address |
| `GEN_NARROW_CONST=1` | shcgen | refuses a live cached constant as the right operand of an ADD/SUB when the left is a register, preserving a possible address displacement | permits reuse for byte/short integer results, which the later address-folding pass excludes; wide integers, pointers, arrays, label handling and template constraints keep their old decisions |
| `GEN_NARROW_NORMALIZE=1` | shcgen | widens a narrow compound result into a separate destination | normalizes it in its uniquely owned automatic-local home for a direct integer relational condition; volatile, address-observable, shared/fixed/reserved homes and other consumers keep the old path |
| `GEN_OR_INDEX_EARLY=1` | shcgen | a constant OR marks r0 as potentially clobbered, so an indexed word store loads its displacement after the OR | once the prepared assignment proves a pure register OR leaving r0 untouched, emits the independent displacement load first; quiet operands, fixed templates and the complete four-record footprint are required |
| `GEN_MEM_INDEX=27` | shcgen | when the address of an access is the sum of an operand that is still in memory and one that is not, loads an operand so that the access is indexed: a pointer read from memory (a row of a table of pointers, `table[a]` in `table[a][b]`; a pointer kept in the frame or in a global) beside an index in a register goes to r0 (`mov.l @(r0,r3),r0`, `mov.l @(r0,r2),r3`); a scaled index kept in the frame beside an array's address is loaded and the address goes to r0 (`mov.l @r15,r2`, `mov.l left,r0`, `mov.w @(r0,r2),r1`); a pointer read from memory beside an index already in r0 goes to a scratch register (`mov.l @r2,r3`, `mov.w @(r0,r3),r1`) | leaves the sum to an add in all three (bits 1, 2 and 8): `mov.l @(r0,r3),r3`, `add r3,r2`, `mov.l @r2,r1`; `mov.l left,r2`, `mov.l @r15,r1`, `add r2,r1`, `mov.w @r1,r3`; `add r3,r0`, `mov.w @r0,r1`. The access is still indexed when the pointer lands in r0 because the value is wanted there. A number beside a temporary of the optimizer that is kept in the frame (bit 16) also goes to the add: the temporary is loaded into the target register and the number added (`mov.l @(8,r15),r3`, `add #6,r3`, `mov.w @r3,r1`), where Release 26 loads it into a scratch register and reaches the member through a displacement. Two operands both in memory (bit 4) stay as in Release 26: no place in the game decides it |
| `GEN_STORE_INDEX=1` | shcgen | under a store whose value takes r0, gives up the indexed access for an address that is the sum of two registers, so the add template chooses the address register at once, before the value (`mov r7,r3; add r10,r3; ... jsr @r2; mov.w r0,@r3` for `ixa[i] = tsc / table[i];`) | keeps the indexed access when every r0 user in the value is a division or modulo: the value is chosen first and the address is then made base first in the next register (`mov r10,r2; add r7,r2; ... jsr @r3; mov.w r0,@r2`). Another r0 user (a call, `x | 1` through `or #imm,r0`) keeps Release 26's code: with any r0 user (bit 2, a diagnostic) Hi_Jump_Attack and Hi_Jump_Attack_Term lose their match |
| `GEN_COND_PREF=1` | shcgen | an assignment to a register that its right side does not need hands the register to the right side as a preference; for a conditional, `msg = (n < 2) ? &one : &many;` with msg in r7, the preference reaches the test, so the tested value is loaded into r7 and the 2 into r1 | does not hand it to a conditional (whose result goes to the register anyway): the test value goes where the chooser puts it (r1, with `cmp/ge #2` through r0 in credit_display_render). A single witness; the broad form, no conditional's test ever taking a preference (bit 2, a diagnostic), breaks effect_13_move and test_menu_init |
| `GEN_R0VAR=2` | shcgen | when one variable is the index of several arrays in a statement, copies it into r0 once and uses every array as a base (`exts.w r14,r0`, `mov.b @(r0,r8),r3`, `mov.b r3,@(r0,r9)`) | has no such variable: the index stays where it is, and each access either takes its array's address into r0 (`mov r8,r0`, `mov.b @(r0,r4),r3`) or adds (`add r4,r2`, `mov.b r3,@r2`) |
| `MDL_ARG_CONST=3` | shcmdl | doesn't count constants passed to calls when choosing register variables | counts them, so a constant used by several calls is kept in a register, also when the calls are inside a loop (bit 8, which kept the immediate inside loops, is no longer in the default) |
| `MDL_MUL_CONST=3` | shcmdl | never lets a `char` or `short` multiply read a constant from a register, so `c *= 16` is two `shll2` even with 16 in r12; sets the 16-bit constant of an `int` multiply of a `char` or `short` aside for `muls.w`, so it is loaded at every multiply | once the constant is in a register for its other uses, a `char` or `short` multiply reads it (`muls.w r12,r3`, `sts macl,r3`); the constant of an `int` multiply of a `char` or `short` counts like any other, so `s * 100` three times keeps 100 in a register (`mul.l r14,r1`) |
| `MDL_IMM_REG=63` | shcmdl | when it weighs a constant for a register and when it makes the uses read that register, passes over every use the operator can take as an immediate: the zero of `a[0]` (an add of zero in the tree) and the constant of `v & 3` stay in place (`mov.w r14,@r3`, `and #3,r0`) | does not pass over a zero that is added or subtracted, nor the constant of a bit-and: with zero in r14, `a[0] = 0` is `mov.w r14,@(r0,r14)` and a counter's start `x + 0` is `add r14,r12`; with 3 in r4, `v & 3` is `and r4,r0`. Bit 4: nor a nonzero constant added to or subtracted from a local variable (`(ix + 1) & 1` with 1 in r12 is `add r12,r2`, `and r12,r2`), while an add to a value first loaded from memory keeps its immediate (`p->code[n] + 1` is `add #1,r7`). Bit 8: nor the constant of an add- or subtract-assignment (`y -= 1` with 1 in r8 is `sub r8,r1`), which then also counts toward keeping the constant in a register. Bit 16: nor the constant of a bit-xor (`p->rl_flag ^ 1` with 1 kept in r11 is `xor r11,r0`). Which constants are candidates is as in Release 26, except bit 32: a zero compared unsigned against a converted value (`i < n` with `unsigned i`, `int n`, the entry test of an inverted loop with `i` folded to 0) is no immediate anywhere, so it is a use of the zero kept in a register and the compare reads that register (`cmp/hs r10,r4`), where Release 26, which reads the comparison's own always-signed type, copies it first (`mov r4,r3`, `cmp/hs r10,r3`); this rule has one witness, `strstr` |
| `MDL_MASK_AND=15` | shcmdl | turns a mask by 0xff into casts, `(T)(unsigned char)x`, for `x & 0xFF` and for `v &= 0xFF` on a variable, so the code extends (`extu.b r5,r5`); sign-extends a computed `short` before masking it, `(s16)-p->x & 0x3FF` (`neg r0,r0`, `exts.w r0,r5`, `and r14,r5`) | leaves the mask an and (`and #255,r0`, or `mov.w` of H'00FF and `and r1,r5`); `extu.b` comes from a cast or an `unsigned char`. 0xffff is converted as before. Bit 4: a computed `char` or `short` (not a variable or memory read) masked by a constant inside its width is not extended first (`neg r0,r0`, `mov r0,r5`, `and r14,r5`), and the and loads its constant before computing the value; this rule has one witness, `update_all_disp_pos_ending`. Bit 8: a value masked as it is stored, `((*cell++ = *tbl++) & 0x100) >> 8`, is extended first like a variable or memory read (`extu.w r1,r1` before `and r7,r1`); this rule has one witness, `eff91_cell_data_set` |
| `MDL_CAST_CSE=7` | shcmdl | takes an integer cast of an array or function name, `(u32)table`, as widening, so computes it once and keeps it across calls | loads it at each use, as Release 26 already does for `(u32)&x`; pointer casts are unaffected |
| `MDL_ARG_CAST=2` | shcmdl | keeps a variable in its argument register across a call only when the call is passed the variable itself | also when it is passed `&p->m` with m at offset 0, so `f(&p->first)` no longer moves p to a callee-saved register |
| `MDL_CAST_MUL=1` | shcmdl | leaves `(long)ix` of a `short` or `char` variable alone when its first use is scaled (`shorts[ix]`), but then keeps `(long)ix * 1`, the index of a `char` array, in a register across blocks (`exts.w r5,r4` once) | makes no temporary of that product either, so each `chars[ix]` extends `ix` again (`exts.w r5,r0`); when the first use of `ix` is not scaled the temporary stays |
| `MDL_MUL_ONE=33` | shcmdl | with the game's `-extra=m=8` keeps every product by 1, so the index of a `char` array read from memory, `(long)p->id * 1`, is another value than `(long)p->id`: beside a wider array indexed by the same member it gets a register copy of its own, and `chars[p->id] &= 0x80` copies the index out of r0 and loads the array's address twice (`mov r0,r3`, `mov.l chars,r0`, `mov.b @(r0,r3),r0`, `mov.l chars,r1`, `and #128,r0`, `add r3,r1`, `mov.b r0,@r1`) | folds the product when its operand is the cast of a value read from memory (a member or an element): the converted value is used as it is, and the compound assignment keeps the index in r0, loads the address once, reads through it indexed and copies it for the store (`mov.l chars,r1`, `mov.b @(r0,r1),r2`, `and r3,r2`, `mov r1,r3`, `add r0,r3`, `mov.b r2,@r3`); the product by 1 of a `char` or `short` variable's cast under a dereference is folded too (bit 32) unless the variable's first such product in the function is the test of an `if`; a product by 1 of any other expression stays |
| `MDL_TEMP_EXPR=1` | shcmdl | leaves every expression that holds a temporary alone: with `table[ix]` used in several blocks and `ix` used more often, the index is shared and each use adds the table address again | shares the expression as well: the index is computed once and the element address once more in front of its uses |
| `MDL_GCSE=10` | shcmdl | when the first of several equal expressions cannot share its value with the others (something on the way changes it), still computes the others once, in the block that dominates them; when the first can share with some of the others but not all (a call or a store comes between), shares the rest among themselves a second time (`&table[id]` once before a call and once more after it) | in the first case leaves the others alone, so each use computes the expression itself; in the second only the uses reached from the first share, and each use after the call computes the expression again |
| `MDL_IV=9` | shcmdl | forgets that a narrowing cast of an induction variable's multiple, `(char)(i * 6)`, is derived from the variable, so multiplies afresh on each pass; bit 8: turns the destination of a structure copy in a loop counting down into a pre-decrement access, which a block move can't take, so the pointer starts one element further and is stepped before each copy (`add #4,r1` before the loop, `add #-4,r1` ahead of the moves) | keeps the derivation, so the value steps by 6 like `i * 6`, for a cast to `char` or to `short` (bits 2 and 4, which picked one of the two, retired in round 52); bit 8: steps a structure copy's pointers after the copy, like any other use (`add #-4,r7` behind the moves) |
| `MDL_IV_BASE=1` | shcmdl | when it looks for induction variables, takes the address of a member reached through a pointer, `p->a`, as unchanging in the loop, so `p->a[i]` becomes a pointer that steps by the element size | takes it as it does when it moves expressions out of loops, as possibly changing: only `i * size` is stepped, and `p` and the member offset are added to it on each pass; the element of a static array, `a[i]`, still becomes a stepping pointer |
| `MDL_IV_TEMP=101` | shcmdl | when an expression derived from the loop variable is used more than once and so already sits in a temporary (`t = i * 2`, `t = &a[i]`), always makes that temporary the one that steps | does so only for an address that another argument of the same call takes again (`f(a[i].x, a[i].y)`) or that is used again in the same test, and for an address that a later statement uses while the variable counts down by one (`b[i].x = b[i - 1].x; b[i].y = b[i - 1].y;`); for a scaled index, whichever way the variable counts (`p->a[i] = p->b[i]`, `t[0][i] = t[0][i - 1]; t[1][i] = t[1][i - 1];`), for an address used again by a later statement while the variable counts up (`a[i].x = 0; a[i].y = 0;`) and for an address used again inside the assignment that first takes it (`r[j + 1] = r[j]` for a record, `x[i].m = k ^ x[i].n`) steps a new temporary and copies it into the first on each pass (`mov r4,r7`): the first use reads the new one, later uses the copy |
| `MDL_LOOP_INV=27` | shcmdl | with `-speed`, copies the test of every loop whose trip count it does not know in front of the loop (`for`/`while` become `if (c) do ... while (c)`) | does so only where it would without `-speed`: when the test compares two local variables or constants and the loop holds no other loop; every other loop keeps one test, at the bottom, entered by a jump, except a floating-point comparison, which is inverted as Release 26 does |
| `ASM_SPECREG=1` | shcasm | can schedule `sts macl` above the multiply it reads (a bug) | never does: the dependency lookup of Release 31 (and 32 and 5.1), which with every other stage of Release 26 compiles every routine of the three games exactly as Release 26 with this setting alone |
| `ASM_MULWAIT=5` | shcasm | holds `sts macl` back for two instructions after a multiply, and when nothing can issue without a stall issues the first ready instruction | holds it back for one; while the multiplier is busy the rule that keeps memory accesses at 0 mod 4 and the rest at 2 mod 4 is not applied (bit 4), so the first ready instruction is issued in either half: `mul.l r7,r0`, `mov r14,r0`, `sts macl,r4`, `mov.l @(disp,pc),r3` with the multiply at 2 mod 4, where Release 26's alignment takes the literal load first |

The value shown is the default. `GEN_CHAIN_SCRATCH_R0=0` restores Release 26's r1 reservation for a compare
chain's jumps, and `=1` the rule without its bit 2 (r0 for every switch); with scratch-r0 enabled, the actual r0 use is always charged.
Large case constants still require r1 for the real comparison. `ASM_SPECREG` fixes a fault in Release 26 itself:
since SH-4 support moved the special registers' numbers, its scheduler sees no dependency through MACL, so for
example `x = (x * 60) / 100` can read MACL before the `mul.l` that sets it. `tests/cases/macl.c` shows it.
Release 28 has the same fault; Release 31 fixed it, and the setting is that fix: Release 31's
`accumulate_operand_register_mask` takes a register from 0x41 on as bit `(reg - 0x41) % 32` of the mask's second
word, for an operand's register and its index register alike (Release 10, older, already gives the special
registers at 0x61 the same bits). Release 31's driver and `shcasm` with Release 26's `shcmdl`, `shcgen` and
`shcpep` compile all 10,048 routines of 3rd Strike, 7,585 of 2nd Impact and 5,458 of New Generation exactly
as the rebuilt stages do with every setting 0 but `ASM_SPECREG=1`. Its other stages are no model for the
games: its `shcmdl` and `shcgen` give Release 26's output, and its `shcpep` (548 routines of 3rd Strike
differ) is farther from the arcade in 389 of them and closer in 88, 51 of these only in a literal's
displacement or a pool's alignment that its own changes shift (it drops a tail `bra` to the next function,
and makes `add #-4,r15; mov.l r4,@r15` in a delay slot a push: so `backup_RO_PT` and `swallow_sprize_check`
match, while the arcade keeps that `bra` and that add and store).

Of the game's 10,066 C routines (sfIII3-cps3-decomp), 3,782 compile to the arcade's instructions with
Release 26 and all 10,066 with the rules; byte for byte, literal pools included, 1,883 and 10,066. With the
rules the linked program has the arcade program's SHA-1.

The rules' code is in `rebuild/shcpep/src/_pep_rules.c`, `rebuild/shcgen/src/_regknobs.c`, `rebuild/shcgen/src/_remaprules.c`,
`rebuild/shcgen/src/_poolrules.c`, `rebuild/shcgen/src/_reloadrules.c`, `rebuild/shcgen/src/_evictrules.c`,
`rebuild/shcgen/src/_gen_rules.c`, `rebuild/shcgen/src/_narrownormalize.c`,
`rebuild/shcgen/src/_memindexrules.c`, `rebuild/shcgen/src/_r0varrules.c`, `rebuild/shcgen/src/_construles.c`, `rebuild/shcgen/src/_orindexrules.c`,
`rebuild/shcmdl/src/_argconst.c`, `rebuild/shcmdl/src/_castrules.c`, `rebuild/shcmdl/src/_castmulrules.c`, `rebuild/shcmdl/src/_gcserules.c`,
`rebuild/shcmdl/src/_ivrules.c`, `rebuild/shcmdl/src/_looprules.c`, `rebuild/shcmdl/src/_maskrules.c`,
`rebuild/shcasm/src/_mulrules.c` and `tools/shcasm-fixes.py`;
`tools/<stage>-fixes.py` puts the calls into the generated functions. `python tests/parity.py --each-rule` lists which test cases each rule changes.

The switch-selector rule was checked over all 460 C modules of the round-21 source: nine direct producers
improved, none moved away from the arcade, and unchanged sites are nondiscriminating. Five direct routines
became byte-exact; two more gained from corrected branch distances after two default-only switches grew to
their arcade sizes. The selector survives conditional fallthrough to the next comparison, but is no longer
needed when a case/default edge is taken. This explains both freeing r1-dependent slots and keeping a slot
empty when its candidate writes r0. The corpus supports the choice; it does not expose an original far-switch
scratch-register witness. See `tests/chain_scratch.py` for executable near, far and default-only controls.

The narrow-constant rule was traced over all 460 C modules: four narrowed short sums use a cached constant
in the arcade, with no opposing narrowed site. Against a blanket bypass, 70 address consumers retain folding
and one wide sum retains its immediate; 17 address sites remain ambiguous. The bounded rule changes only
the four sums: `effect_32_init`, `effect_34_init` and `effect_L6_init` become byte-exact;
`effect_A0_init` improves but retains two unmatched words. No routine loses accuracy, no section grows,
and no non-code bytes or relocations change. The cache requires the complete value and labels to agree.
The signedness-independent width boundary already exists in `fold_address_add_sub`; it is not a literal,
register or function test. The arcade census has no byte/unsigned-short or SUB reuse witness. Native tests
exercise all four byte/short ADD types and verify wide/address controls, conversions and disabled parity;
their SUB cases execute correctly but do not trigger this choice. See `tests/narrow_const.py`.

The indexed-OR rule follows a proved intermediate-file edit. Release 26's preparation conservatively marks
every constant OR as clobbering r0; the later prepared register template can prove that this particular OR
leaves it untouched. The rule refines emission only after that proof, retaining the original preparation,
register choices and pool writers. It does not generally clear the earlier hazard: a cached constant can
alias r0 in other forms. Calls, labels, stack effects, volatile stores and r0 results are excluded.
The whole-game build changes two supported sites in `screentest_draw_crosshatch`; that routine and its
pool neighbour `screentest_page` become exact with native relocation identities checked. All other ROM
bytes stay unchanged. This is a sufficient mechanism supported by the arcade bytes, not a claim that the
arcade compiler implemented the same buffering. Setting `GEN_OR_INDEX_EARLY=0` restores the preceding image.

## Another compiler revision: Street Fighter III 2nd Impact

2nd Impact ([gibletto/sfIII2-cps3-decomp](https://github.com/gibletto/sfIII2-cps3-decomp)) was built by a slightly
different revision of the arcade compiler. Its build (`tools/build2i.py`, `REVISION`) sets fourteen settings, and
compiles its `-optimize=0` modules with `GEN_NARROW_CONST=0`; with those, every one of its 7,902 C routines compiles
to the arcade's exact bytes and the program is byte-identical. The settings that only 2nd Impact uses are off unless
set (`0`: Release 26 and the 3rd Strike build); the shared ones change the 3rd Strike default, and 3rd Strike's
`build.bat` sets `MDL_EQ_CONST=3`, `MDL_IV_WEB_ORDER=1` and `MDL_GCSE=26` as 2nd Impact does, and `PEP_RETURN_EXIT=2` (see New Generation return epilogues). Several rest on one routine so far, as noted.

| Setting (2nd Impact) | Stage | 3rd Strike | What 2nd Impact's revision does, and the routine that shows it |
|---|---|---|---|
| `MDL_MUL_CONST=31` | shcmdl | 3 | bits 4 and 8: a `short`/`char` `c *= k` outside loops; bit 16: the constant of a `short`/`char` multiply in an expression counts toward keeping it in a register (effect_79_init `pl_id * 3` with 3 also stored to my_family: `muls r6,r3`; one routine) |
| `MDL_IMM_REG=191` | shcmdl | 63 | bit 128: a nonzero constant added to an arithmetic expression of identifiers and constants is no immediate (effect_79_init; RANKING Setup_grade in New Generation). Bit 64, the same for locals, parameters and constants only, is retired: 128 covers it |
| `MDL_GCSE=26` | shcmdl | 26 (build.bat) | bit 16: where a loop was unrolled, no common-expression temporary for a cast of a variable (a local or a parameter) whose members are all in loops (sel_pl Setup_EFF75_Order; in all three games PLS03 shot_data_convert, a u16 parameter extended in each unrolled copy) |
| `MDL_IV_AUTOINC=1` | shcmdl | off | no auto-increment access for a widened load through a stepped temporary (RANKING Setup_Wins) |
| `MDL_MOD_CONST=3` | shcmdl | off | the divisor of a modulo (`% 4`) counts as a register use (effg8 effect_G8_init) |
| `MDL_EQ_CONST=3` | shcmdl | 3 (build.bat) | the constant of an `==`/`!=` compare is not an immediate for the weights and rewriters (CMD_MAIN debug_scene_outer_dispatch; in 3rd Strike cmb_cont combo_window_trans) |
| `MDL_IV_START0=6` | shcmdl | off | a stepped temporary that starts at `0 + p` starts at `p`, not for parameters (2) or variables assigned more than once (4) (EffE0 effect_E0_init; sc_trans tilemap_clear_rect keeps `0 + line`) |
| `MDL_IV_ADDR=1` | shcmdl | off | an integer sum whose invariant operand is a cast of an array's address does not extend a derived induction expression, and the address goes first after reduction (sc_trans player_name_trans) |
| `MDL_IV_WEB_ORDER=1` | shcmdl | 1 (build.bat) | in a loop holding a call, when the reduction made two or more `MDL_IV_TEMP` temporaries (one per arm of an if), a plain use's temporary enters the register candidate list right after the first of them met: the unstable profit sort then gives 2i's frame slots (textsound_2 sound_seq_start, in both games) |
| `GEN_STORE_RHS_INDEX=1` | shcgen | off | a store through a sum of two registers goes to the add template when its right side reads through an indexed sum sharing a variable with it; a store nested in the right side is not a read (EM_Cand Initialize_EM_Candidate, aboutspr init_char_gfx_tables) |
| `GEN_LAST_IDX=4` | shcgen | off | a template-slot pick of r4 for the extension of a K&R `short` parameter that only indexes a store leaves the last-chosen register as it was (sel_pl Sel_Arts_Sub; one routine) |
| `XJUMP_2I=18` | shcpep | off | cross-jumping keeps tails 2nd Impact keeps: mov-only label tails of two or more records with a register move, and JMP tails of moves behind labels outside switches (entry_2 Entry_01_Sub, EFFB8 effect_B8_init); bits 4, 8 and 32 (one-call tails, a dead block's label reference, call-plus-slot tails) are retired, so 62 means 18 |
| `PEP_SWITCH_END=1` | shcpep | off | the break label of a nested switch with two or more case bodies, whose following label heads a block starting with the outer break's jump, stays a label for threading (end_2 end_200_3000 / end_201_3000) |
| `ASM_CALL_SLACK=6` | shcasm | off | a forward call to a label in the same section counts 6 bytes nearer for the `bsr`/`jsr` choice (HITCHECK setup_catch_atthit; one routine) |

Each was measured on the whole 2nd Impact build (byte-identical with it) and, where it is off for 3rd Strike, the
3rd Strike build is unchanged. `GEN_OR_LEFT_KEEP` and `GEN_STORE_ADDR_AVOID`, settings of an earlier stage of the
2nd Impact work, are no longer used: they imitated a source difference (2nd Impact's `Suicide` is a scalar, not
3rd Strike's `s8 Suicide[8]`); their code stays, off.

## A third revision: Street Fighter III New Generation

New Generation ([gibletto/sfIII-cps3-decomp](https://github.com/gibletto/sfIII-cps3-decomp)) was built by a revision
close to 2nd Impact's. Its build (`tools/buildng.py`, `REVISION`) sets nine of 2nd Impact's fourteen settings with two of
them widened (the other five, `MDL_MUL_CONST`, `GEN_STORE_RHS_INDEX`, `ASM_CALL_SLACK`, `MDL_IV_ADDR` and
`MDL_IV_WEB_ORDER`, decide nothing in it), adds one more, and gives one module its own scheduler profile. All of them are off unless set, so the 2nd
Impact and 3rd Strike builds are unchanged.

| Setting (New Generation) | Stage | 2nd Impact | What New Generation's revision does, and the routine that shows it |
|---|---|---|---|
| `MDL_IMM_REG=191` | shcmdl | 191 | bit 128 (the same value as 2nd Impact's now): with bit 4, a `+`, `-` or `*` tree of identifiers, constants and casts may reuse a nonzero constant already kept in a register, global scalars included; a bare global, an indirect access or a call keeps the previous rule (RANKING Setup_grade; one routine) |
| `PEP_SWITCH_END=3` | shcpep | 1 | bit 2: consecutive nested switch ends also keep their break labels for threading (`tests/switch_end.py`) |
| `PEP_RETURN_EXIT=1` | shcpep | 2 (build.bat) | see below (EFFD7 effD7_select_end; 3rd Strike EM_Cand Check_EM_Buff); 1 and 2 are the same rule |
| `PEP_AUTOINC=0`, `ASM_READY_WAVES=1` | shcpep, shcasm | default, off | for one module only, `sound_voice_3` (the sequence decoder): no auto-increment folding, and the stable-frontier scheduler described at the top |

The game's `-optimize=0` modules also take `GEN_NARROW_CONST=0`, as in 2nd Impact. New Generation's sound driver
(`textsound_2`, `sound_voice`, `sound_voice_2`) was built by a much older SHC release than any available; its
routines are built from assembler in the game repository, and no setting here models that compiler.

## New Generation return epilogues

`PEP_RETURN_EXIT` is off by default. Any nonzero value makes a terminal numeric
literal a conditional-slot candidate when its block has no outgoing target and
falls through into a next block, whatever that block holds. The existing
stack-add exclusion, diamond/reference checks, call barriers and masks for the
branch and every instruction of both arms remain unchanged. No literal value,
destination register, routine name or address selects the behavior.

New Generation's `EFFD7:effD7_select_end` shows it: removing its branch to the
adjacent epilogue leaves the return literal terminal to the block-local scanner,
and the canonical complete 17-routine unit matches, including all linked pools.
3rd Strike's `EM_Cand:Check_EM_Buff` shows the wider case: `step =
random_16_com() & 1; if (step == 0) step = -1;` before a `while (1)` loop whose
bounds use 15 leaves `mov #15,r13` alone in the preheader the branch over `step =
-1` targets, and the arcade has it in that branch's slot (`bf/s`). 3rd Strike's
`build.bat` sets 2, New Generation 1; 2nd Impact builds byte-identical with or
without it. Value 1 once asked for the next block to hold only metadata and one
`EXIT`; the three full builds are byte-identical with the wider rule, so that
walk is retired. Disabled objects match the prior compiler. `tests/return_exit*.py`
cover the native guard, structural exclusions and SH2 execution.

## Diagnostics

Off unless set. The logs and traces only write files; they never change the output. The settings marked **diag**
change the output on purpose (they were used to find the rules) and exist only in a diagnostic build,
`python build.py --diag` (`build/msvc-diag`); the default build leaves their code out, so no setting outside the
rules above can change what the default stages produce. `tests/parity.py` clears every setting the stages read
before each compile.

| Setting | Stage | |
|---|---|---|
| `PEP_SKIP`, `PEP_POST_SKIP=<mask>` | shcpep | **diag**: leave out optimization passes |
| `JNEXT_LOG=<file>` | shcpep | log each jump to the next block the flow pass meets: function, label, the label record's kind, whether a block was deleted between them and whether one of those was more than a bare jump under a dead label, and the verdict |
| `PEP_LOG=<file>`, `XJUMP_LOG=<file>` | shcpep | log literal-pool and tail-merging decisions (a line per decision, with the function) |
| `XJUMP_OFF=<mask>` | shcpep | refuse kinds of tail merging (2: every `return` tail, the default when `PEP_RET_R0=0`; this was the rule before `PEP_RET_R0`) |
| `XJUMP_FLIP=<function>:<n>`, `XJUMP_MIN=<n>` | shcpep | **diag**: turn one logged tail-merging decision round; let tails of n records or more merge |
| `PEP_DUMP=<file>` | shcpep | write each function's blocks and records after loading and after each pass |
| `SHCGEN_REGTRACE=<file>` | shcgen | log every register choice |
| `SHCGEN_CTRACE=1`, `SHCGEN_CTRACE_BT=1` | shcgen | with `SHCGEN_REGTRACE`: also log each change of the r0-r3 notes (statement start, note made, note forgotten with its caller, hit), and with `_BT` the caller chain |
| `GEN_REMAP_LOG=<file>` | shcgen | log what the end-of-function move of register variables to r0-r3 sees |
| `GEN_OR_INDEX_LOG=<file>` | shcgen | log prepared indexed-OR eligibility and emitted footprints; one `%d` expands to the process ID. Headers identify the source. Units with no emitted nodes need separate coverage checks |
| `GEN_RELOAD_LOG=<file>` | shcgen | log each last reference that reads its frame slot again although a register holds the variable |
| `GEN_MEM_INDEX_LOG=<file>` | shcgen | log each address sum with an operand in memory that `GEN_MEM_INDEX` is asked about: the class of the other operand and whether the sum is left to an `add` |
| `MDL_MUL_ONE_LOG=<file>` | shcmdl | log each product by 1 that `MDL_MUL_ONE` folds: function, line and bit |
| `MDL_TEMP_EXPR_LOG=<file>` | shcmdl | log each class of two or more equal expressions that holds a temporary: function, operator, type, line, members, parent operator |
| `MDL_REGVAR_LOG=<file>` | shcmdl | log the register variables chosen and why |
| `MDL_LOOP_LOG=<file>` | shcmdl | log each loop the inversion pass looks at, what it asked and whether it inverted the loop |
| `MDL_IMM_LOG=<file>`, `MDL_MASK_LOG=<file>` | shcmdl | log each use `MDL_IMM_REG` no longer takes as an immediate, and each mask by 0xff the simplifier meets |
| `MDL_IV_LIT_LOG=<file>` | shcmdl | log each sum assigned to a stepped temporary (start or step) that the reassociation meets: function, terms in order and whether `MDL_IV` bit 16 kept the literal's place |
| `PEP_<name>=<int>` (`PEP_WFROM`, `PEP_LFROM`, `PEP_MARGIN`, `PEP_CARRY`, `PEP_LIM_L`, `PEP_LIM_W`, `PEP_ADD_E`, `PEP_ADD_3C`, ...) | shcpep | **diag**: the literal-pool placement's constants and variants (default: Release 26's) |
| `GEN_REG_TB_IDX`, `GEN_REG_ASC_IDX=<n,...>` | shcgen | **diag**: keep the last-chosen register / scan the other way at the listed register choices (numbered as `SHCGEN_REGTRACE` numbers them) |
| `SHCGEN_REGTRACE_DUMP=<file>` | shcgen | with `SHCGEN_REGTRACE`: dump the chooser's state at each choice |
| `GEN_COND_PREF_LOG`, `GEN_EVICT_LOG`, `GEN_STORE_INDEX_LOG=<file>` | shcgen | log each place the rule of that name is asked about |
| `GEN_NARROW_NORMALIZE_TRACE=1` | shcgen | trace each destination `GEN_NARROW_NORMALIZE` changes (stderr) |
| `MDL_GCSE_LOG`, `MDL_GCSE2_LOG`, `MDL_GCSE8_LOG=<file>` | shcmdl | log the common-expression classes each `MDL_GCSE` bit meets |
| `MDL_GCSE2_EXC`, `MDL_GCSE8_EXC=<file>` | shcmdl | **diag**: "function event" lines at which Release 26's reinsertion / new class is kept |
| `MDL_IV_TEMP_LOG=<file>`, `MDL_IV_TEMP_FORCE=<fn:n=v,...>` | shcmdl | log each `MDL_IV_TEMP` decision; **diag**: force one |
| `MDL_ARG_CALL=<hex digit>` | shcmdl | **diag**: narrow `MDL_ARG_CONST`'s groups to constants whose call takes them |
| `MDL_CAST_MUL_LOG`, `MDL_MUL_LOG`, `MDL_TEST_LOG=<file>` | shcmdl | log each place `MDL_CAST_MUL`, `MDL_MUL_CONST` and `MDL_TEST_REPLACE` decide |
| `MDL_REGVAR_BLOCKS=1`, `MDL_REGVAR_PRE=1` | shcmdl | with `MDL_REGVAR_LOG`: also each block's program points and edges, and the candidates before sorting |
| `ASM_NOSCHED=1` | shcasm | issue each scheduling window in input order |
| `SHC_ALIGN_FILE=<file>` | shcasm | **diag**: move named functions as if earlier code were longer |
