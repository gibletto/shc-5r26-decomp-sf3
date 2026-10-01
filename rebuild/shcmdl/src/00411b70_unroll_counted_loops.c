#include "decls.h"
#include "imports.h"

// entry: 00411b70
// name : unroll_counted_loops
// size : 243
// sig  : void unroll_counted_loops(loop * lp)


int __cdecl unroll_counted_loops(loop *lp)

{
  short nstmts;
  bblock *body;
  int copies;
  uint flags;
  node_list *item;
  uint trips;
  
  if (lp->child != (loop *)0x0) {
    unroll_counted_loops(lp->child);
  }
  if (lp->next != (loop *)0x0) {
    unroll_counted_loops(lp->next);
  }
  flags = lp->flag;
  if ((flags & 0x100) != 0) {
LAB_00411c4f:
    if ((flags & 0x4024) == 0) {
      unroll_loop_by_four(lp);
    }
    return;
  }
  if (lp->start->bn_next != lp->exit) goto LAB_00411c4f;
  body = lp->exit;
  if ((flags & 1) == 0) {
    body = lp->start;
  }
  if ((lp->lstep == 0) || (trips = lp->repet, trips == 0)) {
    lp->flag = flags | 0x100;
    unroll_loop_by_four(lp);
    return;
  }
  nstmts = 0;
  for (item = body->ilnode; item != (node_list *)0x0; item = item->next) {
    nstmts = nstmts + 1;
  }
  if (9 < nstmts) {
    lp->flag = flags | 0x100;
    unroll_loop_by_four(lp);
    return;
  }
  if (trips % 3 == 0) {
    copies = 2;
  }
  else {
    if ((trips & 1) != 0) goto LAB_00411c0e;
    copies = 1;
  }
  copy_loop_body_blocks(lp,copies);
  g_tree_changed = 1;
LAB_00411c0e:
  if ((lp->repet != 2) && (lp->repet != 3)) {
    return;
  }
  lp->repet = 1;
  return;
}



