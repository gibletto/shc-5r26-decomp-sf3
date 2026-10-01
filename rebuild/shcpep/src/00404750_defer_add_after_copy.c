#include "decls.h"
#include "imports.h"

// entry: 00404750
// name : defer_add_after_copy
// size : 1144
// sig  : void defer_add_after_copy(code_node * node, psd * copy, int index)


int __cdecl defer_add_after_copy(code_node *node,psd *copy,int index)

{
  unsigned char _frec_36[54];
#define in_block (*(char *)(_frec_36 + 0))
#define dst_reg (*(uchar *)(_frec_36 + 1))
#define local_34 (*(code_node * *)(_frec_36 + 2))
#define overwrite (*(psd * *)(_frec_36 + 6))
#define src_use (*(psd * *)(_frec_36 + 10))
#define dst_use (*(psd * *)(_frec_36 + 14))
#define dst_reg_wide (*(int *)(_frec_36 + 18))
#define src_change (*(psd * *)(_frec_36 + 22))
#define copy_done (*(int *)(_frec_36 + 26))
#define saved_add (*(psd *)(_frec_36 + 30))
  psd *ppVar1;
  byte dst_kind;
  char ok;
  uchar found;
  psd *hole;
  psd *scan;
  int slot_index;
  byte src_kind;
  int pos;
  undefined4 *src_word;
  psd *ppVar2;
  undefined4 init_word;
  bool needs_r0;
  psd_op op;
  ea *operand;
  uchar src_reg;
  
  dst_use = (psd *)0x0;
  src_use = (psd *)0x0;
  src_change = (psd *)0x0;
  copy_done = 0;
  local_34 = (code_node *)0x0;
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
  copy_psd_record(hole,&saved_add);
  pos = index + 2;
  if (((copy->misc & 0x10U) != 0) && ((hole->misc & 0x10U) == 0)) {
    local_34 = (code_node *)0x1;
  }
  scan = find_next_psd_record(node,hole);
  dst_reg_wide = (int)(char)dst_reg;
  overwrite = find_register_overwrite(node,scan,dst_reg,(char)local_34,&in_block);
  if ((overwrite != (psd *)0x0) ||
     (((in_block == '\0' && ((char)dst_reg < '\x04')) && (local_34 == (code_node *)0x0)))) {
    ppVar2 = src_use;
    ppVar1 = src_change;
    if (scan != (psd *)0x0) {
      do {
        if (dst_reg == '\0') {
          op = scan->op;
          if (((op == OP_CMP_EQ) || (op == OP_TST)) && ((scan->ea1->type & 0x1f) == 7)) {
            return;
          }
          if (op == OP_MOV) {
            src_kind = scan->ea1->type;
            if ((scan->flg & 3U) == 2) {
              src_kind = src_kind & 0x1f;
              if (((src_kind == 9) || (dst_kind = scan->ea2->type & 0x1f, dst_kind == 9)) ||
                 ((src_kind == 0xb || (dst_kind == 0xb)))) goto LAB_004048c0;
              needs_r0 = false;
            }
            else {
              src_kind = src_kind & 0x1f;
              if ((src_kind != 8) || (scan->ea1->disp == 0)) {
                dst_kind = scan->ea2->type & 0x1f;
                if (((dst_kind != 8) || (scan->ea2->disp == 0)) &&
                   ((((src_kind != 9 && (dst_kind != 9)) && (src_kind != 0xb)) &&
                    (needs_r0 = false, dst_kind != 0xb)))) goto LAB_004048c5;
              }
LAB_004048c0:
              needs_r0 = true;
            }
LAB_004048c5:
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
        ppVar2 = scan;
        if (scan->ea1 != (ea *)0x0) {
          ok = operand_uses_register(scan,(uchar)dst_reg_wide,'\x01');
          if (ok != '\0') {
            dst_use = scan;
          }
          if ((scan->ea1 != (ea *)0x0) &&
             (ok = operand_uses_register(scan,src_reg,'\x01'), ppVar1 = src_change, ok != '\0'))
          break;
        }
        if (scan->ea2 != (ea *)0x0) {
          ok = operand_uses_register(scan,(uchar)dst_reg_wide,'\x02');
          if (ok != '\0') {
            dst_use = scan;
          }
          if ((scan->ea2 != (ea *)0x0) &&
             (ok = operand_uses_register(scan,src_reg,'\x02'), ppVar1 = src_change, ok != '\0'))
          break;
        }
        local_34 = (code_node *)(int)(char)src_reg;
        found = record_changes_register(scan,src_reg);
        ppVar2 = src_use;
        ppVar1 = scan;
        if ((found != '\0') ||
           (((ok = call_register_effect(scan,(uchar)local_34,0), ppVar2 = src_use, ok != '\0' ||
             (ppVar1 = src_change, scan == overwrite)) ||
            (scan = find_next_psd_record(node,scan), ppVar2 = src_use, ppVar1 = src_change,
            scan == (psd *)0x0)))) break;
      } while( true );
    }
    src_change = ppVar1;
    src_use = ppVar2;
    if ((((src_use == (psd *)0x0) ||
         ((dst_use != (psd *)0x0 && ((src_use == (psd *)0x0 || (src_use != dst_use)))))) &&
        (src_change == (psd *)0x0)) &&
       (((overwrite != (psd *)0x0 || ((char)dst_reg < '\x04')) &&
        ((dst_use != (psd *)0x0 &&
         (((src_use == (psd *)0x0 || (overwrite == src_use)) ||
          (found = register_referenced_between(node,src_use,overwrite,(uchar)dst_reg_wide),
          found == '\0')))))))) {
      if (dst_use != (psd *)0x0) {
        if (((overwrite != (psd *)0x0) && (overwrite == dst_use)) &&
           ((overwrite->op != OP_EXTS &&
            ((overwrite->op != OP_EXTU &&
             (scan = psd_overwrites_register(overwrite,(uchar)dst_reg_wide), scan == (psd *)0x0)))))
           ) {
          return;
        }
        scan = hole + 1;
        local_34 = node;
        while (local_34 != (code_node *)0x0) {
          ppVar2 = scan;
          if (scan != (psd *)0x0) {
            while( true ) {
              scan = ppVar2;
              if (0xe < pos) goto LAB_00404b48;
              if ((ppVar2 == src_use) || (ppVar2 == src_change)) goto LAB_00404b43;
              ok = rename_register_until_redefined(ppVar2,(uchar)dst_reg_wide,src_reg);
              if ((ok != '\0') ||
                 (((ppVar2->op == OP_EXTS || (ppVar2->op == OP_EXTU)) &&
                  (ppVar2->ea1->base == src_reg)))) break;
              if ((copy_done == 1) ||
                 (copy_psd_record(ppVar2,hole), hole = ppVar2, ppVar2 == dst_use))
              goto LAB_00404b43;
              scan = ppVar2 + 1;
              pos = pos + 1;
              ppVar2 = scan;
              if (scan == (psd *)0x0) goto LAB_00404b43;
            }
            if (((ppVar2->op == OP_EXTS) || (ppVar2->op == OP_EXTU)) &&
               (ppVar2->ea1->base == src_reg)) {
              slot_index = pos + -1;
              if (slot_index < 0) {
                slot_index = pos + 0xe;
              }
              hole = move_extension_and_shift_followers(local_34,ppVar2,hole,pos,slot_index);
              copy_psd_record(&saved_add,hole);
              delete_psd_record(copy);
              return;
            }
            operand = ppVar2->ea1;
            if (((operand != (ea *)0x0) && ((operand->type & 0x1f) != 7)) &&
               (operand->base == src_reg)) {
              copy_psd_record(ppVar2,hole);
              hole = ppVar2;
            }
            copy_done = 1;
          }
LAB_00404b43:
          if (pos < 0xf) break;
LAB_00404b48:
          local_34 = local_34->next;
          if (local_34 != (code_node *)0x0) {
            scan = local_34->psd;
            pos = 0;
          }
        }
      }
      copy_psd_record(&saved_add,hole);
      delete_psd_record(copy);
    }
  }
  return;
#undef in_block
#undef dst_reg
#undef local_34
#undef overwrite
#undef src_use
#undef dst_use
#undef dst_reg_wide
#undef src_change
#undef copy_done
#undef saved_add
}



