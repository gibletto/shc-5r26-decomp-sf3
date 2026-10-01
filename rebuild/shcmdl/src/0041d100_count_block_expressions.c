#include "decls.h"
#include "imports.h"

// entry: 0041d100
// name : count_block_expressions
// size : 47
// sig  : void count_block_expressions(bblock * block)


int __cdecl count_block_expressions(bblock *block)

{
  node_list *item;
  
  g_in_builtin_call = '\0';
  g_memory_clobbered = 0;
  for (item = block->ilnode; item != (node_list *)0x0; item = item->next) {
    count_expression_tree(item->node,block);
  }
  return;
}



