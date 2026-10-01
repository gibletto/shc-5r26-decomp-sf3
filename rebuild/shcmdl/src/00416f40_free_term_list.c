#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_term_list
#define g_term_list (*(term * *)(g_sd + 0x1e4c8))


// entry: 00416f40
// name : free_term_list
// size : 52
// sig  : void free_term_list(void)


int __cdecl free_term_list(void)

{
  term *block;
  term *next;
  
  block = g_term_list;
  while (block != (term *)0x0) {
    if (block->node->op == IL_CONST) {
      free_node(block->node);
    }
    next = block->next;
    pool_free(block,0xc);
    block = next;
  }
  return;
}



