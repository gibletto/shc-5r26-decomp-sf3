#include "decls.h"
#include "imports.h"

// entry: 00408fa0
// name : dump_loop_tree
// size : 193
// sig  : void dump_loop_tree(loop * lp, int depth)


int __cdecl dump_loop_tree(loop *lp,int depth)

{
  int i;
  int indent;
  
  if (lp != (loop *)0x0) {
    indent = depth + -1;
    i = indent;
    do {
      for (; -1 < i; i = i + -1) {
        FID_conflict__wprintf(&g_str_loop_tree_bar);
      }
      FID_conflict__wprintf(s___CUR_0x_08x__00434d14,lp);
      FID_conflict__wprintf(s_nestcnt__d__lpnumber__d__00434cf8,(int)lp->nestcnt,(int)lp->lpnumber);
      FID_conflict__wprintf(s_lp_flag_0x_08x_00434ce8,lp->flag);
      for (i = indent; -1 < i; i = i + -1) {
        FID_conflict__wprintf(&g_str_loop_tree_bar);
      }
      FID_conflict__wprintf
                (s___startcfg_0x_08x____d____exitcf_00434ca0,lp->start,(int)lp->start->number,
                 lp->exit,(int)lp->exit->number,lp->pre,(int)lp->pre->number);
      if (lp->child != (loop *)0x0) {
        dump_loop_tree(lp->child,depth + 1);
      }
      lp = lp->next;
      i = indent;
    } while (lp != (loop *)0x0);
  }
  return;
}



