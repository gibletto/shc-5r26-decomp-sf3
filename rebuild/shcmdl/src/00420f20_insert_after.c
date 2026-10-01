#include "decls.h"
#include "imports.h"

// entry: 00420f20
// name : insert_after
// size : 49
// sig  : void insert_after(il_node * pos, il_node * node)


int __cdecl insert_after(il_node *pos,il_node *node)

{
  if ((pos == (il_node *)0x0) || (node == (il_node *)0x0)) {
    fatal_error(0x1072);
  }
  node->parent = pos->parent;
  node->next = pos->next;
  pos->next = node;
  return;
}



