#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_cur_block
#define g_cfg_cur_block (*(bblock * *)(g_sd + 0x26868))
#undef g_cfg_cur_loop
#define g_cfg_cur_loop (*(loop * *)(g_sd + 0x2684c))
#undef g_cfg_last_stmt
#define g_cfg_last_stmt (*(node_list * *)(g_sd + 0x267ec))
#undef g_cfg_next_block
#define g_cfg_next_block (*(bblock * *)(g_sd + 0x26a70))
#undef g_cfg_pending_jumps
#define g_cfg_pending_jumps (*(block_list * *)(g_sd + 0x1e718))


// entry: 004054b0
// name : cfg_append_statement
// size : 139
// sig  : void cfg_append_statement(il_node * stmt)


int __cdecl cfg_append_statement(il_node *stmt)

{
  node_list *cell;
  
  cell = pool_alloc(8);
  if (cell == (node_list *)0x0) {
    cfg_out_of_memory();
  }
  if (g_cfg_last_stmt == (node_list *)0x0) {
    g_cfg_cur_block = g_cfg_next_block;
    g_cfg_next_block = new_bblock();
    g_cfg_cur_block->lptbl = g_cfg_cur_loop;
    g_cfg_cur_block->ilnode = cell;
    add_edges_from_list_and_free(g_cfg_pending_jumps,g_cfg_cur_block);
    g_cfg_pending_jumps = (block_list *)0x0;
  }
  else {
    g_cfg_last_stmt->next = cell;
  }
  g_cfg_last_stmt = cell;
  cell->node = stmt;
  g_cfg_cur_block->tcount = g_cfg_cur_block->tcount + 1;
  return;
}



