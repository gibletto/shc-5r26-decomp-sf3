#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_dt_loop
#define g_dt_loop (*(loop * *)(g_sd + 0x26844))


// entry: 0040c2d0
// name : assign_final_value_after_loop
// size : 163
// sig  : void assign_final_value_after_loop(il_node * cond, il_node * stmt)


int __cdecl assign_final_value_after_loop(il_node *cond,il_node *stmt)

{
  il_node *final_val;
  block_list *succ;
  block_list *second;
  
  insert_before(g_dt_loop->node->next,stmt);
  final_val = copy_tree(0,cond->child->next);
  if ((cond->op == IL_GE) || (cond->op == IL_LE)) {
    if (g_dt_loop->lstep < 1) {
      final_val->val = final_val->val + -1;
    }
    else {
      final_val->val = final_val->val + 1;
    }
  }
  stmt->filn = 0;
  stmt->line = 0;
  stmt->listno = 0;
  replace_and_free_node(stmt->child->next,final_val);
  succ = g_dt_loop->start->suclst;
  second = succ->next;
  if ((second != (block_list *)0x0) && (succ->block->number < second->block->number)) {
    succ = second;
  }
  push_list_item(&succ->block->ilnode,stmt);
  return;
}



