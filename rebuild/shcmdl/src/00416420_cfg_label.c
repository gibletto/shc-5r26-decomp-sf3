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


// entry: 00416420
// name : cfg_label
// size : 154
// sig  : void cfg_label(il_node * stmt)


int __cdecl cfg_label(il_node *stmt)

{
  label_rec *rec;
  bblock *old_block;
  
  rec = find_label_record(stmt->symx);
  if (rec == (label_rec *)0x0) {
    rec = new_label_record(stmt->symx);
  }
  rec->block = g_cfg_next_block;
  if (g_cfg_last_stmt != (node_list *)0x0) {
    g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,g_cfg_cur_block);
    g_cfg_last_stmt = (node_list *)0x0;
  }
  if (g_cfg_cur_loop != (loop *)0x0) {
    g_cfg_cur_loop->flag = g_cfg_cur_loop->flag | 4;
  }
  old_block = g_cfg_cur_block;
  if (-1 < stmt->symx) {
    cfg_add_statement(stmt->child);
  }
  if (old_block == g_cfg_cur_block) {
    cfg_start_block(1);
  }
  return;
}



