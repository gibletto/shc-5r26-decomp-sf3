/* The arcade's argument-constant rule, MDL_ARG_CONST (only with SHC_REBUILD_UPDATED=1).

   The register-variable weight of a common expression (weigh_common_expression_candidates) counts each occurrence of a constant but skips
   one the operator can take as an immediate (is_immediate_operand(parent, operand position, value) != 0). For a call
   argument (parent IL_ARG) an imm8 constant bound for r4..r7 counts as an immediate, so `f(w, -1, 7, 1, -1)` gives the
   -1 weight 1: never >= 3, never hoisted into a callee-saved register. The arcade's compiler hoists such constants,
   as if register-bound arguments counted.

   MDL_ARG_CONST=<hex digit>, a bit mask over the callers of is_immediate_operand (ARGCONST_FIT's group):
     1  the weight counter (weigh_common_expression_candidates)
     2  the rewriters that make the occurrences read the register (materialize_constant_lreg, write_lreg_numbers)
     4  collect_register_candidate
     8  with 1 or 2: keep the stock answer for an occurrence inside a loop (its block has an lptbl). Retired
        2026-10-16 (no longer in the default): in the arcade's load_player_color the zero passed to
        polygon2d_submit_quad inside a loop comes from a register (`mov r14,r7`), as outside loops.
   A set bit answers 0 ("not an immediate") for a constant whose parent is a call argument. Unset: 3 (weight and
   rewriters: the arcade behaviour; b until 2026-10-16); 0: Release 26.
   MDL_ARG_CALL=<hex digit>, the same groups (unset: 0), a diagnostic (builds with SHC_REBUILD_DIAG=1 only): narrows the 0 answer to a constant whose call
   also passes the same value in an argument is_immediate_operand does not take as an immediate (a stack argument). */
#include "decls.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <process.h>

#define ARG_CONST_DEFAULT 0x3

/* the variable's first character as a hex digit ('0'-'9', 'a'-'f'); dflt when unset */
static int knob(const char *name, int dflt)
{
    const char *v = getenv(name);
    unsigned int c;
    if (!v)
        return dflt;
    c = (unsigned char)*v - 0x30;
    if (c > 9)
        c -= 0x27;
    return (int)c;
}

/* the stock answer, or 0 if a sibling argument of the same constant value is not an immediate */
static int call_rule(il_node *parent, int pos, unsigned int value)
{
    int r = is_immediate_operand(parent, pos, value), i = 1;
    il_node *arg;
    if (r == 0)
        return 0;
    for (arg = parent->child; arg != 0; arg = arg->next, i++) {
        if (i != pos && arg->op == IL_CONST && (unsigned int)arg->val == value && is_immediate_operand(parent, i, value) == 0)
            return 0;
    }
    return r;
}

