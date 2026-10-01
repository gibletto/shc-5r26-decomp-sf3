#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_bn_chain
#define g_bn_chain (*(bblock * *)(g_sd + 0x26ef8))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 004058a0
// name : free_all_bblocks
// size : 121
// sig  : void free_all_bblocks(void)


int __cdecl free_all_bblocks(void)

{
  bblock *block;
  bblock *next_block;
  
  block = g_bn_chain;
  if ((g_debug_flags & 0x1000) != 0) {
    FID_conflict__wprintf(s_bbnd_free_00433668);
    block = g_bn_chain;
  }
  while (block != (bblock *)0x0) {
    next_block = block->bn_next;
    if ((g_debug_flags & 0x1000) != 0) {
      FID_conflict__wprintf(s_No__d__00433660,(int)block->number);
    }
    free_bblock(block);
    block = next_block;
  }
  if ((g_debug_flags & 0x1000) != 0) {
    FID_conflict__wprintf(&g_str_newline);
  }
  g_bn_chain = (bblock *)0x0;
  g_f_chain = (bblock *)0x0;
  return;
}



