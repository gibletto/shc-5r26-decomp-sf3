#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_b_chain
#define g_b_chain (*(bblock * *)(g_sd + 0x267f8))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 00405150
// name : link_blocks_reverse_postorder
// size : 92
// sig  : void link_blocks_reverse_postorder(bblock * block)


int __cdecl link_blocks_reverse_postorder(bblock *block)

{
  block_list *succ;
  
  if ((block->flag & 1) == 0) {
    block->flag = 1;
    for (succ = block->suclst; succ != (block_list *)0x0; succ = succ->next) {
      link_blocks_reverse_postorder(succ->block);
    }
    block->f_next = g_f_chain;
    if (g_f_chain != (bblock *)0x0) {
      g_f_chain->b_next = block;
      g_f_chain = block;
      return;
    }
    g_b_chain = block;
    g_f_chain = block;
  }
  return;
}



