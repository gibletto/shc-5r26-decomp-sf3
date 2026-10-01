#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cse_variables
#define g_cse_variables (*(node_list * *)(g_sd + 0x267a4))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))


// entry: 0041d060
// name : count_global_expressions
// size : 154
// sig  : void count_global_expressions(void)


int __cdecl count_global_expressions(void)

{
  bblock *blk;
  node_list *item;
  
  g_value_number = 0;
  g_cse_variables = (node_list *)0x0;
  g_cse_cond_depth = '\0';
  for (blk = g_f_chain->f_next; item = g_cse_variables, blk != (bblock *)0x0; blk = blk->f_next) {
    count_block_expressions(blk);
  }
  for (; item != (node_list *)0x0; item = item->next) {
    if (item->node->op == IL_ID) {
      g_leaf_table[item->node->nleaf].lastnd = (il_node *)0x0;
    }
  }
  for (blk = g_f_chain->f_next; blk != (bblock *)0x0; blk = blk->f_next) {
    cse_global_block(blk);
  }
  cse_free_tables();
  if (g_debug_flags == 2) {
    dump_tree(g_func_node,0,s_after_glbx_cnt_tree_00435be0);
  }
  return;
}



