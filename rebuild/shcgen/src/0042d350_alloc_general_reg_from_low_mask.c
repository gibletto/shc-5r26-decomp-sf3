#include "decls.h"
#include "imports.h"

// entry: 0042d350
// name : alloc_general_reg_from_low_mask
// size : 84
// sig  : short alloc_general_reg_from_low_mask(ushort busy)


short __cdecl alloc_general_reg_from_low_mask(ushort busy)

{
  short reg;
  ushort bit;
  
  bit = 0x10;
  reg = -1;
  if (((byte)busy & 0xf0) != 0xf0) {
    reg = 4;
    while ((busy & bit) != 0) {
      bit = bit * 2;
      reg = reg + 1;
      if (7 < reg) {
        return -1;
      }
    }
    g_used_gpr_mask = g_used_gpr_mask | 1 << ((byte)reg & 0x1f);
  }
  return reg;
}



