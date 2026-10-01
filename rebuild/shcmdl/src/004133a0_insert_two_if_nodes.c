#include "decls.h"
#include "imports.h"

// entry: 004133a0
// name : insert_two_if_nodes
// size : 35
// sig  : void insert_two_if_nodes(il_node * pos)


int __cdecl insert_two_if_nodes(il_node *pos)

{
  il_node *node;
  int n;
  
  n = 2;
  do {
    node = alloc_node();
    node->op = IL_IF;
    insert_before(pos,node);
    n = n + -1;
  } while (n != 0);
  return;
}



