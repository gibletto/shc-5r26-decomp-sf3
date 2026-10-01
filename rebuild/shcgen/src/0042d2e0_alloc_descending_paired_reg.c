#include "decls.h"
#include "imports.h"

// entry: 0042d2e0
// name : alloc_descending_paired_reg
// size : 97
// sig  : short alloc_descending_paired_reg(int lowest)


short __cdecl alloc_descending_paired_reg(int lowest)

{
  short reg;
  uint bits;
  
  bits = 0xc000;
  reg = -1;
  if (lowest < 0x2f) {
    reg = 0x2e;
    while (((int)(short)g_var_fpr_mask & bits) != 0) {
      bits = bits >> 2;
      reg = reg + -2;
      if (reg < lowest) {
        return -1;
      }
    }
    g_var_fpr_mask = g_var_fpr_mask | (ushort)bits;
    g_used_fpr_mask = g_used_fpr_mask | (ushort)bits;
  }
  return reg;
}



