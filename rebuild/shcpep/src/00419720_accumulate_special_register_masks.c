#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_rec_def_mask_hi
#define g_rec_def_mask_hi (*(unsigned int *)(g_sd + 0x6d5c))
#undef g_rec_use_mask_hi
#define g_rec_use_mask_hi (*(unsigned int *)(g_sd + 0x5c44))


// entry: 00419720
// name : accumulate_special_register_masks
// size : 132
// sig  : void accumulate_special_register_masks(psd * rec)


int __cdecl accumulate_special_register_masks(psd *rec)

{
  psd_op op;
  
  op = rec->op;
  if ((((op == OP_MULU) || (op == OP_MULS)) || (op == OP_MUL)) || (op == OP_MAC)) {
    if ((op != OP_CLRMAC) && (op != OP_MAC)) goto LAB_0041977b;
  }
  else if (op != OP_CLRMAC) {
    accumulate_t_bit_masks(rec);
    return;
  }
  g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[100];
  g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[100];
LAB_0041977b:
  g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[0x65];
  g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x65];
  return;
}



