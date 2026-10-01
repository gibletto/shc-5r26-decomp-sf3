#include "decls.h"
#include "imports.h"

// entry: 00411610
// name : retarget_result_to_copy_destination
// size : 583
// sig  : void retarget_result_to_copy_destination(code_node * node)


/* WARNING: Removing unreachable block (ram,0x004116af) */

int __cdecl retarget_result_to_copy_destination(code_node *node)

{
  byte kind;
  char cVar1;
  uchar copy_reg;
  uchar uVar2;
  uchar dst_reg;
  psd *start;
  psd *to;
  psd *rec;
  int remaining;
  psd_op op;
  bool uses_r0_index;
  
  do {
    if (node == (code_node *)0x0) {
      return;
    }
    remaining = 0xf;
    rec = node->psd;
    do {
      op = rec->op;
      if ((((((op == OP_MOV_LOC) || (op == OP_MOVI)) || (op == OP_MOV)) ||
           ((op == OP_NON_B0 || (op == OP_EXTS)))) || (op == OP_EXTU)) &&
         ((rec->ea2->type & 0x1f) == 1)) {
        dst_reg = rec->ea2->base;
        if ((op == OP_MOV) && (dst_reg == '\0')) {
          if ((rec->flg & 3U) == 2) {
            kind = rec->ea1->type & 0x1f;
            if ((kind == 9) || (kind == 0xb)) {
LAB_004116cc:
              uses_r0_index = true;
            }
            else {
              uses_r0_index = false;
            }
          }
          else {
            kind = rec->ea1->type & 0x1f;
            if ((((kind == 8) && (rec->ea1->disp != 0)) || (kind == 9)) || (kind == 0xb))
            goto LAB_004116cc;
            uses_r0_index = false;
          }
          if (uses_r0_index) goto LAB_00411837;
        }
        start = find_next_psd_record(node,rec);
        to = find_register_overwrite(node,start,dst_reg,'\0',(char *)0x0);
        if ((to != (psd *)0x0) && (to != start)) {
          while ((((op = start->op, op != OP_MOV && (op != OP_NON_B0)) &&
                  ((((start->flg ^ rec->flg) & 3U) != 0 ||
                   (((op != OP_EXTS || (rec->op == OP_EXTU)) &&
                    ((op != OP_EXTU || (rec->op != OP_EXTU)))))))) ||
                 ((((start->ea1->type & 0x1f) != 1 || ((start->ea2->type & 0x1f) != 1)) ||
                  (start->ea1->base != dst_reg))))) {
            cVar1 = operand_uses_register(start,dst_reg,'\x01');
            if ((((((cVar1 != '\0') ||
                   (cVar1 = operand_uses_register(start,dst_reg,'\x02'), cVar1 != '\0')) ||
                  (copy_reg = record_changes_register(start,dst_reg), copy_reg != '\0')) ||
                 ((op = start->op, op == OP_JSR || (op == OP_BSR)))) ||
                ((op == OP_CALL || ((op == OP_TRAPA || (op == OP_BSRF)))))) ||
               (start = find_next_psd_record(node,start), to == start)) goto LAB_00411837;
          }
          copy_reg = start->ea2->base;
          uVar2 = register_referenced_between(node,rec,start,copy_reg);
          if ((uVar2 == '\0') &&
             (dst_reg = register_referenced_between(node,start,to,dst_reg), dst_reg == '\0')) {
            if ((rec->op == OP_MOV) &&
               (((rec->ea1->type & 0x1f) == 1 && (rec->ea1->base == copy_reg)))) {
              delete_psd_record(rec);
            }
            else {
              rec->ea2->base = copy_reg;
            }
            delete_psd_record(start);
          }
        }
      }
LAB_00411837:
      rec = rec + 1;
      remaining = remaining + -1;
    } while (remaining != 0);
    node = node->next;
  } while( true );
}



