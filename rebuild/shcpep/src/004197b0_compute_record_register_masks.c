#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0x5bf0))
#undef g_rec_def_mask_hi
#define g_rec_def_mask_hi (*(unsigned int *)(g_sd + 0x6d5c))
#undef g_rec_def_mask_lo
#define g_rec_def_mask_lo (*(unsigned int *)(g_sd + 0x6d58))
#undef g_rec_use_mask_hi
#define g_rec_use_mask_hi (*(unsigned int *)(g_sd + 0x5c44))
#undef g_rec_use_mask_lo
#define g_rec_use_mask_lo (*(unsigned int *)(g_sd + 0x5c40))


// entry: 004197b0
// name : compute_record_register_masks
// size : 3930
// sig  : char compute_record_register_masks(psd * rec)


char __cdecl compute_record_register_masks(psd *rec)

{
  char cVar1;
  byte ea_kind;
  uint extra_use_mask;
  psd_op op;
  ea *operand;
  
  g_rec_use_mask_lo = 0;
  g_rec_use_mask_hi = 0;
  g_rec_def_mask_lo = 0;
  g_rec_def_mask_hi = 0;
  if (rec == (psd *)0x0) {
    return '\x01';
  }
  op = rec->op;
  if ((op < OP_NON_10) || ((OP_NON_13 < op && (op < OP_ENTER)))) {
    return '\0';
  }
  if ((op == OP_SLEEP) || (op == OP_NON_10)) {
    return '\x01';
  }
  if ((op == OP_NON_C0) || (op == OP_NON_C1)) {
    g_rec_use_mask_hi = g_reg_mask_table[0x68];
  }
  switch(rec->op) {
  case OP_CASEJMP:
    g_rec_def_mask_lo = g_reg_mask_table[0] | g_reg_mask_table[1];
    g_rec_use_mask_lo = g_reg_mask_table[0] | g_reg_mask_table[1];
    g_rec_def_mask_hi = g_reg_mask_table[0x6b];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x7f];
    break;
  default:
    extra_use_mask = g_reg_mask_table[0x68];
    switch(rec->op) {
    case OP_MOV_LOC:
      cVar1 = macro_record_changes_register(rec,'\0');
      if (cVar1 != '\0') {
        g_rec_def_mask_lo = g_rec_def_mask_lo | g_reg_mask_table[0];
        g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[0];
      }
      cVar1 = macro_record_references_register(rec,'\0');
      if (cVar1 != '\0') {
        g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[0];
      }
      cVar1 = macro_record_changes_register(rec,rec->tmp);
      if (cVar1 != '\0') {
        cVar1 = rec->tmp;
        if ((cVar1 < '\0') || ('_' < cVar1)) {
          if ('_' < rec->tmp) {
            g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[rec->tmp];
          }
        }
        else {
          g_rec_def_mask_lo = g_rec_def_mask_lo | g_reg_mask_table[cVar1];
        }
        cVar1 = rec->tmp;
        if ((cVar1 < '\0') || ('_' < cVar1)) {
          if ('_' < rec->tmp) {
            g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[rec->tmp];
          }
        }
        else {
          g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
        }
      }
      cVar1 = macro_record_references_register(rec,rec->tmp);
      if (cVar1 != '\0') {
        cVar1 = rec->tmp;
        if ((cVar1 < '\0') || ('_' < cVar1)) {
          if ('_' < rec->tmp) {
            g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[rec->tmp];
          }
        }
        else {
          g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
        }
      }
    case OP_MOVA_LC:
      cVar1 = macro_record_changes_register(rec,'\x0f');
      if (cVar1 != '\0') {
        g_rec_def_mask_lo = g_rec_def_mask_lo | g_reg_mask_table[0xf];
        g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[0xf];
      }
      cVar1 = macro_record_references_register(rec,'\x0f');
      if (cVar1 != '\0') {
        g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[0xf];
      }
switchD_0041985d_caseD_29:
      cVar1 = macro_record_changes_register(rec,'k');
      if (cVar1 != '\0') {
        g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x6b];
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
      }
      cVar1 = macro_record_references_register(rec,'k');
      extra_use_mask = g_reg_mask_table[0x6b];
      if (cVar1 != '\0') goto LAB_00419a58;
      break;
    case OP_MOVA_PC:
    case OP_MOVI:
      goto switchD_0041985d_caseD_29;
    case OP_MOVA_FC:
      goto switchD_0041985d_caseD_2b;
    case OP_NON_2C:
      cVar1 = macro_record_changes_register(rec,'g');
      if (cVar1 != '\0') {
        g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x67];
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x67];
      }
