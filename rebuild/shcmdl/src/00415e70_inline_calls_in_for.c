#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_inline_call_list
#define g_inline_call_list (*(inline_group * *)(g_sd + 0xdeb8))
#undef g_inline_loop
#define g_inline_loop (*(il_node * *)(g_sd + 0xde54))


// entry: 00415e70
// name : inline_calls_in_for
// size : 646
// sig  : void inline_calls_in_for(il_node * stmt)


int __cdecl inline_calls_in_for(il_node *stmt)

{
  il_node *piVar1;
  int pos;
  il_node *piVar2;
  uint labno;
  il_node *node;
  inline_group *group;
  inline_group *test_group;
  inline_call *cand;
  short saved_label;
  il_node *saved_loop;
  
  saved_loop = g_inline_loop;
  saved_label = g_inline_continue_label;
  g_inline_continue_label = 0;
  test_group = (inline_group *)0x0;
  g_inline_loop = (il_node *)0x0;
  expand_inline_calls_in_expr(stmt->child,stmt);
  g_inline_call_list = (inline_group *)0x0;
  g_inline_cond_depth = 0;
  find_inline_calls(stmt->child->next->next->next);
  group = (inline_group *)0x0;
  if (g_inline_call_list != (inline_group *)0x0) {
    g_inline_loop = stmt;
    group = g_inline_call_list;
  }
  g_inline_call_list = (inline_group *)0x0;
  g_inline_cond_depth = 0;
  find_inline_calls(stmt->child->next->next);
  if (g_inline_call_list != (inline_group *)0x0) {
    g_inline_loop = stmt;
    test_group = g_inline_call_list;
  }
  expand_inline_calls_in_stmt(stmt->child->next);
  if (test_group != (inline_group *)0x0) {
    piVar1 = stmt->child->next;
    if (piVar1->op != IL_BLOCK) {
      wrap_stmt_in_scope(piVar1);
    }
    piVar1 = last_operand(stmt->child->next);
    for (cand = test_group->calls; cand != (inline_call *)0x0; cand = cand->next) {
      expand_inline_call(cand,piVar1);
    }
    free_inline_group(test_group);
  }
  if (group != (inline_group *)0x0) {
    if (stmt->parent->op != IL_BLOCK) {
      wrap_stmt_in_scope(stmt);
    }
    if (stmt->child->op != IL_NULL) {
      piVar1 = copy_tree(0,stmt->child);
      pos = operand_index(stmt);
      insert_operands(stmt->parent,piVar1,pos);
      piVar1 = alloc_node();
      piVar1->op = IL_NULL;
      replace_operand(stmt,piVar1,1);
    }
    piVar2 = alloc_node();
    piVar2->op = IL_GOTO;
    labno = new_symbol(0,'\v');
    piVar2->symx = (short)labno;
    insert_before(stmt,piVar2);
    piVar1 = stmt->child->next;
    if (piVar1->next->op != IL_NULL) {
      if (piVar1->op != IL_BLOCK) {
        wrap_stmt_in_scope(piVar1);
      }
      piVar1 = last_operand(stmt->child->next);
      node = copy_tree(0,stmt->child->next->next);
      node->filn = 0;
      node->line = 0;
      node->listno = 0;
      insert_before(piVar1,node);
      piVar1 = alloc_node();
      piVar1->op = IL_NULL;
      replace_operand(stmt,piVar1,3);
    }
    piVar1 = stmt->child->next;
    if (piVar1->op != IL_BLOCK) {
      wrap_stmt_in_scope(piVar1);
    }
    piVar1 = new_glabel_stmt(piVar2->symx);
    piVar2 = last_operand(stmt->child->next);
    insert_before(piVar2,piVar1);
    piVar1 = last_operand(stmt->child->next);
    for (cand = group->calls; cand != (inline_call *)0x0; cand = cand->next) {
      expand_inline_call(cand,piVar1);
    }
    free_inline_group(group);
  }
  g_inline_continue_label = saved_label;
  g_inline_loop = saved_loop;
  return;
}