/* The arcade's rules for the constant of a multiply, MDL_MUL_CONST.

   is_immediate_operand's multiply case answers 1 ("the operator takes this constant as it is", so the constant is
   no register candidate, adds no weight to its class and the rewriters leave it in place) for
     A  an int multiply of a widened char or short by a 16-bit constant: Release 26's shcgen multiplies those with
        muls.w/mulu.w and loads the constant itself;
     B  any multiply whose own type is char or short (`c *= 16`, an index a cast has narrowed);
     C  50 or 100 with -speed on the SH-1;
     D, E  a constant shcgen expands into one shift or two shift-and-add terms.
   shcgen shifts for a multiply only while its operand is still a constant and multiplies when it is a register,
   so whether `c *= 16` becomes two shll2 or muls.w is decided here, by the rewriters' question.

   MDL_MUL_CONST=<bits> (unset: 3; 0: Release 26)
     1  the rewriters (materialize_constant_lreg, write_lreg_numbers) take the constant of a char or short
        multiply (B) as not an immediate: once the constant has a register through its other uses, the multiply
        reads the register, also where shifts would be shorter (`muls.w r12,r3` / `sts macl,r3` for `c *= 16` with
        16 in r12, and MACL saved). Candidates and weight are as in Release 26.
     2  A is passed over for every asker, so the constant is judged by C, D and E like any int multiply's: one
        that is no shift-and-add constant (100, 38) is a candidate and counts, and with three uses it is kept in a
        register and multiplied from there (`mul.l r14,r1`). This is the shcmdl side of GEN_MUL_L: the arcade's
        shcgen leaves such a multiply a mul.l, and its shcmdl does not set the constant aside for a muls.w.
     4  (2nd Impact's compiler revision; off in the 3rd Strike build) the weight counter counts the constant of a
        `c *= k` on a char or short (A_MUL, B) outside any loop as not an immediate, and
     8  (with 4) collect_register_candidate takes it as not an immediate, so it can open the constant's class:
        `ix = Game_setting.mode != 0; ix *= 2;` with 2 also stored to my_family keeps 2 in a register and
        multiplies by it (`muls.w r7,r14`). Inside a loop, or for an index multiply (MUL), the constant stays an
        immediate (`w_flag *= 2` in cmd_main_2's loops, the row scale 40 in test_menu_select are shifts in 2i).
        Measured 2026-10-19 (2nd Impact, MDL_MUL_CONST=15): EFF16 effect_16_init and EFFI0's effect_H9_init
        multiply as 2i does; no other function of the 5,916 already matched changes.
    16  (2nd Impact's compiler revision) the weight counter also counts the constant of a char or short multiply
        in an expression (MUL, B) as not an immediate, in a loop too; it opens no class.
        With the constant in a register for a store, it then stays there for the multiply: effect_79_init's
        `my_family = 3` and `plate_id + pl_id * 3 + 16` keep 3 in r6 and multiply by it (`muls r6,r3`).
        Measured 2026-10-29: in 2nd Impact the answer changes at that one place; 3rd Strike and New Generation
        with bit 16 (19) build byte-identical.
   Bits 4, 8 and 16 take any constant k (they asked for k in -128..127 before), and bit 16 no longer asks that the
   multiply be outside every loop: the full 3rd Strike, 2nd Impact and New Generation builds are byte-identical
   without those conditions (2026-10-29).
   Evidence over the Street Fighter III build (10,048 C routines, the arcade program as the reference):
     1  The rewriters meet a multiply's constant that Release 26 takes as an immediate at three places. Two are
        char multiplies by 16 (game_config_2p_round_item_jp and _en: one source line in twin routines); the
        arcade multiplies by the register in both and both match with the rule. The third is an unsigned long multiply by 1
        (ranking_insert_all_four, D, not matched and not decided), which the rule leaves alone. In the arcade
        program those two are the only muls.w/mulu.w by a callee-saved register holding a constant, and no
        multiply copies a constant out of such a register. For 2, against 0, undecided 1. The same answer for
        the candidates and the weight is refused by 220 matched routines (the arcade loads 76, 152 or 1176 into
        a scratch register at every narrow multiply, 31 times in debug_parts_disp); B passed over instead of
        answered loses 65 and does not give the twins' multiply (16 is one shift).
     2  A answers at 10,591 places; passing it over changes the answer at the 22 whose constant is no
        shift-and-add constant, and the code of four routines, all toward the arcade:
        grade_get_my_point_percentage (100 in r14, four mul.l), Setup_Wins and Setup_Wins2 (100 in r7 for two
        divisions and a mul.l) match, bbbs_com_execute (38 in r9, nine mul.l) comes closer. For 4, against 0.
        Only all three askers together give the arcade's code (the rewriters alone or the candidates alone
        change nothing, candidates and weight without the rewriters go part of the way: 92.5% against 100%
        in grade_get_my_point_percentage). A answered "not an immediate" outright, powers of two included,
        loses 831 routines; D so answered loses 97, E 6.
   MDL_MUL_LOG=<file> (a diagnostic, off unless set) lists every question about a multiply's constant: function,
   asker (g4 candidates, g1 weight, g2 rewriters), operator and type, value, the part that answers in Release 26
   (F a float operand, N none), Release 26's answer and the one given. The process id is appended to the name. */
