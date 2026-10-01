#include "decls.h"
#include "imports.h"

// entry: 00410250
// name : simplify_cast
// size : 259
// sig  : il_node * simplify_cast(il_node * node)


il_node * __cdecl simplify_cast(il_node *node)

{
  byte new_type;
  int inner_unsigned;
  int iVar1;
  byte cast_type;
  il_node *inner;
  byte inner_type;
  il_node *parent;
  
  parent = node->parent;
  inner = node->child;
  cast_type = node->type;
  new_type = cast_type & 0xfd;
  node->type = new_type;
  inner_type = inner->type;
  if (new_type == inner_type) {
    replace_node(node,inner);
    free_node(node);
    return inner;
  }
  if ((((cast_type & 0xf8) == 0x10) || ((cast_type & 0xf8) == 0x18)) &&
     (((inner_type & 0xf8) == 0x10 || ((inner_type & 0xf8) == 0x18)))) {
    if (((cast_type & 0xe0) != 0) || (iVar1 = 1, (cast_type & 4) == 0)) {
      iVar1 = 0;
    }
    if (((inner_type & 0xe0) != 0) || (inner_unsigned = 1, (inner_type & 4) == 0)) {
      inner_unsigned = 0;
    }
    if (iVar1 == inner_unsigned) {
      if (inner->op != IL_ID) {
        inner->type = new_type;
      }
      replace_node(node,inner);
      free_node(node);
      return inner;
    }
  }
  iVar1 = tree_has_float(node);
  if ((iVar1 == 0) && (parent->op == IL_CAST)) {
    iVar1 = inner_cast_rank_ok(parent->type,node->type,inner->type);
    if (iVar1 != 0) {
      iVar1 = inner_cast_kind_ok(parent->type,node->type,inner->type);
      if (iVar1 != 0) {
        replace_node(node,inner);
        free_node(node);
        node = inner;
      }
    }
  }
  return node;
}



