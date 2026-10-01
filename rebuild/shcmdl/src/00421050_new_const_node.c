#include "decls.h"
#include "imports.h"

// entry: 00421050
// name : new_const_node
// size : 218
// sig  : il_node * new_const_node(uchar type, uint value)


il_node * __cdecl new_const_node(uchar type,uint value)

{
  byte kind;
  il_node *node;
  
  node = alloc_node_or_null();
  if (node == (il_node *)0x0) {
    abort_function_optimization();
  }
  node->op = IL_CONST;
  node->type = type;
  if (((type & 0xf0) == 0x80) || ((type & 0xf0) == 0x90)) {
    node->type = '\x1c';
  }
  node->nodes = '\x01';
  kind = node->type & 0xf8;
  if (kind == 0x28) {
    convert_int_to_float(&value,(uint *)&node->val);
    return node;
  }
  if (kind == 0x30) {
    convert_int_to_double(&value,(uint *)&node->val);
    return node;
  }
  if (kind != 0x38) {
    switch(node->type & 0x1c) {
    case 0:
      node->val = (int)(char)value;
      return node;
    case 4:
      node->val = value & 0xff;
      return node;
    case 8:
      node->val = (int)(short)value;
      return node;
    case 0xc:
      node->val = value & 0xffff;
      return node;
    default:
      node->val = value;
      return node;
    }
  }
  convert_int_to_ldouble(&value,(uint *)&node->val);
  return node;
}



