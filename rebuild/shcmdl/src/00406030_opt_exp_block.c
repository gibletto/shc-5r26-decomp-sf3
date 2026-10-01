#include "decls.h"
#include "imports.h"

// entry: 00406030
// name : opt_exp_block
// size : 114
// sig  : void opt_exp_block(bblock * block)


int __cdecl opt_exp_block(bblock *block)

{
  il_node *node;
  node_list *stmt;
  
  for (stmt = block->ilnode; stmt != (node_list *)0x0; stmt = stmt->next) {
    if ((g_debug_flags & 0x7f8) != 0) {
      dump_tree(stmt->node,1,s_cnt_expblk_00433e78);
    }
    node = opt_exp(stmt->node);
    stmt->node = node;
    if ((g_debug_flags & 0x7f8) != 0) {
      dump_tree(node,1,s_opt_exp_after_00433e68);
    }
    if (g_opt_exp_pass == 0) {
      report_fold_warnings(stmt->node);
    }
  }
  return;
}



