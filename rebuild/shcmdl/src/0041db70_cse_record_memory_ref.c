#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_memory_refs
#define g_memory_refs (*(node_list * *)(g_sd + 0x1e780))


// entry: 0041db70
// name : cse_record_memory_ref
// size : 51
// sig  : void cse_record_memory_ref(il_node * node, bblock * block)


int __cdecl cse_record_memory_ref(il_node *node,bblock *block)

{
  node_list *item;
  
  item = pool_alloc(8);
  if (item == (node_list *)0x0) {
    cse_out_of_memory();
  }
  item->node = node;
  item->next = g_memory_refs;
  g_memory_refs = item;
  node->cse_block = block;
  return;
}



