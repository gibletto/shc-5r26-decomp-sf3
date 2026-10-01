#include "decls.h"
#include "imports.h"

// entry: 00404d80
// name : read_node_type
// size : 57
// sig  : void read_node_type(il_node * node)


int __cdecl read_node_type(il_node *node)

{
  byte type_class;
  
  read_ila_bytes(1,(char *)&node->type);
  type_class = node->type & 0xf0;
  if ((((type_class == 0x60) || (type_class == 0x70)) || (type_class == 0x80)) ||
     (type_class == 0x90)) {
    read_ila_bytes(4,(char *)&node->val);
  }
  return;
}



