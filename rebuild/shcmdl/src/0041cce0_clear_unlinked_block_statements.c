#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_bn_chain
#define g_bn_chain (*(bblock * *)(g_sd + 0x26ef8))


// entry: 0041cce0
// name : clear_unlinked_block_statements
// size : 61
// sig  : void clear_unlinked_block_statements(void)


int __cdecl clear_unlinked_block_statements(void)

{
  bblock *blk;
  node_list *item;
  
  for (blk = g_bn_chain; blk != (bblock *)0x0; blk = blk->bn_next) {
    if ((blk->f_next == (bblock *)0x0) && (blk->b_next == (bblock *)0x0)) {
      for (item = blk->ilnode; item != (node_list *)0x0; item = item->next) {
        replace_statement_with_zero(item->node);
      }
    }
  }
  return;
}



