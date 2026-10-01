#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 00406000
// name : opt_exp_all_blocks
// size : 37
// sig  : void opt_exp_all_blocks(void)


int __cdecl opt_exp_all_blocks(void)

{
  bblock *block;
  
  for (block = g_f_chain->f_next; block != (bblock *)0x0; block = block->f_next) {
    opt_exp_block(block);
  }
  g_opt_exp_pass = g_opt_exp_pass + 1;
  return;
}



