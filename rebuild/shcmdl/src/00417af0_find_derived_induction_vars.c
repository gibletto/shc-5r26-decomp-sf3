#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef _g_iv_negated_count
#define _g_iv_negated_count (*(short *)(g_sd + 0xdf70))
#undef g_iv_copy_list
#define g_iv_copy_list (*(node_list * *)(g_sd + 0x3a00))
#undef g_iv_negated_count
#define g_iv_negated_count (*(short *)(g_sd + 0xdf70))


// entry: 00417af0
// name : find_derived_induction_vars
// size : 101
// sig  : void find_derived_induction_vars(node_list * stmts)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl find_derived_induction_vars(node_list *stmts)

{
  il_node *copy;
  node_list *item;
  
  for (; stmts != (node_list *)0x0; stmts = stmts->next) {
    _g_iv_negated_count = 0;
    copy = copy_tree_unlinked(0,stmts->node);
    item = pool_alloc(8);
    if (item == (node_list *)0x0) {
      free_induction_tables();
      abort_function_optimization();
    }
    item->node = copy;
    item->next = g_iv_copy_list;
    g_iv_copy_list = item;
    scan_derived_induction_expr(stmts->node,copy);
  }
  return;
}



