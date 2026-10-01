#include "decls.h"
#include "imports.h"

// entry: 004155d0
// name : compare_statements_backward
// size : 347
// sig  : uint compare_statements_backward(il_node * stmt_a, il_node * stmt_b, bblock * block_a, bblock * block_b)


uint __cdecl compare_statements_backward(il_node *stmt_a,il_node *stmt_b,bblock *block_a,bblock *block_b)

{
  uint differ;
  int opno_a;
  int opno_b;
  int is_ctrl;
  il_node *piVar1;
  il_node *prev_b;
  
  if ((stmt_a == (il_node *)0x0) || (stmt_b == (il_node *)0x0)) {
    return (uint)(stmt_b != stmt_a);
  }
  differ = trees_differ(stmt_a,stmt_b);
  if ((stmt_a->parent->op == IL_SWITCH) || (stmt_b->parent->op == IL_SWITCH)) {
    differ = 1;
  }
  if (differ == 0) {
    g_merge_match_depth = g_merge_match_depth + 1;
    opno_a = operand_index(stmt_a);
    opno_b = operand_index(stmt_b);
    piVar1 = block_a->ilnode->node;
    if (piVar1 != stmt_a) {
      if (block_b->ilnode->node != stmt_b) {
        if ((opno_a == 1) || (opno_b == 1)) {
          is_ctrl = parent_is_control_statement(stmt_a);
          if ((is_ctrl != 0) || (is_ctrl = parent_is_control_statement(stmt_b), is_ctrl != 0)) {
            opno_a = operand_index(stmt_a->parent);
            opno_b = operand_index(stmt_b->parent);
            stmt_a = stmt_a->parent;
            stmt_b = stmt_b->parent;
          }
          if ((opno_a == 1) || (opno_b == 1)) {
            return (opno_b == opno_a) - 1 & 2;
          }
        }
        piVar1 = nth_operand(opno_a + -1,stmt_a->parent);
        prev_b = nth_operand(opno_b + -1,stmt_b->parent);
        differ = compare_statements_backward(piVar1,prev_b,block_a,block_b);
        return differ;
      }
      if (piVar1 != stmt_a) {
        return 2;
      }
    }
    if (block_b->ilnode->node != stmt_b) {
      return 2;
    }
    return 0;
  }
  if (g_merge_match_depth == 0) {
    return differ;
  }
  return 2;
}