switchD_0041985d_caseD_2b:
      cVar1 = macro_record_references_register(rec,'k');
      if (cVar1 != '\0') {
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
      }
      cVar1 = macro_record_changes_register(rec,rec->tmp);
      if (cVar1 != '\0') {
        cVar1 = rec->tmp;
        if ((cVar1 < '\0') || ('_' < cVar1)) {
          if ('_' < rec->tmp) {
            g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[rec->tmp];
          }
        }
        else {
          g_rec_def_mask_lo = g_rec_def_mask_lo | g_reg_mask_table[cVar1];
        }
        cVar1 = rec->tmp;
        if ((cVar1 < '\0') || ('_' < cVar1)) {
          if ('_' < rec->tmp) {
            g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[rec->tmp];
          }
        }
        else {
          g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
        }
      }
      cVar1 = macro_record_references_register(rec,rec->tmp);
      if (cVar1 != '\0') {
        cVar1 = rec->tmp;
        if ((cVar1 < '\0') || ('_' < cVar1)) {
          if ('_' < rec->tmp) {
            g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[rec->tmp];
          }
        }
        else {
          g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
        }
      }
      break;
    case OP_NON_30:
    case OP_NON_31:
    case OP_NON_B0:
    case OP_NON_B3:
    case OP_NON_B4:
    case OP_NON_B5:
    case OP_NON_B6:
    case OP_NON_B8:
    case OP_NON_BA:
    case OP_NON_BC:
    case OP_NON_BE:
    case OP_NON_D0:
    case OP_NON_D2:
    case OP_NON_D4:
    case OP_NON_D6:
    case OP_NON_D8:
    case OP_NON_DC:
    case OP_NON_DD:
    case OP_NON_F0:
    case OP_NON_F1:
      goto LAB_00419a58;
    case OP_ADD:
      operand = rec->ea1;
      if ((((operand->type & 0x1f) == 7) && (operand->labels == (label_ref *)0x0)) &&
         (operand->disp == 0)) {
        return '\0';
      }
      break;
    case OP_NON_CC:
      g_rec_use_mask_lo = g_reg_mask_table[0x10];
