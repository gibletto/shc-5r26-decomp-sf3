#include "decls.h"
#include "imports.h"

// entry: 00434be0
// name : format_decimal
// size : 133
// sig  : short format_decimal(int value)


short __cdecl format_decimal(int value)

{
  int iVar1;
  short pos;
  short new_len;
  
  g_decimal_text_length = 0;
  iVar1 = value / 10;
  pos = 0;
  if (iVar1 != 0) {
    format_decimal(iVar1);
    pos = g_decimal_text_length;
  }
  if ((value < 0) && (value = -value, iVar1 == 0)) {
    iVar1 = (int)pos;
    pos = pos + 1;
    (&g_decimal_text)[iVar1] = 0x2d;
  }
  new_len = pos + 1;
  g_decimal_text_length = new_len;
  (&g_decimal_text)[pos] = (char)(value % 10) + '0';
  (&g_decimal_text)[new_len] = 0;
  if (new_len < 0x13) {
    return new_len;
  }
  return -1;
}



