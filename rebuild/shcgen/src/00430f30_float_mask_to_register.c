#include "decls.h"
#include "imports.h"

// entry: 00430f30
// name : float_mask_to_register
// size : 185
// sig  : short float_mask_to_register(ushort mask)


short __cdecl float_mask_to_register(ushort mask)

{
  uint bit;
  ushort reg;
  ushort sign;
  
  if (mask == 0) {
    return -1;
  }
  reg = 0x10;
  bit = 1;
  if ((mask & 1) == 0) {
    do {
      reg = reg + 1;
      bit = bit * 2;
    } while ((bit & (int)(short)mask) == 0);
  }
  if (((short)reg < 0x1f) && ((bit * 2 & (int)(short)mask) != 0)) {
    sign = (short)reg >> 0xf;
    if (((reg ^ sign) - sign & 1 ^ sign) == sign) {
      return reg + 0x10;
    }
    report_codegen_message(0x123c,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return reg;
  }
  if (0x1f < (short)reg) {
    report_codegen_message(0x123c,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  }
  return reg;
}



