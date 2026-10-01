#include "decls.h"
#include "imports.h"

// entry: 00405af0
// name : prune_loops
// size : 132
// sig  : loop * prune_loops(loop * list)


loop * __cdecl prune_loops(loop *list)

{
  loop *lp;
  loop *plVar1;
  bblock *block;
  loop **next_link;
  
  lp = list;
  while (lp != (loop *)0x0) {
    if ((lp->start->b_next == (bblock *)0x0) || ((lp->flag & 0x804) != 0)) {
      next_link = &lp->next;
      if (lp->front == (loop *)0x0) {
        list = *next_link;
      }
      else {
        lp->front->next = *next_link;
      }
      if (*next_link != (loop *)0x0) {
        (*next_link)->front = lp->front;
      }
      plVar1 = *next_link;
      *next_link = (loop *)0x0;
      block = lp->start;
      if (lp->exit != block) {
        do {
          block->lptbl = (loop *)0x0;
          block = block->bn_next;
        } while (lp->exit != block);
      }
      block->lptbl = (loop *)0x0;
      free_loop_tree(lp);
      lp = plVar1;
    }
    else {
      plVar1 = prune_loops(lp->child);
      lp->child = plVar1;
      lp = lp->next;
    }
  }
  return list;
}



