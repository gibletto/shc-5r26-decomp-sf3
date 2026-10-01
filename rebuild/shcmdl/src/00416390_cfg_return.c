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
#undef g_return_preds
#define g_return_preds (*(block_list * *)(g_sd + 0x26ee4))


// entry: 00416390
// name : cfg_return
// size : 143
// sig  : void cfg_return(il_node * stmt)


int __cdecl cfg_return(il_node *stmt)

{
  if (stmt->child->op != IL_NULL) {
    cfg_append_statement(stmt->child);
  }
  if (g_cfg_last_stmt == (node_list *)0x0) {
    if (stmt->parent->op == IL_GLABEL) {
      cfg_start_block(1);
    }
  }
  else {
    g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,g_cfg_cur_block);
    g_cfg_last_stmt = (node_list *)0x0;
  }
  g_return_preds =
       (block_list *)append_node_list((node_list *)g_return_preds,(node_list *)g_cfg_pending_jumps);
  g_cfg_pending_jumps = (block_list *)0x0;
  if (g_cfg_cur_loop != (loop *)0x0) {
    g_cfg_cur_loop->flag = g_cfg_cur_loop->flag | 0x40;
  }
  return;
}



