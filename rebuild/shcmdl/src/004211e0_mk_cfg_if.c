#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_cur_block
#define g_cfg_cur_block (*(bblock * *)(g_sd + 0x26868))
#undef g_cfg_last_stmt
#define g_cfg_last_stmt (*(node_list * *)(g_sd + 0x267ec))
#undef g_cfg_pending_jumps
#define g_cfg_pending_jumps (*(block_list * *)(g_sd + 0x1e718))


// entry: 004211e0
// name : mk_cfg_if
// size : 223
// sig  : void mk_cfg_if(il_node * stmt)


int __cdecl mk_cfg_if(il_node *stmt)

{
  bblock *cond_block;
  block_list *then_jumps;
  
  cfg_append_statement(stmt->child);
  cond_block = g_cfg_cur_block;
  g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,g_cfg_cur_block);
  g_cfg_last_stmt = (node_list *)0x0;
  cfg_add_statement(stmt->child->next);
  if (g_cfg_last_stmt != (node_list *)0x0) {
    g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,g_cfg_cur_block);
    g_cfg_last_stmt = (node_list *)0x0;
  }
  then_jumps = g_cfg_pending_jumps;
  g_cfg_pending_jumps = (block_list *)0x0;
  g_cfg_pending_jumps = new_list_cell((block_list *)0x0,cond_block);
  cfg_add_statement(stmt->child->next->next);
  g_cfg_pending_jumps =
       (block_list *)append_node_list((node_list *)g_cfg_pending_jumps,(node_list *)then_jumps);
  if (g_cfg_last_stmt != (node_list *)0x0) {
    g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,g_cfg_cur_block);
    g_cfg_last_stmt = (node_list *)0x0;
  }
  return;
}



