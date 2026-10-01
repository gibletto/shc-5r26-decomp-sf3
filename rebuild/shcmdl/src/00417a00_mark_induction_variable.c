#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))


// entry: 00417a00
// name : mark_induction_variable
// size : 170
// sig  : void mark_induction_variable(il_node * def)


int __cdecl mark_induction_variable(il_node *def)

{
  int inside;
  bool all_inside;
  node_list *link;
  loop *lp;
  short lpno;
  il_node *ref;
  
  all_inside = true;
  link = def->duptr->links;
  do {
    if (link == (node_list *)0x0) {
LAB_00417a5c:
      if (all_inside) {
        for (ref = def->refchn; ref != (il_node *)0x0; ref = ref->refchn) {
          ref->ivno = (short)g_iv_count;
        }
        for (link = def->duptr->links; link != (node_list *)0x0; link = link->next) {
          for (ref = link->node; ref != (il_node *)0x0; ref = ref->refchn) {
            ref->ivno = (short)g_iv_count;
          }
        }
        g_iv_count = g_iv_count + 1;
      }
      return;
    }
    lp = link->node->duptr->block->lptbl;
    if (lp == (loop *)0x0) {
LAB_00417a5a:
      all_inside = false;
      goto LAB_00417a5c;
    }
    lpno = lp->lpnumber;
    if ((g_cur_loop->lpnumber < lpno) ||
       ((lpno < g_cur_loop->lpnumber &&
        (inside = loop_tree_contains(g_cur_loop->child,(int)lpno), inside == 0))))
    goto LAB_00417a5a;
    link = link->next;
  } while( true );
}



