#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))


// entry: 00418540
// name : set_loop_step
// size : 162
// sig  : void set_loop_step(il_node * step)


int __cdecl set_loop_step(il_node *step)

{
  il_node *node;
  il_node *step_copy;
  uint overflow;
  
  if (step != (il_node *)0x0) {
    node = new_node(IL_CONST,'\x10');
    step_copy = copy_tree(0,step);
    node->child = step_copy;
    step_copy->parent = node;
    overflow = fold_and_check_overflow(node->child);
    if (overflow == 0) {
      *(char *)&g_cur_loop->lstep = (char)node->child->val;
      *(undefined1 *)((int)&g_cur_loop->lstep + 1) = *(undefined1 *)((int)&node->child->val + 1);
      *(undefined1 *)((int)&g_cur_loop->lstep + 2) = *(undefined1 *)((int)&node->child->val + 2);
      *(undefined1 *)((int)&g_cur_loop->lstep + 3) = *(undefined1 *)((int)&node->child->val + 3);
    }
    else {
      g_cur_loop->lstep = 0;
    }
    free_tree(node);
    return;
  }
  g_cur_loop->lstep = -1;
  return;
}



