#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 0040bfb0
// name : delete_redundant_memory_loads
// size : 948
// sig  : void delete_redundant_memory_loads(code_node * block)


int __cdecl delete_redundant_memory_loads(code_node *block)

{
  uchar reg;
  byte bVar1;
  uchar uVar2;
  byte load_size;
  char cVar3;
  uint is_vol;
  ea *src_copy;
  psd *rec;
  psd *later_rec;
  psd_op op;
  char special_dst;
  
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
    _printf(s_delmemld_start__node_pointer___0_0042628c,block);
    dump_node_list_debug(block);
  }
  rec = block->psd;
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_code_pointer___08lx_00426240,rec);
  }
  do {
    if (rec == (psd *)0x0) {
      if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
        dump_node_list_debug(g_current_node_list);
        _printf(s_delmemld_end__0042627c);
      }
      return;
    }
    op = rec->op;
    if ((((op == OP_MOV) || (op == OP_NON_B0)) || ((op == OP_MOV_LOC && ((rec->misc & 0x80U) == 0)))
        ) && (((rec->ea1->type & 0x80) == 0 && (is_vol = is_record_volatile(rec), is_vol == 0)))) {
      bVar1 = rec->ea1->type & 0x1f;
      if (((bVar1 != 3) && (bVar1 != 4)) &&
         (((bVar1 == 2 || ((7 < bVar1 && (bVar1 < 0xd)))) && ((rec->ea2->type & 0x1f) == 1)))) {
        reg = rec->ea2->base;
        if ((((rec->op == OP_MOV) && (uVar2 = record_changes_operand(rec->ea1,rec), uVar2 == '\0'))
            || (rec->op == OP_NON_B0)) || ((rec->op == OP_MOV_LOC && (rec->tmp != reg)))) {
          later_rec = find_next_psd_record(block,rec);
        }
        else {
          later_rec = (psd *)0x0;
        }
        if (((byte)g_stage_flags & 2) != 0) {
          _printf(s_compare_code_pointer___08lx_00426220,later_rec);
        }
        if (later_rec != (psd *)0x0) {
          while ((((op = later_rec->op, op != OP_CASEJMP && (op != OP_SLEEP)) &&
                  ((op != OP_NON_10 && (((op != OP_TAS && (op != OP_CALL)) && (op != OP_JSR)))))) &&
                 (((op != OP_BSR && (op != OP_TRAPA)) && (op != OP_BSRF))))) {
            if (((op != OP_MOV) && (op != OP_NON_B0)) &&
               ((op != OP_MOV_LOC || ((later_rec->misc & 0x80U) != 0)))) {
              uVar2 = record_changes_register(later_rec,reg);
              if (((uVar2 != '\x01') &&
                  (uVar2 = record_changes_operand(rec->ea1,later_rec), uVar2 != '\x01')) &&
                 ((later_rec->ea2 == (ea *)0x0 ||
                  ((((bVar1 = later_rec->ea2->type & 0x1f, bVar1 < 2 || (4 < bVar1)) &&
                    ((bVar1 < 8 || (0xc < bVar1)))) || (bVar1 == 4)))))) goto LAB_0040c2e2;
              break;
            }
            load_size = rec->flg & 3;
            bVar1 = later_rec->flg;
            cVar3 = operands_equal(rec->ea1,later_rec->ea1);
            if (cVar3 == '\x01') {
              if (((('\x0f' < (char)reg) && ((char)reg < ' ')) || (reg == 'g')) ||
                 (cVar3 = '\0', reg == 'h')) {
                cVar3 = '\x01';
              }
              uVar2 = later_rec->ea2->base;
              if ((((char)uVar2 < '\x10') || ('\x1f' < (char)uVar2)) &&
                 ((uVar2 != 'g' && (uVar2 != 'h')))) {
                special_dst = '\0';
              }
              else {
                special_dst = '\x01';
              }
              if ((cVar3 != special_dst) || ((bVar1 & 3) != load_size)) goto LAB_0040c2a3;
              if (uVar2 == reg) {
                delete_psd_record(later_rec);
                goto LAB_0040c2e2;
              }
              if (load_size != 2) {
                uVar2 = record_changes_operand(rec->ea1,later_rec);
                if (uVar2 == '\0') goto LAB_0040c2e2;
                break;
              }
              if (op == OP_MOV_LOC) {
                later_rec->op = OP_NON_B0;
                if (cVar3 == '\0') {
                  later_rec->op = OP_MOV;
                }
                later_rec->misc = '\0';
                later_rec->tmp = -1;
                later_rec->sptravel = 0;
              }
              src_copy = copy_ea(rec->ea2);
              later_rec->ea1 = src_copy;
            }
            else {
LAB_0040c2a3:
              uVar2 = record_changes_operand(rec->ea1,later_rec);
              if (((uVar2 == '\x01') ||
                  (uVar2 = record_changes_register(later_rec,reg), uVar2 == '\x01')) ||
                 ((((bVar1 = later_rec->ea2->type & 0x1f, 1 < bVar1 && (bVar1 < 5)) ||
                   ((7 < bVar1 && (bVar1 < 0xd)))) && (bVar1 != 4)))) break;
LAB_0040c2e2:
              later_rec = find_next_psd_record(block,later_rec);
              if (((byte)g_stage_flags & 2) != 0) {
                _printf(s_compare_code_pointer___08lx_00426220,later_rec);
              }
            }
            if (later_rec == (psd *)0x0) break;
          }
        }
      }
    }
    rec = find_next_psd_record(block,rec);
    if (((byte)g_stage_flags & 2) != 0) {
      _printf(s_code_pointer___08lx_00426240,rec);
    }
  } while( true );
}



