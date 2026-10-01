#include "decls.h"
#include "imports.h"

// entry: 00417ab0
// name : loop_tree_contains
// size : 55
// sig  : int __cdecl loop_tree_contains(loop *lp,int lpnumber)


int __cdecl loop_tree_contains(loop *lp,int lpnumber)

{
  int found;
  
  found = 0;
  while ((lp != (loop *)0x0 && (found == 0))) {
    found = 1;
    if (lp->lpnumber != lpnumber) {
      found = loop_tree_contains(lp->next,lpnumber);
    }
    lp = lp->child;
  }
  return found;
}
