#include "decls.h"
#include "imports.h"

// entry: 00408650
// name : dump_tree_rec
// size : 83
// sig  : void dump_tree_rec(il_node * node, int depth)


int __cdecl dump_tree_rec(il_node *node,int depth)

{
  il_node *child;
  il_node *next_child;
  
  if (node != (il_node *)0x0) {
    dump_tree_node(node,(short)depth);
    child = node->child;
    if (child != (il_node *)0x0) {
      do {
        next_child = child->next;
        (&DAT_004371ea)[depth] = 1;
        if (next_child == (il_node *)0x0) {
          (&DAT_004371ea)[depth] = 0;
        }
        dump_tree_rec(child,depth + 1);
        child = child->next;
      } while (child != (il_node *)0x0);
    }
  }
  return;
}



