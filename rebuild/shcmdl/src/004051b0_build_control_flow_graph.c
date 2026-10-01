#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_b_chain
#define g_b_chain (*(bblock * *)(g_sd + 0x267f8))
#undef g_bn_chain
#define g_bn_chain (*(bblock * *)(g_sd + 0x26ef8))
#undef g_cfg_break_jumps
#define g_cfg_break_jumps (*(block_list * *)(g_sd + 0x267b8))
#undef g_cfg_continue_jumps
#define g_cfg_continue_jumps (*(block_list * *)(g_sd + 0x26f0c))
#undef g_cfg_cur_block
#define g_cfg_cur_block (*(bblock * *)(g_sd + 0x26868))
#undef g_cfg_cur_loop
#define g_cfg_cur_loop (*(loop * *)(g_sd + 0x2684c))
#undef g_cfg_last_loop
#define g_cfg_last_loop (*(loop * *)(g_sd + 0x1e728))
#undef g_cfg_last_stmt
#define g_cfg_last_stmt (*(node_list * *)(g_sd + 0x267ec))
#undef g_cfg_next_block
#define g_cfg_next_block (*(bblock * *)(g_sd + 0x26a70))
#undef g_cfg_pending_jumps
#define g_cfg_pending_jumps (*(block_list * *)(g_sd + 0x1e718))
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_exit_block
#define g_exit_block (*(bblock * *)(g_sd + 0x267cc))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_loop_tree
#define g_loop_tree (*(loop * *)(g_sd + 0x267f0))
#undef g_return_preds
#define g_return_preds (*(block_list * *)(g_sd + 0x26ee4))
#undef g_switch_block
#define g_switch_block (*(bblock * *)(g_sd + 0x1e4e8))


// entry: 004051b0
// name : build_control_flow_graph
// size : 463
// sig  : void build_control_flow_graph(il_node * body)


int __cdecl build_control_flow_graph(il_node *body)

{
  label_rec **bucket;
  label_rec *lab;
  label_rec *next_label;
  
  g_switch_has_default = 0;
  g_loop_count = 0;
  g_has_goto = '\0';
  g_last_loop_number = 0;
  g_block_count = 0;
  g_cfg_last_stmt = (node_list *)0x0;
  g_b_chain = (bblock *)0x0;
  g_f_chain = (bblock *)0x0;
  g_cfg_cur_block = (bblock *)0x0;
  g_cfg_next_block = (bblock *)0x0;
  g_bn_chain = (bblock *)0x0;
  g_loop_tree = (loop *)0x0;
  g_cfg_last_loop = (loop *)0x0;
  g_cfg_cur_loop = (loop *)0x0;
  g_return_preds = (block_list *)0x0;
  g_cfg_break_jumps = (block_list *)0x0;
  g_cfg_continue_jumps = (block_list *)0x0;
  g_cfg_pending_jumps = (block_list *)0x0;
  g_switch_block = (bblock *)0x0;
  g_cfg_next_block = new_bblock();
  g_bn_chain = g_cfg_next_block;
  cfg_start_block(1);
  cfg_add_statement(body);
  g_cfg_next_block->ilnode = (node_list *)0x0;
  if (g_cfg_last_stmt != (node_list *)0x0) {
    g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,g_cfg_cur_block);
    g_cfg_last_stmt = (node_list *)0x0;
  }
  add_edges_from_list_and_free(g_cfg_pending_jumps,g_cfg_next_block);
  bucket = g_label_hash;
  add_edges_from_list_and_free(g_return_preds,g_cfg_next_block);
  g_exit_block = g_cfg_next_block;
  do {
    lab = *bucket;
    while (lab != (label_rec *)0x0) {
      next_label = lab->next;
      add_edges_from_list_and_free(lab->gotos,lab->block);
      pool_free(lab,0x10);
      lab = next_label;
    }
    *bucket = (label_rec *)0x0;
    bucket = bucket + 1;
  } while (bucket < &DAT_00458ee0);
  g_return_preds = (block_list *)0x0;
  g_cfg_break_jumps = (block_list *)0x0;
  g_cfg_continue_jumps = (block_list *)0x0;
  g_cfg_pending_jumps = (block_list *)0x0;
  link_blocks_reverse_postorder(g_bn_chain);
  compute_dominators();
  g_loop_tree = prune_loops(g_loop_tree);
  number_loops(g_loop_tree,0);
  if (((*(unsigned char *)((char *)&g_debug_flags + 1)) & 8) != 0) {
    dump_tree(body,0,s_mk_cfg_after_00433650);
    dump_cfg_blocks();
    FID_conflict__wprintf(s_______loop_tbl_______00433638);
    dump_loop_table(g_loop_tree);
  }
  return;
}



