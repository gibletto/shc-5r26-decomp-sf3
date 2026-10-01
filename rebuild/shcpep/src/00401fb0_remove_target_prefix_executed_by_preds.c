#include "decls.h"
#include "imports.h"
#include "pep_rules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_rec_def_mask_hi
#define g_rec_def_mask_hi (*(unsigned int *)(g_sd + 0x6d5c))
#undef g_rec_def_mask_lo
#define g_rec_def_mask_lo (*(unsigned int *)(g_sd + 0x6d58))
#undef g_rec_use_mask_hi
#define g_rec_use_mask_hi (*(unsigned int *)(g_sd + 0x5c44))
#undef g_rec_use_mask_lo
#define g_rec_use_mask_lo (*(unsigned int *)(g_sd + 0x5c40))


// entry: 00401fb0
// name : remove_target_prefix_executed_by_preds
// size : 1339
// sig  : void remove_target_prefix_executed_by_preds(flow_block * block)


int __cdecl remove_target_prefix_executed_by_preds(flow_block *block)

{
  unsigned char _frec_20[32];
#define match_in_block (*(psd * *)(_frec_20 + 0))
#define match_in_pred (*(psd * *)(_frec_20 + 4))
#define succ1 (*(flow_block * *)(_frec_20 + 8))
#define local_14 (*(psd * *)(_frec_20 + 12))
#define local_10 (*(code_node * *)(_frec_20 + 16))
#define saved_use_lo (*(uint *)(_frec_20 + 20))
#define saved_use_hi (*(uint *)(_frec_20 + 24))
#define succ2 (*(flow_block * *)(_frec_20 + 28))
  flow_block *block_00;
  flow_edge *edges;
  char result;
  char deleted;
  code_node *node;
  flow_edge *next_edge;
  psd_op op;
  flow_block *prev_block;
  
  if ((block != (flow_block *)0x0) && (node = block->code, node != (code_node *)0x0)) {
    op = node->psd[0].op;
    if (((op == OP_LABEL) || ((op == OP_DLABEL || (op == OP_CLABEL)))) &&
       (local_14 = find_next_psd_record(node,node->psd), local_14 != (psd *)0x0)) {
      succ1 = next_flow_block_dropping_empty(block);
      succ2 = next_flow_block_dropping_empty(succ1);
      edges = block->preds;
joined_r0x0040201a:
      if (edges == (flow_edge *)0x0) {
        return;
      }
      block_00 = edges->block;
      if (block_00 != (flow_block *)0x0) {
        if (block_00 == block) {
          return;
        }
        local_10 = block_00->code;
        if (local_10 == (code_node *)0x0) {
          return;
        }
        match_in_pred = (psd *)0x0;
        match_in_block = (psd *)0x0;
        if (block_00->target != block->target) {
          result = match_leading_records(node,local_14,local_10,&match_in_block);
          if (result == -1) {
            return;
          }
          if (((((result == '\x01') && (block->preds == edges)) && (edges->next == (flow_edge *)0x0)
               ) && !pep_keep_target_head((int)block_00, (unsigned char *)local_14) && ((prev_block = block->prev, prev_block != (flow_block *)0x0 &&
                     (((prev_block->flags & 1) != 0 || (block_00 == prev_block)))))) &&
             (deleted = delete_matched_target_prefix(node,local_10,&match_in_block), deleted != '\0'
             )) {
            scan_flow_block_records(block,'\x01');
            if ((local_14->op == OP_DUMMY) &&
               (local_14 = find_next_psd_record(node,local_14), local_14 == (psd *)0x0)) {
              return;
            }
          }
          else {
            if ((result != '\x02') || (pep_no_thread() & 4) ||
               (result = retarget_block_branch
                                   (block_00,match_in_pred,node->target_labno,block->target),
               result == '\0')) goto LAB_0040213b;
            next_edge = edges->next;
            edges->next = (flow_edge *)0x0;
            append_pred_edges(block->target,edges);
            increment_label_ref_count(node->target_labno);
            edges = next_edge;
          }
          goto joined_r0x0040201a;
        }
LAB_0040213b:
        if (!(pep_no_thread() & 4) && (((block_00->preds == (flow_edge *)0x0) &&
             (prev_block = block_00->prev, prev_block != (flow_block *)0x0)) &&
            ((prev_block->flags & 1) == 0)) &&
           (((block->flags & 1) == 0 && (succ1 != (flow_block *)0x0)))) {
          if (succ1->target != block_00->target) {
            match_in_pred = (psd *)0x0;
            match_in_block = (psd *)0x0;
            result = match_leading_records(node,local_14,prev_block->code,&match_in_block);
            if (result == -1) {
              return;
            }
            if ((result == '\x02') ||
               (((result == '\x01' && (match_in_block == (psd *)0x0)) &&
                (match_in_pred == (psd *)0x0)))) {
              saved_use_lo = g_rec_use_mask_lo;
              saved_use_hi = g_rec_use_mask_hi;
              match_in_pred = (psd *)0x0;
              match_in_block = (psd *)0x0;
              result = match_common_record_run
                                 (succ1->code,(psd *)0x0,block_00->code,(psd *)0x0,&match_in_block);
              if (result == '\x02') {
                if (((((g_rec_def_mask_lo & g_rec_use_mask_lo) != 0) ||
                     ((g_rec_def_mask_hi & g_rec_use_mask_hi) != 0)) ||
                    ((g_rec_def_mask_lo & saved_use_lo) != 0)) ||
                   ((g_rec_def_mask_hi & saved_use_hi) != 0)) goto LAB_004024d8;
                result = retarget_block_branch
                                   (block_00,match_in_pred,succ1->code->target_labno,succ1->target);
                if (result != '\0') {
                  next_edge = edges->next;
                  edges->next = (flow_edge *)0x0;
                  append_pred_edges(succ1->target,edges);
                  increment_label_ref_count(succ1->code->target_labno);
                  edges = next_edge;
                  goto joined_r0x0040201a;
                }
              }
            }
          }
          local_10 = (code_node *)block_00->prev;
          if ((((((flow_block *)local_10)->preds == (flow_edge *)0x0) &&
               (prev_block = ((flow_block *)local_10)->prev, prev_block != (flow_block *)0x0)) &&
              (((prev_block->flags & 1) == 0 &&
               (((succ1->flags & 1) == 0 && (succ2 != (flow_block *)0x0)))))) &&
             (block_00->target != succ2->target)) {
            match_in_pred = (psd *)0x0;
            match_in_block = (psd *)0x0;
            result = match_leading_records(node,local_14,prev_block->code,&match_in_block);
            if (result == -1) {
              return;
            }
            if ((result != '\x02') &&
               (((result != '\x01' || (match_in_block != (psd *)0x0)) ||
                (match_in_pred != (psd *)0x0)))) goto LAB_004024d8;
            saved_use_lo = g_rec_use_mask_lo;
            saved_use_hi = g_rec_use_mask_hi;
            match_in_pred = (psd *)0x0;
            match_in_block = (psd *)0x0;
            result = match_common_record_run
                               (succ1->code,(psd *)0x0,*(code_node **)&local_10->flags,(psd *)0x0,
                                &match_in_block);
            if (((result == '\x02') ||
                (((result == '\x01' && (match_in_block == (psd *)0x0)) &&
                 (match_in_pred == (psd *)0x0)))) &&
               ((((g_rec_def_mask_lo & g_rec_use_mask_lo) == 0 &&
                 ((g_rec_def_mask_hi & g_rec_use_mask_hi) == 0)) &&
                (((g_rec_def_mask_lo & saved_use_lo) == 0 &&
                 ((g_rec_def_mask_hi & saved_use_hi) == 0)))))) {
              saved_use_lo = saved_use_lo | g_rec_use_mask_lo;
              node = succ2->code;
              saved_use_hi = saved_use_hi | g_rec_use_mask_hi;
              if (node != (code_node *)0x0) {
                match_in_pred = (psd *)0x0;
                match_in_block = (psd *)0x0;
                result = match_common_record_run
                                   (node,(psd *)0x0,block_00->code,(psd *)0x0,&match_in_block);
                if (((((result == '\x02') && ((g_rec_def_mask_lo & g_rec_use_mask_lo) == 0)) &&
                     ((g_rec_def_mask_hi & g_rec_use_mask_hi) == 0)) &&
                    (((g_rec_def_mask_lo & saved_use_lo) == 0 &&
                     ((g_rec_def_mask_hi & saved_use_hi) == 0)))) &&
                   (result = retarget_block_branch
                                       (block_00,match_in_pred,node->target_labno,succ2->target),
                   result != '\0')) {
                  next_edge = edges->next;
                  edges->next = (flow_edge *)0x0;
                  append_pred_edges(succ2->target,edges);
                  increment_label_ref_count(node->target_labno);
                  node = block->code;
                  edges = next_edge;
                  goto joined_r0x0040201a;
                }
              }
            }
            node = block->code;
          }
        }
      }
LAB_004024d8:
      edges = edges->next;
      goto joined_r0x0040201a;
    }
  }
  return;
#undef match_in_block
#undef match_in_pred
#undef succ1
#undef local_14
#undef local_10
#undef saved_use_lo
#undef saved_use_hi
#undef succ2
}



