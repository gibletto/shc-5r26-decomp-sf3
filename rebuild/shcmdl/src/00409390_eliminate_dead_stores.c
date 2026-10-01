#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 00409390
// name : eliminate_dead_stores
// size : 135
// sig  : int eliminate_dead_stores(void)


int __cdecl eliminate_dead_stores(void)

{
  il_node *node;
  il_node *extraout_EAX;
  il_node *extraout_EAX_00;
  bblock *block;
  node_list *stmt;
  
  if (g_tree_changed == 1) {
    build_dag_chains('\x01');
    compute_dataflow('\x01');
  }
  g_tree_changed = 0;
  node = (il_node *)g_f_chain;
  for (block = g_f_chain->f_next; block != (bblock *)0x0; block = block->f_next) {
    for (stmt = block->ilnode; stmt != (node_list *)0x0; stmt = stmt->next) {
      node = eliminate_dead_stores_in_tree(stmt->node);
      stmt->node = node;
      if ((g_debug_flags & 0x20000) != 0) {
        dump_tree(node,0,&g_str_ggg);
        node = extraout_EAX;
      }
    }
  }
  if (g_tree_changed == 1) {
    free_du_tables();
    node = extraout_EAX_00;
  }
  return (int)node;
}
