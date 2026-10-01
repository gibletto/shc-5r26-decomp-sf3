#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))
#undef g_loop_limit
#define g_loop_limit (*(int *)(g_sd + 0x267bc))
#undef g_loop_test
#define g_loop_test (*(il_node * *)(g_sd + 0x26854))


// entry: 00411540
// name : compute_loop_trip_counts
// size : 229
// sig  : void compute_loop_trip_counts(loop * lp)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl compute_loop_trip_counts(loop *lp)

{
  il_node *test;
  uint is_zero;
  bblock *block;
  il_op lhs_op;
  il_op op;
  
  if (lp->child != (loop *)0x0) {
    compute_loop_trip_counts(lp->child);
  }
  if (lp->next != (loop *)0x0) {
    compute_loop_trip_counts(lp->next);
  }
  g_cur_loop = lp;
  if ((lp->flag & 0x4024) == 0) {
    g_loop_init = 0;
    _g_loop_limit = 0;
    if ((lp->flag & 1) == 0) {
      block = lp->exit;
    }
    else {
      block = lp->start;
    }
    test = block->ilnode->node;
    op = test->op;
    g_loop_test = test;
    if ((((op == IL_LT) || (op == IL_GT)) || (op == IL_LE)) || ((op == IL_GE || (op == IL_NE)))) {
      lhs_op = test->child->op;
      if ((lhs_op == IL_ID) || ((lhs_op == IL_CAST && (test->child->child->op == IL_ID)))) {
        find_loop_induction_in_block(block);
        read_loop_limit(test);
        compute_loop_trip_count(test);
        return;
      }
    }
    if (((((lp->flag & 0x10) == 0) && (op == IL_CONST)) &&
        (is_zero = is_const_value(test,0,test->type), is_zero != 0)) &&
       (g_cur_loop->node->op == IL_DO)) {
      g_cur_loop->repet = 1;
      return;
    }
  }
  return;
}



