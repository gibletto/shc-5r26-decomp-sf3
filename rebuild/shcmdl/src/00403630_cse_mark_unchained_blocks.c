#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_bn_chain
#define g_bn_chain (*(bblock * *)(g_sd + 0x26ef8))


// entry: 00403630
// name : cse_mark_unchained_blocks
// size : 61
// sig  : void cse_mark_unchained_blocks(void)


int __cdecl cse_mark_unchained_blocks(void)

{
  bblock *block;
  node_list *stmt;
  
  for (block = g_bn_chain; block != (bblock *)0x0; block = block->bn_next) {
    if ((block->f_next == (bblock *)0x0) && (block->b_next == (bblock *)0x0)) {
      for (stmt = block->ilnode; stmt != (node_list *)0x0; stmt = stmt->next) {
        cse_mark_subtree_skipped(stmt->node);
      }
    }
  }
  return;
}



