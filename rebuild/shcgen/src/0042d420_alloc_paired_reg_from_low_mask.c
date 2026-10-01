#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0042d420
// name : alloc_paired_reg_from_low_mask
// size : 128
// sig  : short alloc_paired_reg_from_low_mask(short busy)


short __cdecl alloc_paired_reg_from_low_mask(short busy)

{
  short no_reg;
  short reg;
  short remaining;
  uint bank_mask;
  uint bits;
  byte bank_count;
  short next_reg;
  
  no_reg = -1;
  bits = 0x30;
  bank_count = g_request->scratch_bank_reg_count;
  bank_mask = ((1 << (bank_count & 0x1f)) + -1) * 0x10;
  reg = no_reg;
  if (((bank_mask & (int)busy) != bank_mask) &&
     (remaining = (short)(char)bank_count, next_reg = 0x24, bank_count != 0)) {
    while (reg = next_reg, ((int)busy & bits) != 0) {
      bits = (uint)(ushort)((short)bits << 2);
      remaining = remaining + -2;
      next_reg = reg + 2;
      if (remaining == 0) {
        return no_reg;
      }
    }
    g_used_fpr_mask =
         g_used_fpr_mask | 1 << ((char)reg - 0x1fU & 0x1f) | 1 << ((char)reg - 0x20U & 0x1f);
  }
  return reg;
}



