#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0040289d
// name : append_reloc_entry_header
// size : 277
// sig  : int append_reloc_entry_header(int address, short bit_width, int flag)


int __cdecl append_reloc_entry_header(int address,short bit_width,int flag)

{
  int iVar1;
  byte kind_bits;
  
  if (g_current_request->endian == '\0') {
    kind_bits = -(flag == 0) & 3;
  }
  else {
    kind_bits = -(flag == 0) & 3U | (char)bit_width * '\x02' - 0x10U;
  }
  kind_bits = kind_bits | 4;
  append_reloc_expression_byte((int)(char)kind_bits);
  append_reloc_expression_long(address);
  if (g_current_request->endian == '\0') {
    append_reloc_expression_byte(0);
    iVar1 = append_reloc_expression_byte((int)(char)bit_width);
  }
  else {
    iVar1 = (int)bit_width;
    if (iVar1 != 8) {
      if (iVar1 != 0x10) {
        if (iVar1 != 0x20) {
          return iVar1;
        }
        append_reloc_expression_byte(0x18);
        append_reloc_expression_byte(8);
        append_reloc_expression_byte(0x10);
        append_reloc_expression_byte(8);
      }
      append_reloc_expression_byte(8);
      append_reloc_expression_byte(8);
    }
    append_reloc_expression_byte(0);
    iVar1 = append_reloc_expression_byte(8);
  }
  return iVar1;
}



