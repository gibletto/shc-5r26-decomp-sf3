#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_memory_refs
#define g_memory_refs (*(node_list * *)(g_sd + 0x1e780))


// entry: 0040a7e0
// name : add_memory_reference
// size : 45
// sig  : void add_memory_reference(il_node * node)


int __cdecl add_memory_reference(il_node *node)

{
  node_list *cell;
  
  cell = pool_alloc(8);
  if (cell == (node_list *)0x0) {
    free_def_tables_and_abort();
  }
  cell->node = node;
  cell->next = g_memory_refs;
  g_memory_refs = cell;
  return;
}



