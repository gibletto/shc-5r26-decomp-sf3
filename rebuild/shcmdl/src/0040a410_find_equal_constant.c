#include "decls.h"
#include "imports.h"

// entry: 0040a410
// name : find_equal_constant
// size : 80
// sig  : il_node * find_equal_constant(il_node * node)


il_node * __cdecl find_equal_constant(il_node *node)

{
  uint sum;
  int iVar1;
  uint sign;
  node_cell *cell;
  
  sum = node->val2 + node->val3 + node->val;
  sign = (int)sum >> 0x1f;
  iVar1 = ((sum ^ sign) - sign & 0xf ^ sign) - sign;
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  cell = g_const_hash[iVar1];
  if (cell != (node_cell *)0x0) {
    do {
      iVar1 = constants_equal(node,cell->node);
      if (iVar1 != 0) break;
      cell = cell->next;
    } while (cell != (node_cell *)0x0);
    if (cell != (node_cell *)0x0) {
      return cell->node;
    }
  }
  return (il_node *)0x0;
}



