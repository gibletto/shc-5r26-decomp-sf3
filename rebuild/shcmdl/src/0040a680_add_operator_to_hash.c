#include "decls.h"
#include "imports.h"

// entry: 0040a680
// name : add_operator_to_hash
// size : 92
// sig  : void add_operator_to_hash(il_node * node)


int __cdecl add_operator_to_hash(il_node *node)

{
  uint hash;
  node_list *cell;
  int rhs_vn;
  uint sign;
  il_node *rhs;
  
  rhs_vn = 0;
  rhs = node->child->next;
  if (rhs != (il_node *)0x0) {
    rhs_vn = (int)(short)rhs->pp;
  }
  hash = (int)(short)node->child->pp + (int)(char)node->op + rhs_vn;
  sign = (int)hash >> 0x1f;
  cell = pool_alloc(8);
  if (cell == (node_list *)0x0) {
    free_def_tables_and_abort();
  }
  cell->node = node;
  cell->next = g_expr_hash[((hash ^ sign) - sign & 0x7f ^ sign) - sign];
  g_expr_hash[((hash ^ sign) - sign & 0x7f ^ sign) - sign] = cell;
  return;
}



