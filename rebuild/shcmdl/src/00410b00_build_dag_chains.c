#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 00410b00
// name : build_dag_chains
// size : 51
// sig  : void build_dag_chains(char make_du)


int __cdecl build_dag_chains(char make_du)

{
  bblock *block;
  
  g_def_count = 0;
  g_use_count = 0;
  for (block = g_f_chain; block != (bblock *)0x0; block = block->f_next) {
    build_block_dag_chain(block,make_du);
  }
  return;
}



