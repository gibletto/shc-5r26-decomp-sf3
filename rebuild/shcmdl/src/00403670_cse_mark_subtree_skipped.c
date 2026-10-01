#include "decls.h"
#include "imports.h"

// entry: 00403670
// name : cse_mark_subtree_skipped
// size : 36
// sig  : void cse_mark_subtree_skipped(il_node * node)


int __cdecl cse_mark_subtree_skipped(il_node *node)

{
  il_node *child;
  
  for (child = node->child; child != (il_node *)0x0; child = child->next) {
    cse_mark_subtree_skipped(child);
  }
  *(byte *)&node->flag2 = (byte)node->flag2 | 1;
  return;
}



