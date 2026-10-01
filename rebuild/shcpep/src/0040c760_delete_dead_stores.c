#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 0040c760
// name : delete_dead_stores
// size : 774
// sig  : void delete_dead_stores(code_node * node)


int __cdecl delete_dead_stores(code_node *node)

{
  byte bVar1;
  byte bVar2;
  char equal;
  uchar blocked;
  uint is_volatile;
  psd *later_rec;
  psd *store_rec;
  psd_op op;
  
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
    _printf(s_delstore_start__node_pointer___0_004262f8,node);
    dump_node_list_debug(node);
  }
  store_rec = node->psd;
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_code_pointer___08lx_00426240,store_rec);
  }
  do {
    if (store_rec == (psd *)0x0) {
      if (((byte)g_stage_flags & 2) != 0) {
        dump_node_list_debug(g_current_node_list);
        _printf(s_delstore_end__004262e8);
      }
      return;
    }
    op = store_rec->op;
    if ((((op == OP_MOV) || (op == OP_NON_B0)) ||
        ((op == OP_MOV_LOC && ((store_rec->misc & 0x80U) != 0)))) &&
       ((bVar1 = store_rec->ea1->type & 0x1f, bVar1 != 4 && (bVar1 != 3)))) {
      bVar1 = store_rec->ea2->type;
      bVar2 = bVar1 & 0x1f;
      if (((bVar2 == 2) || ((7 < bVar2 && (bVar2 < 0xd)))) &&
         (((bVar1 & 0x80) == 0 && (is_volatile = is_record_volatile(store_rec), is_volatile == 0))))
      {
        later_rec = find_next_psd_record(node,store_rec);
        if (((byte)g_stage_flags & 2) != 0) {
          _printf(s_compare_code_pointer___08lx_00426220,later_rec);
        }
        while (later_rec != (psd *)0x0) {
          op = later_rec->op;
          if (((op == OP_MOV) || (op == OP_NON_B0)) ||
             ((op == OP_MOV_LOC && ((later_rec->misc & 0x80U) != 0)))) {
            bVar1 = store_rec->flg;
            bVar2 = later_rec->flg;
            equal = operands_equal(store_rec->ea2,later_rec->ea2);
            if ((equal == '\x01') && ((bVar1 & 3) == (bVar2 & 3))) {
              delete_psd_record(store_rec);
              break;
            }
            equal = operands_equal(store_rec->ea2,later_rec->ea1);
            if (((((equal != '\0') ||
                  (equal = operands_equal(store_rec->ea2,later_rec->ea2), equal != '\0')) ||
                 (blocked = record_changes_operand(store_rec->ea2,later_rec), blocked != '\0')) ||
                ((bVar1 = later_rec->ea2->type & 0x1f, 1 < bVar1 && (bVar1 < 5)))) ||
               ((7 < bVar1 && (bVar1 < 0xd)))) break;
            blocked = record_has_memory_source(later_rec);
          }
          else {
            if ((((((op == OP_CALL) || (op == OP_JSR)) ||
                  ((op == OP_BSR || (((op == OP_TRAPA || (op == OP_BSRF)) || (op == OP_NON_10))))))
                 || ((op == OP_SLEEP || (op == OP_CASEJMP)))) ||
                ((later_rec->ea2 != (ea *)0x0 &&
                 (((equal = operands_equal(store_rec->ea2,later_rec->ea2), equal == '\x01' ||
                   ((bVar1 = later_rec->ea2->type & 0x1f, 1 < bVar1 && (bVar1 < 5)))) ||
                  ((7 < bVar1 && (bVar1 < 0xd)))))))) ||
               ((later_rec->ea1 != (ea *)0x0 &&
                ((equal = operands_equal(store_rec->ea2,later_rec->ea1), equal == '\x01' ||
                 (equal = record_has_memory_source(later_rec), equal == '\x01')))))) break;
            blocked = record_changes_operand(store_rec->ea2,later_rec);
          }
          if (blocked != '\0') break;
          later_rec = find_next_psd_record(node,later_rec);
          if (((byte)g_stage_flags & 2) != 0) {
            _printf(s_compare_code_pointer___08lx_00426220,later_rec);
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



