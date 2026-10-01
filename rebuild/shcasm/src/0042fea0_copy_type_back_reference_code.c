#include "decls.h"
#include "imports.h"

// entry: 0042fea0
// name : copy_type_back_reference_code
// size : 85
// sig  : short copy_type_back_reference_code(char * src, char * dst, int * consumed)


short __cdecl copy_type_back_reference_code(char *src,char *dst,int *consumed)

{
  char cVar1;
  byte bVar2;
  short i;
  
  *dst = *src;
  cVar1 = src[1];
  if (cVar1 == '\0') {
    return -1;
  }
  i = 1;
  while (cVar1 != '\0') {
    bVar2 = src[i];
    if ((bVar2 < 0x30) || (0x39 < bVar2)) break;
    dst[i] = bVar2;
    cVar1 = src[(short)(i + 1)];
    i = i + 1;
  }
  dst[i] = '\0';
  *consumed = (int)i;
  return 0;
}



