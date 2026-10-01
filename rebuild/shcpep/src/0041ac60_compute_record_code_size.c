#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x6e04))


// entry: 0041ac60
// name : compute_record_code_size
// size : 1157
// sig  : short compute_record_code_size(psd * rec)


short __cdecl compute_record_code_size(psd *rec)

{
  ushort aux_flags;
  short base_size;
  short sVar1;
  ushort uVar2;
  uint attr;
  int iVar3;
  byte access_size;
  int iVar4;
  aux_record *aux;
  char *flg_ptr;
  short size;
  int column;
  char reg;
  
  base_size = g_op_code_size_table[rec->op];
  size = base_size;
  switch((uint)rec->op) {
  case 0x10:
    if (rec->ea2 != (ea *)0x0) {
      aux_flags = (ushort)rec->ea2;
      size = (aux_flags & 1) + 2 + aux_flags;
    }
    break;
  case 0x14:
    size = rec->filno * 4;
    break;
  case 0x20:
    if ((((g_aux_record_table[g_current_aux_index].flags & 0x4000) != 0) &&
        (aux_flags = g_aux_record_table[g_current_aux_index].flags & 0x1800, aux_flags != 0)) &&
       (((size = base_size + 8, aux_flags == 0x1800 &&
         (attr = get_symbol_attr_low_bits
                           ((short)g_aux_record_table[g_current_aux_index].stack_value), attr == 1))
        || ((((byte)(g_aux_record_table[g_current_aux_index].flags >> 8) & 0x18) == 0x10 &&
            (attr = get_symbol_attr_low_bits
                              ((short)g_aux_record_table[g_current_aux_index].stack_value),
            attr == 0)))))) {
      size = base_size + 10;
    }
    base_size = count_saved_registers((short)g_current_aux_index);
    size = size + base_size * 2;
    if ((g_aux_record_table[g_current_aux_index].flags & 0x8000) == 0) {
      size = size + 2;
    }
    iVar3 = g_aux_record_table[g_current_aux_index].frame_size;
    if (iVar3 != 0) {
      if (iVar3 < 0x81) {
        size = size + 2;
      }
      else {
        size = size + 4;
      }
    }
    break;
  case 0x21:
switchD_0041ac8b_caseD_21:
    aux = g_aux_record_table + g_current_aux_index;
    iVar3 = aux->sp_adjust + aux->frame_size;
    if (iVar3 != 0) {
      if (iVar3 < 0x80) {
        base_size = base_size + 2;
      }
      else {
        base_size = base_size + 4;
      }
    }
    if ((aux->flags & 0x8000) == 0) {
      base_size = base_size + 2;
    }
    size = count_saved_registers((short)g_current_aux_index);
    base_size = base_size + size * 2;
    aux_flags = g_aux_record_table[g_current_aux_index].flags;
    uVar2 = aux_flags & 0x4000;
    if ((uVar2 != 0) && ((aux_flags & 0x1800) != 0)) {
      base_size = base_size + 4;
    }
    if ((uVar2 == 0) || ((aux_flags & 0x2000) == 0)) {
      base_size = base_size + 4;
      size = base_size;
      if ((uVar2 == 0) &&
         (((g_aux_record_table[g_current_aux_index].saved_regs != 0 ||
           (g_aux_record_table[g_current_aux_index].saved_regs2 != 0)) ||
          (((aux_flags & 0x8000) != 0 &&
           (((iVar3 != 0 || ((g_aux_record_table[g_current_aux_index].saved_sys & 3) != 0)) ||
            ((g_aux_record_table[g_current_aux_index].saved_mac & 3) != 0)))))))) goto LAB_0041b0ce;
    }
    else {
      size = base_size + 2;
    }
    break;
  case 0x22:
    sVar1 = count_saved_registers((short)g_current_aux_index);
    size = g_op_code_size_table[0x24];
    if (sVar1 < 2) goto switchD_0041ac8b_caseD_21;
    break;
  case 0x27:
    if ((rec->misc & 0x80U) == 0) {
      iVar3 = frame_offset_to_sp_displacement(rec->ea1->disp,rec->sptravel);
      access_size = rec->flg & 3;
      if ((rec->flg & 3U) == 0) {
        column = 0;
      }
      else if (access_size == 1) {
        column = 1;
      }
      else if (access_size == 2) {
        reg = rec->ea2->base;
        if ((reg < '\x10') || ('\x1f' < reg)) {
          column = 2;
        }
        else {
          column = 6;
        }
      }
    }
    else {
      iVar3 = frame_offset_to_sp_displacement(rec->ea2->disp,rec->sptravel);
      access_size = rec->flg & 3;
      if ((rec->flg & 3U) == 0) {
        column = 3;
      }
      else if (access_size == 1) {
        column = 4;
      }
      else if (access_size == 2) {
        reg = rec->ea1->base;
        if ((reg < '\x10') || ('\x1f' < reg)) {
          column = 5;
        }
        else {
          column = 7;
        }
      }
    }
    flg_ptr = &rec->flg;
    if (rec->tmp == '\0') {
      if (iVar3 == 0) {
        iVar4 = 3;
      }
      else if ((iVar3 < 1) || (0x10 << (*flg_ptr & 3U) <= iVar3)) {
        if ((iVar3 < -0x80) || (iVar4 = 1, 0x7f < iVar3)) {
          iVar4 = 0;
        }
      }
      else {
        iVar4 = 2;
      }
    }
    else if (iVar3 == 0) {
      iVar4 = 6;
    }
    else if ((iVar3 < 1) || (0x10 << (*flg_ptr & 3U) <= iVar3)) {
      if ((iVar3 < -0x80) || (0x7f < iVar3)) {
        iVar4 = 7;
      }
      else {
        iVar4 = 4;
      }
    }
    else {
      iVar4 = 5;
    }
    size = (short)(char)(&g_mov_loc_size_table)[iVar4 * 8 + column];
    if ((g_request->flags_13d & 4) == 0) {
LAB_0041af16:
      if (((iVar4 == 2) && ((column == 0 || (column == 1)))) && (rec->ea1->base == '\0')) {
        size = size + -2;
      }
    }
    else if (iVar4 == 2) {
      if ((((column == 3) || (column == 4)) && (rec->tmp == '\0')) && ((*flg_ptr & 0x40U) == 0)) {
        size = size + 2;
      }
      goto LAB_0041af16;
    }
    if (((iVar4 == 5) && ((column == 3 || (column == 4)))) && (rec->ea2->base == '\0')) {
      size = size + -4;
    }
    break;
  case 0x28:
    iVar3 = frame_offset_to_sp_displacement(rec->ea1->disp,rec->sptravel);
    if (iVar3 == 0) {
      size = base_size + 2;
      if ((g_request->flags_13d & 4) != 0) {
        if ((rec->flg & 0x40U) != 0) goto LAB_0041b0d7;
        if (rec->ea2->base == '\0') {
          size = base_size + 4;
        }
      }
    }
    else {
      size = base_size + 4;
    }
    break;
  case 0x2a:
    if ((rec->misc & 0x40U) == 0) {
LAB_0041b0ce:
      size = base_size + -2;
    }
    break;
  case 0x2c:
    size = (-(ushort)(rec->tmp == '\0') & 0xfffe) + 6;
    break;
  case 0x40:
    if ((g_request->flags_13d & 4) == 0) break;
    if ((rec->flg & 0x40U) == 0) {
      if ((((rec->ea1->type & 0x1f) == 1) && ((rec->ea2->type & 0x1f) == 1)) &&
         (rec->ea2->base == '\0')) {
        size = base_size + 2;
      }
      break;
    }
    goto LAB_0041b0d7;
  }
  if ((rec->flg & 0x40U) != 0) {
LAB_0041b0d7:
    size = size + -2;
  }
  return size;
}



