#include "decls.h"
#include "imports.h"

// entry: 0043eb50
// name : stock_strncpy
// size : 36
// sig  : char * stock_strncpy(char * dest, char * source, int count)


char * __cdecl stock_strncpy(char *dest,char *source,int count)

{
  char *p;
  char *pcVar1;
  
  p = dest;
  if (count != 0) {
    do {
      pcVar1 = p;
      if (*source == '\0') break;
      pcVar1 = p + 1;
      *p = *source;
      count = count + -1;
      source = source + 1;
      p = pcVar1;
    } while (count != 0);
    for (; count != 0; count = count + -1) {
      *pcVar1 = '\0';
      pcVar1 = pcVar1 + 1;
    }
  }
  return dest;
}



