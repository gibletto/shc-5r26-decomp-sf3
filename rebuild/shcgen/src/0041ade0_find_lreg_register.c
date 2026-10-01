#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lreg_table
#define g_lreg_table (*(short * *)(g_sd + 0x1fa10))


// entry: 0041ade0
// name : find_lreg_register
// size : 60
// sig  : short find_lreg_register(short lreg)


short __cdecl find_lreg_register(short lreg)

{
  short *entry;
  short reg;
  ushort sign;
  
  sign = lreg >> 0xf;
  reg = -1;
  if (((ushort)(lreg ^ sign) != sign) && (entry = g_lreg_table, *g_lreg_table != 0)) {
    while (*entry != (ushort)((lreg ^ sign) - sign)) {
      entry = entry + 0x12;
      if (*entry == 0) {
        return -1;
      }
    }
    reg = entry[1];
  }
  return reg;
}



