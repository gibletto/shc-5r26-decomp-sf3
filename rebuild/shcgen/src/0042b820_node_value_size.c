#include "decls.h"
#include "imports.h"

// entry: 0042b820
// name : node_value_size
// size : 147
// sig  : int node_value_size(gen_node * node)


int __cdecl node_value_size(gen_node *node)

{
  int size_bytes;
  byte type_bits;
  
  size_bytes = 0;
  type_bits = node->type;
  switch(type_bits & 0xe0) {
  case 0:
    if ((type_bits & 0x18) == 0) {
      return 1;
    }
    if ((type_bits & 0x18) == 8) {
      return 2;
    }
    return 4;
  case 0x20:
    if ((type_bits & 0x18) == 8) {
      return 4;
    }
    if ((type_bits & 0x18) == 0x10) {
      return 8;
    }
    return 8;
  case 0x40:
    if (((type_bits & 0x18) == 0) || ((type_bits & 0x18) == 8)) {
      return 4;
    }
    break;
  case 0x60:
    return node->val;
  case 0x80:
    size_bytes = 4;
  }
  return size_bytes;
}



