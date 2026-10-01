#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_defined_leaves
#define g_defined_leaves (*(int * *)(g_sd + 0x267a8))


// entry: 0040a510
// name : record_defined_leaf
// size : 50
// sig  : void record_defined_leaf(il_node * node)


int __cdecl record_defined_leaf(il_node *node)

{
  undefined4 *cell;
  
  cell = pool_alloc(8);
  if (cell == (undefined4 *)0x0) {
    free_def_tables_and_abort();
  }
  *(short *)(cell + 1) = node->nleaf;
  *cell = g_defined_leaves;
  g_defined_leaves = cell;
  return;
}



