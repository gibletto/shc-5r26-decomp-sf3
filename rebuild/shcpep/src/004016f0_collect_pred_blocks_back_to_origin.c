#include "decls.h"
#include "imports.h"

// entry: 004016f0
// name : collect_pred_blocks_back_to_origin
// size : 565
// sig  : int collect_pred_blocks_back_to_origin(flow_block * origin, flow_block * block, flow_block * * out, int max)


int __cdecl collect_pred_blocks_back_to_origin(flow_block *origin,flow_block *block,flow_block **out,int max)

{
  flow_block **slot;
  int last;
  int j;
  int i;
  flow_edge *edge;
  bool origin_found;
  byte origin_reached;
  flow_block *pred;
  flow_block *prev;
  
  last = 0;
  i = 0;
  origin_reached = 0;
  if ((((origin == (flow_block *)0x0) || (block == (flow_block *)0x0)) || (block == origin)) ||
     ((out == (flow_block **)0x0 || (max < 1)))) {
    return -1;
  }
  j = max;
  slot = out;
  if (0 < max) {
    for (; j != 0; j = j + -1) {
      *slot = (flow_block *)0x0;
      slot = slot + 1;
    }
  }
  pred = block->prev;
  if (pred == (flow_block *)0x0) {
    return -1;
  }
  if ((pred->flags & 1) == 0) {
    if (pred == origin) {
      origin_reached = 1;
      if (block->preds == (flow_edge *)0x0) {
        return 0;
      }
    }
    else {
      *out = pred;
    }
  }
  slot = out;
  for (edge = block->preds; edge != (flow_edge *)0x0; edge = edge->next) {
    pred = edge->block;
    if (pred == (flow_block *)0x0) {
      return -1;
    }
    if (pred == origin) {
      origin_reached = 1;
    }
    else if (*out == (flow_block *)0x0) {
      *out = pred;
    }
    else if (pred != *out) {
      slot = slot + 1;
      last = last + 1;
      if (max <= last) {
        return -1;
      }
      *slot = pred;
    }
  }
  if (*out == (flow_block *)0x0) {
    return origin_reached - 1;
  }
  origin_found = false;
  if (0 < max) {
    do {
      pred = out[i];
      prev = pred->prev;
      if (prev == (flow_block *)0x0) {
        return -1;
      }
      if (prev == origin) {
        if ((prev->flags & 1) == 0) {
          origin_found = true;
        }
        else {
LAB_0040184c:
          if (pred->preds == (flow_edge *)0x0) {
            return -1;
          }
        }
      }
      else {
        if ((prev->flags & 1) != 0) goto LAB_0040184c;
        j = 0;
        slot = out;
        if (-1 < last) {
          do {
            if (*slot == prev) break;
            j = j + 1;
            slot = slot + 1;
          } while (j <= last);
        }
        if (last < j) {
          last = last + 1;
          if (max <= last) {
            return -1;
          }
          out[last] = prev;
        }
      }
      for (edge = out[i]->preds; edge != (flow_edge *)0x0; edge = edge->next) {
        pred = edge->block;
        if (pred == (flow_block *)0x0) {
          return -1;
        }
        if (pred == origin) {
          origin_found = true;
        }
        else {
          j = 0;
          slot = out;
          if (-1 < last) {
            do {
              if (*slot == pred) break;
              j = j + 1;
              slot = slot + 1;
            } while (j <= last);
          }
          if (last < j) {
            last = last + 1;
            if (max <= last) {
              return -1;
            }
            out[last] = pred;
          }
        }
      }
      if (i == last) {
        if (!origin_found) {
          return -1;
        }
        return i + 1;
      }
      i = i + 1;
    } while (i < max);
  }
  return -1;
}



