#include "decls.h"
#include "imports.h"

// entry: 004114c0
// name : insert_in_loop_preheader
// size : 123
// sig  : void insert_in_loop_preheader(loop * lp, il_node * expr, il_node * assign)


int __cdecl insert_in_loop_preheader(loop *lp,il_node *expr,il_node *assign)

{
  if (lp->child != (loop *)0x0) {
    insert_in_loop_preheader(lp->child,expr,assign);
  }
  if (lp->next != (loop *)0x0) {
    insert_in_loop_preheader(lp->next,expr,assign);
  }
  if ((short)expr->invno == lp->lpnumber) {
    insert_before(lp->node,assign);
    append_list_item(&lp->pre->ilnode,assign);
    g_tree_changed = 1;
    clear_induction_marks(assign);
  }
  return;
}



