#include "decls.h"
#include "imports.h"

// entry: 00417700
// name : adjust_label_sptravel_for_moved_record
// size : 246
// sig  : void adjust_label_sptravel_for_moved_record(psd * rec, code_node * target_block, code_node * second_block)


int __cdecl adjust_label_sptravel_for_moved_record(psd *rec,code_node *target_block,code_node *second_block)

{
  int size;
  int delta;
  psd_op op;
  ea *opnd;
  int *sptravel_ptr;
  
  delta = 0;
  if (rec != (psd *)0x0) {
    switch(rec->op) {
    case OP_PROGRAM:
    case OP_NON_10:
    case OP_CASEJMP:
    case OP_CTBL:
    case OP_CENT:
    case OP_LINE:
    case OP_MOV_LOC:
    case OP_MOVA_LC:
      break;
    default:
      opnd = rec->ea1;
      if (((opnd != (ea *)0x0) && ((opnd->type & 0x1f) == 4)) && (opnd->base == '\x0f')) {
        delta = psd_operand_size_bytes(rec);
        delta = -delta;
      }
      opnd = rec->ea2;
      if (opnd != (ea *)0x0) {
        if (((opnd->type & 0x1f) == 3) && (opnd->base == '\x0f')) {
          size = psd_operand_size_bytes(rec);
          delta = delta + size;
        }
        if (((rec->ea2->type & 0x1f) == 4) && (rec->ea2->base == '\x0f')) {
          size = psd_operand_size_bytes(rec);
          delta = delta - size;
        }
      }
      break;
    case OP_ADD:
      if ((((rec->ea2->type & 0x1f) == 1) && (rec->ea2->base == '\x0f')) &&
         ((rec->ea1->type & 0x1f) == 7)) {
        delta = -rec->ea1->disp;
      }
    }
    if ((delta != 0) && (target_block != (code_node *)0x0)) {
      op = target_block->psd[0].op;
      if ((OP_BEND < op) && (op < OP_FLABEL)) {
        sptravel_ptr = &target_block->psd[0].sptravel;
        *sptravel_ptr = *sptravel_ptr + delta;
      }
      if ((((second_block != (code_node *)0x0) && (second_block != target_block)) &&
          (op = second_block->psd[0].op, OP_BEND < op)) && (op < OP_FLABEL)) {
        sptravel_ptr = &second_block->psd[0].sptravel;
        *sptravel_ptr = *sptravel_ptr + delta;
      }
    }
  }
  return;
}