#define MUL_CONST_DEFAULT 3

static int mul_clause(il_node *op, int pos, unsigned int value, int skip_a)
{
    char terms[32];
    il_node *operand;
    unsigned char kind;
    int n, i;
    if ((op->type & 0xe0) == 0x20 || (nth_operand(pos, op)->type & 0xe0) == 0x20)
        return 'F';
    if (!skip_a
        && (((int)value > -0x8001 && (int)value < 0x8000 && (op->child->next->type & 4) == 0 && pos == 2)
            || ((int)value > -1 && (int)value < 0x10000 && (op->child->next->type & 4) != 0 && pos == 2))
        && (operand = op->child, operand->op == IL_CAST && (operand->type & 0xe0) == 0)
        && (kind = operand->type & 0xf8, kind != 0 && kind != 8)
        && (kind = operand->child->type & 0xf8, kind == 0 || kind == 8))
        return 'A';
    kind = op->type & 0xf8;
    if (kind == 0 || kind == 8)
        return 'B';
    if (g_options->cpu == 0 && g_options->unknown_20 != 0 && (value == 0x32 || value == 100))
        return 'C';
    n = count_shift_add_terms(terms, value, (op->type & 4) == 0);
    if (n == 1)
        return 'D';
    if (n != 2)
        return 'N';
    if (terms[0] == 0)
        for (i = 0; i < 0x20; i++)
            if (terms[i] == -1)
                return 'N';
    return 'E';
}

static int mul_fit(int group, il_node *parent, int pos, unsigned int value, const_use *occ)
{
    static FILE *log = (FILE *)1;
    static int bits = -1;
    int stock = is_immediate_operand(parent, pos, value), r = stock, c, c0;
    if (bits < 0) {
        const char *v = getenv("MDL_MUL_CONST");
        bits = (v && *v) ? atoi(v) : MUL_CONST_DEFAULT;
    }
    if (log == (FILE *)1) {
        const char *p = getenv("MDL_MUL_LOG");
        char name[600];
        log = 0;
        if (p && *p && strlen(p) < 500) {
            sprintf(name, "%s.%d", p, (int)_getpid());
            log = fopen(name, "a");
        }
    }
    if (stock == 0 && !log)
        return 0;
    c = c0 = mul_clause(parent, pos, value, 0);
    if ((bits & 2) && c == 'A') {
        c = mul_clause(parent, pos, value, 1);
        r = c != 'N';
    }
    if ((bits & 1) && group == 2 && c == 'B')
        r = 0;
    if ((bits & 4) && group == 1 && c == 'B' && parent->op == IL_A_MUL
        && occ && occ->block->lptbl == 0 && count_enclosing_loops(occ->node) == 0)
        r = 0;
    if ((bits & 16) && group == 1 && c == 'B' && parent->op == IL_MUL)
        r = 0;
    if ((bits & 8) && group == 4 && c == 'B' && parent->op == IL_A_MUL
        && nth_operand(pos, parent) && count_enclosing_loops(nth_operand(pos, parent)) == 0)
        r = 0;
    if (log) {
        fprintf(log, "%s\tg%d\t%s\tty=%02x\tpos=%d\tv=%d\t%c\tstock=%d\tans=%d\tline=%d\n",
                g_symtab[g_func_node->symx].name, group, parent->op == IL_MUL ? "MUL" : "A_MUL", parent->type, pos,
                (int)value, c0, stock, r, (int)parent->line);
        fflush(log);
    }
    return r;
}

