#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_flow_blocks
#define g_flow_blocks (*(flow_block * *)(g_sd + 0x6e08))


// entry: 00402770
// name : delete_repeated_r0_constant_loads
// size : 378
// sig  : void delete_repeated_r0_constant_loads(flow_block * block)


int __cdecl delete_repeated_r0_constant_loads(flow_block *block)

{
  unsigned char _frec_10[16];
#define block_defs (*(uint (*)[2])(_frec_10 + 0))
#define uses (*(uint (*)[2])(_frec_10 + 8))
  code_node *node;
  char equal;
  int feeds_stack;
  psd *next_rec;
  uint vol;
  psd *movi;
  int n;
  psd *rec;
  bool deleted;
  byte old_flags2;
  psd_op op;
  flow_block *other;
  
  deleted = false;
  if (block != (flow_block *)0x0) {
    movi = (psd *)0x0;
    for (node = block->code; node != (code_node *)0x0; node = node->next) {
      rec = node->psd;
      n = 0xf;
      do {
        op = rec->op;
        if (((((op != OP_LABEL) && (op != OP_DLABEL)) && (op != OP_CLABEL)) &&
            ((op != OP_DUMMY && (op != OP_LINE)))) && ((op != OP_BBGN && (op != OP_BEND)))) {
          if (movi == (psd *)0x0) {
            if ((op == OP_MOVI) && (rec->ea2->base == '\0')) {
LAB_00402879:
              movi = rec;
            }
          }
          else if ((op == OP_MOVI) && (rec->ea2->base == '\0')) {
            equal = operands_equal(rec->ea1,movi->ea1);
            if ((((equal == '\0') ||
                 (feeds_stack = is_movi_feeding_stack_add(node,rec), feeds_stack != 0)) ||
                ((rec->op == OP_MOVI &&
                 ((rec->ea1->labels == (label_ref *)0x0 &&
                  (next_rec = find_next_psd_record(node,rec), next_rec == (psd *)0x0)))))) ||
               (vol = is_record_volatile(rec), vol != 0)) goto LAB_00402879;
            delete_psd_record(rec);
            deleted = true;
          }
          else {
            compute_record_register_use_def(rec,uses,block_defs);
            if ((g_reg_mask_table[0] & block_defs[0]) != 0) {
              movi = (psd *)0x0;
            }
          }
        }
        rec = rec + 1;
        n = n + -1;
      } while (n != 0);
    }
    if (movi != (psd *)0x0) {
      if (deleted) {
        scan_flow_block_records(block,'\x01');
      }
      block->flags2 = block->flags2 | 1;
      propagate_r0_constant_to_successors(block,block,movi);
      for (other = g_flow_blocks; other != (flow_block *)0x0; other = other->next) {
        old_flags2 = other->flags2;
        other->flags2 = old_flags2 & 0xfe;
        other->flags2 = old_flags2 & 0xfc;
        other->flags2 = old_flags2 & 0xf8;
      }
    }
  }
  return;
#undef block_defs
#undef uses
}



