#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cse_variables
#define g_cse_variables (*(node_list * *)(g_sd + 0x267a4))


// entry: 0041d970
// name : cse_record_variable
// size : 52
// sig  : void cse_record_variable(il_node * node, bblock * block)


int __cdecl cse_record_variable(il_node *node,bblock *block)

{
  node_list *item;
  
  item = pool_alloc(8);
  if (item == (node_list *)0x0) {
    cse_out_of_memory();
  }
  node->cse_block = block;
  item->node = node;
  item->next = g_cse_variables;
  g_cse_variables = item;
  return;
}



