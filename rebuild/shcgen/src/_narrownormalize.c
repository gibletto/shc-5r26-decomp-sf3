/* GEN_NARROW_NORMALIZE: extend the result of a narrow compound assignment in
   its uniquely owned automatic-local home when consumed by an integer relational
   condition. The low bits remain the local's C value; the extension supplies its
   promoted representation. Shared/fixed/address-observable homes and other
   consumers are excluded. All masks and ordinary template accounting remain.

   Unset:1; explicit0 restores Release26's destination selection. The proof is
   independent of function, symbol, physical home, literal and source location. */
#if SHC_REBUILD_UPDATED
#include "decls.h"
#include "imports.h"
#include "gen_rules.h"
#include "narrow_normalize_proof.h"

void gen_narrow_normalize(gen_node *node)
{
    unsigned int count, function;
    const ea *home;
    if (!gen_narrow_normalize_mode()) return;
    count = *(unsigned int *)((unsigned char *)g_request + 0xb0) + 0xb7;
    function = (unsigned short)g_current_function;
    home = nn_owned_home(node, g_symbol_table, count,
        (lreg_entry *)(*(void **)(g_sd + 0x1fa10)),
        g_request->reg_mask_150, function < count ? g_symbol_table + function : 0);
    if (!home) return;
    copy_ea_into(&node->desc->dest, (ea *)home);
    if (getenv("GEN_NARROW_NORMALIZE_TRACE"))
        fprintf(stderr, "NN_ACCEPT %s line=%u type=%u lreg=%d home=%d\n",
            g_symbol_table[function].name, node->line, node->child->type,
            node->child->child->lreg, home->base);
}
#endif
