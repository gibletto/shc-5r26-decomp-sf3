#include "decls.h"
#include "imports.h"

// entry: 00411be0
// name : load_compare_operand_into_r0
// size : 589
// sig  : void load_compare_operand_into_r0(code_node * node)


int __cdecl load_compare_operand_into_r0(code_node *node)

{
  uchar uVar1;
  uint uVar2;
  psd *next_rec;
  psd *rec;
  psd *ppVar3;
  psd *load_rec;
  byte bVar4;
  char value_reg;
  psd *extu_rec;
  char cmp_reg;
  ea *dst_ea;
  psd_op op;
  ea **src_ea_ptr;
  
  for (load_rec = node->psd; load_rec != (psd *)0x0; load_rec = find_next_psd_record(node,load_rec))
  {
    extu_rec = (psd *)0x0;
    if (load_rec->op == OP_MOV) {
      bVar4 = load_rec->ea1->type & 0x1f;
      if ((((bVar4 != 3) && (bVar4 != 4)) && ((bVar4 == 2 || ((7 < bVar4 && (bVar4 < 0xd)))))) &&
         ((uVar1 = record_changes_operand(load_rec->ea1,load_rec), uVar1 == '\0' &&
          ((((load_rec->ea2->type & 0x1f) == 1 && ((load_rec->ea1->type & 0x80) == 0)) &&
           (uVar2 = is_record_volatile(load_rec), uVar2 == 0)))))) {
        value_reg = load_rec->ea2->base;
        bVar4 = load_rec->flg;
        next_rec = find_next_psd_record(node,load_rec);
        if (next_rec != (psd *)0x0) {
          rec = next_rec;
          if (((next_rec->op == OP_EXTU) && ((next_rec->flg & 3U) == (bVar4 & 3))) &&
             ((next_rec->ea1->base == value_reg &&
              ((value_reg == '\0' || (next_rec->ea2->base == value_reg)))))) {
            value_reg = next_rec->ea2->base;
            rec = find_next_psd_record(node,next_rec);
            extu_rec = next_rec;
          }
          if (((rec != (psd *)0x0) && (rec->op == OP_MOV)) &&
             (src_ea_ptr = &rec->ea1, ((*src_ea_ptr)->type & 0x1f) == 1)) {
            dst_ea = rec->ea2;
            if (((dst_ea->type & 0x1f) == 1) && ((*src_ea_ptr)->base == value_reg)) {
              value_reg = dst_ea->base;
              next_rec = find_next_psd_record(node,rec);
              if ((((next_rec != (psd *)0x0) &&
                   ((next_rec->op == OP_CMP_EQ || (next_rec->op == OP_TST)))) &&
                  ((next_rec->ea1->type & 0x1f) == 7)) &&
                 ((((next_rec->ea2->type & 0x1f) == 1 &&
                   (cmp_reg = next_rec->ea2->base, value_reg == cmp_reg)) && (cmp_reg == '\0')))) {
                ppVar3 = find_next_psd_record(node,next_rec);
                op = ppVar3->op;
                if (((op == OP_JUMP) || (op == OP_JUMPT)) || (op == OP_JUMPF)) {
                  if (ppVar3->tmp == (*src_ea_ptr)->base) {
                    delete_psd_record(rec);
                  }
                  else {
                    rec->ea2->base = (*src_ea_ptr)->base;
                    (*src_ea_ptr)->base = '\0';
                    ppVar3 = (psd *)alloc_zeroed_flushing_blocks(0x18);
                    copy_psd_record(rec,ppVar3);
                    copy_psd_record(next_rec,rec);
                    copy_psd_record(ppVar3,next_rec);
                  }
                  if (extu_rec == (psd *)0x0) {
                    load_rec->ea2->base = '\0';
                  }
                  else {
                    extu_rec->ea2->base = '\0';
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return;
}



