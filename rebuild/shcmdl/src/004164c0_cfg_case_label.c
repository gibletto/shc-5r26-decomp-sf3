#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_cur_block
#define g_cfg_cur_block (*(bblock * *)(g_sd + 0x26868))
#undef g_cfg_cur_loop
#define g_cfg_cur_loop (*(loop * *)(g_sd + 0x2684c))
#undef g_cfg_last_stmt
#define g_cfg_last_stmt (*(node_list * *)(g_sd + 0x267ec))
#undef g_cfg_pending_jumps
#define g_cfg_pending_jumps (*(block_list * *)(g_sd + 0x1e718))
#undef g_switch_block
#define g_switch_block (*(bblock * *)(g_sd + 0x1e4e8))


// entry: 004164c0
// name : cfg_case_label
// size : 109
// sig  : void cfg_case_label(il_node * stmt)


int __cdecl cfg_case_label(il_node *stmt)

{
  if (g_cfg_last_stmt != (node_list *)0x0) {
    g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,g_cfg_cur_block);
    g_cfg_last_stmt = (node_list *)0x0;
  }
  if (g_cfg_cur_loop != (loop *)0x0) {
    g_cfg_cur_loop->flag = g_cfg_cur_loop->flag | 0x800;
  }
  g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,g_switch_block);
  cfg_add_statement(stmt->child);
  return;
}



