#include "decls.h"
#include "imports.h"

// entry: 00405960
// name : free_loop_tree
// size : 81
// sig  : void free_loop_tree(loop * lp)


int __cdecl free_loop_tree(loop *lp)

{
  loop *next_lp;
  
  while (lp != (loop *)0x0) {
    next_lp = lp->next;
    if (lp->child != (loop *)0x0) {
      free_loop_tree(lp->child);
    }
    if ((g_debug_flags & 0x1000) != 0) {
      FID_conflict__wprintf(s_free_lptbl_LP_d_00433674,(int)lp->lpnumber);
    }
    pool_free(lp,0x3c);
    lp = next_lp;
  }
  return;
}