LAB_00419a58:
      g_rec_use_mask_hi = g_rec_use_mask_hi | extra_use_mask;
    }
    if (rec->ea1 != (ea *)0x0) {
      accumulate_operand_register_masks(rec,1);
      cVar1 = record_has_memory_source(rec);
      if (cVar1 != '\0') {
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x7f];
      }
      if (rec->op == OP_TAS) {
        g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x7f];
      }
    }
    if (rec->ea2 != (ea *)0x0) {
      accumulate_operand_register_masks(rec,2);
      ea_kind = rec->ea2->type & 0x1f;
      if ((ea_kind != 4) && (((1 < ea_kind && (ea_kind < 5)) || ((7 < ea_kind && (ea_kind < 0xd)))))
         ) {
        g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x7f];
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x7f];
      }
    }
    break;
  case OP_EXIT:
  case OP_RETURN:
    g_rec_def_mask_lo = g_reg_mask_table[1] | g_reg_mask_table[0xf];
    g_rec_use_mask_lo = g_reg_mask_table[1] | g_reg_mask_table[0xf];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x66];
    g_rec_def_mask_hi = g_reg_mask_table[0x66] | g_reg_mask_table[0x65];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x65];
    g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x6b];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
    break;
  case OP_CALL:
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x67];
    g_rec_def_mask_hi = g_reg_mask_table[0x67] | g_reg_mask_table[0x68];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x68];
    cVar1 = rec->tmp;
    if ((cVar1 < '\0') || ('_' < cVar1)) {
      if ('_' < rec->tmp) {
        g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[rec->tmp];
      }
    }
    else {
      g_rec_def_mask_lo = g_reg_mask_table[cVar1];
    }
    cVar1 = rec->tmp;
    if ((cVar1 < '\0') || ('_' < cVar1)) {
      if ('_' < rec->tmp) {
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[rec->tmp];
      }
    }
    else {
      g_rec_use_mask_lo = g_reg_mask_table[cVar1];
    }
    g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x66];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x66];
    g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x6b];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
    g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x7f];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x7f];
    if (g_current_request->macsave == '\0') {
      g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[100];
      g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[100];
      g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x65];
      g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x65];
    }
    break;
  case OP_JUMP:
  case OP_JUMPT:
  case OP_JUMPF:
    cVar1 = rec->tmp;
    if ((cVar1 < '\0') || ('_' < cVar1)) {
      if ('_' < rec->tmp) {
        g_rec_def_mask_hi = g_reg_mask_table[rec->tmp];
      }
    }
    else {
      g_rec_def_mask_lo = g_reg_mask_table[cVar1];
    }
    cVar1 = rec->tmp;
    if ((cVar1 < '\0') || ('_' < cVar1)) {
      if ('_' < rec->tmp) {
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[rec->tmp];
      }
    }
    else {
      g_rec_use_mask_lo = g_reg_mask_table[cVar1];
    }
    g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x6b];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
    break;
  case OP_NON_2E:
    g_rec_def_mask_lo = g_reg_mask_table[0x30] | g_reg_mask_table[0x34];
    g_rec_use_mask_lo = g_reg_mask_table[0x30] | g_reg_mask_table[0x34];
    g_rec_def_mask_lo = g_rec_def_mask_lo | g_reg_mask_table[0x38];
    g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[0x38];
    g_rec_def_mask_lo = g_rec_def_mask_lo | g_reg_mask_table[0x3c];
    g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[0x3c];
    g_rec_def_mask_hi = g_reg_mask_table[0x68];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x68];
    break;
  case OP_TST:
    if ((rec->ea2->type & 0x1f) == 0xc) {
      g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x62];
      cVar1 = rec->ea2->index;
      if ((cVar1 < '\0') || ('_' < cVar1)) {
        cVar1 = rec->ea2->index;
        if ('_' < cVar1) {
          g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[cVar1];
        }
      }
      else {
        g_rec_use_mask_lo = g_reg_mask_table[cVar1];
      }
      g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x7f];
    }
  case OP_CMP_EQ:
  case OP_CMP_HS:
  case OP_CMP_GE:
  case OP_CMP_HI:
  case OP_CMP_GT:
  case OP_CMP_STR:
  case OP_NON_C0:
  case OP_NON_C1:
    operand = rec->ea2;
    if ((operand != (ea *)0x0) && ((operand->type & 0x1f) == 1)) {
      cVar1 = operand->base;
      if ((cVar1 < '\0') || ('_' < cVar1)) {
        if ('_' < operand->base) {
          g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[operand->base];
        }
      }
      else {
        g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
      }
    }
  case OP_CMP_PZ:
  case OP_CMP_PL:
  case OP_NON_C7:
    operand = rec->ea1;
    if ((operand != (ea *)0x0) && ((operand->type & 0x1f) == 1)) {
      cVar1 = operand->base;
      if ((cVar1 < '\0') || ('_' < cVar1)) {
        if ('_' < operand->base) {
          g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[operand->base];
        }
      }
      else {
        g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
      }
    }
    break;
  case OP_DT:
    operand = rec->ea1;
    if ((operand != (ea *)0x0) && ((operand->type & 0x1f) == 1)) {
      cVar1 = operand->base;
      if ((cVar1 < '\0') || ('_' < cVar1)) {
        if ('_' < operand->base) {
          g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[operand->base];
        }
      }
      else {
        g_rec_use_mask_lo = g_reg_mask_table[cVar1];
      }
      cVar1 = rec->ea1->base;
      if ((cVar1 < '\0') || ('_' < cVar1)) {
        cVar1 = rec->ea1->base;
        if ('_' < cVar1) {
          g_rec_def_mask_hi = g_reg_mask_table[cVar1];
        }
      }
      else {
        g_rec_def_mask_lo = g_reg_mask_table[cVar1];
      }
    }
    break;
  case OP_RTE:
  case OP_BF:
  case OP_BT:
  case OP_BRA:
  case OP_BT_S:
  case OP_BF_S:
    g_rec_def_mask_hi = g_reg_mask_table[0x6b];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
    break;
  case OP_JMP:
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x7f];
    cVar1 = rec->ea1->base;
    if ((cVar1 < '\0') || ('_' < cVar1)) {
      cVar1 = rec->ea1->base;
      if ('_' < cVar1) {
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[cVar1];
      }
    }
    else {
      g_rec_use_mask_lo = g_reg_mask_table[cVar1];
    }
    g_rec_def_mask_hi = g_reg_mask_table[0x6b];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
    break;
  case OP_JSR:
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x7f];
  case OP_BSRF:
    cVar1 = rec->ea1->base;
    if ((cVar1 < '\0') || ('_' < cVar1)) {
      cVar1 = rec->ea1->base;
      if ('_' < cVar1) {
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[cVar1];
      }
    }
    else {
      g_rec_use_mask_lo = g_reg_mask_table[cVar1];
    }
  case OP_BSR:
    if (g_current_request->macsave == '\0') {
      g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[100];
      g_rec_def_mask_hi = g_reg_mask_table[100] | g_reg_mask_table[0x65];
      g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x65];
    }
    g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x66];
  case OP_RTS:
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x66];
    g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x6b];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
    break;
  case OP_BRAF:
    cVar1 = rec->ea1->base;
    if ((cVar1 < '\0') || ('_' < cVar1)) {
      cVar1 = rec->ea1->base;
      if ('_' < cVar1) {
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[cVar1];
      }
    }
    else {
      g_rec_use_mask_lo = g_reg_mask_table[cVar1];
    }
    g_rec_def_mask_hi = g_reg_mask_table[0x6b];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
    break;
  case OP_TRAPA:
    g_rec_use_mask_lo = g_reg_mask_table[0];
    g_rec_def_mask_hi = g_reg_mask_table[0x6b];
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
  }
  accumulate_special_register_masks(rec);
  cVar1 = is_register_scan_barrier(rec);
  return '\x01' - (cVar1 == '\0');
}



