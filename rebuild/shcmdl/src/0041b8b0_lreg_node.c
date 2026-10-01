#include "decls.h"
#include "imports.h"

// entry: 0041b8b0
// name : lreg_node
// size : 38
// sig  : il_node * lreg_node(lreg * lr)


il_node * __cdecl lreg_node(lreg *lr)

{
  il_node *node;
  
  node = (il_node *)0x0;
  if (lr->set == 1) {
    return *(il_node **)((int)lr->chain + 0x10);
  }
  if (lr->set == 0) {
    node = *(il_node **)(*(int *)((int)lr->chain + 8) + 8);
  }
  return node;
}



