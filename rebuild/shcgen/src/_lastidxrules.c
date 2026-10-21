/* GEN_LAST_IDX (only with SHC_REBUILD_UPDATED=1; unset or 0: Release 26 and the 3rd Strike build): a compiler
   revision's behaviour seen in Street Fighter III 2nd Impact.

   choose_general_register records each pick in g_last_chosen_reg (f93c in SHCGEN_REGTRACE), and the next scratch
   choice ranks that register behind the others. assign_template_slot_registers picks the register of a template
   slot through it too, so the r4 that holds the sign extension of a K&R s16 parameter (exts.w r14,r4 for the index
   of `Moving_Plate[PL_id] = 2`, a slot that prefers r4 with r5-r14 excluded) becomes last-chosen. In 2nd Impact's
   sel_pl Sel_Arts_Sub the next constant after Sound_SE(ID + 96) then takes r2 (the call's r3 is still last-chosen)
   where Release 26 takes r3, and every later pick in the block flips with it.

   GEN_LAST_IDX=<n>: a template-slot pick of r4 for an IL_CAST of an IL_ID leaves g_last_chosen_reg as it was,
     1  for any such cast
     2  only when the variable is a parameter (sclass 7/8)
     3  2, and the slot excluded every register above r4 (excluded & 0x7fe0 == 0x7fe0)
     4  3, and the cast is the scaled index of a store: its parent an IL_MUL under an IL_ASSIGN (@(r0,r4))
   4 is the 2nd Impact setting. Measured 2026-10-20 (si2fields) on the 2nd Impact build (C 7407): 1 changes
   EFFA6, EFFB8, EFFF9, eff90, n_input and se_3 (loop-index locals); 2 changes n_input Name_Input (an ANSI s16
   parameter, not a store index); 3 changes entry_2 Entry_Main_Sub (also a K&R s16 PL_id with r5-r14 excluded,
   but its extension feeds address arithmetic, an IL_MUL under an IL_ADD: E_Number[PL_id][0] = 8, where 2nd Impact
   does update last-chosen); 4 leaves the build byte-identical and makes Sel_Arts_Sub match. The argument
   extensions in the same routine (mov.w @r11,r4 for Sound_SE(ID + 98), a cast of a memory load) keep updating it,
   which is why "no update for any pick above r3" stops at the third call. */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include "decls.h"
#include "imports.h"

int gen_last_idx_keep(gen_node *node, int chosen, unsigned int excluded)
{
    static int mode = -1;
    gen_node *v;
    int sc;
    if (mode < 0) {
        const char *p = getenv("GEN_LAST_IDX");
        mode = (p && *p) ? atoi(p) : 0;
    }
    if (!mode || chosen != 4 || node == 0 || node->op != IL_CAST)
        return 0;
    v = node->child;
    if (v == 0 || v->op != IL_ID || v->next != 0)
        return 0;
    if (mode == 1)
        return 1;
    sc = v->symx > 0 ? g_symbol_table[v->symx + 0xb6].sclass : 0;
    if (sc != 7 && sc != 8)
        return 0;
    if (mode == 2)
        return 1;
    if ((excluded & 0x7fe0) != 0x7fe0)
        return 0;
    if (mode == 3)
        return 1;
    return node->parent != 0 && node->parent->op == IL_MUL && node->parent->parent != 0
           && node->parent->parent->op == IL_ASSIGN;
}
#endif
