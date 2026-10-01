#include "decls.h"
#include "imports.h"

// entry: 00401340
// name : scan_flow_block_records
// size : 436
// sig  : void scan_flow_block_records(flow_block * block, char compute_regs)


int __cdecl scan_flow_block_records(flow_block *block,char compute_regs)

{
  unsigned char _frec_10[16];
#define use_lo (*(uint *)(_frec_10 + 0))
#define use_hi (*(uint *)(_frec_10 + 4))
#define def_lo (*(uint *)(_frec_10 + 8))
#define def_hi (*(uint *)(_frec_10 + 12))
  bool bVar1;
  uint live_hi;
  uint uVar2;
  int n;
  uint uVar3;
  psd *rec;
  uint defs_hi;
  code_node *node;
  psd_op op;
  ea *src;
  
  bVar1 = false;
  if (block != (flow_block *)0x0) {
    if (compute_regs != '\0') {
      if (block != (flow_block *)0xffffffec) {
        block->live_in[0] = 0;
        block->live_in[1] = 0;
      }
      if (block != (flow_block *)0xffffffe4) {
        block->defs[0] = 0;
        block->defs[1] = 0;
      }
    }
    for (node = block->code; node != (code_node *)0x0; node = node->next) {
      n = 0xf;
      rec = node->psd;
      do {
        if ((((rec->op == OP_ADD) && (src = rec->ea1, (src->type & 0x1f) == 7)) &&
            (src->labels == (label_ref *)0x0)) && (src->disp == 0)) {
          delete_psd_record(rec);
        }
        op = rec->op;
        if (((op != OP_DUMMY) && (op != OP_LINE)) && ((op != OP_BBGN && (op != OP_BEND)))) {
          if (compute_regs != '\0') {
            compute_record_register_use_def(rec,&use_lo,&def_lo);
            uVar2 = block->defs[0];
            defs_hi = block->defs[1];
            block->live_in[0] = block->live_in[0] | ~uVar2 & use_lo;
            live_hi = ~defs_hi & use_hi | block->live_in[1];
            block->live_in[1] = live_hi;
            if ((use_hi & 1) != 0) {
              uVar3 = 0;
              if (block != (flow_block *)0xffffffe4) {
                uVar3 = defs_hi & 1;
              }
              if (uVar3 != 0) {
                bVar1 = true;
              }
            }
            block->defs[0] = uVar2 | def_lo;
            block->defs[1] = defs_hi | def_hi;
            if ((((def_hi & 1) != 0) && (bVar1)) && (block != (flow_block *)0xffffffec)) {
              block->live_in[1] = live_hi | 1;
            }
          }
          if (((((block->flags & 0x10) != 0) && (op = rec->op, op != OP_LABEL)) && (op != OP_DLABEL)
              ) && (op != OP_CLABEL)) {
            block->flags = block->flags & 0xef;
          }
          uVar2 = is_record_volatile(rec);
          if (uVar2 != 0) {
            block->flags = block->flags | 0x40;
          }
          switch(rec->op) {
          case OP_NON_10:
            block->flags = block->flags | 8;
            break;
          case OP_CASEJMP:
            block->flags = block->flags | 0x20;
            break;
          case OP_LABEL:
          case OP_CLABEL:
          case OP_DLABEL:
          case OP_FLABEL:
            block->flags = block->flags | 0x10;
            break;
          case OP_EXIT:
            block->flags = block->flags | 2;
          case OP_RETURN:
          case OP_JUMP:
          case OP_BRA:
          case OP_JMP:
            block->flags = block->flags | 1;
            break;
          case OP_CALL:
            block->flags = block->flags | 4;
          }
        }
        rec = rec + 1;
        n = n + -1;
      } while (n != 0);
    }
  }
  return;
#undef use_lo
#undef use_hi
#undef def_lo
#undef def_hi
}



