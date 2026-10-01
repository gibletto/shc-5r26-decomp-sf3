#include "decls.h"
#include "imports.h"

// entry: 0041dae0
// name : cse_hash_arith_expr
// size : 99
// sig  : void cse_hash_arith_expr(il_node * node, bblock * block)


int __cdecl cse_hash_arith_expr(il_node *node,bblock *block)

{
  uint hash;
  node_list *item;
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
  item = pool_alloc(8);
  if (item == (node_list *)0x0) {
    cse_out_of_memory();
  }
  item->node = node;
  item->next = g_expr_hash[((hash ^ sign) - sign & 0x7f ^ sign) - sign];
  g_expr_hash[((hash ^ sign) - sign & 0x7f ^ sign) - sign] = item;
  node->cse_block = block;
  return;
}



