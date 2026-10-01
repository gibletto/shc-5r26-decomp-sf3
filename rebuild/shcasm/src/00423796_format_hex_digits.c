#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef PTR_s_0123456789ABCDEF_0043cef0
#define PTR_s_0123456789ABCDEF_0043cef0 (*(unsigned char * *)(g_sd + 0x1ef0))


// entry: 00423796
// name : format_hex_digits
// size : 96
// sig  : void __cdecl format_hex_digits(int value,short nbytes,char *out)


int __cdecl format_hex_digits(int value,short nbytes,char *out)

{
  short digit_pos;
  
  digit_pos = nbytes * 2;
  while (digit_pos = digit_pos + -1, -1 < digit_pos) {
    out[digit_pos] = PTR_s_0123456789ABCDEF_0043cef0[(short)((ushort)value & 0xf)];
    value = value >> 4;
  }
  return;
}
