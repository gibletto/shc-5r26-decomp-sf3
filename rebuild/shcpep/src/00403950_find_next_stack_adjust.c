#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))


// entry: 00403950
// name : find_next_stack_adjust
// size : 442
// sig  : psd * find_next_stack_adjust(code_node * node, psd * rec)


psd * __cdecl find_next_stack_adjust(code_node *node,psd *rec)

{
  uchar changes_sp;
  char uses_sp;
  byte bVar1;
  psd *adjust;
  uint vol;
  psd *between;
  int adjust_disp;
  psd_op op;
  int rec_disp;
  
  adjust = find_next_psd_record(node,rec);
  if (adjust != (psd *)0x0) {
    while ((((adjust->op != OP_ADD || (vol = is_record_volatile(adjust), vol != 0)) ||
            ((adjust->ea1->type & 0x1f) != 7)) ||
           (((adjust->ea2->type & 0x1f) != 1 || (adjust->ea2->base != '\x0f'))))) {
      if (((adjust->op == OP_EXIT) && (vol = is_record_volatile(adjust), vol == 0)) ||
         (adjust = find_next_psd_record(node,adjust), adjust == (psd *)0x0)) break;
    }
    if (adjust != (psd *)0x0) {
      rec_disp = rec->ea1->disp;
      if (adjust->op == OP_EXIT) {
        adjust_disp = g_aux_record_table[g_current_aux_index].sp_adjust +
                      g_aux_record_table[g_current_aux_index].frame_size;
      }
      else {
        adjust_disp = adjust->ea1->disp;
      }
      for (between = find_next_psd_record(node,rec); between != adjust;
          between = find_next_psd_record(node,between)) {
        changes_sp = record_changes_register(between,'\x0f');
        if (((changes_sp == '\0') &&
            (uses_sp = operand_uses_register(between,'\x0f','\x01'), uses_sp == '\0')) &&
           (uses_sp = operand_uses_register(between,'\x0f','\x02'), uses_sp == '\0')) {
          op = between->op;
          if ((((op == OP_CALL) || (op == OP_JSR)) || (op == OP_BSR)) ||
             ((op == OP_TRAPA || (op == OP_BSRF)))) {
            if ((((rec->flg & 8U) == 0) && (((adjust->flg & 8U) == 0 && (0 < rec_disp)))) &&
               (0 < adjust_disp)) goto LAB_00403a7f;
            goto LAB_00403ab1;
          }
        }
        else {
LAB_00403a7f:
          if (((((rec->flg & 8U) != 0) || ((adjust->flg & 8U) != 0)) || (rec_disp < 1)) ||
             (adjust_disp < 1)) {
LAB_00403ab1:
            adjust = (psd *)0x0;
            break;
          }
        }
      }
      if (adjust != (psd *)0x0) {
        bVar1 = rec->flg & 8;
        if (((((bVar1 != 0) || ((adjust->flg & 8U) != 0)) || ((0 < rec_disp && (0 < adjust_disp))))
            && ((((0 < rec_disp && (0 < adjust_disp)) ||
                 ((bVar1 != 0 && (((adjust->flg & 8U) != 0 || ((bVar1 != 0 && (0 < adjust_disp))))))
                 )) || ((0 < rec_disp && ((adjust->flg & 8U) != 0)))))) &&
           (((rec->flg & 0x20U) != 0 || ((adjust->flg & 0x20U) != 0)))) {
          adjust = (psd *)0x0;
        }
      }
    }
  }
  return adjust;
}



