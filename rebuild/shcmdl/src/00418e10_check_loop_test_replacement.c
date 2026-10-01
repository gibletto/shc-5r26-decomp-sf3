#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_iv_copy_list
#define g_iv_copy_list (*(node_list * *)(g_sd + 0x3a00))
#undef g_iv_update_stmt
#define g_iv_update_stmt (*(il_node * *)(g_sd + 0x26ac4))
#undef g_loop_test
#define g_loop_test (*(il_node * *)(g_sd + 0x26854))
#undef g_loop_test_copy
#define g_loop_test_copy (*(il_node * *)(g_sd + 0x1e4f8))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 00418e10
// name : check_loop_test_replacement
// size : 631
// sig  : uint check_loop_test_replacement(iv_entry * entry)


uint __cdecl check_loop_test_replacement(iv_entry *entry)

{
  il_node *temp;
  node_list *item;
  il_node *temp_assign;
  il_node *expr;
  uint uVar1;
  byte ty;
  iv_use *test_use;
  int test_size;
  il_node *test_assign;
  short iv_leaf;
  iv_use *use;
  
  g_loop_test_copy = copy_tree(0,g_loop_test);
  g_iv_update_stmt = entry->update;
  iv_leaf = g_iv_update_stmt->nleaf;
  test_use = (iv_use *)0x0;
  ty = g_loop_test_copy->child->type;
  if ((ty & 0x40) == 0) {
    test_size = (int)(char)((ty & 0x1c) >> 2);
  }
  else {
    test_size = 8;
  }
  for (use = entry->uses; use != (iv_use *)0x0; use = use->next) {
    if (2 < g_iv_tested_count) break;
    expr = use->copy;
    ty = expr->type;
    if (((ty & 0xe0) == 0x80) || ((ty & 0xf8) == 0x40)) {
      if ((g_options->option_bits & 1) != 0) {
        return 1;
      }
      ty = 0x40;
      uVar1 = 8;
    }
    else {
      uVar1 = ((int)(char)ty & 0x1cU) >> 2;
    }
    temp = new_node(IL_ID,ty);
    item = g_iv_copy_list;
    if (g_iv_copy_list == (node_list *)0x0) {
LAB_00418f0b:
      replace_node(expr,temp);
    }
    else {
      do {
        if (item->node == expr) {
          temp->parent = (il_node *)0x0;
          temp->next = expr->next;
          expr->parent = (il_node *)0x0;
          expr->next = (il_node *)0x0;
          item->node = temp;
          break;
        }
        item = item->next;
      } while (item != (node_list *)0x0);
      if (item == (node_list *)0x0) goto LAB_00418f0b;
    }
    temp_assign = new_node(IL_ASSIGN,ty);
    temp = copy_tree(1,temp);
    temp_assign->child = temp;
    temp->parent = temp_assign;
    temp_assign->child->next = expr;
    expr->parent = temp_assign;
    temp->next = expr;
    if (((&g_iv_test_type_table)[test_size + uVar1 * 0xb] != '\0') && ((use->copy->flag2 & 4) == 0))
    {
      test_use = use;
      test_assign = temp_assign;
    }
    g_iv_tested_count = g_iv_tested_count + 1;
  }
  if ((((test_use != (iv_use *)0x0) && (g_loop_test_copy != (il_node *)0x0)) &&
      (use == (iv_use *)0x0)) &&
     (((int)g_loop_test_copy->child->nleaf == (int)iv_leaf && (g_iv_tested_count < 4)))) {
    g_loop_test_copy->op = g_loop_test_copy->op + (char)test_use->test_adjust;
    replace_loop_test_copy(test_assign,test_use);
    uVar1 = fold_and_check_overflow(g_loop_test_copy->child->next);
    if (uVar1 == 3) {
      uVar1 = check_test_variables(g_loop_test_copy->child->next,(int)iv_leaf);
      return uVar1;
    }
    if (uVar1 == 0) {
      if ((g_loop_test_copy->op != IL_NE) &&
         (expr = simplify_relational(g_loop_test_copy), expr->op == IL_COMMA)) {
        uVar1 = 1;
      }
      if (uVar1 == 0) {
        uVar1 = 3;
      }
    }
    if ((uVar1 == 1) || (uVar1 == 2)) {
      g_test_replace_ok = 0;
    }
    return uVar1;
  }
  return 1;
}



