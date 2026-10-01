#include "decls.h"
#include "imports.h"

// entry: 0042d280
// name : alloc_descending_extended_reg
// size : 95
// sig  : short alloc_descending_extended_reg(int lowest)


short __cdecl alloc_descending_extended_reg(int lowest)

{
  uint bit;
  short reg;
  
  bit = 0x8000;
  reg = -1;
  if (lowest < 0x20) {
    reg = 0x1f;
    while (((int)(short)g_var_fpr_mask & bit) != 0) {
      bit = bit >> 1;
      reg = reg + -1;
      if (reg < lowest) {
        return -1;
      }
    }
    g_var_fpr_mask = g_var_fpr_mask | (ushort)bit;
    g_used_fpr_mask = g_used_fpr_mask | (ushort)bit;
  }
  return reg;
}



