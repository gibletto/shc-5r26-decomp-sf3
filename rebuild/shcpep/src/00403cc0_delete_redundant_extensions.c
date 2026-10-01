#include "decls.h"
#include "imports.h"

// entry: 00403cc0
// name : delete_redundant_extensions
// size : 776
// sig  : void delete_redundant_extensions(code_node * node)


int __cdecl delete_redundant_extensions(code_node *node)

{
  uchar reg;
  byte bVar1;
  char ok;
  uchar uVar2;
  byte dst_kind;
  uint is_volatile;
  psd *rec;
  psd *overwrite;
  psd *first;
  psd *start;
  int i;
  bool blocked;
  bool needs_r0;
  psd_op op;
  
  blocked = false;
  while( true ) {
    if (node == (code_node *)0x0) {
      return;
    }
    i = 0;
    first = node->psd;
    if (first != (psd *)0x0) break;
LAB_00403fb5:
    node = node->next;
  }
LAB_00403cee:
  if (i < 0xf) {
    op = first->op;
    if (((((op == OP_MOV) &&
          ((bVar1 = first->ea1->type & 0x1f, bVar1 == 2 || ((7 < bVar1 && (bVar1 < 0xd)))))) &&
         ((bVar1 = first->flg & 3, bVar1 == 0 || (bVar1 == 1)))) ||
        ((op == OP_EXTU || (op == OP_EXTS)))) &&
       (((first->ea1->type & 0x80) == 0 &&
        (((is_volatile = is_record_volatile(first), is_volatile == 0 &&
          (bVar1 = first->ea1->type & 0x1f, bVar1 != 3)) && (bVar1 != 4)))))) {
      reg = first->ea2->base;
      rec = find_next_psd_record(node,first);
      while (rec != (psd *)0x0) {
        if (((rec->op == OP_EXTS) && ((first->op == OP_MOV || (first->op == OP_EXTS)))) ||
           ((rec->op == OP_EXTU && (first->op == OP_EXTU)))) {
          bVar1 = first->flg & 3;
          if (((bVar1 == 0) || (bVar1 == 1)) &&
             (((rec->flg & 3U) == bVar1 && (ok = operands_equal(first->ea2,rec->ea1), ok != '\0'))))
          {
            start = (psd *)0x0;
            uVar2 = rec->ea2->base;
            if (reg != uVar2) {
              start = find_next_psd_record(node,rec);
            }
            if (((start == (psd *)0x0) ||
                (ok = no_use_after_register_clobbered(node,start,uVar2,reg), ok != '\0')) &&
               ((overwrite = find_register_overwrite(node,start,uVar2,'\0',(char *)0x0),
                reg == uVar2 || (overwrite != (psd *)0x0)))) goto joined_r0x00403e92;
            break;
          }
          uVar2 = record_changes_register(rec,reg);
          if (uVar2 == '\0') goto LAB_00403e02;
LAB_00403e10:
          rec = (psd *)0x0;
        }
        else {
          uVar2 = record_changes_register(rec,reg);
          if (((uVar2 != '\0') || (op = rec->op, op == OP_CALL)) ||
             ((op == OP_JSR || (((op == OP_BSR || (op == OP_TRAPA)) || (op == OP_BSRF))))))
          goto LAB_00403e10;
LAB_00403e02:
          rec = find_next_psd_record(node,rec);
        }
      }
    }
    goto LAB_00403fa8;
  }
  goto LAB_00403fb5;
joined_r0x00403e92:
  if (start != (psd *)0x0) {
    if (uVar2 == '\0') {
      op = start->op;
      if (((op != OP_CMP_EQ) && (op != OP_TST)) || ((start->ea1->type & 0x1f) != 7)) {
        if (op == OP_MOV) {
          bVar1 = start->ea1->type;
          if ((start->flg & 3U) == 2) {
            bVar1 = bVar1 & 0x1f;
            if ((((bVar1 == 9) || (dst_kind = start->ea2->type & 0x1f, dst_kind == 9)) ||
                (bVar1 == 0xb)) || (dst_kind == 0xb)) goto LAB_00403f27;
            needs_r0 = false;
          }
          else {
            bVar1 = bVar1 & 0x1f;
            if ((bVar1 != 8) || (start->ea1->disp == 0)) {
              dst_kind = start->ea2->type & 0x1f;
              if ((((dst_kind != 8) || (start->ea2->disp == 0)) &&
                  (((bVar1 != 9 && (dst_kind != 9)) && (bVar1 != 0xb)))) &&
                 (needs_r0 = false, dst_kind != 0xb)) goto LAB_00403f2c;
            }
LAB_00403f27:
            needs_r0 = true;
          }
LAB_00403f2c:
          if (needs_r0) goto LAB_00403f86;
        }
        if (((start->ea1 == (ea *)0x0) || ((start->ea1->type & 0x1f) != 0xc)) &&
           ((start->ea2 == (ea *)0x0 || ((start->ea2->type & 0x1f) != 0xc)))) goto LAB_00403f4e;
      }
LAB_00403f86:
      blocked = true;
      goto LAB_00403f8e;
    }
LAB_00403f4e:
    ok = rename_register_until_redefined(start,uVar2,reg);
    if (ok == '\0') {
      if (overwrite == start) goto LAB_00403f8e;
      start = find_next_psd_record(node,start);
    }
    else {
      start = (psd *)0x0;
    }
    goto joined_r0x00403e92;
  }
LAB_00403f8e:
  if (blocked) {
    blocked = false;
  }
  else {
    delete_psd_record(rec);
  }
LAB_00403fa8:
  i = i + 1;
  first = first + 1;
  if (first == (psd *)0x0) goto LAB_00403fb5;
  goto LAB_00403cee;
}



