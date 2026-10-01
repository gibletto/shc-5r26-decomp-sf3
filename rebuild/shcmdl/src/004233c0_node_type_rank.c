#include "decls.h"
#include "imports.h"

// entry: 004233c0
// name : node_type_rank
// size : 66
// sig  : int node_type_rank(il_node * node)


int __cdecl node_type_rank(il_node *node)

{
  int rank;
  
  rank = 0;
  switch(node->type) {
  case '\0':
  case '\x04':
    return 1;
  case '\b':
  case '\f':
    return 2;
  case '\x10':
  case '\x14':
  case '\x18':
  case '\x1c':
  case '@':
    return 3;
  case '(':
    return 4;
  case '0':
    return 5;
  case '8':
    rank = 6;
  }
  return rank;
}



