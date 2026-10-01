#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_branch_defs_hi
#define g_branch_defs_hi (*(unsigned int *)(g_sd + 0x5ba4))
#undef g_branch_defs_lo
#define g_branch_defs_lo (*(unsigned int *)(g_sd + 0x5ba0))
#undef g_branch_uses_hi
#define g_branch_uses_hi (*(unsigned int *)(g_sd + 0x5b9c))
#undef g_branch_uses_lo
#define g_branch_uses_lo (*(unsigned int *)(g_sd + 0x5b98))


// entry: 00416d40
// name : accumulate_compare_test_record_masks
// size : 678
// sig  : char accumulate_compare_test_record_masks(psd * rec)


char __cdecl accumulate_compare_test_record_masks(psd *rec)

{
  char is_compare;
  psd_op op;
  ea *opnd;
  char reg;
  
  is_compare = '\0';
  op = rec->op;
  if (((((OP_ROTCL < op) && (op < OP_SHLD)) || (op == OP_TST)) ||
      ((op == OP_DT || (op == OP_NON_C0)))) || ((op == OP_NON_C1 || (op == OP_NON_C7)))) {
    is_compare = '\x01';
    g_branch_uses_hi = g_branch_uses_hi | g_reg_mask_table[0x61];
    g_branch_defs_hi = g_branch_defs_hi | g_reg_mask_table[0x61];
    switch(rec->op) {
    case OP_TST:
      if ((rec->ea2->type & 0x1f) == 0xc) {
        g_branch_uses_hi = g_branch_uses_hi | g_reg_mask_table[0x62];
        reg = rec->ea2->index;
        if ((reg < '\0') || ('_' < reg)) {
          reg = rec->ea2->index;
          if ('_' < reg) {
            g_branch_uses_hi = g_branch_uses_hi | g_reg_mask_table[reg];
          }
        }
        else {
          g_branch_uses_lo = g_branch_uses_lo | g_reg_mask_table[reg];
        }
        g_branch_uses_hi = g_branch_uses_hi | g_reg_mask_table[0x7f];
      }
    case OP_CMP_EQ:
    case OP_CMP_HS:
    case OP_CMP_GE:
    case OP_CMP_HI:
    case OP_CMP_GT:
    case OP_CMP_STR:
    case OP_NON_C0:
    case OP_NON_C1:
      opnd = rec->ea2;
      if ((opnd != (ea *)0x0) && ((opnd->type & 0x1f) == 1)) {
        reg = opnd->base;
        if ((reg < '\0') || ('_' < reg)) {
          if ('_' < opnd->base) {
            g_branch_uses_hi = g_branch_uses_hi | g_reg_mask_table[opnd->base];
          }
        }
        else {
          g_branch_uses_lo = g_branch_uses_lo | g_reg_mask_table[reg];
        }
      }
    case OP_CMP_PZ:
    case OP_CMP_PL:
    case OP_NON_C7:
      opnd = rec->ea1;
      if ((opnd != (ea *)0x0) && ((opnd->type & 0x1f) == 1)) {
        reg = opnd->base;
        if ((-1 < reg) && (reg < '`')) {
          g_branch_uses_lo = g_branch_uses_lo | g_reg_mask_table[reg];
          return is_compare;
        }
        if ('_' < opnd->base) {
          g_branch_uses_hi = g_branch_uses_hi | g_reg_mask_table[opnd->base];
        }
      }
      break;
    case OP_DT:
      opnd = rec->ea1;
      if ((opnd != (ea *)0x0) && ((opnd->type & 0x1f) == 1)) {
        reg = opnd->base;
        if ((reg < '\0') || ('_' < reg)) {
          if ('_' < opnd->base) {
            g_branch_uses_hi = g_branch_uses_hi | g_reg_mask_table[opnd->base];
          }
        }
        else {
          g_branch_uses_lo = g_branch_uses_lo | g_reg_mask_table[reg];
        }
        reg = rec->ea1->base;
        if ((-1 < reg) && (reg < '`')) {
          g_branch_defs_lo = g_branch_defs_lo | g_reg_mask_table[reg];
          return is_compare;
        }
        reg = rec->ea1->base;
        if ('_' < reg) {
          g_branch_defs_hi = g_branch_defs_hi | g_reg_mask_table[reg];
          return is_compare;
        }
      }
    }
  }
  return is_compare;
}



