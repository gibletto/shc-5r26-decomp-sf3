#include "decls.h"
#include "imports.h"

// entry: 004100e0
// name : postfix_to_prefix_incdec
// size : 26
// sig  : il_node * postfix_to_prefix_incdec(il_node * node)


il_node * __cdecl postfix_to_prefix_incdec(il_node *node)

{
  if ((node->flag & 0x20) == 0) {
    node->op = IL_PRD - (node->op == IL_POI);
  }
  return node;
}



