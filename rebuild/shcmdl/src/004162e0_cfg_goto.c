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


// entry: 004162e0
// name : cfg_goto
// size : 173
// sig  : void cfg_goto(il_node * stmt)


int __cdecl cfg_goto(il_node *stmt)

{
  label_rec *rec;
  block_list *list;
  
  rec = find_label_record(stmt->symx);
  if (rec == (label_rec *)0x0) {
    rec = new_label_record(stmt->symx);
  }
  if (g_cfg_last_stmt == (node_list *)0x0) {
    if (stmt->parent->op == IL_GLABEL) {
      cfg_start_block(0);
      list = new_list_cell(rec->gotos,g_cfg_cur_block);
      rec->gotos = list;
    }
  }
  else {
    list = new_list_cell(rec->gotos,g_cfg_cur_block);
    rec->gotos = list;
    g_cfg_last_stmt = (node_list *)0x0;
  }
  list = (block_list *)append_node_list((node_list *)rec->gotos,(node_list *)g_cfg_pending_jumps);
  rec->gotos = list;
  g_cfg_pending_jumps = (block_list *)0x0;
  if (g_cfg_cur_loop != (loop *)0x0) {
    g_cfg_cur_loop->flag = g_cfg_cur_loop->flag | 8;
  }
  return;
}



