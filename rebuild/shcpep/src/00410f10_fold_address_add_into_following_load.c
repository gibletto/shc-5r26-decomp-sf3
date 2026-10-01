#include "decls.h"
#include "imports.h"

// entry: 00410f10
// name : fold_address_add_into_following_load
// size : 668
// sig  : void fold_address_add_into_following_load(code_node * node)


int __cdecl fold_address_add_into_following_load(code_node *node)

{
  uchar reg;
  byte kind;
  uchar uVar1;
  char cVar2;
  uint max_disp;
  psd *rec;
  psd *to;
  uint aligned;
  byte add_src_kind;
  uchar add_src_reg;
  psd *add_rec;
  int remaining;
  uint disp;
  psd_op op;
  ea *src_ea;
  
  do {
    if (node == (code_node *)0x0) {
      return;
    }
    remaining = 0xf;
    add_rec = node->psd;
    do {
      if (((add_rec->op == OP_ADD) && (max_disp = is_record_volatile(add_rec), max_disp == 0)) &&
         (reg = add_rec->ea2->base, reg != '\x0f')) {
        add_src_kind = add_rec->ea1->type & 0x1f;
        if ((((add_src_kind != 1) || (add_src_reg = add_rec->ea1->base, add_src_reg == '\0')) ||
            (reg == '\0')) && (rec = find_next_psd_record(node,add_rec), rec != (psd *)0x0)) {
          do {
            if ((rec->op == OP_MOV) || ((rec->op == OP_NON_B0 && (add_src_kind == 1)))) {
              src_ea = rec->ea1;
              kind = src_ea->type & 0x1f;
              if ((((kind == 8) && (src_ea->disp == 0)) || (kind == 2)) && (src_ea->base == reg)) {
                if ((rec->ea2->base != reg) &&
                   ((to = find_register_overwrite(node,rec,reg,'\0',(char *)0x0), to == (psd *)0x0
                    || (uVar1 = register_referenced_between(node,rec,to,reg), uVar1 != '\0'))))
                break;
                if (add_src_kind == 7) {
                  add_src_kind = rec->flg;
                  kind = add_src_kind & 3;
                  if (kind == 2) {
LAB_00411042:
                    max_disp = 0x40;
                  }
                  else {
                    if (rec->ea2->base != '\0') break;
                    if (kind == 2) goto LAB_00411042;
                    if (kind == 1) {
                      max_disp = 0x20;
                    }
                    else {
                      max_disp = -(uint)((add_src_kind & 3) == 0) & 0x10;
                    }
                  }
                  disp = add_rec->ea1->disp;
                  if ((add_src_kind & 3) == 0) {
                    aligned = 1;
                  }
                  else if (kind == 1) {
                    aligned = ~disp & 1;
                  }
                  else {
                    aligned = 0;
                    if (kind == 2) {
                      aligned = (uint)((disp & 3) == 0);
                    }
                  }
                  if (((aligned == 0) || ((int)max_disp <= (int)disp)) || ((int)disp < 1)) break;
                  rec->ea1->type = '\b';
                  rec->ea1->disp = disp;
                }
                else {
                  rec->ea1->type = '\t';
                  if (reg == '\0') {
                    rec->ea1->base = add_src_reg;
                    rec->ea1->index = '\0';
                  }
                  else {
                    rec->ea1->base = reg;
                    rec->ea1->index = '\0';
                  }
                }
                delete_psd_record(add_rec);
                break;
              }
            }
            uVar1 = record_changes_register(rec,reg);
            if ((((uVar1 != '\0') || (cVar2 = operand_uses_register(rec,reg,'\x01'), cVar2 != '\0'))
                || (((cVar2 = operand_uses_register(rec,reg,'\x02'), cVar2 != '\0' ||
                     ((add_src_kind == 1 &&
                      (uVar1 = record_changes_register(rec,add_src_reg), uVar1 != '\0')))) ||
                    (op = rec->op, op == OP_JSR)))) ||
               ((((op == OP_BSR || (op == OP_CALL)) || (op == OP_TRAPA)) ||
                ((op == OP_BSRF || (rec = find_next_psd_record(node,rec), rec == (psd *)0x0))))))
            break;
          } while( true );
        }
      }
      add_rec = add_rec + 1;
      remaining = remaining + -1;
    } while (remaining != 0);
    node = node->next;
  } while( true );
}



