#include "decls.h"
#include "imports.h"

// entry: 00401e30
// name : append_pred_edges
// size : 86
// sig  : char append_pred_edges(flow_block * block, flow_edge * edges)


char __cdecl append_pred_edges(flow_block *block,flow_edge *edges)

{
  char appended;
  flow_edge *edge;
  flow_edge *cursor;
  flow_edge *tail;
  flow_block *pred;
  
  appended = '\0';
  if ((((block != (flow_block *)0x0) && (block->code->labno != 0)) && (edges != (flow_edge *)0x0))
     && (pred = edges->block, pred != (flow_block *)0x0)) {
    tail = block->preds;
    if (tail == (flow_edge *)0x0) {
      block->preds = edges;
      return '\x01';
    }
    if (tail->block != pred) {
      cursor = tail->next;
      if (tail->next != (flow_edge *)0x0) {
        do {
          edge = cursor;
          cursor = edge;
          if (edge->block == pred) break;
          cursor = edge->next;
          tail = edge;
        } while (cursor != (flow_edge *)0x0);
        if (cursor != (flow_edge *)0x0) {
          return '\0';
        }
      }
      appended = '\x01';
      tail->next = edges;
    }
  }
  return appended;
}



