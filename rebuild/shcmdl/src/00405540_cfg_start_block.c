#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_cur_block
#define g_cfg_cur_block (*(bblock * *)(g_sd + 0x26868))
#undef g_cfg_cur_loop
#define g_cfg_cur_loop (*(loop * *)(g_sd + 0x2684c))
#undef g_cfg_next_block
#define g_cfg_next_block (*(bblock * *)(g_sd + 0x26a70))
#undef g_cfg_pending_jumps
#define g_cfg_pending_jumps (*(block_list * *)(g_sd + 0x1e718))


// entry: 00405540
// name : cfg_start_block
// size : 107
// sig  : void cfg_start_block(int fall_through)


int __cdecl cfg_start_block(int fall_through)

{
  g_cfg_cur_block = g_cfg_next_block;
  g_cfg_next_block = new_bblock();
  g_cfg_cur_block->lptbl = g_cfg_cur_loop;
  g_cfg_cur_block->ilnode = (node_list *)0x0;
  add_edges_from_list_and_free(g_cfg_pending_jumps,g_cfg_cur_block);
  g_cfg_pending_jumps = (block_list *)0x0;
  if (fall_through != 0) {
    g_cfg_pending_jumps = new_list_cell((block_list *)0x0,g_cfg_cur_block);
  }
  return;
}



