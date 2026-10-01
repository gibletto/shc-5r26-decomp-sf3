#include "decls.h"
#include "imports.h"

// entry: 00414f20
// name : match_statement_tails
// size : 402
// sig  : void match_statement_tails(il_node * stmt_a, il_node * stmt_b, bblock * block_a, bblock * block_b)


int __cdecl match_statement_tails(il_node *stmt_a,il_node *stmt_b,bblock *block_a,bblock *block_b)

{
  uint differ;
  int opno_a;
  int opno_b;
  int is_ctrl;
  
  do {
    differ = trees_differ(stmt_a,stmt_b);
    if ((stmt_a->parent->op == IL_SWITCH) || (stmt_b->parent->op == IL_SWITCH)) {
      differ = 1;
    }
    if (differ != 0) {
      if (g_merge_match_depth == 0) {
        return;
      }
      record_common_tail(stmt_a->next,stmt_b->next,block_a,block_b,'\0');
      return;
    }
    g_merge_match_depth = g_merge_match_depth + 1;
    opno_a = operand_index(stmt_a);
    opno_b = operand_index(stmt_b);
    if ((block_a->ilnode->node == stmt_a) || (block_b->ilnode->node == stmt_b)) {
      if ((block_a->ilnode->node == stmt_a) && (block_b->ilnode->node == stmt_b)) {
        record_common_tail(stmt_a,stmt_b,block_a,block_b,'\x01');
        return;
      }
      record_common_tail(stmt_a,stmt_b,block_a,block_b,'\0');
      return;
    }
    if ((opno_a == 1) || (opno_b == 1)) {
      is_ctrl = parent_is_control_statement(stmt_a);
      if ((is_ctrl != 0) || (is_ctrl = parent_is_control_statement(stmt_b), is_ctrl != 0)) {
        opno_a = operand_index(stmt_a->parent);
        opno_b = operand_index(stmt_b->parent);
        stmt_a = stmt_a->parent;
        stmt_b = stmt_b->parent;
      }
      if ((opno_a == 1) || (opno_b == 1)) {
        if (opno_b != opno_a) {
          record_common_tail(stmt_a,stmt_b,block_a,block_b,'\0');
          return;
        }
        record_common_tail(stmt_a,stmt_b,block_a,block_b,'\x01');
        return;
      }
    }
    stmt_a = nth_operand(opno_a + -1,stmt_a->parent);
    stmt_b = nth_operand(opno_b + -1,stmt_b->parent);
  } while( true );
}



