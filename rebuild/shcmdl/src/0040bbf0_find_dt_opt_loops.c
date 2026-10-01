#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_dt_loop
#define g_dt_loop (*(loop * *)(g_sd + 0x26844))
#undef g_loop_test
#define g_loop_test (*(il_node * *)(g_sd + 0x26854))


// entry: 0040bbf0
// name : find_dt_opt_loops
// size : 168
// sig  : void find_dt_opt_loops(loop * lp)


int __cdecl find_dt_opt_loops(loop *lp)

{
  il_node *node;
  uint is_zero;
  
  if (lp->child != (loop *)0x0) {
    find_dt_opt_loops(lp->child);
  }
  if (lp->next != (loop *)0x0) {
    find_dt_opt_loops(lp->next);
  }
  if ((lp->repet != 0) && ((lp->lstep == 1 || (lp->lstep == -1)))) {
    g_dt_loop = lp;
    g_loop_test = lp->node->child->next;
    if (lp->node->op == IL_FOR) {
      g_loop_test = g_loop_test->next->next;
    }
    if ((((g_loop_test->op != IL_NE) || (lp->lstep != -1)) ||
        (node = g_loop_test->child->next, is_zero = is_const_value(node,0,node->type), is_zero == 0)
        ) && ((g_loop_test->op != IL_LE && (g_loop_test->op != IL_GE)))) {
      convert_loop_to_decrement_test(g_loop_test);
    }
  }
  return;
}



