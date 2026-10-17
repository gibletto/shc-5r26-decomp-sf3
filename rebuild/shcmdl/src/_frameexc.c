/* MDL_FRAME_EXC=<bits> (default 1; 0 = Release 26): an owner-approved exception in the memory-slot frequency sort
   of reflect_register_numbers. bit 1: in attack_hit_check, the records of the loop-3 stack variables `boxes` and
   `lp2` (equal frequency) are ordered boxes first, as in the arcade program.
   This is not a general rule. The order of equal-frequency records follows the sorted register-candidate table,
   and the arcade has boxes and lp2 the other way round from Release 26's creation order (first use). A whole-ROM
   census of 335 other equal-frequency pairs in byte-exact routines found every one in Release 26's order, and every
   general creation-order or frequency rule tested changed between 8 and 508 byte-exact routines. So this one site is
   recorded as an exception rather than a rule. */
#include "decls.h"
#include <stdlib.h>
#include <string.h>

static int frame_exc_bits(void)
{
    static int bits = -1;
    if (bits < 0) {
        const char *v = getenv("MDL_FRAME_EXC");
        bits = (v && *v) ? atoi(v) : 1;
    }
    return bits;
}

static const char *record_name(mem_freq *m)
{
    lreg *lr = m->lreg;
    il_node *nd;
    if (!lr || !(lr->set == 1 || lr->set == 3) || !lr->chain)
        return 0;
    nd = ((dutbl *)lr->chain)->node;
    if (nd->op != IL_ID)
        nd = nd->child;
    if (!nd || nd->symx <= 0)
        return 0;
    return g_symtab[nd->symx].name;
}

void mdl_frame_exception(void)
{
    mem_freq **pp, **pa = 0, **pb = 0;
    const char *fn, *nm;
    if (!(frame_exc_bits() & 1))
        return;
    fn = g_symtab[g_func_node->symx].name;
    if (strcmp(fn, "attack_hit_check") != 0)
        return;
    for (pp = &g_mem_freq_list; *pp; pp = &(*pp)->next) {
        if ((*pp)->merge_prev || (*pp)->merge_next)
            continue;
        nm = record_name(*pp);
        if (!nm)
            continue;
        if (!pa && strcmp(nm, "lp2") == 0)
            pa = pp;
        else if (pa && !pb && strcmp(nm, "boxes") == 0)
            pb = pp;
    }
    /* only when lp2's record precedes boxes' with equal frequency: exchange their contents, keeping the links */
    if (pa && pb && (*pa)->freq == (*pb)->freq) {
        mem_freq tmp = **pa, *na = (*pa)->next, *nb = (*pb)->next;
        **pa = **pb;
        (*pa)->next = na;
        **pb = tmp;
        (*pb)->next = nb;
    }
}
