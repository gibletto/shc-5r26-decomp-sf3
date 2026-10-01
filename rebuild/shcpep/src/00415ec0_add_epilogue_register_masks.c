#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))
#undef g_branch_defs_hi
#define g_branch_defs_hi (*(unsigned int *)(g_sd + 0x5ba4))
#undef g_branch_defs_lo
#define g_branch_defs_lo (*(unsigned int *)(g_sd + 0x5ba0))
#undef g_branch_uses_hi
#define g_branch_uses_hi (*(unsigned int *)(g_sd + 0x5b9c))
#undef g_branch_uses_lo
#define g_branch_uses_lo (*(unsigned int *)(g_sd + 0x5b98))


// entry: 00415ec0
// name : add_epilogue_register_masks
// size : 586
// sig  : void add_epilogue_register_masks(void)


int __cdecl add_epilogue_register_masks(void)

{
  int frame_bytes;
  uint mask;
  aux_record *aux;
  
  aux = g_aux_record_table + g_current_aux_index;
  frame_bytes = aux->sp_adjust + aux->frame_size;
  if (frame_bytes < 0x80) {
    if (frame_bytes != 0) {
      g_branch_defs_lo = g_branch_defs_lo | g_reg_mask_table[0xf];
      g_branch_uses_lo = g_branch_uses_lo | g_reg_mask_table[0xf];
      g_branch_defs_hi = g_branch_defs_hi | g_reg_mask_table[0x7f];
      g_branch_uses_hi = g_branch_uses_hi | g_reg_mask_table[0x7f];
    }
    if ((aux->flags & 0x8000) != 0) goto LAB_00416007;
    g_branch_defs_hi = g_branch_defs_hi | g_reg_mask_table[0x66];
    mask = g_reg_mask_table[0x66];
  }
  else {
    g_branch_defs_lo = g_branch_defs_lo | g_reg_mask_table[1];
    g_branch_uses_lo = g_branch_uses_lo | g_reg_mask_table[1];
    g_branch_defs_hi = g_branch_defs_hi | g_reg_mask_table[0x7f];
    mask = g_reg_mask_table[0x7f];
  }
  g_branch_defs_lo = g_branch_defs_lo | g_reg_mask_table[0xf];
  g_branch_uses_lo = g_branch_uses_lo | g_reg_mask_table[0xf];
  g_branch_uses_hi = g_branch_uses_hi | mask;
LAB_00416007:
  if ((aux->saved_mac & 1) != 0) {
    g_branch_defs_lo = g_branch_defs_lo | g_reg_mask_table[0xf];
    g_branch_uses_lo = g_branch_uses_lo | g_reg_mask_table[0xf];
    g_branch_defs_hi = g_branch_defs_hi | g_reg_mask_table[0x65];
    g_branch_uses_hi = g_branch_uses_hi | g_reg_mask_table[0x65];
  }
  if ((aux->saved_sys & 1) != 0) {
    g_branch_defs_lo = g_branch_defs_lo | g_reg_mask_table[0xf];
    g_branch_uses_lo = g_branch_uses_lo | g_reg_mask_table[0xf];
    g_branch_defs_hi = g_branch_defs_hi | g_reg_mask_table[0x67];
    g_branch_uses_hi = g_branch_uses_hi | g_reg_mask_table[0x67];
  }
  if ((aux->saved_sys & 2) != 0) {
    g_branch_defs_lo = g_branch_defs_lo | g_reg_mask_table[0xf];
    g_branch_uses_lo = g_branch_uses_lo | g_reg_mask_table[0xf];
    g_branch_defs_hi = g_branch_defs_hi | g_reg_mask_table[0x68];
    g_branch_uses_hi = g_branch_uses_hi | g_reg_mask_table[0x68];
  }
  return;
}



