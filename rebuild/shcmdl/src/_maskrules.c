/* The arcade's rules for a mask by 0xff and for a mask that makes an extension redundant, MDL_MASK_AND (only with
   SHC_REBUILD_UPDATED=1).

   Release 26's expression simplifier turns a bit-and with 0xff or 0xffff into a pair of casts: `x & 0xff` is
   (T)(unsigned char)x (simplify_bitand_bitor), and `v &= 0xff` on a variable is v = (T)(unsigned char)v
   (simplify_and_or_assign; an and-assignment to memory is left alone). shcgen then extends (extu.b r5,r5), or
   loads only the low byte of a short it has not loaded yet. The arcade's compiler leaves the 0xff mask an and:
   and #255,r0 where the value is in r0 (Check_Store_Lever: extu.w r5,r0 / and #255,r0 for `Tech_Number & 0xFF`),
   and a load of H'00FF and and r1,r5 where it is not (Setup_Char_Index: `xx &= 0xFF`). Its extu.b come from
   casts and unsigned char objects.

   MDL_MASK_AND=<bits> (unset: 15; 0: Release 26)
     1  `x & 0xff` stays a bit-and
     2  `v &= 0xff` stays an and-assignment
     4  a bit-and with a constant mask whose bits all lie inside a char or short operand's width takes that operand
        without its widening cast when the operand is a computed value: the mask clears every bit the extension
        would set. `(s16)-p->x & 0x3FF` is narrowed to and(cast(int, neg.s16(p->x)), 0x3FF); with the cast gone
        there is no exts.w and the and reads the negation's register (neg r0,r0 / mov r0,r5 / and r14,r5 in
        update_all_disp_pos_ending, where Release 26 has exts.w r0,r5). Only when the operand, looking through any
        casts inside it, is not a variable or memory read (an ID, * or member), and the and is not a condition.
        ONE WITNESS: update_all_disp_pos_ending (two sites), the only place the rule reaches over the SF3 build.
        The operand condition is fitted: a memory or variable operand costs no extension (the load extends), and
        dropping its cast as well costs 867 exact routines (the cast's own evaluation order and the bit tests are
        lost); without looking through inner casts sprite_display_list_build (`(s16)rec->w0 & 0x1FF`) is lost.
     8  bit 4 leaves the cast also when the operand, looking through any casts inside it, is an assignment
        (= or a compound assignment): its value is the stored object's, which the store has already made, like
        a variable's. ((*cell++ = *tbl++) & 0x100) >> 8 keeps the widening cast before the and, `extu.w`
        (eff91_cell_data_set, the arcade's 178 bytes with its inner loop written as one statement).
        ONE WITNESS: no other routine of the SF3 build changes with the bit.
   0xffff is converted under every setting: the arcade program has no and with a register holding H'0000FFFF,
   and sound_note_to_pitch (`v &= 0xFFFF` on an int, extu.w in the arcade) matches with the conversion.
   The evidence over the Street Fighter III build is in tools/public/SF3.md and notes/shcmdl.md.
   MDL_MASK_LOG=<file> (a diagnostic, off unless set) lists each mask by 0xff the simplifier meets: function,
   bit, the and's type, source line and whether it was kept. The process id is appended to the name. */
#include "decls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>

#define MASK_AND_DEFAULT 15

static int mask_bits(void)
{
    static int bits = -1;
    if (bits < 0) {
        const char *v = getenv("MDL_MASK_AND");
        bits = (v && *v) ? atoi(v) : MASK_AND_DEFAULT;
    }
    return bits;
}

/* 1: make the casts (Release 26); 0: leave the and. mask is the constant operand, bit the asker (1 `&`, 2 `&=`) */
int mdl_mask_to_cast(il_node *node, il_node *mask, int bit)
{
    static FILE *log = (FILE *)1;
    int bits;
    if (is_const_value(mask, 0xff, node->type) == 0)
        return 1;
    bits = mask_bits();
    if (log == (FILE *)1) {
        const char *p = getenv("MDL_MASK_LOG");
        char name[600];
        log = 0;
        if (p && *p && strlen(p) < 500) {
            sprintf(name, "%s.%d", p, (int)_getpid());
            log = fopen(name, "a");
        }
    }
    if (log) {
        fprintf(log, "%s\tbit=%d\tty=%02x\tline=%d\tkept=%d\n",
                g_func_node && g_func_node->symx > 0 ? g_symtab[g_func_node->symx].name : "?", bit, node->type,
                (int)node->line, (bits & bit) != 0);
        fflush(log);
    }
    return (bits & bit) == 0;
}

static int int_size(unsigned char t)
{
    switch (t & 0xf8) {
    case 0x00: return 1;
    case 0x08: return 2;
    case 0x10: case 0x18: return 4;
    }
    return 0;
}

/* MDL_MASK_AND bit 4: the and (left as an and) takes a computed char or short operand without its widening cast when
   the constant mask lies inside the operand's width */
il_node *mdl_mask_drop_cast(il_node *node)
{
    il_node *cast, *mask, *inner;
    int from;
    if (!(mask_bits() & 4) || node->op != IL_B_AND)
        return node;
    cast = node->child;
    mask = cast->next;
    if (mask->op == IL_CAST && mask->child->op == IL_CONST)
        mask = mask->child;
    if (cast->op != IL_CAST || mask->op != IL_CONST)
        return node;
    if ((node->type & 0xe0) != 0 || (cast->type & 0xe0) != 0 || (cast->child->type & 0xe0) != 0)
        return node;
    from = int_size(cast->child->type);
    if (from == 0 || from >= 4 || int_size(cast->type) != 4 || ((unsigned int)mask->val >> (8 * from)) != 0)
        return node;
    for (inner = cast->child; inner->op == IL_CAST; inner = inner->child)
        ;
    if (inner->op == IL_ID || inner->op == IL_ASTER || inner->op == IL_QUALIFY || is_condition_operand(node))
        return node;
    if ((mask_bits() & 8) && (inner->op == IL_ASSIGN || ((&g_op_class)[(char)inner->op] & 0x20) != 0))
        return node;
    replace_node(cast, cast->child);
    cast->child = (il_node *)0;
    free_node(cast);
    return node;
}
