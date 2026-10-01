#include "decls.h"
#include "imports.h"

// entry: 00421150
// name : new_temp_id
// size : 64
// sig  : il_node * new_temp_id(uchar type)


il_node * __cdecl new_temp_id(uchar type)

{
  short symno;
  il_node *node;
  int leafno;
  
  node = alloc_node_or_null();
  if (node == (il_node *)0x0) {
    abort_function_optimization();
  }
  node->op = IL_ID;
  g_temp_symx = g_temp_symx + -1;
  symno = g_temp_symx;
  node->symx = g_temp_symx;
  leafno = new_leaf(symno);
  node->nleaf = (short)leafno;
  node->type = type;
  return node;
}



