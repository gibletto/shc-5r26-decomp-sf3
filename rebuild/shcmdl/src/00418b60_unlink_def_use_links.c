#include "decls.h"
#include "imports.h"

// entry: 00418b60
// name : unlink_def_use_links
// size : 97
// sig  : void unlink_def_use_links(il_node * node)


int __cdecl unlink_def_use_links(il_node *node)

{
  node_list **prev_link;
  node_list *cur_link;
  node_list *link;
  node_list *next_link;
  dutbl *web;
  
  cur_link = node->duptr->links;
  do {
    if (cur_link == (node_list *)0x0) {
      node->duptr->links = (node_list *)0x0;
      return;
    }
    next_link = cur_link->next;
    web = cur_link->node->duptr;
    prev_link = &web->links;
    link = web->links;
    while (link != (node_list *)0x0) {
      if (link->node == node) {
        *prev_link = link->next;
        pool_free(link,8);
        break;
      }
      prev_link = &link->next;
      link = *prev_link;
    }
    pool_free(cur_link,8);
    cur_link = next_link;
  } while( true );
}



