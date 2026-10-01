#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0040d5d0
// name : frame_operand_sp_displacement
// size : 184
// sig  : int frame_operand_sp_displacement(ea * operand)


int __cdecl frame_operand_sp_displacement(ea *operand)

{
  int iVar1;
  ushort save_mask;
  uint uVar2;
  int sp_disp;
  
  iVar1 = operand->disp;
  sp_disp = g_sptravel + g_max_temp_frame + g_local_frame_size;
  if (-1 < iVar1) {
    sp_disp = sp_disp + iVar1;
    uVar2 = (int)g_current_function >> 0x1f;
    iVar1 = ((int)g_current_function ^ uVar2) - uVar2;
    if ((g_symbol_table[iVar1].attr & 0x10) == 0) {
      if ((g_symbol_table[iVar1].attr & 0xc) == 0) {
        for (save_mask = g_used_gpr_mask & 0x7f00; save_mask != 0; save_mask = (short)save_mask >> 1
            ) {
          if ((save_mask & 0x100) != 0) {
            sp_disp = sp_disp + 4;
          }
        }
        if (g_request->macsave != '\0') {
          if ((g_mac_regs_used & 1) != 0) {
            sp_disp = sp_disp + 4;
          }
          if ((g_mac_regs_used & 2) != 0) {
            sp_disp = sp_disp + 4;
          }
        }
      }
    }
    else {
      sp_disp = sp_disp + 0x1c;
    }
    if ((g_symbol_table[iVar1].sym_flags & 4) == 0) {
      sp_disp = sp_disp + 4;
    }
    if (((g_symbol_table[iVar1].ret_type & 0xe0) == 0x60) ||
       ((g_symbol_table[iVar1].ret_type & 0xf8) == 0x30)) {
      sp_disp = sp_disp + 4;
    }
    return sp_disp;
  }
  return iVar1 + 4 + sp_disp;
}



