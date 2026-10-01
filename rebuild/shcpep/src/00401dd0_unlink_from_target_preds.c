#include "decls.h"
#include "imports.h"

// entry: 00401dd0
// name : unlink_from_target_preds
// size : 84
// sig  : char unlink_from_target_preds(flow_block * block)


char __cdecl unlink_from_target_preds(flow_block *block)

{
  char removed;
  flow_edge *edge;
  flow_edge *next_edge;
  flow_edge *prev_edge;
  flow_block *target;
  
  removed = '\0';
  if ((((block != (flow_block *)0x0) && (target = block->target, target != (flow_block *)0x0)) &&
      (block->code->target_labno != 0)) &&
     (prev_edge = target->preds, prev_edge != (flow_edge *)0x0)) {
    if (prev_edge->block == block) {
      target->preds = prev_edge->next;
      return '\x01';
    }
    next_edge = prev_edge->next;
    while ((next_edge != (flow_edge *)0x0 && (edge = prev_edge->next, edge->block != block))) {
      next_edge = edge->next;
      prev_edge = edge;
    }
    if (prev_edge->next != (flow_edge *)0x0) {
      prev_edge->next = prev_edge->next->next;
      removed = '\x01';
    }
  }
  return removed;
}



