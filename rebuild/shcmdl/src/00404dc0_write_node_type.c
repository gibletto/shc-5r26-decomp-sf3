#include "decls.h"
#include "imports.h"

// entry: 00404dc0
// name : write_node_type
// size : 57
// sig  : void write_node_type(il_node * node)


int __cdecl write_node_type(il_node *node)

{
  byte type_class;
  
  write_ilb_bytes(1,(char *)&node->type);
  type_class = node->type & 0xf0;
  if ((((type_class == 0x60) || (type_class == 0x70)) || (type_class == 0x80)) ||
     (type_class == 0x90)) {
    write_ilb_bytes(4,(char *)&node->val);
  }
  return;
}



