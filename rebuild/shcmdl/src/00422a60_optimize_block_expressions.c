#include "decls.h"
#include "imports.h"

// entry: 00422a60
// name : optimize_block_expressions
// size : 105
// sig  : void optimize_block_expressions(bblock * block)


int __cdecl optimize_block_expressions(bblock *block)

{
  node_list *stmt;
  il_node *new_tree;
  
  build_dag_chains('\x01');
  compute_dataflow('\x01');
  for (stmt = block->ilnode; stmt != (node_list *)0x0; stmt = stmt->next) {
    new_tree = optimize_expression_tree(stmt->node,stmt,block);
    stmt->node = new_tree;
    forward_member_constant_store(stmt);
    if ((g_debug_flags & 0x18000) != 0) {
      dump_tree(stmt->node,0,&g_str_ttt);
    }
  }
  free_du_tables();
  return;
}



