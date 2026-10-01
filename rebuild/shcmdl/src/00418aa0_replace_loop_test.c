#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))
#undef g_loop_test
#define g_loop_test (*(il_node * *)(g_sd + 0x26854))


// entry: 00418aa0
// name : replace_loop_test
// size : 178
// sig  : void replace_loop_test(il_node * temp_assign, iv_use * use)


int __cdecl replace_loop_test(il_node *temp_assign,iv_use *use)

{
  il_node *piVar1;
  il_node *rhs_copy;
  
  piVar1 = copy_tree(0,temp_assign->child);
  unlink_def_use_links(g_loop_test->child);
  replace_and_free_node(g_loop_test->child,piVar1);
  piVar1 = temp_assign->child->next;
  rhs_copy = copy_tree_unlinked(0,piVar1);
  replace_node(piVar1,rhs_copy);
  move_def_use_links(use->id,rhs_copy);
  replace_and_free_node(use->id,g_loop_test->child->next);
  g_loop_test->child->next = piVar1;
  piVar1->parent = g_loop_test;
  g_loop_test->child->next = piVar1;
  g_cur_loop->flag = g_cur_loop->flag | 0x200;
  return;
}



