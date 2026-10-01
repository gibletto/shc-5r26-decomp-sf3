#include "decls.h"
#include "imports.h"

// entry: 0042d220
// name : alloc_descending_general_reg
// size : 95
// sig  : short alloc_descending_general_reg(int lowest)


short __cdecl alloc_descending_general_reg(int lowest)

{
  short reg;
  uint bit;
  
  bit = 0x4000;
  reg = -1;
  if (lowest < 0xf) {
    reg = 0xe;
    while (((int)(short)g_var_gpr_mask & bit) != 0) {
      bit = bit >> 1;
      reg = reg + -1;
      if (reg < lowest) {
        return -1;
      }
    }
    g_var_gpr_mask = g_var_gpr_mask | (ushort)bit;
    g_used_gpr_mask = g_used_gpr_mask | (ushort)bit;
  }
  return reg;
}



