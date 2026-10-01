#include "decls.h"
#include "imports.h"
#include "pep_rules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_branch_defs_hi
#define g_branch_defs_hi (*(unsigned int *)(g_sd + 0x5ba4))
#undef g_branch_defs_lo
#define g_branch_defs_lo (*(unsigned int *)(g_sd + 0x5ba0))
#undef g_branch_uses_hi
#define g_branch_uses_hi (*(unsigned int *)(g_sd + 0x5b9c))
#undef g_branch_uses_lo
#define g_branch_uses_lo (*(unsigned int *)(g_sd + 0x5b98))
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


// entry: 004162f0
// name : select_delay_slot_record
// size : 2274
// sig  : char select_delay_slot_record(code_node * node, psd * cand)


char __cdecl select_delay_slot_record(code_node *node,psd *cand)

{
  char cVar1;
  byte ea2_kind;
  psd *scan_rec;
  char selected;
  psd_op op;
  
  selected = '\0';
  if (cand == (psd *)0x0) {
    return '\0';
  }
  do {
    cVar1 = is_register_scan_barrier(cand);
    if (cVar1 != '\0') {
      return selected;
    }
    g_rec_use_mask_lo = 0;
    g_rec_use_mask_hi = 0;
    g_rec_def_mask_lo = 0;
    g_rec_def_mask_hi = 0;
    switch(cand->op) {
    case OP_MOV_LOC:
      cVar1 = macro_record_changes_register(cand,'\0');
      if (cVar1 != '\0') {
        g_rec_def_mask_lo = g_rec_def_mask_lo | g_reg_mask_table[0];
        g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[0];
      }
      cVar1 = macro_record_references_register(cand,'\0');
      if (cVar1 != '\0') {
        g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[0];
      }
      cVar1 = macro_record_changes_register(cand,cand->tmp);
      if (cVar1 != '\0') {
        cVar1 = cand->tmp;
        if ((cVar1 < '\0') || ('_' < cVar1)) {
          if ('_' < cand->tmp) {
            g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[cand->tmp];
          }
        }
        else {
          g_rec_def_mask_lo = g_rec_def_mask_lo | g_reg_mask_table[cVar1];
        }
        cVar1 = cand->tmp;
        if ((cVar1 < '\0') || ('_' < cVar1)) {
          if ('_' < cand->tmp) {
            g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[cand->tmp];
          }
        }
        else {
          g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
        }
      }
      cVar1 = macro_record_references_register(cand,cand->tmp);
      if (cVar1 != '\0') {
        cVar1 = cand->tmp;
        if ((cVar1 < '\0') || ('_' < cVar1)) {
          if ('_' < cand->tmp) {
            g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[cand->tmp];
          }
        }
        else {
          g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
        }
      }
    case OP_MOVA_LC:
      cVar1 = macro_record_changes_register(cand,'\x0f');
      if (cVar1 != '\0') {
        g_rec_def_mask_lo = g_rec_def_mask_lo | g_reg_mask_table[0xf];
        g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[0xf];
      }
      cVar1 = macro_record_references_register(cand,'\x0f');
      if (cVar1 != '\0') {
        g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[0xf];
      }
      break;
    case OP_MOVA_PC:
    case OP_MOVI:
      cVar1 = macro_record_changes_register(cand,'k');
      if (cVar1 != '\0') {
        g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x6b];
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
      }
      cVar1 = macro_record_references_register(cand,'k');
      if (cVar1 != '\0') {
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
      }
      break;
    case OP_MOVA_FC:
      cVar1 = macro_record_references_register(cand,'k');
      if (cVar1 != '\0') {
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
      }
      cVar1 = macro_record_changes_register(cand,cand->tmp);
      if (cVar1 != '\0') {
        cVar1 = cand->tmp;
        if ((cVar1 < '\0') || ('_' < cVar1)) {
          if ('_' < cand->tmp) {
            g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[cand->tmp];
          }
        }
        else {
          g_rec_def_mask_lo = g_rec_def_mask_lo | g_reg_mask_table[cVar1];
        }
        cVar1 = cand->tmp;
        if ((cVar1 < '\0') || ('_' < cVar1)) {
          if ('_' < cand->tmp) {
            g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[cand->tmp];
          }
        }
        else {
          g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
        }
      }
      cVar1 = macro_record_references_register(cand,cand->tmp);
      if (cVar1 != '\0') {
        cVar1 = cand->tmp;
        if ((cVar1 < '\0') || ('_' < cVar1)) {
          if ('_' < cand->tmp) {
            g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[cand->tmp];
          }
        }
        else {
          g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
        }
      }
      break;
    case OP_NON_2C:
      if (cand->tmp == '\0') {
        g_rec_use_mask_lo = g_reg_mask_table[0];
        g_rec_use_mask_hi = g_reg_mask_table[0x7f];
      }
      else {
        g_rec_use_mask_hi = g_reg_mask_table[0x67];
      }
      break;
    case OP_NON_2E:
      cVar1 = macro_record_references_register(cand,cand->ea1->base);
      if (cVar1 != '\0') {
        cVar1 = cand->ea1->base;
        if ((cVar1 < '\0') || ('_' < cVar1)) {
          cVar1 = cand->ea1->base;
          if ('_' < cVar1) {
            g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[cVar1];
          }
        }
        else {
          g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
        }
      }
      cVar1 = macro_record_changes_register(cand,'h');
      if (cVar1 != '\0') {
        g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x68];
      }
      break;
    case OP_NON_30:
    case OP_NON_31:
      cVar1 = macro_record_references_register(cand,'h');
      if (cVar1 != '\0') {
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x68];
      }
      cVar1 = macro_record_changes_register(cand,'h');
      if (cVar1 != '\0') {
        g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x68];
      }
      break;
    case OP_TRAPA:
      g_rec_use_mask_hi = g_reg_mask_table[0x6b];
      break;
    case OP_NON_B0:
    case OP_NON_B3:
    case OP_NON_B4:
    case OP_NON_B5:
    case OP_NON_B6:
    case OP_NON_B8:
    case OP_NON_BA:
    case OP_NON_BC:
    case OP_NON_BE:
    case OP_NON_C0:
    case OP_NON_C1:
    case OP_NON_D0:
    case OP_NON_D2:
    case OP_NON_D4:
    case OP_NON_D6:
    case OP_NON_D8:
    case OP_NON_DC:
    case OP_NON_DD:
    case OP_NON_F0:
    case OP_NON_F1:
      g_rec_use_mask_hi = g_reg_mask_table[0x68];
      break;
    case OP_NON_CC:
      g_rec_use_mask_lo = g_reg_mask_table[0x10];
      g_rec_use_mask_hi = g_reg_mask_table[0x68];
    }
    op = cand->op;
    if (((op != OP_NON_2E) && (op != OP_NON_30)) && (op != OP_NON_31)) {
      if (cand->ea1 != (ea *)0x0) {
        accumulate_operand_register_masks(cand,1);
        if ((cand->op != OP_NON_2C) && (cVar1 = record_has_memory_source(cand), cVar1 != '\0')) {
          g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x7f];
        }
        if (cand->op == OP_TAS) {
          g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x7f];
        }
      }
      if (cand->ea2 != (ea *)0x0) {
        accumulate_operand_register_masks(cand,2);
        if ((cand->op != OP_TST) || ((cand->ea2->type & 0x1f) != 0xc)) {
          ea2_kind = cand->ea2->type & 0x1f;
          if ((ea2_kind == 4) ||
             (((ea2_kind < 2 || (4 < ea2_kind)) && ((ea2_kind < 8 || (0xc < ea2_kind))))))
          goto LAB_0041696e;
          g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x7f];
        }
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x7f];
      }
    }