/* The arcade's rule for a constant that is added or subtracted and for the constant of a bit-and, MDL_IMM_REG.

   A constant is kept in a register by its class (the constants of one value and size in a block). A class is a
   candidate when its first member is not an immediate of its operator (collect_register_candidate); the weight
   counter then counts the members that are not immediates, and the rewriters make those read the register.
   Release 26 asks is_immediate_operand at all three places. For an add or subtract any imm8 is an immediate, zero
   included, and for a bit-and of a char or short an 8-bit constant is. The zero of `a[0]` is such an operand:
   the index is scaled and added in the tree, and shcmdl never folds `a + 0`.

   The arcade's compiler collects the classes as Release 26 does, but counts and rewrites
     - a zero that is added or subtracted: with zero in a register for its other uses, `a[0] = x` is an indexed
       store through that register (mov.w r14,@(r0,r14) in Game2_4, mov.b r2,@(r0,r14) in Game2_5) and the start
       value `x + 0` of a strength-reduced `x + col` is add r14,r12 (scfont_sqput);
     - the constant of a bit-and: `v & 3` reads the 3 kept in a register (game_config_init), and the uses count
       toward keeping it there.
     - a constant other than zero that is added to or subtracted from a local variable (a parameter, a local or a
       compiler temporary, also under a cast): `(ix + 1) & 1` with 1 in r12 is add r12,r2 and and r12,r2
       (set_base_data), and the step of a counter that runs down, `t + -1`, is add r4,r6 (effect_work_init). An
       add to a value that is first loaded from memory keeps its immediate: `np->code[n] + 1` passed to a call is
       mov.w, add #1,r7 with 1 in r10 (effect_B5_move, effect_79_move, effect_51_move), and
       `dbg_save_mode = dbg_save_mode + 1` on a global is add #1,r3 (debug_playback_mode_cycle);
     - the constant of an add- or subtract-assignment: `Rank_Pos_Y -= 1` and `Rank_Pos_Y += 1` read the 1 kept
       in r8 (sub r8,r1, add r8,r3 in Ranking_01_2nd) and count toward keeping it there, which there takes the
       register Release 26 gives to 180.
   A class whose first member is such a zero is still no candidate (Game01_Sub stores win_mark_rno[0] plainly with
   zero in r14: there the first long zero of the block is the index of an array).

   MDL_IMM_REG=<bits> (unset: 63; 0: Release 26), for the weight counter and the rewriters only (bit 32 also for
   collect_register_candidate)
     1  a zero operand of an add or a subtract is not an immediate
     2  the constant of a bit-and is not an immediate
     4  a nonzero constant added to or subtracted from a local variable is not an immediate
     8  the constant of an add- or subtract-assignment is not an immediate
     16 the constant of a bit-xor is not an immediate (`x->rl_flag ^ 1` with 1 kept in r11 is xor r11,r0 in
        eff09_11000; whole build: that routine alone changes)
     128 with 4: a nonzero constant added to an arithmetic expression of identifiers and constants
        (+, -, * and casts) is not an immediate, including expressions whose identifiers are globals.
        A direct global load, indirect read or call still follows the existing eligibility rules.
        `char_index = plate_id + ix + 16` with 16 kept in a register is add r5,r0 in 2nd Impact's effect_79_init
        (the front end puts the constant last, so the left operand is a sum); RANKING Setup_grade in New
        Generation (2nd Impact and New Generation: 191). The full 3rd Strike build is byte-identical with it too.
        (Bit 64, the same for expressions of locals, parameters and constants only, is retired: bit 128 covers it,
        and 2nd Impact builds byte-identical with 191 in place of 127, 2026-10-29.)
     32 a zero compared unsigned (<, <=, >, >= whose zero operand has an unsigned type) against a converted value
        (the other operand a cast) is not an immediate, for collect_register_candidate too: the SH has no unsigned
        compare with an immediate, and Release 26 reads the relational node's own type, which is always a signed
        int, so it calls such a zero an immediate and shcgen copies the zero's register before the compare
        (mov r4,r3, cmp/hs r10,r3). The arcade's compiler compares the zero's register itself (cmp/hs r10,r4 in
        strstr, `i < n` with u32 i and s32 n, the entry test that loop inversion copies in front of the loop with
        i folded to 0). One witness: strstr. Without the cast condition the rule costs seven exact routines whose
        compares are unsigned on both sides (tilemap_put_block, hex_to_bcd, ...).
   The evidence over the Street Fighter III build is in tools/public/SF3.md and notes/shcmdl.md.
   What the arcade's compiler asks instead is not known; the bits are the operators its code decides.
   MDL_IMM_LOG=<file> (a diagnostic, off unless set) lists each answer the rule changes: function, asker (g1
   weight, g2 rewriters), operator, value and source line. The process id is appended to the name. */
