#include "decls.h"
#include "imports.h"

// entry: 0041e3e0
// name : stmts_modify_expr
// size : 117
// sig  : int stmts_modify_expr(node_list * stmts, il_node * expr, int memory_kind, int mode)


int __cdecl stmts_modify_expr(node_list *stmts,il_node *expr,int memory_kind,int mode)

{
  int rc;
  il_node *stmt;
  
  while( true ) {
    if (((stmts == (node_list *)0x0) || (expr == stmts->node)) ||
       ((mode == 1 &&
        ((rc = tree_has_conditional_op(stmts->node), rc == 0 &&
         (stmt = tree_contains_node(stmts->node,expr), stmt != (il_node *)0x0)))))) {
      return 0;
    }
    stmt = stmts->node;
    if ((stmt->flag2 & 0x10) != 0) {
      stmt = stmt->child->next;
    }
    rc = stmt_modifies_operands(stmt,expr,memory_kind);
    if (rc != 0) break;
    stmts = stmts->next;
  }
  return 1;
}



