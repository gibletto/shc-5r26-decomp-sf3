/* The order of stepped temporaries' webs (only with SHC_REBUILD_UPDATED=1).

   MDL_IV_WEB_ORDER=<bits> (unset or 0: Release 26 and the 3rd Strike build): a compiler revision's behaviour seen in
   Street Fighter III 2nd Impact.

   prepare_register_allocation makes a web's logical register where the scan over the blocks first meets the web, and
   that list order is the order sort_lregs_by_profit starts from: its sort is not stable, so lregs of equal profit
   come out in an order that follows from it (and the frame slots of memory lregs with them). For the temporaries
   reduce_induction_variable made for one induction variable, 2nd Impact's order is not the order of first use:
     1  in a loop that holds a call (lp_flag 0x2000), when the reduction made two or more temporaries for MDL_IV_TEMP
        (t = expr steps a new temporary, one for each arm of an if), a temporary it made for a plain use enters the
        list right after the first of those met, in the order the reduction made them.
   Witness: textsound_2 sound_seq_start's SE loop (pan ramp copies in both arms of `if (ramp != -1)`, se_tick_step[i]
   after the if, midi_vlq_decode_while called in the loop): with 1 the three tied memory lregs take 2i's frame slots
   (tick @12, pan-else @28). spgauge_cont_init (the same arms, no call) keeps Release 26's order, as do PLMAIN
   Player_move, sc_sub_2 fade_cont_init and PLS03 (one MDL_IV_TEMP temporary). */
#include "decls.h"
#include <stdlib.h>
#undef g_lreg_list
#define g_lreg_list (*(lreg * *)(g_sd + 0x16264))
#undef g_candidate_list_tail
#define g_candidate_list_tail (*(lreg * *)(g_sd + 0x1626c))

#define TMAX 512
static short t_symx[TMAX];
static int t_group[TMAX], t_tempcls[TMAX], t_call[TMAX], t_n, t_fn = -1, t_gcount;
static void *t_entry;

int mdl_iv_web_order(void)
{
    static int k = -1;
    if (k < 0) {
        const char *v = getenv("MDL_IV_WEB_ORDER");
        k = (v && *v) ? atoi(v) : 0;
    }
    return k;
}

/* reduce_induction_variable made temporary symx for an iv_entry; tempcls: for MDL_IV_TEMP's t = expr */
void mdl_iv_web_note(void *entry, short symx, int tempcls)
{
    if (!(mdl_iv_web_order() & 1))
        return;
    if (t_fn != g_func_node->symx) {
        t_fn = g_func_node->symx;
        t_n = 0;
        t_entry = 0;
    }
    if (entry != t_entry) {
        t_entry = entry;
        t_gcount++;
    }
    if (t_n < TMAX) {
        t_symx[t_n] = symx;
        t_group[t_n] = t_gcount;
        t_tempcls[t_n] = tempcls;
        t_call[t_n] = (g_cur_loop->flag & 0x2000) != 0;
        t_n++;
    }
}

/* the noted temporary a web (set 1) belongs to, or -1 */
static int noted(lreg *lr)
{
    dutbl *d;
    int i;
    if (lr->set != 1)
        return -1;
    for (d = (dutbl *)lr->chain; d; d = d->next) {
        il_node *n = d->node;
        if (n && n->op != IL_ID && n->child && n->child->op == IL_ID)
            n = n->child;
        if (n == 0 || n->op != IL_ID)
            continue;
        for (i = 0; i < t_n; i++)
            if (t_symx[i] == n->symx)
                return i;
        return -1;
    }
    return -1;
}

/* sort_lregs_by_profit, before it fills the table */
void mdl_iv_web_reorder(void)
{
    static lreg *all[16384], *out[16384];
    static int ti[16384], used[16384];
    int na = 0, no = 0, i, j, k, ntemp, first;
    lreg *lr;
    if (!(mdl_iv_web_order() & 1) || t_fn != g_func_node->symx || t_n == 0)
        return;
    for (lr = g_lreg_list; lr && na < 16384; lr = lr->next) {
        all[na] = lr;
        ti[na] = noted(lr);
        used[na] = 0;
        na++;
    }
    for (i = 0; i < na; i++) {
        if (used[i])
            continue;
        out[no++] = all[i];
        used[i] = 1;
        if (ti[i] < 0 || !t_tempcls[ti[i]] || !t_call[ti[i]])
            continue;
        for (k = 0, ntemp = 0; k < t_n; k++)
            if (t_group[k] == t_group[ti[i]] && t_tempcls[k])
                ntemp++;
        for (k = 0, first = 1; k < i; k++)
            if (ti[k] >= 0 && t_group[ti[k]] == t_group[ti[i]] && t_tempcls[ti[k]])
                first = 0;
        if (ntemp < 2 || !first)
            continue;
        /* the plain temporaries of the group, in the order the reduction made them */
        for (;;) {
            int best = -1;
            for (j = i + 1; j < na; j++)
                if (!used[j] && ti[j] >= 0 && t_group[ti[j]] == t_group[ti[i]] && !t_tempcls[ti[j]] &&
                    (best < 0 || ti[j] < ti[best]))
                    best = j;
            if (best < 0)
                break;
            out[no++] = all[best];
            used[best] = 1;
        }
    }
    for (i = 0; i + 1 < no; i++)
        out[i]->next = out[i + 1];
    if (no) {
        out[no - 1]->next = 0;
        g_lreg_list = out[0];
        g_candidate_list_tail = out[no - 1];
    }
}
