#include "decls.h"
#include "imports.h"

// entry: 00434da0
// name : stock_strlen
// size : 119
// sig  : uint stock_strlen(char * str)


uint __cdecl stock_strlen(char *str)

{
  uint *scan;
  uint *cur;
  uint word_bits;
  
  scan = (uint *)str;
  do {
    if (((uint)scan & 3) == 0) goto LAB_00434dbc;
    word_bits = *scan;
    scan = (uint *)((int)scan + 1);
  } while ((char)word_bits != '\0');
LAB_00434def:
  return (uint)((int)scan + (-1 - (int)str));
LAB_00434dbc:
  do {
    do {
      cur = scan;
      scan = cur + 1;
    } while (((*cur ^ 0xffffffff ^ *cur + 0x7efefeff) & 0x81010100) == 0);
    word_bits = *cur;
    if ((char)word_bits == '\0') {
      return (int)cur - (int)str;
    }
    if ((char)(word_bits >> 8) == '\0') {
      return (uint)((int)cur + (1 - (int)str));
    }
    if ((word_bits & 0xff0000) == 0) {
      return (uint)((int)cur + (2 - (int)str));
    }
  } while ((word_bits & 0xff000000) != 0);
  goto LAB_00434def;
}



