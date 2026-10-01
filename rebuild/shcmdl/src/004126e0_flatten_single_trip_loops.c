#include "decls.h"
#include "imports.h"

// entry: 004126e0
// name : flatten_single_trip_loops
// size : 122
// sig  : void flatten_single_trip_loops(loop * lp)


int __cdecl flatten_single_trip_loops(loop *lp)

{
  il_node *body;
  il_op op;
  
  if (lp->child != (loop *)0x0) {
    flatten_single_trip_loops(lp->child);
  }
  if (lp->next != (loop *)0x0) {
    flatten_single_trip_loops(lp->next);
  }
  if (lp->repet != 1) {
    return;
  }
  body = lp->node;
  op = body->op;
  if (op != IL_DO) {
    if (g_has_goto != '\0') {
      return;
    }
    if ((lp->flag & 0x1000) != 0) {
      return;
    }
    if (op != IL_DO) {
      body = body->child;
      if (op != IL_WHILE) {
        body = body->next;
      }
      goto LAB_00412739;
    }
  }
  body = body->child;
LAB_00412739:
  body = copy_tree(0,body);
  replace_and_free_node(lp->node,body);
  g_loops_flattened = '\x01';
  return;
}



