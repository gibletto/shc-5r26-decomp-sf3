#include "decls.h"
#include "imports.h"
#include "pep_rules.h"

// entry: 00401a10
// name : simplify_flow_block
// size : 705
// sig  : char simplify_flow_block(flow_block * block)


char __cdecl simplify_flow_block(flow_block *block)

{
  short labno;
  code_node *node;
  char result;
  flow_block *pfVar1;
  psd *branch;
  flow_edge *edge;
  char removed;
  psd *next_rec;
  flow_block *prev_prev;
  
  removed = '\0';
  if (pep_no_thread() & 2) return 0;
  if (((block == (flow_block *)0x0) || (node = block->code, node == (code_node *)0x0)) ||
     (block->prev == (flow_block *)0x0)) {
    return '\0';
  }
  if ((node->labno != 0) &&
     (pfVar1 = prev_flow_block_dropping_empty(block), pfVar1 != (flow_block *)0x0)) {
    while ((pfVar1->target == block && (edge = block->preds, edge != (flow_edge *)0x0))) {
      do {
        if (edge->block == pfVar1) break;
        edge = edge->next;
      } while (edge != (flow_edge *)0x0);
      if ((edge == (flow_edge *)0x0) || keep_jump_to_next((int *)block) ||
         (result = retarget_block_branch(block->prev,(psd *)0x0,0,(flow_block *)0x0), result == '\0'
         )) break;
      pfVar1 = prev_flow_block_dropping_empty(block);
      pool_free(edge,8);
      if (pfVar1 == (flow_block *)0x0) break;
    }
    if ((((((pfVar1 != (flow_block *)0x0) &&
           (prev_prev = pfVar1->prev, prev_prev != (flow_block *)0x0)) &&
          (prev_prev->target == block)) &&
         (((prev_prev->flags & 1) == 0 && ((pfVar1->flags & 1) != 0)))) &&
        !keep_branch_over_jump((int *)block) &&
        ((branch = find_block_final_record(pfVar1->code), branch != (psd *)0x0 &&
         ((branch = find_previous_psd_record(pfVar1->code,branch), branch == (psd *)0x0 &&
          (branch = find_block_final_record(pfVar1->prev->code), branch != (psd *)0x0)))))) &&
       (result = retarget_block_branch
                           (pfVar1->prev,branch,pfVar1->code->target_labno,pfVar1->target),
       result != '\0')) {
      if (branch->op == OP_JUMPT) {
        branch->op = OP_JUMPF;
      }
      else if (branch->op == OP_JUMPF) {
        branch->op = OP_JUMPT;
      }
      edge = pfVar1->target->preds;
      if (edge != (flow_edge *)0x0) {
        do {
          if (edge->block == pfVar1) break;
          edge = edge->next;
        } while (edge != (flow_edge *)0x0);
        if (edge != (flow_edge *)0x0) {
          edge->block = pfVar1->prev;
        }
      }
      pfVar1->target = (flow_block *)0x0;
      result = unlink_unreferenced_flow_block(pfVar1);
      if (result != '\0') {
        free_flow_block(pfVar1);
      }
    }
  }
  edge = block->preds;
  if (edge == (flow_edge *)0x0) {
    if ((block->prev->flags & 1) != 0) {
      result = unlink_unreferenced_flow_block(block);
      return result;
    }
    if ((block->flags & 0x10) != 0) {
      result = unlink_unreferenced_flow_block(block);
      return result;
    }
    if (node->labno != 0) {
      delete_psd_record(node->psd);
      node->labno = 0;
      return '\0';
    }
  }
  else {
    pfVar1 = (flow_block *)0x0;
    if (edge->block != (flow_block *)0x0) {
      next_rec = (psd *)0x0;
      if ((block->flags & 0x10) == 0) {
        next_rec = node->psd;
        if (((next_rec != (psd *)0x0) &&
            (next_rec = find_next_psd_record(node,next_rec), next_rec != (psd *)0x0)) &&
           (next_rec->op == OP_JUMP)) {
          pfVar1 = block->target;
        }
      }
      else {
        pfVar1 = block->next;
      }
      if (((pfVar1 != (flow_block *)0x0) && (labno = pfVar1->code->labno, labno != 0)) && !pep_no_thread_here((int *)block, (int *)pfVar1) &&
         ((node->labno != labno && (result = append_pred_edges(pfVar1,edge), result != '\0')))) {
        block->preds = (flow_edge *)0x0;
        for (; edge != (flow_edge *)0x0; edge = edge->next) {
          result = retarget_block_branch(edge->block,(psd *)0x0,labno,pfVar1);
          if (result != '\0') {
            increment_label_ref_count(labno);
          }
        }
        if (next_rec == (psd *)0x0) {
          removed = unlink_unreferenced_flow_block(block);
        }
        else {
          result = simplify_flow_block(pfVar1);
          if (result != '\0') {
            free_flow_block(pfVar1);
            return '\0';
          }
        }
      }
    }
  }
  return removed;
}



