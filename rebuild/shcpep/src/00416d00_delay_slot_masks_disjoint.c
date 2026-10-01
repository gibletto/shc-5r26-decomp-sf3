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
#undef g_rec_def_mask_hi
#define g_rec_def_mask_hi (*(unsigned int *)(g_sd + 0x6d5c))
#undef g_rec_def_mask_lo
#define g_rec_def_mask_lo (*(unsigned int *)(g_sd + 0x6d58))
#undef g_rec_use_mask_hi
#define g_rec_use_mask_hi (*(unsigned int *)(g_sd + 0x5c44))
#undef g_rec_use_mask_lo
#define g_rec_use_mask_lo (*(unsigned int *)(g_sd + 0x5c40))


// entry: 00416d00
// name : delay_slot_masks_disjoint
// size : 61
// sig  : char delay_slot_masks_disjoint(void)


char __cdecl delay_slot_masks_disjoint(void)

{
  char disjoint;
  
  disjoint = '\0';
  if (((((g_rec_def_mask_lo & g_branch_uses_lo) == 0) &&
       ((g_rec_def_mask_hi & g_branch_uses_hi) == 0)) &&
      ((g_rec_use_mask_lo & g_branch_defs_lo) == 0)) &&
     ((g_rec_use_mask_hi & g_branch_defs_hi) == 0)) {
    disjoint = '\x01';
  }
  return disjoint;
}



