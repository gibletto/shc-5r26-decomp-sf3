#include "decls.h"
#include "imports.h"
#include "pep_rules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_flow_blocks
#define g_flow_blocks (*(flow_block * *)(g_sd + 0x6e08))


// entry: 00401000
// name : optimize_flow_graph
// size : 254
// sig  : void optimize_flow_graph(void)


int __cdecl optimize_flow_graph(void)

{
  char result;
  bool sets_r0;
  flow_block *block;
  flow_block *next;
  
  if ((g_current_node_list != (code_node *)0x0) || (g_block_flushed_early == 0)) {
    result = build_flow_blocks();
    if (result == '\0') {
      free_flow_block((flow_block *)0x0);
      return;
    }
    result = link_flow_block_targets_and_preds();
    next = g_flow_blocks;
    if (result == '\0') {
      free_flow_block((flow_block *)0x0);
      return;
    }
    while (block = next, next = g_flow_blocks, block != (flow_block *)0x0) {
      result = pep_post_skip(8) ? 0 : simplify_flow_block(block);
      next = block->next;
      if (result != '\0') {
        free_flow_block(block);
      }
    }
    for (; block = g_flow_blocks, next != (flow_block *)0x0; next = next->next) {
      scan_flow_block_records(next,'\x01');
    }
    while (block != (flow_block *)0x0) {
      if (block->preds != (flow_edge *)0x0 && !pep_post_skip(6)) {
        remove_target_prefix_executed_by_preds(block);
      }
      result = simplify_flow_block(block);
      if (result == '\0') {
        sets_r0 = false;
        if (block != (flow_block *)0xffffffe4) {
          sets_r0 = (block->defs[0] & g_reg_mask_table[0]) != 0;
        }
        if (sets_r0 && !pep_post_skip(7)) {
          delete_repeated_r0_constant_loads(block);
        }
        block = block->next;
      }
      else {
        next = block->next;
        free_flow_block(block);
        block = next;
      }
    }
    free_flow_block((flow_block *)0x0);
  }
  return;
}



