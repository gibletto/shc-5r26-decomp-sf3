#include "decls.h"
#include "imports.h"

// entry: 0041e4b0
// name : stmt_modifies_operands
// size : 204
// sig  : int stmt_modifies_operands(il_node * stmt, il_node * expr, int memory_kind)


int __cdecl stmt_modifies_operands(il_node *stmt,il_node *expr,int memory_kind)

{
  int rc;
  il_node *operand;
  
  if ((memory_kind != 0) && (rc = stmt_clobbers_memory(stmt,memory_kind), rc != 0)) {
    return 1;
  }
  if (expr->op == IL_ID) {
    if (((((&g_op_class)[(char)stmt->op] & 0x20) != 0) && (stmt->child->symx == expr->symx)) &&
       ((stmt->child->flag2 & 0x20) == 0)) {
      return 1;
    }
    for (operand = stmt->child; operand != (il_node *)0x0; operand = operand->next) {
      rc = stmt_modifies_operands(operand,expr,memory_kind);
      if (rc != 0) {
        return 1;
      }
    }
  }
  else {
    if ((expr->child != (il_node *)0x0) &&
       (rc = stmt_modifies_operands(stmt,expr->child,memory_kind), rc != 0)) {
      return 1;
    }
    if (((expr->child != (il_node *)0x0) && (operand = expr->child->next, operand != (il_node *)0x0)
        ) && (rc = stmt_modifies_operands(stmt,operand,memory_kind), rc != 0)) {
      return 1;
    }
  }
  return 0;
}



