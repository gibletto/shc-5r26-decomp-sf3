#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_bn_chain
#define g_bn_chain (*(bblock * *)(g_sd + 0x26ef8))


// entry: 00409ac0
// name : mark_referenced_functions
// size : 47
// sig  : void mark_referenced_functions(void)


int __cdecl mark_referenced_functions(void)

{
  bblock *block;
  node_list *stmt;
  
  for (block = g_bn_chain; block != (bblock *)0x0; block = block->bn_next) {
    for (stmt = block->ilnode; stmt != (node_list *)0x0; stmt = stmt->next) {
      mark_referenced_functions_in_tree(stmt->node);
    }
  }
  return;
}



