#include "decls.h"
#include "imports.h"

// entry: 00435c50
// name : genfname
// size : 115
// sig  : undefined4 genfname(byte * param_1)


/* Library Function - Single Match
    _genfname
   
   Library: Visual Studio 1998 Release */

undefined4 __cdecl genfname(byte *param_1)

{
  unsigned char _frec_4[4];
#define digits (*(char (*)[4])(_frec_4 + 0))
  char *dot;
  ulong number;
  char *src;
  uint len;
  uint n;
  char *pcVar1;
  char ch;
  
  dot = stock_mbsrchr(param_1,0x2e);
  number = _strtoul(dot + 1,(char **)0x0,0x20);
  if (0x7ffe < number + 1) {
    return 0xffffffff;
  }
  src = __ultoa(number + 1,digits,0x20);
  len = 0xffffffff;
  do {
    pcVar1 = src;
    if (len == 0) break;
    len = len - 1;
    pcVar1 = src + 1;
    ch = *src;
    src = pcVar1;
  } while (ch != '\0');
  len = ~len;
  src = pcVar1 + -len;
  dot = dot + 1;
  for (n = len >> 2; n != 0; n = n - 1) {
    *(undefined4 *)dot = *(undefined4 *)src;
    src = src + 4;
    dot = dot + 4;
  }
  for (len = len & 3; len != 0; len = len - 1) {
    *dot = *src;
    src = src + 1;
    dot = dot + 1;
  }
  return 0;
#undef digits
}



