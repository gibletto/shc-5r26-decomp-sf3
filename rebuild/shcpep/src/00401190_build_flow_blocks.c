#include "decls.h"
#include "imports.h"
#include "pep_rules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_flow_blocks
#define g_flow_blocks (*(flow_block * *)(g_sd + 0x6e08))


// entry: 00401190
// name : build_flow_blocks
// size : 425
// sig  : char build_flow_blocks(void)


char __cdecl build_flow_blocks(void)

{
  flow_block *block;
  flow_edge *edge;
  flow_block *new_block;
  int i;
  psd *rec;
  code_node *next_code;
  code_node *node;
  psd_op op;
  
  block = try_alloc_zeroed(0x28);
  if (block == (flow_block *)0x0) {
    return '\0';
  }
  g_flow_blocks = block;
  block->code = g_current_node_list;
  if (g_current_node_list->psd[0].op == OP_FLABEL) {
    edge = try_alloc_zeroed(8);
    if (edge == (flow_edge *)0x0) {
      return '\0';
    }
    g_flow_blocks->preds = edge;
  }
  scan_flow_block_records(block,'\0');
  next_code = g_current_node_list->next_block;
  do {
    if (next_code == (code_node *)0x0) {
      return '\x01';
    }
    if ((block->code->target_labno != 0) && ((block->flags & 1) != 0)) {
      while ((next_code != (code_node *)0x0 && (node = next_code, next_code->labno == 0))) {
        PEP_GAP_NOTE(block->code->target_labno, next_code);
        for (; node != (code_node *)0x0; node = node->next) {
          i = 0;
          rec = node->psd;
          do {
            if (rec->op == OP_NON_10) break;
            i = i + 1;
            delete_psd_record(rec);
            rec = rec + 1;
          } while (i < 0xf);
          if (i < 0xf) break;
        }
        if (node != (code_node *)0x0) break;
        if (next_code->target_labno != 0 && !PEP_DEAD_REF_KEPT(next_code->target_labno)) {
          decrement_label_ref_count(next_code->target_labno);
        }
        node = next_code->next_block;
        free_node_list(next_code);
        next_code = node;
      }
      block->code->next_block = next_code;
      if (next_code == (code_node *)0x0) {
        return '\x01';
      }
    }
    new_block = try_alloc_zeroed(0x28);
    if (new_block == (flow_block *)0x0) {
      return '\0';
    }
    op = next_code->psd[0].op;
    if ((op == OP_CLABEL) || (op == OP_FLABEL)) {
      edge = try_alloc_zeroed(8);
      if (edge == (flow_edge *)0x0) {
        free_flow_block(new_block);
        return '\0';
      }
      new_block->preds = edge;
    }
    new_block->code = next_code;
    new_block->prev = block;
    scan_flow_block_records(new_block,'\0');
    block->next = new_block;
    next_code = next_code->next_block;
    block = new_block;
  } while( true );
}



