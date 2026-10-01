#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_rec_def_mask_hi
#define g_rec_def_mask_hi (*(unsigned int *)(g_sd + 0x6d5c))
#undef g_rec_use_mask_hi
#define g_rec_use_mask_hi (*(unsigned int *)(g_sd + 0x5c44))


// entry: 00419540
// name : accumulate_t_bit_masks
// size : 154
// sig  : void accumulate_t_bit_masks(psd * rec)


int __cdecl accumulate_t_bit_masks(psd *rec)

{
  psd_op op;
  
  op = rec->op;
  if ((OP_XTRCT < op) && (op < OP_NON_7A)) {
    switch(op) {
    case OP_SHAD:
    case OP_SHLL2:
    case OP_SHLL8:
    case OP_SHLL16:
    case OP_SHLD:
    case OP_SHLR2:
    case OP_SHLR8:
    case OP_SHLR16:
    case OP_ADD:
    case OP_SUB:
    case OP_MUL:
    case OP_MULS:
    case OP_MULU:
    case OP_MAC:
    case OP_DIV1:
    case OP_NEG:
      goto switchD_00419564_caseD_48;
    default:
      g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x61];
      g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x61];
      return;
    }
  }
  switch(op) {
  case OP_CASEJMP:
  case OP_TST:
  case OP_TAS:
  case OP_DT:
  case OP_CLRT:
  case OP_RTE:
  case OP_SETT:
  case OP_NON_C0:
  case OP_NON_C1:
  case OP_NON_C7:
    g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x61];
switchD_004195aa_caseD_25:
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x61];
    return;
  default:
switchD_00419564_caseD_48:
    return;
  case OP_JUMPT:
  case OP_JUMPF:
  case OP_MOVT:
  case OP_BF:
  case OP_BT:
  case OP_BT_S:
  case OP_BF_S:
  case OP_TRAPA:
    goto switchD_004195aa_caseD_25;
  }
}



