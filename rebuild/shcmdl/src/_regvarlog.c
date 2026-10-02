/* The register-variable selection diagnostic, MDL_REGVAR_LOG (only with SHC_REBUILD_UPDATED=1).

   MDL_REGVAR_LOG=<file> (off unless set; a %d in the name is replaced by the process id): after
   assign_physical_registers, one line per function with the program points of its calls, and one per logical
   register: its register (1-4 r4-r7, 5-11 r14-r8, < 0 a memory id, 0 none), set (0 constant, 1 variable web,
   3 deleted), weight (priori), profit, how many lregs it clashes with, whether a call conflicts with it (cc, the
   test for r4-r7) or lies in its life (sc), what it holds and its life ranges in program points. With
   MDL_REGVAR_BLOCKS set, also each basic block's program points, predecessors and successors. */
#include "decls.h"
#include <stdio.h>
#include <stdlib.h>
#include <process.h>

void mdl_regvar_log(void)
{
    static FILE *f;
    static int opened;
    node_cell *call;
    int i;
    if (!opened) {
        const char *p = getenv("MDL_REGVAR_LOG");
        char path[512];
        opened = 1;
        if (p && *p) {
            _snprintf(path, sizeof path, p, _getpid());
            f = fopen(path, "a");
        }
    }
    if (!f)
        return;
    fprintf(f, "F %s calls:", g_symtab[g_func_node->symx].name);
    for (call = g_call_list; call; call = call->next)
        fprintf(f, " %u", (unsigned)call->node->pp);
    fputc('\n', f);
    if (getenv("MDL_REGVAR_BLOCKS")) {
        bblock *b;
        for (b = g_f_chain; b; b = b->f_next) {
            block_list *l;
            fprintf(f, "  B%d pp%u-%u pred", b->number, b->startpp, b->endpp);
            for (l = b->prelst; l; l = l->next)
                fprintf(f, " %d", l->block->number);
            fprintf(f, " succ");
            for (l = b->suclst; l; l = l->next)
                fprintf(f, " %d", l->block->number);
            fputc('\n', f);
        }
    }
    for (i = 1; i <= g_lreg_count; i++) {
        lreg *lr = g_lreg_table[i];
        int nclash = 0;
        void **c;
        for (c = (void **)lr->clashed; c; c = (void **)*c)
            nclash++;
        fprintf(f, "  L%d R%d s%d w%d p%d c%d cc%d sc%d", i, lr->pregno, lr->set, lr->priori, lr->profit, nclash,
                lr->set != 3 ? lreg_conflicts_with_call(lr) : -1, lreg_spans_call(lr));
        if (lr->set == 1 || lr->set == 3) {
            il_node *nd = ((dutbl *)lr->chain)->node;
            if (nd->op != IL_ID)
                nd = nd->child;
            fprintf(f, " var=%s sc%d", nd->symx > 0 ? g_symtab[nd->symx].name : "?",
                    nd->symx > 0 ? g_symtab[nd->symx].sclass : -1);
        } else {
            const_data *cd = (const_data *)lr->chain;
            const_use *u;
            fprintf(f, " const=%d:%d dom%d uses", cd->contents, cd->value, cd->dom_type);
            for (u = cd->uses; u; u = u->next)
                fprintf(f, " B%d", u->block->number);
        }
        fprintf(f, " life");
        for (c = (void **)lr->life; c; c = (void **)*c)
            fprintf(f, " %u-%u", (unsigned)((lifetbl *)c[1])->st, (unsigned)((lifetbl *)c[1])->en);
        fputc('\n', f);
    }
    fflush(f);
}
