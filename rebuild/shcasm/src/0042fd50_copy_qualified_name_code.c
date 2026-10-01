#include "decls.h"
#include "imports.h"

// entry: 0042fd50
// name : copy_qualified_name_code
// size : 240
// sig  : short copy_qualified_name_code(char * src, char * dst, int * consumed)


short __cdecl copy_qualified_name_code(char *src,char *dst,int *consumed)

{
  unsigned char _frec_120[288];
#define part_count (*(int *)(_frec_120 + 0))
#define digit_count (*(int *)(_frec_120 + 4))
#define part_len (*(int *)(_frec_120 + 8))
#define digits (*(byte (*)[20])(_frec_120 + 12))
#define part_name (*(char (*)[256])(_frec_120 + 32))
  char cVar1;
  byte bVar2;
  ushort uVar3;
  int i;
  int count;
  
  cVar1 = src[1];
  for (i = 0; ((cVar1 != '\0' && (bVar2 = src[i + 1], 0x2f < bVar2)) && (bVar2 < 0x3a)); i = i + 1)
  {
    digits[i] = bVar2;
    cVar1 = src[i + 2];
  }
  digits[i] = 0;
  parse_decimal_digits((char *)digits,&part_count,&digit_count);
  if (part_count != 0) {
    if ((src[digit_count + 1] == '_') && (src[digit_count + 2] == '_')) {
      i = 0;
      count = digit_count + 3;
      if (0 < part_count) {
        do {
          uVar3 = copy_length_prefixed_name(src + count,part_name,&part_len);
          if (uVar3 != 0) {
            return -1;
          }
          count = count + part_len;
          i = i + 1;
        } while (i < part_count);
      }
      stock_strncpy(dst,src,count);
      dst[count] = '\0';
      *consumed = count;
      return 0;
    }
    return -1;
  }
  return -1;
#undef part_count
#undef digit_count
#undef part_len
#undef digits
#undef part_name
}



