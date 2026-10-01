#include "decls.h"
#include "imports.h"

// entry: 004111b0
// name : reuse_loaded_constants_and_copies
// size : 1119
// sig  : void reuse_loaded_constants_and_copies(code_node * node)


/* WARNING: Removing unreachable block (ram,0x00411449) */

int __cdecl reuse_loaded_constants_and_copies(code_node *node)

{
  char cVar1;
  uchar uVar2;
  uchar uVar3;
  psd *next_rec;
  int iVar4;
  psd *ppVar5;
  uint uVar6;
  ea *new_ea;
  byte kind;
  psd *rec;
  int remaining;
  uchar dst_reg;
  psd_op op;
  char *src_base_ptr;
  bool uses_r0_index;
  
  do {
    if (node == (code_node *)0x0) {
      return;
    }
    remaining = 0xf;
    rec = node->psd;
    do {
      op = rec->op;
      if ((((op == OP_MOVI) || (op == OP_NON_2C)) && ((rec->ea2->type & 0x1f) == 1)) &&
         (dst_reg = rec->ea2->base, dst_reg != '\x0f')) {
        for (next_rec = find_next_psd_record(node,rec); next_rec != (psd *)0x0;
            next_rec = find_next_psd_record(node,next_rec)) {
          op = next_rec->op;
          if (((((op == OP_MOVI) || (op == OP_NON_2C)) &&
               ((rec->op == op && (iVar4 = is_movi_feeding_stack_add(node,next_rec), iVar4 == 0))))
              && (((next_rec->op != OP_MOVI || (next_rec->ea1->labels != (label_ref *)0x0)) ||
                  (ppVar5 = find_next_psd_record(node,next_rec), ppVar5 != (psd *)0x0)))) &&
             (((uVar6 = is_record_volatile(next_rec), uVar6 == 0 &&
               ((next_rec->ea2->type & 0x1f) == 1)) &&
              (cVar1 = operands_equal(rec->ea1,next_rec->ea1), cVar1 != '\0')))) {
            if (next_rec->ea2->base == dst_reg) {
              delete_psd_record(next_rec);
            }
            else {
              op = next_rec->op;
              next_rec->op = OP_NON_B0;
              if (op != OP_NON_2C) {
                next_rec->op = OP_MOV;
              }
              next_rec->flg = '\x02';
              release_label_refs_of_record(next_rec,0);
              free_ea(next_rec->ea1);
              new_ea = copy_ea(rec->ea2);
              next_rec->ea1 = new_ea;
              uVar2 = record_changes_register(next_rec,dst_reg);
joined_r0x00411335:
              if (uVar2 != '\0') break;
            }
          }
          else {
            uVar2 = record_changes_register(next_rec,dst_reg);
            if (uVar2 != '\0') break;
            op = next_rec->op;
            if (((op == OP_JSR) || (op == OP_BSR)) ||
               ((op == OP_CALL || ((op == OP_TRAPA || (op == OP_BSRF)))))) {
              uVar2 = call_register_effect(next_rec,dst_reg,0);
              goto joined_r0x00411335;
            }
          }
        }
      }
      else if (((op == OP_MOV) || (op == OP_NON_B0)) &&
              (((rec->ea1->type & 0x1f) == 1 &&
               (((rec->ea2->type & 0x1f) == 1 && (dst_reg = rec->ea2->base, dst_reg != '\x0f'))))))
      {
        uVar2 = rec->ea1->base;
        for (next_rec = find_next_psd_record(node,rec); next_rec != (psd *)0x0;
            next_rec = find_next_psd_record(node,next_rec)) {
          if ((((next_rec->op == OP_MOV) || (next_rec->op == OP_NON_B0)) &&
              (uVar6 = is_record_volatile(next_rec), uVar6 == 0)) &&
             (((next_rec->ea1->type & 0x1f) == 1 &&
              (src_base_ptr = &next_rec->ea1->base, *src_base_ptr == uVar2)))) {
            new_ea = next_rec->ea2;
            if ((new_ea->base != dst_reg) || ((new_ea->type & 0x1f) != 1)) {
              if (uVar2 == '\0') {
                if ((next_rec->flg & 3U) == 2) {
                  kind = new_ea->type & 0x1f;
                  if ((kind == 9) || (kind == 0xb)) {
LAB_00411478:
                    uses_r0_index = true;
                  }
                  else {
                    uses_r0_index = false;
                  }
                }
                else {
                  kind = new_ea->type & 0x1f;
                  if ((((kind == 8) && (new_ea->disp != 0)) || (kind == 9)) ||
                     (uses_r0_index = false, kind == 0xb)) goto LAB_00411478;
                }
                if (!uses_r0_index) goto LAB_00411481;
              }
              else {
LAB_00411481:
                *src_base_ptr = dst_reg;
              }
              uVar3 = record_changes_register(next_rec,dst_reg);
              if (uVar3 == '\0') {
                uVar3 = record_changes_register(next_rec,uVar2);
                goto joined_r0x0041151c;
              }
              break;
            }
            delete_psd_record(next_rec);
          }
          else {
            uVar3 = record_changes_register(next_rec,dst_reg);
            if ((uVar3 != '\0') || (uVar3 = record_changes_register(next_rec,uVar2), uVar3 != '\0'))
            break;
            op = next_rec->op;
            if ((((op != OP_JSR) && (op != OP_BSR)) && (op != OP_CALL)) &&
               ((op != OP_TRAPA && (op != OP_BSRF)))) goto LAB_00411522;
            cVar1 = call_register_effect(next_rec,dst_reg,0);
            if (cVar1 != '\0') break;
            uVar3 = call_register_effect(next_rec,uVar2,0);
joined_r0x0041151c:
            if (uVar3 != '\0') break;
          }
LAB_00411522: ;
        }
      }
      else if ((op == OP_NON_B3) || ((op == OP_NON_B4 || (op == OP_NON_D2)))) {
        dst_reg = rec->ea1->base;
        for (next_rec = find_next_psd_record(node,rec); next_rec != (psd *)0x0;
            next_rec = find_next_psd_record(node,next_rec)) {
          op = next_rec->op;
          if ((((op == OP_NON_B3) || (op == OP_NON_B4)) || (op == OP_NON_D2)) &&
             (((rec->op == op && (uVar6 = is_record_volatile(next_rec), uVar6 == 0)) &&
              (next_rec->ea1->base == dst_reg)))) {
            delete_psd_record(next_rec);
          }
          else {
            uVar2 = record_changes_register(next_rec,dst_reg);
            if ((uVar2 != '\0') ||
               ((((op = next_rec->op, op == OP_JSR || (op == OP_BSR)) ||
                 ((op == OP_CALL || ((op == OP_TRAPA || (op == OP_BSRF)))))) &&
                (cVar1 = call_register_effect(next_rec,dst_reg,0), cVar1 != '\0')))) break;
          }
        }
      }
      rec = rec + 1;
      remaining = remaining + -1;
    } while (remaining != 0);
    node = node->next;
  } while( true );
}



