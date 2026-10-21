/* GEN_STORE_ADDR_AVOID (only with SHC_REBUILD_UPDATED=1; unset or 0: Release 26 and the 3rd Strike build): a
   compiler revision's behaviour seen in Street Fighter III 2nd Impact.

   apply_template_to_node ends by setting the chooser's avoid mask (g_avoid_reg_mask, f93e in SHCGEN_REGTRACE) from
   the node's own template registers. For `Break_Into = 0;` the store template loads the address itself, so its
   register (r3) stays in the mask and the next choice avoids it. For `Suicide[0] = 0;` (an IL_ADD of a global and a
   constant under the IL_ASTER) the address register belongs to the operand, the store's own mask ends empty and the
   next choice takes r3 again. 2nd Impact's Win_2nd and Ranking_01_1st (si2core) have the scalar store's picks there:
   `mov #40,r2` after `Suicide[0] = 0; System_all_clear_Wait();`.

   GEN_STORE_ADDR_AVOID=<bits>: 2 any store through `*` (diagnostic: 416 objects move in 2nd Impact); 4 only
   `*(id + const)`; 16 only when the stored value is a cast; 32 only when the cast operand is a constant or a
   compiler temporary (a shared constant). 52 (4|16|32) is the 2nd Impact setting: measured 2026-10-20, the 2nd
   Impact build stays byte-identical (C 6814) and the witness probe takes r2. Without 32, Setup_Demo_Arts
   (`Super_Arts[0] = table[...]`) and coin_sw change; without 16, sprite_template_chain_init (`p[k] = k`) does.

   Bit 64 (si2core, 2026-10-20): the scalar store's order as well. prepare_dereference_node keeps `*(id + 0)` a
   memory operand when it is the target of a store of the constant 0 or a compiler temporary, as it does for a
   symbol it may address directly, so the store template chooses the address register after the value: RANKING's
   Ranking_01_1st (`D_No1 = D_No1 + 1; Suicide[0] = 0; tilemap_fill_all(0, 32);`) has `mov #0,r2`, `mov.l
   =Suicide,r1` as 2nd Impact does (Release 26: address r2 first, then the value). Index 0 and value 0 only:
   Ranking_00_1st's `Flash_Sign[0] = 1` and Ranking_00_5th's `Flash_Sign[1] = 0` keep the Release 26 order in 2nd
   Impact. Opt0 units keep it too (poly_queue_init's `poly_line_cnt[0] = 0`, coin_sw's switch_work_clear), so the
   2nd Impact setting is 116 (52|64) with 52 for opt0 units (build2i REVISION_BY_FLAGS). Measured 2026-10-20: the
   2nd Impact build stays byte-identical (C 6998, no matched routine changes) and with RANKING added (C 7021) it
   stays byte-identical. */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include "decls.h"
#include "imports.h"

unsigned short gen_store_addr_avoid(gen_node *node)
{
    static int mode = -1;
    gen_node *left, *v;
    if (mode < 0) {
        const char *p = getenv("GEN_STORE_ADDR_AVOID");
        mode = (p && *p) ? (int)strtol(p, 0, 0) : 0;
    }
    if (!mode || node == 0 || node->op != IL_ASSIGN)
        return 0;
    left = node->child;
    if (left == 0 || left->op != IL_ASTER || left->child == 0)
        return 0;
    if ((mode & 4) && !(left->child->op == IL_ADD && left->child->child != 0 && left->child->child->op == IL_ID
                        && left->child->child->next != 0 && left->child->child->next->op == IL_CONST))
        return 0;
    if ((mode & 16) && (left->next == 0 || left->next->op != IL_CAST))
        return 0;
    if (mode & 32) {
        v = left->next ? left->next->child : 0;
        if (v == 0 || !(v->op == IL_CONST || (v->op == IL_ID && v->symx < 0)))
            return 0;
    }
    if ((left->desc->value.type & 0x1f) == 0)
        return 0;
    return (unsigned short)ea_register_mask(&left->desc->value);
}

/* bit 64: prepare_dereference_node keeps the target of `*(id + 0) = 0` (or = a compiler temporary, through a
   cast or not) a memory operand, so the store's address register is chosen after its value */
int gen_store_value_first(gen_node *node)
{
    gen_node *left, *v;
    const char *p = getenv("GEN_STORE_ADDR_AVOID");
    int mode = (p && *p) ? (int)strtol(p, 0, 0) : 0;
    if (!(mode & 64) || node == 0 || node->op != IL_ASSIGN)
        return 0;
    left = node->child;
    if (left == 0 || left->op != IL_ASTER || left->child == 0)
        return 0;
    if (!(left->child->op == IL_ADD && left->child->child != 0 && left->child->child->op == IL_ID
          && left->child->child->next != 0 && left->child->child->next->op == IL_CONST
          && left->child->child->next->val == 0))
        return 0;
    v = left->next;
    if (v != 0 && v->op == IL_CAST)
        v = v->child;
    if (v == 0 || !((v->op == IL_CONST && v->val == 0) || (v->op == IL_ID && v->symx < 0)))
        return 0;
    return 1;
}
#else
unsigned short gen_store_addr_avoid(void *node) { return 0; }
int gen_store_value_first(void *node) { return 0; }
#endif
