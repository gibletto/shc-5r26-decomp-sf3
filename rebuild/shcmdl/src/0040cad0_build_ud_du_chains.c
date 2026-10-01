#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 0040cad0
// name : build_ud_du_chains
// size : 48
// sig  : void build_ud_du_chains(void)


int __cdecl build_ud_du_chains(void)

{
  bblock *block;
  node_list *item;
  
  for (block = g_f_chain; block != (bblock *)0x0; block = block->f_next) {
    for (item = block->ilnode; item != (node_list *)0x0; item = item->next) {
      link_ud_du_chains(block,item->node);
    }
  }
  return;
}



