#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_current_aux_index
#define g_current_aux_index (*(int *)(g_sd + 0xf8ec))
#undef g_request_copy
#define g_request_copy (*(request * *)(g_sd + 0x129a8))


// entry: 0042e390
// name : compute_record_code_size
// size : 2163
// sig  : short compute_record_code_size(psd * rec)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

short __cdecl compute_record_code_size(psd *rec)

{
  byte access_size;
  short sVar1;
  short code_size;
  int saved_count;
  int sp_disp;
  int disp_form;
  short cur_size;
  int move_form;
  
  sVar1 = g_op_code_size_table[rec->op];
  code_size = sVar1;
  switch(rec->op) {
  case OP_B_ASM:
    if (rec->ea2 != (ea *)0x0) {
      code_size = ((ushort)rec->ea2 & 1) + (short)rec->ea2 + 2;
    }
    break;
  case OP_CTBL:
    code_size = rec->filno << 2;
    break;
  case OP_ENTER:
    cur_size = sVar1;
    if ((((g_aux_record_table[_g_current_aux_index].flags & 0x4000) != 0) &&
        ((g_aux_record_table[_g_current_aux_index].flags & 0x1800) != 0)) &&
       (((cur_size = sVar1 + 8,
         ((byte)(g_aux_record_table[_g_current_aux_index].flags >> 8) & 0x18) == 0x18 &&
         (saved_count = get_symbol_attribute_bits
                                  ((short)g_aux_record_table[_g_current_aux_index].stack_value),
         saved_count == 1)) ||
        ((((byte)(g_aux_record_table[_g_current_aux_index].flags >> 8) & 0x18) == 0x10 &&
         (saved_count = get_symbol_attribute_bits
                                  ((short)g_aux_record_table[_g_current_aux_index].stack_value),
         saved_count == 0)))))) {
      cur_size = sVar1 + 10;
    }
    sVar1 = count_saved_registers(g_current_aux_index);
    cur_size = cur_size + sVar1 * 2;
    if (((int)(short)g_aux_record_table[_g_current_aux_index].flags & 0x8000U) == 0) {
      cur_size = cur_size + 2;
    }
    code_size = cur_size;
    if (g_aux_record_table[_g_current_aux_index].frame_size != 0) {
      if (g_aux_record_table[_g_current_aux_index].frame_size < 0x81) {
        code_size = cur_size + 2;
      }
      else {
        code_size = cur_size + 4;
      }
    }
    break;
  case OP_RETURN:
    code_size = count_saved_registers(g_current_aux_index);
    if (1 < code_size) {
      cur_size = g_op_code_size_table[0x24];
      code_size = cur_size;
      break;
    }
  case OP_EXIT:
    saved_count = g_aux_record_table[_g_current_aux_index].sp_adjust +
                  g_aux_record_table[_g_current_aux_index].frame_size;
    if (saved_count != 0) {
      if (saved_count < 0x80) {
        sVar1 = sVar1 + 2;
      }
      else {
        sVar1 = sVar1 + 4;
      }
    }
    if (((int)(short)g_aux_record_table[_g_current_aux_index].flags & 0x8000U) == 0) {
      sVar1 = sVar1 + 2;
    }
    code_size = count_saved_registers(g_current_aux_index);
    cur_size = sVar1 + code_size * 2;
    if (((g_aux_record_table[_g_current_aux_index].flags & 0x4000) != 0) &&
       ((g_aux_record_table[_g_current_aux_index].flags & 0x1800) != 0)) {
      cur_size = cur_size + 4;
    }
    if (((g_aux_record_table[_g_current_aux_index].flags & 0x4000) == 0) ||
       ((g_aux_record_table[_g_current_aux_index].flags & 0x2000) == 0)) {
      code_size = cur_size + 4;
      if (((g_aux_record_table[_g_current_aux_index].flags & 0x4000) == 0) &&
         (((g_aux_record_table[_g_current_aux_index].saved_regs != 0 ||
           (g_aux_record_table[_g_current_aux_index].saved_regs2 != 0)) ||
          ((((int)(short)g_aux_record_table[_g_current_aux_index].flags & 0x8000U) != 0 &&
           (((saved_count != 0 || ((g_aux_record_table[_g_current_aux_index].saved_sys & 3) != 0))
            || ((g_aux_record_table[_g_current_aux_index].saved_mac & 3) != 0)))))))) {
        code_size = cur_size + 2;
      }
    }
    else {
      code_size = cur_size + 2;
    }
    break;
  case OP_MV_LOC:
    if ((rec->misc & 0x80U) == 0) {
      sp_disp = frame_offset_to_sp_displacement(rec->ea1->disp,rec->sptravel);
      access_size = rec->flg & 3;
      if (access_size == 0) {
        move_form = 0;
      }
      else if (access_size == 1) {
        move_form = 1;
      }
      else if (access_size == 2) {
        if (((char)rec->ea2->base < '\x10') || ('\x1f' < (char)rec->ea2->base)) {
          move_form = 2;
        }
        else {
          move_form = 6;
        }
      }
    }
    else {
      sp_disp = frame_offset_to_sp_displacement(rec->ea2->disp,rec->sptravel);
      access_size = rec->flg & 3;
      if (access_size == 0) {
        move_form = 3;
      }
      else if (access_size == 1) {
        move_form = 4;
      }
      else if (access_size == 2) {
        if (((char)rec->ea1->base < '\x10') || ('\x1f' < (char)rec->ea1->base)) {
          move_form = 5;
        }
        else {
          move_form = 7;
        }
      }
    }
    if (rec->tmp == '\0') {
      if (sp_disp == 0) {
        disp_form = 3;
      }
      else if ((sp_disp < 1) || (0x10 << (rec->flg & 3) <= sp_disp)) {
        if ((sp_disp < -0x80) || (0x7f < sp_disp)) {
          disp_form = 0;
        }
        else {
          disp_form = 1;
        }
      }
      else {
        disp_form = 2;
      }
    }
    else if (sp_disp == 0) {
      disp_form = 6;
    }
    else if ((sp_disp < 1) || (0x10 << (rec->flg & 3) <= sp_disp)) {
      if ((sp_disp < -0x80) || (0x7f < sp_disp)) {
        disp_form = 7;
      }
      else {
        disp_form = 4;
      }
    }
    else {
      disp_form = 5;
    }
    code_size = (short)(char)(&g_mv_loc_size_table)[disp_form * 8 + move_form];
    if (((((g_request_copy->flags_13d & 4) != 0) && (disp_form == 2)) &&
        ((move_form == 3 || (move_form == 4)))) && ((rec->tmp == '\0' && ((rec->flg & 0x40) == 0))))
    {
      code_size = code_size + 2;
    }
    if ((disp_form == 2) && (((move_form == 0 || (move_form == 1)) && (rec->ea1->base == REG_R0))))
    {
      code_size = code_size + -2;
    }
    if (((disp_form == 5) && ((move_form == 3 || (move_form == 4)))) && (rec->ea2->base == REG_R0))
    {
      code_size = code_size + -4;
    }
    break;
  case OP_MVA_LC:
    saved_count = frame_offset_to_sp_displacement(rec->ea1->disp,rec->sptravel);
    if (saved_count == 0) {
      code_size = sVar1 + 2;
      if ((((g_request_copy->flags_13d & 4) != 0) && ((rec->flg & 0x40) == 0)) &&
         (rec->ea2->base == REG_R0)) {
        code_size = sVar1 + 4;
      }
    }
    else {
      code_size = sVar1 + 4;
    }
    break;
  case OP_MOVI:
    if ((rec->misc & 0x40U) == 0) {
      code_size = sVar1 + -2;
    }
    break;
  case OP_MOVIF:
    if (rec->tmp == '\0') {
      cur_size = 4;
      code_size = cur_size;
    }
    else {
      cur_size = 6;
      code_size = cur_size;
    }
    break;
  case OP_MOV:
    if (((((g_request_copy->flags_13d & 4) != 0) && ((rec->flg & 0x40) == 0)) &&
        ((rec->ea1->type & 0x1f) == 1)) &&
       (((rec->ea2->type & 0x1f) == 1 && (rec->ea2->base == REG_R0)))) {
      cur_size = sVar1 + 2;
      code_size = cur_size;
    }
  }
  cur_size = code_size;
  if ((rec->flg & 0x40) != 0) {
    cur_size = cur_size + -2;
  }
  return cur_size;
}



