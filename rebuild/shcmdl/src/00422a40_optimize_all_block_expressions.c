#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 00422a40
// name : optimize_all_block_expressions
// size : 31
// sig  : void optimize_all_block_expressions(void)


int __cdecl optimize_all_block_expressions(void)

{
  bblock *block;
  
  for (block = g_f_chain->f_next; block != (bblock *)0x0; block = block->f_next) {
    optimize_block_expressions(block);
  }
  return;
}



