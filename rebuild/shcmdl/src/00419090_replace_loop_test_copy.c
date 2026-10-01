#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loop_test_copy
#define g_loop_test_copy (*(il_node * *)(g_sd + 0x1e4f8))


// entry: 00419090
// name : replace_loop_test_copy
// size : 128
// sig  : void replace_loop_test_copy(il_node * temp_assign, iv_use * use)


int __cdecl replace_loop_test_copy(il_node *temp_assign,iv_use *use)

{
  il_node *piVar1;
  il_node *rhs_copy;
  
  piVar1 = copy_tree(0,temp_assign->child);
  replace_and_free_node(g_loop_test_copy->child,piVar1);
  piVar1 = temp_assign->child->next;
  rhs_copy = copy_tree_unlinked(0,piVar1);
  replace_node(piVar1,rhs_copy);
  replace_and_free_node(use->copy_id,g_loop_test_copy->child->next);
  g_loop_test_copy->child->next = piVar1;
  piVar1->parent = g_loop_test_copy;
  g_loop_test_copy->child->next = piVar1;
  return;
}



