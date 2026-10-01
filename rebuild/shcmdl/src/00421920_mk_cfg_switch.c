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
#undef g_switch_block
#define g_switch_block (*(bblock * *)(g_sd + 0x1e4e8))


// entry: 00421920
// name : mk_cfg_switch
// size : 290
// sig  : void mk_cfg_switch(il_node * stmt)


int __cdecl mk_cfg_switch(il_node *stmt)

{
  uint saved_loop_flag;
  block_list *saved_breaks;
  undefined2 saved_has_default;
  bblock *saved_switch_block;
  
  saved_breaks = g_cfg_break_jumps;
  saved_has_default = g_switch_has_default;
  saved_switch_block = g_switch_block;
  g_switch_has_default = 0;
  g_cfg_break_jumps = (block_list *)0x0;
  if (g_cfg_cur_loop != (loop *)0x0) {
    saved_loop_flag = g_cfg_cur_loop->flag;
  }
  cfg_append_statement(stmt->child);
  g_cfg_last_stmt = (node_list *)0x0;
  g_switch_block = g_cfg_cur_block;
  cfg_add_statement(stmt->child->next);
  if (g_cfg_last_stmt != (node_list *)0x0) {
    g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,g_cfg_cur_block);
    g_cfg_last_stmt = (node_list *)0x0;
  }
  if (g_cfg_cur_loop != (loop *)0x0) {
    g_cfg_cur_loop->flag = g_cfg_cur_loop->flag & 0xfffff7ef;
    g_cfg_cur_loop->flag = g_cfg_cur_loop->flag | saved_loop_flag;
    g_cfg_cur_loop->flag = g_cfg_cur_loop->flag | 0x4000;
  }
  if (g_switch_has_default == 0) {
    g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,g_switch_block);
  }
  g_cfg_pending_jumps =
       (block_list *)
       append_node_list((node_list *)g_cfg_pending_jumps,(node_list *)g_cfg_break_jumps);
  g_switch_has_default = saved_has_default;
  g_cfg_break_jumps = saved_breaks;
  g_switch_block = saved_switch_block;
  return;
}



