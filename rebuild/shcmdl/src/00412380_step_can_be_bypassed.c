#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 00412380
// name : step_can_be_bypassed
// size : 68
// sig  : int step_can_be_bypassed(node_list * def)


int __cdecl step_can_be_bypassed(node_list *def)

{
  int result;
  bblock *blk;
  dutbl *du;
  byte *flagp;
  
  result = 1;
  du = def->node->duptr;
  if (du != (dutbl *)0x0) {
    result = path_avoids_block(g_cur_loop->start,du->block->number,g_cur_loop->start->number);
    for (blk = g_f_chain; blk != (bblock *)0x0; blk = blk->f_next) {
      flagp = (byte *)((int)&blk->flag + 1);
      *flagp = *flagp & 0xfb;
    }
  }
  return result;
}



