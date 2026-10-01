#include "decls.h"
#include "imports.h"

// entry: 0040a4c0
// name : add_constant_to_hash
// size : 77
// sig  : void add_constant_to_hash(il_node * node)


int __cdecl add_constant_to_hash(il_node *node)

{
  uint sum;
  int bucket;
  node_cell *cell;
  uint sign;
  
  sum = node->val2 + node->val3 + node->val;
  sign = (int)sum >> 0x1f;
  bucket = ((sum ^ sign) - sign & 0xf ^ sign) - sign;
  if (bucket < 0) {
    bucket = -bucket;
  }
  cell = pool_alloc(8);
  if (cell == (node_cell *)0x0) {
    free_def_tables_and_abort();
  }
  cell->node = node;
  cell->next = g_const_hash[bucket];
  g_const_hash[bucket] = cell;
  return;
}