#define IMM_REG_DEFAULT 63

/* Arithmetic expressions can reuse an existing constant even when scalar inputs have global storage.
   Direct loads, indirect accesses and calls do not qualify through this path. Off unless bit 128 is set. */
static int arithmetic_only(il_node *n)
{
    il_node *c;
    if (n == 0)
        return 0;
    switch (n->op) {
    case IL_CONST:
        return 1;
    case IL_ID:
        return 1;
    case IL_CAST:
        return arithmetic_only(n->child);
    case IL_ADD:
    case IL_SUB:
    case IL_MUL:
        for (c = n->child; c != 0; c = c->next)
            if (!arithmetic_only(c))
                return 0;
        return 1;
    default:
        return 0;
    }
}


static int immreg_fit(int group, il_node *parent, int pos, unsigned int value)
{
    static FILE *log = (FILE *)1;
    static int bits = -1;
    int r = is_immediate_operand(parent, pos, value);
    if (r == 0 || (group != 1 && group != 2))
        return r;
    if (bits < 0) {
        const char *v = getenv("MDL_IMM_REG");
        bits = (v && *v) ? atoi(v) : IMM_REG_DEFAULT;
    }
    if (parent->op == IL_A_ADD || parent->op == IL_A_SUB) {
        if (!(bits & 8))
            return r;
    } else if (parent->op == IL_B_AND) {
        if (!(bits & 2))
            return r;
    } else if (parent->op == IL_B_XOR) {
        if (!(bits & 16))
            return r;
    } else if (value == 0) {
        if (!(bits & 1))
            return r;
    } else {
        /* the other operand, through its casts: a variable that is not static or external */
        il_node *v = pos == 1 ? parent->child->next : parent->child;
        if (!(bits & 4))
            return r;
        while (v && v->op == IL_CAST)
            v = v->child;
        if (!v)
            return r;
        if (v->op != IL_ID) {
            if (!(bits & 128) || !arithmetic_only(v))
                return r;
        } else if (v->symx > 0 && g_symtab[v->symx].sclass >= 1 && g_symtab[v->symx].sclass <= 4)
            return r;
    }
    if (log == (FILE *)1) {
        const char *p = getenv("MDL_IMM_LOG");
        char name[600];
        log = 0;
        if (p && *p && strlen(p) < 500) {
            sprintf(name, "%s.%d", p, (int)_getpid());
            log = fopen(name, "a");
        }
    }
    if (log) {
        fprintf(log, "%s\tg%d\t%s\tty=%02x\tv=%d\tline=%d\n", g_symtab[g_func_node->symx].name, group,
                parent->op == IL_ADD ? "ADD" : parent->op == IL_SUB ? "SUB" : parent->op == IL_A_ADD ? "A_ADD" :
                parent->op == IL_A_SUB ? "A_SUB" : parent->op == IL_B_XOR ? "B_XOR" : "B_AND", parent->type, (int)value,
                (int)parent->line);
        fflush(log);
    }
    return 0;
}

/* MDL_IMM_REG bit 32: the zero of an unsigned compare against a cast is no immediate (all three groups) */
static int relzero_fit(il_node *parent, int pos, unsigned int value)
{
    static int bits = -1;
    il_node *zero, *other;
    int r = is_immediate_operand(parent, pos, value);
    if (r == 0 || value != 0)
        return r;
    if (bits < 0) {
        const char *v = getenv("MDL_IMM_REG");
        bits = (v && *v) ? atoi(v) : IMM_REG_DEFAULT;
    }
    if (!(bits & 32))
        return r;
    zero = nth_operand(pos, parent);
    other = nth_operand(pos == 1 ? 2 : 1, parent);
    if (!zero || (zero->type & 0xe0) != 0 || !(zero->type & 4) || !other || other->op != IL_CAST)
        return r;
    return 0;
}

