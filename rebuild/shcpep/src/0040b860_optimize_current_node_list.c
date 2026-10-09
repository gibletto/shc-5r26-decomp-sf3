#include "decls.h"
#include "imports.h"
#include "pep_rules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_last_block
#define g_last_block (*(code_node * *)(g_sd + 0x5bc4))
#undef g_node_list_word_00429c08
#define g_node_list_word_00429c08 (*(short *)(g_sd + 0x5c08))
#undef g_pushed_back_record
#define g_pushed_back_record (*(psd * *)(g_sd + 0x5bc0))
#undef g_stage_flags
#define g_stage_flags (*(unsigned int *)(g_sd + 0x6d64))
#undef g_switch_scan_block
#define g_switch_scan_block (*(code_node * *)(g_sd + 0x5c04))


// entry: 0040b860
// name : optimize_current_node_list
// size : 261
// sig  : void optimize_current_node_list(void)


int __cdecl optimize_current_node_list(void)

{
  code_node *pcVar1;
  code_node *block;
  code_node *list_head;
  
#if SHC_REBUILD_UPDATED
  pep_xj_labels_clear();
#endif
  g_section_end = 0;
  g_current_node_list = (code_node *)0x0;
  (*(unsigned short *)((char *)&g_node_list_word_00429c08 + 0)) = 0;
  g_switch_scan_block = (code_node *)0x0;
  g_after_switch_end = 0;
  g_switch_marker_depth = 0;
  g_switch_scan_single_block = 0;
  g_block_flushed_early = 0;
  g_pushed_back_record = (psd *)0x0;
  g_entry_arg_move_pending = 1;
  do {
    if (g_input_finished != 0) break;
    block = load_next_code_node_list();
    pcVar1 = block;
    list_head = block;
    if ((g_current_node_list != (code_node *)0x0) && (g_current_node_list != block)) {
      g_last_block->next_block = block;
      pcVar1 = g_last_block->next_block;
      list_head = g_current_node_list;
    }
    g_current_node_list = list_head;
    g_last_block = pcVar1;
    if ((g_stage_flags & 0x800) == 0) {
      run_node_optimization_passes(block);
    }
  } while (g_section_end == 0);
  if ((g_stage_flags & 0x800) == 0) {
#if SHC_REBUILD_UPDATED
    pep_load_scan(g_current_node_list);
    pep_dump("load", g_current_node_list);
#endif
    PEPPOST(0, rewrite_branch_targets_for_node_list());
    PEPPOST(1, clean_records_and_merge_common_code());
    PEPPOST(2, expand_tail_calls_into_epilogue_jumps());
    PEPPOST(3, delete_dead_labels_from_node_list());
    PEPPOST(4, merge_fallthrough_blocks_and_drop_unused_labels());
    for (pcVar1 = g_current_node_list; pcVar1 != (code_node *)0x0; pcVar1 = pcVar1->next_block) {
      run_node_optimization_passes(pcVar1);
    }
  }
  if ((g_stage_flags & 0x400) == 0) {
    PEPPOST(5, optimize_flow_graph());
  }
#if SHC_REBUILD_UPDATED
  pep_dump("flow", g_current_node_list);
#endif
  fill_branch_delay_slots(g_current_node_list);
#if SHC_REBUILD_UPDATED
  pep_dump("slots", g_current_node_list);
#endif
  emit_backend_record_streams();
  return;
}



