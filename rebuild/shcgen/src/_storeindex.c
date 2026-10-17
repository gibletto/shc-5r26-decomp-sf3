/* GEN_STORE_INDEX (only with SHC_REBUILD_UPDATED=1): a store of a quotient through a sum of two registers is
   indexed and its address made after the value.

   fold_address_add turns `*(a + b)` with a and b in registers other than r0 into @(r0,Rn) (case 7). Under a
   store whose right side takes r0 (mark_node_clobbering_r0, desc flags7 0x20) Release 26 gives up and leaves the
   sum to the add template, which chooses the address register at once, before the right side:

       mov r7,r3 / add r10,r3 / ... jsr @r2 (division routine) ... / mov.w r0,@r3

   The arcade's code for `ixa[i] = tsc / table[i];` (score_bunkai_eff16, score_bunkai_G0) fits the indexed access
   kept: the right side is chosen first (routine address r3), then resolve_operand_register_conflicts sees r0 in
   both the address and the value and load_operand_address_into_new_register makes the address base first in the
   next register (mov r10,r2 / add r7,r2 / ... jsr @r3 ... / mov.w r0,@r2). Where r0 is taken by anything other
   than a division or modulo (a call, `x | 1` through or #imm,r0: Jump_Air_Guard, Hi_Jump_Attack,
   Hi_Jump_Attack_Term, Hi_Jump_Command_Attack_Term, Command_Type_00) the arcade has Release 26's code, so the
   rule asks that every r0 taker in the right side be a division or modulo.

   Measured on the game (every C routine, 15f3f43d): case 7 under such a store arises at 9 places in 7 routines;
   the 4 places with a quotient are in the two score_bunkai routines, which become byte-exact (image 636 -> 624
   halfwords from the arcade, nothing else changes). With bit 2 (any r0 taker) the 5 other places change and
   Hi_Jump_Attack / Hi_Jump_Attack_Term lose their match.

   GEN_STORE_INDEX=<bits> (unset: 1, the arcade rule; 0: Release 26): 1 the rule (every r0 taker a division or
   modulo); 2 any r0 taker (a diagnostic, off: it breaks Hi_Jump_Attack and Hi_Jump_Attack_Term).
   GEN_STORE_INDEX_LOG=<file> logs each decision (and every fold_address_add case with its operand classes). */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include "decls.h"
#include "imports.h"
#include "gen_rules.h"

extern char *gen_function_name;

static int store_index_mode(void)
{
    static int mode = -1;
    if (mode < 0) {
        const char *p = getenv("GEN_STORE_INDEX");
        mode = (p && *p) ? (int)strtol(p, 0, 0) : 1;
    }
    return mode;
}

static FILE *store_index_log(void)
{
    static FILE *f;
    static int opened;
    if (!opened) {
        const char *p = getenv("GEN_STORE_INDEX_LOG");
        char path[512];
        opened = 1;
        if (p && *p) {
            _snprintf(path, sizeof path, p, _getpid());
            f = fopen(path, "a");
        }
    }
    return f;
}

/* What in the subtree of n takes r0 (mark_node_clobbering_r0 marks such a node and the marks are carried up):
   bit 1 a division or modulo (a runtime routine whose result arrives in r0), bit 2 anything else (a call, a bit
   field, an operation or comparison with a constant through r0, a routine for a multiply or shift the cpu lacks,
   floating point without an FPU). */
static int r0_takers(gen_node *n)
{
    int k = 0;
    gen_node *c;
    if (!n)
        return 0;
    for (c = n->child; c; c = c->next)
        k |= r0_takers(c);
    if (!n->desc || (n->desc->flags7 & 0x20) == 0)
        return k;
    switch (n->op) {
    case IL_DIV: case IL_MOD: case IL_A_DIV: case IL_A_MOD:
        if ((n->type & 0xe0) != 0x20)
            return k | 1;
        break;
    default:
        break;
    }
    /* marked: by its own operation unless a marked operand explains it */
    if (k == 0 || n->op == IL_CALL || n->op == IL_B_QUALIFY || (n->type & 0xe0) == 0x20)
        k |= 2;
    else {
        switch (n->op) {
        case IL_B_AND: case IL_B_XOR: case IL_B_OR: case IL_A_AND: case IL_A_XOR: case IL_A_OR:
        case IL_EQ: case IL_NE: case IL_LT: case IL_LE: case IL_GT: case IL_GE:
            if ((n->child && n->child->op == IL_CONST) || (n->child && n->child->next && n->child->next->op == IL_CONST))
                k |= 2;
            break;
        case IL_MUL: case IL_A_MUL: case IL_SL: case IL_SR: case IL_A_SL: case IL_A_SR:
            k |= 2;     /* only marked on the cpus without the instruction; conservative */
            break;
        default:
            break;
        }
    }
    return k;
}

/* fold_address_add case 7 (both operands in registers other than r0) under a dereference that a store or compound
   assignment uses, whose template keeps r0 out of the address: 1 makes the indexed access anyway (the conflict is
   resolved after the right side), 0 keeps Release 26's return to the add template. */
int gen_store_index_late(gen_node *node, gen_node *left, gen_node *right, gen_node *assign)
{
    int mode = store_index_mode(), r = 0;
    gen_node *value = assign->child ? assign->child->next : 0;
    int takers = value ? r0_takers(value) : 2;
    FILE *f = store_index_log();
    if ((mode & 1) && takers == 1)
        r = 1;
    if (mode & 2)
        r = 1;
    if (f) {
        fprintf(f, "%s line %d asg op %02x type %02x f7 %02x excl %02x | L op %02x lreg %d symx %d ea %02x/%d cls %d | R op %02x lreg %d symx %d ea %02x/%d cls %d | val op %02x type %02x ea %02x/%d need %04x takers %d -> %d\n",
                gen_function_name ? gen_function_name : "?", node->line, (unsigned char)assign->op, assign->type, assign->desc->flags7,
                assign->desc->tmpl->excluded,
                (unsigned char)left->op, (int)(short)left->lreg, (int)left->symx, left->desc->value.type, left->desc->value.base, left->desc->opnd_class,
                (unsigned char)right->op, (int)(short)right->lreg, (int)right->symx, right->desc->value.type, right->desc->value.base, right->desc->opnd_class,
                value ? (unsigned char)value->op : 0, value ? value->type : 0,
                value ? value->desc->value.type : 0, value ? value->desc->value.base : 0, value ? (unsigned short)value->desc->need_regs : 0, takers, r);
        fflush(f);
    }
    return r;
}
#endif
#if SHC_REBUILD_UPDATED
void gen_store_index_trace(gen_node *node, gen_node *left, gen_node *right, int lc, int rc, int kind)
{
    FILE *f = store_index_log();
    gen_node *p = node->parent, *g = p ? p->parent : 0;
    if (!f) return;
    fprintf(f, "T %s line %d kind %d lc %d rc %d | p op %02x type %02x usage %d | g op %02x f7 %02x excl %02x | Lcls %d Rcls %d\n",
            gen_function_name ? gen_function_name : "?", node->line, kind & 0xff, lc, rc,
            p ? (unsigned char)p->op : 0, p ? p->type : 0, p && p->desc ? p->desc->usage : -1,
            g ? (unsigned char)g->op : 0, g && g->desc ? g->desc->flags7 : 0,
            g && g->desc && g->desc->tmpl ? g->desc->tmpl->excluded : 0xff,
            left->desc->opnd_class, right->desc->opnd_class);
    fflush(f);
}
#endif
