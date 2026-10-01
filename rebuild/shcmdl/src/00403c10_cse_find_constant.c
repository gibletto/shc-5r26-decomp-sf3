#include "decls.h"
#include "imports.h"

// entry: 00403c10
// name : cse_find_constant
// size : 80
// sig  : il_node * cse_find_constant(il_node * node)


il_node * __cdecl cse_find_constant(il_node *node)

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
  cell = g_cse_const_hash[iVar1];
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



