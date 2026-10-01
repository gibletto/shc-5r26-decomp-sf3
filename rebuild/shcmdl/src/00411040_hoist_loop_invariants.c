#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))


// entry: 00411040
// name : hoist_loop_invariants
// size : 90
// sig  : void hoist_loop_invariants(loop * lp)


int __cdecl hoist_loop_invariants(loop *lp)

{
  bblock *block;
  
  if (lp->child != (loop *)0x0) {
    hoist_loop_invariants(lp->child);
  }
  if (lp->next != (loop *)0x0) {
    hoist_loop_invariants(lp->next);
  }
  g_cur_loop = lp;
  block = lp->start;
  if (lp->exit->bn_next != block) {
    do {
      if (block->f_next != (bblock *)0x0) {
        hoist_invariants_in_block(block);
      }
      block = block->bn_next;
    } while (g_cur_loop->exit->bn_next != block);
  }
  return;
}



