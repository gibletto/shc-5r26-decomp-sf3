#include "decls.h"
#include "imports.h"

// entry: 0041d920
// name : cse_hash_constant
// size : 77
// sig  : void cse_hash_constant(il_node * node)


int __cdecl cse_hash_constant(il_node *node)

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
    cse_out_of_memory();
  }
  cell->node = node;
  cell->next = g_const_hash[bucket];
  g_const_hash[bucket] = cell;
  return;
}



