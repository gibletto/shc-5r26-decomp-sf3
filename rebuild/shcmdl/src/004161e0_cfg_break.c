#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_break_jumps
#define g_cfg_break_jumps (*(block_list * *)(g_sd + 0x267b8))
#undef g_cfg_cur_block
#define g_cfg_cur_block (*(bblock * *)(g_sd + 0x26868))
#undef g_cfg_cur_loop
#define g_cfg_cur_loop (*(loop * *)(g_sd + 0x2684c))
#undef g_cfg_last_stmt
#define g_cfg_last_stmt (*(node_list * *)(g_sd + 0x267ec))
#undef g_cfg_pending_jumps
#define g_cfg_pending_jumps (*(block_list * *)(g_sd + 0x1e718))


// entry: 004161e0
// name : cfg_break
// size : 124
// sig  : void cfg_break(il_node * stmt)


int __cdecl cfg_break(il_node *stmt)

{
  if (g_cfg_last_stmt == (node_list *)0x0) {
    if (stmt->parent->op != IL_GLABEL) goto LAB_00416225;
    cfg_start_block(0);
  }
  else {
    g_cfg_last_stmt = (node_list *)0x0;
  }
  g_cfg_break_jumps = new_list_cell(g_cfg_break_jumps,g_cfg_cur_block);
LAB_00416225:
  g_cfg_break_jumps =
       (block_list *)
       append_node_list((node_list *)g_cfg_break_jumps,(node_list *)g_cfg_pending_jumps);
  g_cfg_pending_jumps = (block_list *)0x0;
  if (g_cfg_cur_loop != (loop *)0x0) {
    g_cfg_cur_loop->flag = g_cfg_cur_loop->flag | 0x10;
  }
  return;
}