/* The constant of a signed modulo, MDL_MOD_CONST (only with SHC_REBUILD_UPDATED=1; unset or 0: Release 26 and the 3rd
   Strike build): a compiler revision's behaviour seen in Street Fighter III 2nd Impact.

   is_immediate_operand answers 1 for the divisor of a modulo when it is one shift term (a power of two) below 0x80,
   signed or not. shcgen still calls _modls for a signed `i % 4` and loads the 4 into r0 itself, so Release 26 counts
   no weight for that occurrence and leaves it out of the constant's register. 2nd Impact's effg8 effect_G8_init
   (`type = (u8)i / 4; old_rno[6] = i % 4; ... effg8_speed_tbl[i / 4]`) passes the 4 from its register to _modls as
   to both _divls calls (`mov r14,r0`), and the third counted use gives 4 the first callee-saved register.

   MDL_MOD_CONST=<bits>, the ARGCONST_FIT groups (1 the weight counter, 2 the rewriters, 4 collect_register_candidate):
   a set bit answers 0 ("not an immediate") for the divisor of a signed modulo. 3 is the 2nd Impact setting: measured
   2026-10-20 (si2core) the 2nd Impact build stays byte-identical (C 7039, no matched routine changes) and
   effect_G8_init matches; 1 or 2 alone does not.

   MDL_EQ_CONST=<bits>, the same groups (unset or 0: Release 26): a set bit answers 0 for the constant of an == or
   != compare. 3 is the 2nd Impact and the 3rd Strike setting: `(dbg_p2sw_0 & 0x70) == 0x70` in 2nd Impact's
   CMD_MAIN debug_scene_outer_dispatch keeps 112 in r4 for both the and and the compare (mov #112,r4; and r4,r3;
   cmp/eq r4,r3); measured 2026-10-20 the 2nd Impact build stays byte-identical (C 7270, no matched routine
   changes). 3rd Strike's cmb_cont combo_window_trans `(end_flag[PL] & 3) == 3` does the same with 3 (mov #3,r4;
   and r4,r3; cmp/eq r4,r3, where unset gives and #3,r0; cmp/eq #3,r0); measured 2026-10-28 the full 3rd Strike
   build stays byte-identical with it (964 modules, the program's SHA-1). */

/* occ: the occurrence record ({next, block, node}) of the node being weighed or rewritten, 0 for group 4 */
int mdl_argconst_fit(int group, il_node *parent, int pos, unsigned int value, const_use *occ)
{
    int bits = knob("MDL_ARG_CONST", ARG_CONST_DEFAULT);
    if (parent->op == IL_MUL || parent->op == IL_A_MUL)
        return mul_fit(group, parent, pos, value, occ);
    if (parent->op == IL_ADD || parent->op == IL_SUB || parent->op == IL_B_AND || parent->op == IL_A_ADD
        || parent->op == IL_A_SUB || parent->op == IL_B_XOR)
        return immreg_fit(group, parent, pos, value);
    if ((parent->op == IL_MOD || parent->op == IL_A_MOD) && (knob("MDL_MOD_CONST", 0) & group) && pos == 2
        && (parent->type & 4) == 0)
        return 0;
    if (parent->op == IL_LT || parent->op == IL_LE || parent->op == IL_GT || parent->op == IL_GE)
        return relzero_fit(parent, pos, value);
    if ((parent->op == IL_EQ || parent->op == IL_NE) && (knob("MDL_EQ_CONST", 0) & group))
        return 0;
    if (!(bits & group) || parent->op != IL_ARG)
        return is_immediate_operand(parent, pos, value);
    if ((bits & 8) && occ && occ->block->lptbl != 0)
        return is_immediate_operand(parent, pos, value);
#if SHC_REBUILD_DIAG
    if (knob("MDL_ARG_CALL", 0) & group)
        return call_rule(parent, pos, value);
#endif
    return 0;
}
