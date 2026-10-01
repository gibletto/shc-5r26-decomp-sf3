#include "decls.h"
#include "imports.h"

// entry: 00418d30
// name : clear_induction_numbers
// size : 67
// sig  : void clear_induction_numbers(il_node * tree)


int __cdecl clear_induction_numbers(il_node *tree)

{
  il_node *child;
  node_list *link;
  
  for (child = tree->child; child != (il_node *)0x0; child = child->next) {
    clear_induction_numbers(child);
  }
  if (tree->duptr != (dutbl *)0x0) {
    for (link = tree->duptr->links; link != (node_list *)0x0; link = link->next) {
      link->node->ivno = 0;
    }
  }
  tree->ivno = 0;
  return;
}



