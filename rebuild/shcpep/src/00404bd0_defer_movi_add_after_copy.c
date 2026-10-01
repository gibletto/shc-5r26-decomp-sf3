#include "decls.h"
#include "imports.h"

// entry: 00404bd0
// name : defer_movi_add_after_copy
// size : 1796
// sig  : void defer_movi_add_after_copy(code_node * node, psd * copy, int index)


int __cdecl defer_movi_add_after_copy(code_node *node,psd *copy,int index)

{
  unsigned char _frec_58[88];
#define overwrite (*(psd * *)(_frec_58 + 0))
#define dst_use (*(psd * *)(_frec_58 + 4))
#define add_reg_use (*(psd * *)(_frec_58 + 8))
#define src_use (*(psd * *)(_frec_58 + 12))
#define hole_index (*(int *)(_frec_58 + 20))
#define call_mode (*(int *)(_frec_58 + 28))
#define src_change (*(psd * *)(_frec_58 + 32))
#define saved_movi (*(psd *)(_frec_58 + 40))
#define saved_add (*(psd *)(_frec_58 + 64))
  psd *ppVar1;
  psd *ppVar2;
  psd *ppVar3;
  byte src_kind;
  char ok;
  uchar changed;
  uchar uVar4;
  psd *hole;
  psd *ppVar5;
  psd *scan;
  code_node *cur_node;
  byte dst_kind;
  int pos;
  undefined4 *src_word;
  bool copy_done;
  uchar dst_reg;
  undefined4 init_word;
  bool needs_r0;
  psd_op op;
  ea *operand;
  uchar src_reg;
  
  src_change = (psd *)0x0;
  dst_use = (psd *)0x0;
  add_reg_use = (psd *)0x0;
  src_use = (psd *)0x0;
  copy_done = false;
  call_mode = 0;
  src_word = &g_empty_psd;
  hole = &saved_movi;
  for (pos = 6; pos != 0; pos = pos + -1) {
    init_word = *src_word;
    hole->op = (char)init_word;
    hole->flg = (char)((uint)init_word >> 8);
    hole->misc = (char)((uint)init_word >> 0x10);
    hole->tmp = (char)((uint)init_word >> 0x18);
    src_word = src_word + 1;
    hole = (psd *)&hole->sptravel;
  }
  src_word = &g_empty_psd;
  hole = &saved_add;
  for (pos = 6; pos != 0; pos = pos + -1) {
    init_word = *src_word;
    hole->op = (char)init_word;
    hole->flg = (char)((uint)init_word >> 8);
    hole->misc = (char)((uint)init_word >> 0x10);
    hole->tmp = (char)((uint)init_word >> 0x18);
    src_word = src_word + 1;
    hole = (psd *)&hole->sptravel;
  }
  dst_reg = copy->ea2->base;
  src_reg = copy->ea1->base;
  hole = find_next_psd_record(node,copy);
  ppVar5 = find_next_psd_record(node,hole);
  if ((ppVar5 != (psd *)0x0) &&
     (((ppVar5->op == OP_ADD || (ppVar5->op == OP_SUB)) && ((ppVar5->misc & 0x20U) != 0)))) {
    uVar4 = ppVar5->ea1->base;
    copy_psd_record(hole,&saved_movi);
    copy_psd_record(ppVar5,&saved_add);
    pos = index + 3;
    hole_index = index + 1;
    if (((copy->misc & 0x10U) != 0) && ((ppVar5->misc & 0x10U) == 0)) {
      call_mode = 1;
    }
    scan = find_next_psd_record(node,ppVar5);
    overwrite = find_register_overwrite(node,scan,dst_reg,(char)call_mode,(char *)0x0);
    if (overwrite != (psd *)0x0) {
      ppVar1 = add_reg_use;
      ppVar2 = src_use;
      ppVar3 = src_change;
      if (scan != (psd *)0x0) {
        do {
          if (dst_reg == '\0') {
            op = scan->op;
            if (((op == OP_CMP_EQ) || (op == OP_TST)) && ((scan->ea1->type & 0x1f) == 7)) {
              return;
            }
            if (op == OP_MOV) {
              if ((scan->flg & 3U) == 2) {
                src_kind = scan->ea1->type & 0x1f;
                if (((src_kind == 9) || (dst_kind = scan->ea2->type & 0x1f, dst_kind == 9)) ||
                   ((src_kind == 0xb || (dst_kind == 0xb)))) goto LAB_00404d8f;
                needs_r0 = false;
              }
              else {
                src_kind = scan->ea1->type & 0x1f;
                if ((src_kind != 8) || (scan->ea1->disp == 0)) {
                  dst_kind = scan->ea2->type & 0x1f;
                  if ((((dst_kind != 8) || (scan->ea2->disp == 0)) &&
                      (((src_kind != 9 && (dst_kind != 9)) && (src_kind != 0xb)))) &&
                     (needs_r0 = false, dst_kind != 0xb)) goto LAB_00404d94;
                }
LAB_00404d8f:
                needs_r0 = true;
              }
LAB_00404d94:
              if (needs_r0) {
                return;
              }
            }
            if ((scan->ea1 != (ea *)0x0) && ((scan->ea1->type & 0x1f) == 0xc)) {
              return;
            }
            if ((scan->ea2 != (ea *)0x0) && ((scan->ea2->type & 0x1f) == 0xc)) {
              return;
            }
          }
          op = scan->op;
          if ((((op == OP_CALL) || (op == OP_JSR)) || (op == OP_BSR)) ||
             ((op == OP_TRAPA || (op == OP_BSRF)))) {
            ok = call_register_effect(scan,uVar4,call_mode);
            if (ok == -1) {
              return;
            }
            if (ok != '\x01') goto LAB_00404dfc;
            if (dst_use == scan) {
              return;
            }
            ppVar1 = add_reg_use;
            ppVar2 = src_use;
            ppVar3 = src_change;
            if (overwrite != scan) {
              uVar4 = register_referenced_between(node,scan,overwrite,dst_reg);
joined_r0x00404f4f:
              overwrite = scan;
              ppVar1 = add_reg_use;
              ppVar2 = src_use;
              ppVar3 = src_change;
              if (uVar4 != '\0') {
                return;
              }
            }
            break;
          }
LAB_00404dfc:
          if (scan->ea1 != (ea *)0x0) {
            ok = operand_uses_register(scan,dst_reg,'\x01');
            if (ok != '\0') {
              dst_use = scan;
            }
            ok = operand_uses_register(scan,uVar4,'\x01');
            ppVar1 = scan;
            ppVar2 = src_use;
            ppVar3 = src_change;
            if ((ok != '\0') ||
               (ok = operand_uses_register(scan,src_reg,'\x01'), ppVar1 = add_reg_use, ppVar2 = scan
               , ok != '\0')) break;
          }
          if (scan->ea2 != (ea *)0x0) {
            ok = operand_uses_register(scan,dst_reg,'\x02');
            if (ok != '\0') {
              dst_use = scan;
            }
            ok = operand_uses_register(scan,uVar4,'\x02');
            ppVar1 = scan;
            ppVar2 = src_use;
            ppVar3 = src_change;
            if ((ok != '\0') ||
               (ok = operand_uses_register(scan,src_reg,'\x02'), ppVar1 = add_reg_use, ppVar2 = scan
               , ok != '\0')) break;
          }
          changed = record_changes_register(scan,uVar4);
          if ((changed != '\0') || (ok = call_register_effect(scan,uVar4,0), ok != '\0')) {
            if (dst_use == scan) {
              return;
            }
            ppVar1 = add_reg_use;
            ppVar2 = src_use;
            ppVar3 = src_change;
            if (overwrite != scan) {
              uVar4 = register_referenced_between(node,scan,overwrite,dst_reg);
              goto joined_r0x00404f4f;
            }
            break;
          }
          changed = record_changes_register(scan,src_reg);
          ppVar1 = add_reg_use;
          ppVar2 = src_use;
          ppVar3 = scan;
          if ((((changed != '\0') || (ok = call_register_effect(scan,src_reg,0), ok != '\0')) ||
              (ppVar3 = src_change, overwrite == scan)) ||
             (scan = find_next_psd_record(node,scan), scan == (psd *)0x0)) break;
        } while( true );
      }
      src_change = ppVar3;
      src_use = ppVar2;
      add_reg_use = ppVar1;
      if ((((src_use == (psd *)0x0) ||
           ((dst_use != (psd *)0x0 && ((src_use == (psd *)0x0 || (src_use != dst_use)))))) &&
          (src_change == (psd *)0x0)) &&
         (((add_reg_use == (psd *)0x0 ||
           ((dst_use != (psd *)0x0 && ((add_reg_use == (psd *)0x0 || (add_reg_use != dst_use))))))
          && ((overwrite != (psd *)0x0 &&
              ((((dst_use != (psd *)0x0 && ((add_reg_use == (psd *)0x0 || (dst_use != (psd *)0x0))))
                && ((src_use == (psd *)0x0 ||
                    ((src_use == overwrite ||
                     (uVar4 = register_referenced_between(node,src_use,overwrite,dst_reg),
                     uVar4 == '\0')))))) &&
               ((add_reg_use == (psd *)0x0 ||
                ((add_reg_use == overwrite ||
                 (uVar4 = register_referenced_between(node,add_reg_use,overwrite,dst_reg),
                 uVar4 == '\0')))))))))))) {
        if (dst_use != (psd *)0x0) {
          if ((((overwrite != (psd *)0x0) && (dst_use == overwrite)) && (overwrite->op != OP_EXTS))
             && ((overwrite->op != OP_EXTU &&
                 (scan = psd_overwrites_register(overwrite,dst_reg), scan == (psd *)0x0)))) {
            return;
          }
          ppVar5 = ppVar5 + 1;
          cur_node = node;
          while (cur_node != (code_node *)0x0) {
            for (; ppVar5 != (psd *)0x0; ppVar5 = ppVar5 + 1) {
              if (0xe < pos) goto LAB_004051e2;
              if ((src_use == ppVar5) || (ppVar5 == (psd *)0x0)) break;
              ok = rename_register_until_redefined(ppVar5,dst_reg,src_reg);
              if ((ok != '\0') ||
                 (((ppVar5->op == OP_EXTS || (ppVar5->op == OP_EXTU)) &&
                  (ppVar5->ea1->base == src_reg)))) {
                if (((ppVar5->op == OP_EXTS) || (ppVar5->op == OP_EXTU)) &&
                   (ppVar5->ea1->base == src_reg)) {
                  hole = move_extension_and_shift_followers(cur_node,ppVar5,hole,pos,hole_index);
                  copy_psd_record(&saved_movi,hole);
                  while (hole != ppVar5) {
                    ppVar5 = ppVar5 + 1;
                    pos = pos + 1;
                    if ((pos == 0xf) && (cur_node = cur_node->next, cur_node != (code_node *)0x0)) {
                      ppVar5 = cur_node->psd;
                      pos = 0;
                    }
                  }
                  if (pos == 0xe) {
                    if (cur_node->next != (code_node *)0x0) {
                      hole = cur_node->next->psd;
                    }
                  }
                  else {
                    hole = hole + 1;
                  }
                  copy_psd_record(&saved_add,hole);
                  delete_psd_record(copy);
                  return;
                }
                operand = ppVar5->ea1;
                if (((operand != (ea *)0x0) && ((operand->type & 0x1f) != 7)) &&
                   (operand->base == src_reg)) {
                  copy_psd_record(ppVar5,hole);
                  hole_index = hole_index + 1;
                  if (hole_index < 0xf) {
                    hole = hole + 1;
                  }
                  else {
                    hole_index = 0;
                    hole = cur_node->psd;
                  }
                }
                copy_done = true;
                break;
              }
              if (copy_done) break;
              copy_psd_record(ppVar5,hole);
              hole_index = hole_index + 1;
              if (hole_index < 0xf) {
                hole = hole + 1;
              }
              else {
                hole_index = 0;
                hole = cur_node->psd;
              }
              if (dst_use == ppVar5) break;
              pos = pos + 1;
            }
            if (pos < 0xf) break;
LAB_004051e2:
            cur_node = cur_node->next;
            if (cur_node == (code_node *)0x0) break;
            ppVar5 = cur_node->psd;
            if (pos < 0x10) {
              pos = 0;
            }
            else {
              pos = pos + -0xf;
              ppVar5 = cur_node->psd + 1;
            }
          }
        }
        copy_psd_record(&saved_movi,hole);
        if (hole_index == 0xe) {
          cur_node = find_node_containing_record(node,hole);
          if (cur_node->next != (code_node *)0x0) {
            hole = cur_node->next->psd;
          }
        }
        else {
          hole = hole + 1;
        }
        copy_psd_record(&saved_add,hole);
        delete_psd_record(copy);
      }
    }
  }
  return;
#undef overwrite
#undef dst_use
#undef add_reg_use
#undef src_use
#undef hole_index
#undef call_mode
#undef src_change
#undef saved_movi
#undef saved_add
}



