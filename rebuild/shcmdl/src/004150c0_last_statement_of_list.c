#include "decls.h"
#include "imports.h"

// entry: 004150c0
// name : last_statement_of_list
// size : 67
// sig  : il_node * last_statement_of_list(node_list * list)


il_node * __cdecl last_statement_of_list(node_list *list)

{
  il_node *stmt;
  node_list *next;
  il_node *next_stmt;
  il_op parent_op;
  
  if (list == (node_list *)0x0) {
    return (il_node *)0x0;
  }
  next = list->next;
  while (next != (node_list *)0x0) {
    list = list->next;
    next = list->next;
  }
  stmt = list->node;
  next_stmt = stmt->next;
  if ((next_stmt != (il_node *)0x0) && (next_stmt->op == IL_GOTO)) {
    return next_stmt;
  }
  parent_op = stmt->parent->op;
  if (((parent_op == IL_GLABEL) || (parent_op == IL_CLABEL)) || (parent_op == IL_DLABEL)) {
    stmt = stmt->parent;
  }
  return stmt;
}



