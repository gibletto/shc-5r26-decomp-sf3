#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_flow_blocks
#define g_flow_blocks (*(flow_block * *)(g_sd + 0x6e08))


// entry: 004015b0
// name : link_flow_block_targets_and_preds
// size : 312
// sig  : char link_flow_block_targets_and_preds(void)


char __cdecl link_flow_block_targets_and_preds(void)

{
  flow_edge *edge;
  flow_edge *new_edge;
  flow_block *block;
  psd *rec;
  int i;
  short want_labno;
  ushort case_labno;
  code_node *node;
  flow_block *other;
  
  case_labno = 0;
  block = g_flow_blocks;
  do {
    if (block == (flow_block *)0x0) {
      return '\x01';
    }
    node = block->code;
    if ((block->flags & 0x20) != 0) {
      for (; node != (code_node *)0x0; node = node->next) {
        rec = node->psd;
        i = 0;
        do {
          if (rec->op == OP_CASEJMP) {
            case_labno = rec->linno;
            break;
          }
          i = i + 1;
          rec = rec + 1;
        } while (i < 0xf);
        if (i < 0xf) break;
      }
    }
    want_labno = block->code->target_labno;
    other = g_flow_blocks;
    if ((want_labno != 0) || (case_labno != 0)) {
      for (; other != (flow_block *)0x0; other = other->next) {
        if ((case_labno != 0) && (other->code->labno == case_labno)) {
          edge = try_alloc_zeroed(8);
          if (edge == (flow_edge *)0x0) {
            return '\0';
          }
          if (other->preds != (flow_edge *)0x0) {
            edge->next = other->preds;
          }
          case_labno = 0;
          other->preds = edge;
        }
        if ((want_labno != 0) && (other->code->labno == want_labno)) {
          block->target = other;
          edge = other->preds;
          if (edge == (flow_edge *)0x0) {
            edge = try_alloc_zeroed(8);
            if (edge == (flow_edge *)0x0) {
              return '\0';
            }
            edge->block = block;
            other->preds = edge;
          }
          else {
            if (edge->next != (flow_edge *)0x0) {
              do {
                if (edge->block == block) break;
                edge = edge->next;
              } while (edge->next != (flow_edge *)0x0);
              if (edge->next != (flow_edge *)0x0) goto LAB_004016a1;
            }
            new_edge = try_alloc_zeroed(8);
            if (new_edge == (flow_edge *)0x0) {
              return '\0';
            }
            new_edge->block = block;
            edge->next = new_edge;
          }
LAB_004016a1:
          want_labno = 0;
        }
        if ((case_labno == 0) && (want_labno == 0)) break;
      }
    }
    block = next_flow_block_dropping_empty(block);
  } while( true );
}



