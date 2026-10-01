#include "decls.h"
#include "imports.h"

// entry: 00405b80
// name : number_loops
// size : 162
// sig  : void number_loops(loop * lp, int depth)


int __cdecl number_loops(loop *lp,int depth)

{
  short brc;
  short nestcnt;
  loop *inner;
  
  if (lp != (loop *)0x0) {
    if (lp->next == (loop *)0x0) {
      number_loops(lp->child,depth + 1);
      g_last_loop_number = g_last_loop_number + 1;
      lp->lpnumber = g_last_loop_number;
      brc = g_last_loop_number + (short)depth;
    }
    else {
      number_loops(lp->next,0);
      number_loops(lp->child,1);
      g_last_loop_number = g_last_loop_number + 1;
      lp->lpnumber = g_last_loop_number;
      brc = g_last_loop_number;
    }
    nestcnt = 1;
    lp->brc = brc;
    for (inner = lp->child; inner != (loop *)0x0; inner = inner->next) {
      if (nestcnt <= inner->nestcnt) {
        nestcnt = inner->nestcnt + 1;
      }
    }
    lp->nestcnt = nestcnt;
  }
  return;
}



