#include "decls.h"
#include "imports.h"

// entry: 0042a0b0
// name : stock_strncpy
// size : 36
// sig  : char * stock_strncpy(char * dst, char * src, int count)


char * __cdecl stock_strncpy(char *dst,char *src,int count)

{
  char *pcVar1;
  char *pcVar2;
  
  pcVar1 = dst;
  if (count != 0) {
    do {
      pcVar2 = pcVar1;
      if (*src == '\0') break;
      pcVar2 = pcVar1 + 1;
      *pcVar1 = *src;
      count = count + -1;
      src = src + 1;
      pcVar1 = pcVar2;
    } while (count != 0);
    for (; count != 0; count = count + -1) {
      *pcVar2 = '\0';
      pcVar2 = pcVar2 + 1;
    }
  }
  return dst;
}



