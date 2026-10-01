#include "decls.h"
#include "imports.h"

// entry: 0040ccf0
// name : dump_du_chains_in_tree
// size : 47
// sig  : void dump_du_chains_in_tree(il_node * node)


int __cdecl dump_du_chains_in_tree(il_node *node)

{
  il_node *sub;
  
  for (sub = node->child; sub != (il_node *)0x0; sub = sub->next) {
    dump_du_chains_in_tree(sub);
  }
  if (node->duptr != (dutbl *)0x0) {
    dump_du_chain(node);
  }
  return;
}



