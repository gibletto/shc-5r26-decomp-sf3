#include "decls.h"
#include "imports.h"

// entry: 004321b0
// name : parse_length_prefixed_name
// size : 140
// sig  : short parse_length_prefixed_name(char * src, char * dst, int * consumed)


short __cdecl parse_length_prefixed_name(char *src,char *dst,int *consumed)

{
  unsigned char _frec_1c[28];
#define parsed_len (*(int *)(_frec_1c + 0))
#define digit_count (*(int *)(_frec_1c + 4))
#define digits (*(byte (*)[20])(_frec_1c + 8))
  char cVar1;
  byte bVar2;
  int i;
  int iVar3;
  
  i = 0;
  cVar1 = *src;
  while (((cVar1 != '\0' && (bVar2 = src[i], 0x2f < bVar2)) && (bVar2 < 0x3a))) {
    digits[i] = bVar2;
    i = i + 1;
    cVar1 = src[i];
  }
  digits[i] = 0;
  parse_decimal_digits((char *)digits,&parsed_len,&digit_count);
  if (parsed_len != 0) {
    iVar3 = 0;
    i = iVar3;
    if (0 < parsed_len) {
      do {
        iVar3 = i + 1;
        dst[i] = src[digit_count + i];
        i = iVar3;
      } while (iVar3 < parsed_len);
    }
    dst[iVar3] = '\0';
    *consumed = digit_count + parsed_len;
    return 0;
  }
  return -1;
#undef parsed_len
#undef digit_count
#undef digits
}



