#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 00403e90
// name : cse_replace_in_blocks
// size : 31
// sig  : void cse_replace_in_blocks(void)


int __cdecl cse_replace_in_blocks(void)

{
  bblock *block;
  
  for (block = g_f_chain->f_next; block != (bblock *)0x0; block = block->f_next) {
    cse_replace_in_block(block);
  }
  return;
}



