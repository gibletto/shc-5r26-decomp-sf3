#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_memory_refs
#define g_memory_refs (*(node_list * *)(g_sd + 0x1e780))


// entry: 00410d00
// name : free_dag_node_list
// size : 42
// sig  : void free_dag_node_list(void)


int __cdecl free_dag_node_list(void)

{
  node_list *item;
  node_list *next;
  
  item = g_memory_refs;
  while (item != (node_list *)0x0) {
    next = item->next;
    pool_free(item,8);
    item = next;
  }
  g_memory_refs = (node_list *)0x0;
  return;
}



