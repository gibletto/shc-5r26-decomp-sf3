#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 0040c370
// name : delete_store_load_pairs
// size : 1008
// sig  : void delete_store_load_pairs(code_node * node)


int __cdecl delete_store_load_pairs(code_node *node)

{
  uchar reg;
  uchar uVar1;
  char cVar2;
  uint is_volatile;
  ea *new_ea;
  psd *store_rec;
  byte bVar3;
  psd *later_rec;
  char reg_is_special;
  bool no_propagate;
  psd_op op;
  
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
    _printf(s_delstld_start__node_pointer___08_004262c4,node);
    dump_node_list_debug(node);
  }
  store_rec = node->psd;
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_code_pointer___08lx_00426240,store_rec);
  }
  do {
    if (store_rec == (psd *)0x0) {
      if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
        dump_node_list_debug(g_current_node_list);
        _printf(s_delstld_end__004262b4);
      }
      return;
    }
    op = store_rec->op;
    if ((((op == OP_MOV) || (op == OP_NON_B0)) ||
        ((op == OP_MOV_LOC && ((store_rec->misc & 0x80U) != 0)))) &&
       ((((store_rec->flg & 3U) == 2 && ((store_rec->ea2->type & 0x80) == 0)) &&
        (is_volatile = is_record_volatile(store_rec), is_volatile == 0)))) {
      bVar3 = store_rec->ea2->type & 0x1f;
      if (((bVar3 != 3) && (bVar3 != 4)) && ((store_rec->ea1->type & 0x1f) == 1)) {
        reg = store_rec->ea1->base;
        op = store_rec->op;
        if (((op == OP_MOV) || (op == OP_NON_B0)) || ((op == OP_MOV_LOC && (store_rec->tmp != reg)))
           ) {
          if ((bVar3 == 1) && (store_rec->ea2->base == reg)) {
            later_rec = (psd *)0x0;
            delete_psd_record(store_rec);
          }
          else {
            later_rec = find_next_psd_record(node,store_rec);
          }
        }
        else {
          later_rec = (psd *)0x0;
        }
        if (((byte)g_stage_flags & 2) != 0) {
          _printf(s_compare_code_pointer___08lx_00426220,later_rec);
        }
        if (later_rec != (psd *)0x0) {
          while (((((op = later_rec->op, op != OP_CASEJMP && (op != OP_SLEEP)) && (op != OP_NON_10))
                  && ((op != OP_TAS && (op != OP_CALL)))) &&
                 (((op != OP_JSR && ((op != OP_BSR && (op != OP_TRAPA)))) && (op != OP_BSRF))))) {
            if (((op == OP_MOV) || (op == OP_NON_B0)) ||
               ((op == OP_MOV_LOC && ((later_rec->misc & 0x80U) == 0)))) {
              bVar3 = later_rec->flg;
              cVar2 = operands_equal(store_rec->ea2,later_rec->ea1);
              if (cVar2 != '\x01') {
LAB_0040c699:
                uVar1 = record_changes_operand(store_rec->ea2,later_rec);
                if (((uVar1 != '\x01') &&
                    (uVar1 = record_changes_register(later_rec,reg), uVar1 != '\x01')) &&
                   ((((bVar3 = later_rec->ea2->type & 0x1f, bVar3 < 2 || (4 < bVar3)) &&
                     ((bVar3 < 8 || (0xc < bVar3)))) || (bVar3 == 4)))) goto LAB_0040c6d6;
                break;
              }
              if (((((char)reg < '\x10') || ('\x1f' < (char)reg)) && (reg != 'g')) && (reg != 'h'))
              {
                reg_is_special = '\0';
              }
              else {
                reg_is_special = '\x01';
              }
              uVar1 = later_rec->ea2->base;
              if ((('\x0f' < (char)uVar1) && ((char)uVar1 < ' ')) ||
                 ((uVar1 == 'g' || (cVar2 = '\0', uVar1 == 'h')))) {
                cVar2 = '\x01';
              }
              if ((reg_is_special != cVar2) || ((bVar3 & 3) != 2)) goto LAB_0040c699;
              if ((reg == uVar1) &&
                 (cVar2 = operands_equal(store_rec->ea1,later_rec->ea2), cVar2 != '\0')) {
                delete_psd_record(later_rec);
                goto LAB_0040c6d6;
              }
              if (op == OP_MOV_LOC) {
                later_rec->op = OP_NON_B0;
                if (reg_is_special == '\0') {
                  later_rec->op = OP_MOV;
                }
                later_rec->misc = '\0';
                later_rec->tmp = -1;
                later_rec->sptravel = 0;
              }
              if (op == OP_MOV) {
                bVar3 = later_rec->ea2->type & 0x1f;
                if (bVar3 == 0xb) {
                  no_propagate = true;
                }
                else if ((bVar3 == 8) && ((bVar3 = later_rec->flg & 3, bVar3 == 0 || (bVar3 == 1))))
                {
                  no_propagate = true;
                }
                else {
                  no_propagate = false;
                }
                if (no_propagate) break;
              }
              new_ea = copy_ea(store_rec->ea1);
              later_rec->ea1 = new_ea;
            }
            else {
              uVar1 = record_changes_register(later_rec,reg);
              if (((uVar1 == '\x01') ||
                  (uVar1 = record_changes_operand(store_rec->ea2,later_rec), uVar1 == '\x01')) ||
                 ((later_rec->ea2 != (ea *)0x0 &&
                  ((((bVar3 = later_rec->ea2->type & 0x1f, 1 < bVar3 && (bVar3 < 5)) ||
                    ((7 < bVar3 && (bVar3 < 0xd)))) && (bVar3 != 4)))))) break;
LAB_0040c6d6:
              later_rec = find_next_psd_record(node,later_rec);
              if (((byte)g_stage_flags & 2) != 0) {
                _printf(s_compare_code_pointer___08lx_00426220,later_rec);
              }
            }
            if (later_rec == (psd *)0x0) break;
          }
        }
      }
    }
    store_rec = find_next_psd_record(node,store_rec);
    if (((byte)g_stage_flags & 2) != 0) {
      _printf(s_code_pointer___08lx_00426240,store_rec);
    }
  } while( true );
}