LAB_0041696e:
    accumulate_special_register_masks(cand);
    selected = delay_slot_masks_disjoint();
#if SHC_REBUILD_UPDATED
    if (selected == 1 && slot_no_stack() != 0 && slot_record_is_frame_access((unsigned char *)cand)) {
      if (slot_no_stack() == 2) {
        return 0;
      }
      selected = 0;
    }
#endif
    if ((((selected == '\x01') && (op = cand->op, op != OP_NON_A0)) && (op != OP_NON_30)) &&
       (op != OP_NON_31)) {
      if ((((g_current_request->flags_13d & 4) == 0) ||
          ((((cand->op != OP_MOV || ((cand->ea1->type & 0x1f) != 1)) ||
            (((cand->ea2->type & 0x1f) != 1 || (cand->ea2->base != '\0')))) &&
           (((cand->op != OP_MOVA_LC || ((cand->ea2->type & 0x1f) != 1)) ||
            (cand->ea2->base != '\0')))))) ||
         (scan_rec = find_next_psd_record(node,cand), scan_rec == (psd *)0x0)) goto LAB_00416b67;
      break;
    }
    op = cand->op;
    if ((op == OP_MOV_LOC) || (op == OP_MOVA_LC)) {
      g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
    }
    else if (op == OP_NON_2C) {
      g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
      cVar1 = cand->tmp;
      if ((cVar1 < '\0') || ('_' < cVar1)) {
        if ('_' < cand->tmp) {
          g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[cand->tmp];
        }
      }
      else {
        g_rec_def_mask_lo = g_rec_def_mask_lo | g_reg_mask_table[cVar1];
      }
      cVar1 = cand->tmp;
      if ((cVar1 < '\0') || ('_' < cVar1)) {
        if ('_' < cand->tmp) {
          g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[cand->tmp];
        }
      }
      else {
        g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
      }
      if (cand->tmp != '\0') {
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x7f];
        g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x67];
      }
    }
    g_branch_defs_lo = g_branch_defs_lo | g_rec_def_mask_lo;
    g_branch_defs_hi = g_branch_defs_hi | g_rec_def_mask_hi;
    g_branch_uses_lo = g_branch_uses_lo | g_rec_use_mask_lo;
    g_branch_uses_hi = g_branch_uses_hi | g_rec_use_mask_hi;
    scan_rec = find_previous_psd_record(node,cand);
    cand = find_previous_slot_candidate(node,scan_rec);
    if (cand == (psd *)0x0) {
      return selected;
    }
  } while( true );
  while (scan_rec = find_next_psd_record(node,scan_rec), scan_rec != (psd *)0x0) {
    if ((scan_rec->op == OP_JUMPT) || (scan_rec->op == OP_JUMPF)) break;
  }
  if (scan_rec == (psd *)0x0) {
LAB_00416b67:
    cand->flg = cand->flg | 0x40;
    scan_rec = find_next_psd_record(node,cand);
    if (scan_rec != (psd *)0x0) {
      while (((((op = scan_rec->op, op < OP_EXIT || (OP_JUMPF < op)) && (op != OP_RTE)) &&
              ((op < OP_BRA || (OP_RTS < op)))) && ((op != OP_BSRF && (op != OP_BRAF))))) {
        scan_rec = find_next_psd_record(node,scan_rec);
        if (scan_rec == (psd *)0x0) {
          return '\x01';
        }
      }
      if ((scan_rec->op == OP_JUMPT) || (scan_rec->op == OP_JUMPF)) {
        scan_rec->misc = scan_rec->misc | 0x80;
      }
    }
  }
  return '\x01';
}



