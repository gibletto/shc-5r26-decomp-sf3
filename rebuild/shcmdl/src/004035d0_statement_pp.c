#include "decls.h"
#include "imports.h"

// entry: 004035d0
// name : statement_pp
// size : 31
// sig  : ushort statement_pp(il_node * node)


ushort __cdecl statement_pp(il_node *node)

{
  ushort flag;
  
  flag = node->flag;
  while ((flag & 0x200) == 0) {
    node = node->parent;
    flag = node->flag;
  }
  return node->pp;
}



