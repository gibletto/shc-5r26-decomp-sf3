#include "decls.h"
#include "imports.h"
#include "pep_rules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))


// entry: 0040a860
// name : expand_tail_calls_into_epilogue_jumps
// size : 511
// sig  : void expand_tail_calls_into_epilogue_jumps(void)


int __cdecl expand_tail_calls_into_epilogue_jumps(void)

{
  code_node *pcVar1;
  code_node *node;
  char jumps_to_label;
  int node_count;
  psd *rec;
  psd *call;
  code_node *epi_next;
  code_node *epi_nodes;
  int i;
  code_node *block;
  psd_op op;
  
  block = g_current_node_list;
  do {
    node = block;
    if (block == (code_node *)0x0) {
      drop_pr_save_restore_if_no_calls();
      return;
    }
    for (; node != (code_node *)0x0; node = node->next) {
      i = 0;
      call = node->psd;
      do {
        if (call == (psd *)0x0) break;
        op = call->op;
        if ((((op == OP_JSR) || (op == OP_BSR)) || (op == OP_CALL)) && ((call->misc & 0x80U) != 0))
        {
          if (((0x7f < g_aux_record_table[g_current_aux_index].sp_adjust +
                       g_aux_record_table[g_current_aux_index].frame_size) && (op == OP_JSR)) &&
             (call->ea1->base == '\x01')) goto LAB_0040aa32;
          node_count = count_tail_call_epilogue_nodes();
          epi_next = (code_node *)0x0;
          for (; node_count != 0; node_count = node_count + -1) {
            epi_nodes = (code_node *)alloc_zeroed_flushing_blocks(0x178);
            epi_nodes->next = epi_next;
            epi_next = epi_nodes;
          }
          jumps_to_label = build_tail_call_epilogue_records(epi_nodes,call);
          for (pcVar1 = g_current_node_list; block != pcVar1; pcVar1 = pcVar1->next_block) {
            if (pcVar1 == (code_node *)0x0) {
              free_node_list(epi_nodes);
              return;
            }
          }
          if (jumps_to_label == '\0') {
            block->flags = block->flags | 1;
          }
          else {
            block->target_labno = call->ea1->labels->labno1;
          }
          rec = find_next_psd_record(node,call);
          if (rec == (psd *)0x0) {
            if (block->next_block != (code_node *)0x0) {
              rec = block->next_block->psd;
            }
          }
          else {
            do {
              op = rec->op;
              if (((op == OP_RETURN) || (op == OP_EXIT)) || (op == OP_JUMP)) break;
              delete_psd_record(rec);
              rec = find_next_psd_record(node,rec);
            } while (rec != (psd *)0x0);
          }
#if SHC_REBUILD_UPDATED
          pep_log_tail(rec ? rec->op : 0);
#endif
          if (((rec != (psd *)0x0) && (op = rec->op, op != OP_LABEL)) &&
             ((op == OP_RETURN || ((op == OP_EXIT || (op == OP_JUMP)))))) {
            if (jumps_to_label == '\0') {
              block->target_labno = 0;
            }
            else {
              block->flags = '\0';
            }
            if ((rec->op == OP_RETURN) || (rec->op == OP_JUMP)) {
              decrement_label_ref_count(rec->ea1->labels->labno1);
            }
            delete_psd_record(rec);
          }
          delete_psd_record(call);
          pcVar1 = node->next;
          if (pcVar1 != (code_node *)0x0) {
            pcVar1->next_block = block->next_block;
            block->next_block = pcVar1;
            node->next = (code_node *)0x0;
          }
          node->next = epi_nodes;
        }
        call = call + 1;
        i = i + 1;
      } while (i < 0xf);
    }
LAB_0040aa32:
    block = block->next_block;
  } while( true );
}



