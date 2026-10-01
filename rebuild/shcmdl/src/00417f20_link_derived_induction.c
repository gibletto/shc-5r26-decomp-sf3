#include "decls.h"
#include "imports.h"

// entry: 00417f20
// name : link_derived_induction
// size : 64
// sig  : void link_derived_induction(il_node * node, il_node * operand, il_node * copy, il_node * copy_operand)


int __cdecl link_derived_induction(il_node *node,il_node *operand,il_node *copy,il_node *copy_operand)

{
  short ivno;
  
  ivno = operand->ivno;
  node->ivno = ivno;
  (g_iv_table[ivno].uses)->expr = node;
  copy->ivno = copy_operand->ivno;
  (g_iv_table[node->ivno].uses)->copy = copy;
  return;
}



