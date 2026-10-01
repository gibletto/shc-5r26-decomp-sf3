#include "decls.h"
#include "imports.h"

// entry: 0042fcb0
// name : copy_length_prefixed_name
// size : 148
// sig  : ushort copy_length_prefixed_name(char * src, char * dst, int * consumed)


ushort __cdecl copy_length_prefixed_name(char *src,char *dst,int *consumed)

{
  unsigned char _frec_1c[28];
#define parsed_len (*(int *)(_frec_1c + 0))
#define local_18 (*(int *)(_frec_1c + 4))
#define digits (*(byte (*)[20])(_frec_1c + 8))
  char cVar1;
  byte bVar2;
  int i;
  
  i = 0;
  cVar1 = *src;
  while (((cVar1 != '\0' && (bVar2 = src[i], 0x2f < bVar2)) && (bVar2 < 0x3a))) {
    digits[i] = bVar2;
    i = i + 1;
    cVar1 = src[i];
  }
  digits[i] = 0;
  parse_decimal_digits((char *)digits,&parsed_len,&local_18);
  if (parsed_len == 0) {
    return 0xffff;
  }
  i = 0;
  local_18 = local_18 + parsed_len;
  if (0 < local_18) {
    do {
      if (src[i] == '\0') {
        return 0xffff;
      }
      dst[i] = src[i];
      i = i + 1;
    } while (i < local_18);
  }
  dst[i] = '\0';
  *consumed = local_18;
  return 0;
#undef parsed_len
#undef local_18
#undef digits
}



