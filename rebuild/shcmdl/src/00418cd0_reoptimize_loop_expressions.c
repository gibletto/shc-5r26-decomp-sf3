#include "decls.h"
#include "imports.h"

// entry: 00418cd0
// name : reoptimize_loop_expressions
// size : 81
// sig  : void reoptimize_loop_expressions(loop * lp)


int __cdecl reoptimize_loop_expressions(loop *lp)

{
  bblock *block;
  
  if (lp->child != (loop *)0x0) {
    reoptimize_loop_expressions(lp->child);
  }
  if (lp->next != (loop *)0x0) {
    reoptimize_loop_expressions(lp->next);
  }
  block = lp->start;
  if (lp->exit->bn_next != block) {
    do {
      if (block->f_next != (bblock *)0x0) {
        opt_exp_block(block);
      }
      block = block->bn_next;
    } while (lp->exit->bn_next != block);
  }
  return;
}



