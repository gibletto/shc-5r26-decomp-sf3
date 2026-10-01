#include "decls.h"
#include "imports.h"

// entry: 00418bd0
// name : move_def_use_links
// size : 109
// sig  : void move_def_use_links(il_node * from, il_node * to_tree)


int __cdecl move_def_use_links(il_node *from,il_node *to_tree)

{
  node_list *back_link;
  il_node *child;
  node_list *link;
  
  for (child = to_tree->child; child != (il_node *)0x0; child = child->next) {
    move_def_use_links(from,child);
  }
  if (from->symx == to_tree->symx) {
    to_tree->duptr = from->duptr;
    for (link = from->cmnexp->duptr->links; link != (node_list *)0x0; link = link->next) {
      for (back_link = link->node->duptr->links; back_link != (node_list *)0x0;
          back_link = back_link->next) {
        if (back_link->node == from) {
          back_link->node = to_tree;
          break;
        }
      }
    }
    from->duptr = (dutbl *)0x0;
  }
  return;
}



