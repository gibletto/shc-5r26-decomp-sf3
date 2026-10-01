#include "decls.h"
#include "imports.h"

// entry: 00406910
// name : expand_unsigned_float_assign
// size : 61
// sig  : il_node * __cdecl expand_unsigned_float_assign(il_node *node)


il_node * __cdecl expand_unsigned_float_assign(il_node *node)

{
  il_node *piVar1;
  byte size_class;
  byte type;
  
  if (node->op == IL_ASSIGN) {
    type = node->type;
    size_class = type & 0xf8;
    if (size_class == 0x28) {
      piVar1 = expand_unsigned_to_float(node);
      return piVar1;
    }
    if (((((type & 0xe0) == 0) && (size_class != 0)) && (size_class != 8)) && ((type & 4) != 0)) {
      node = expand_float_to_unsigned(node);
    }
  }
  return node;
}
