#include "decls.h"
#include "imports.h"

// entry: 004228a0
// name : stock_strncpy
// size : 36
// sig  : char * stock_strncpy(char * dest, char * source, int count)


char * __cdecl stock_strncpy(char *dest,char *source,int count)

{
  char *pcVar1;
  char *pcVar2;
  
  pcVar1 = dest;
  if (count != 0) {
    do {
      pcVar2 = pcVar1;
      if (*source == '\0') break;
      pcVar2 = pcVar1 + 1;
      *pcVar1 = *source;
      count = count + -1;
      source = source + 1;
      pcVar1 = pcVar2;
    } while (count != 0);
    for (; count != 0; count = count + -1) {
      *pcVar2 = '\0';
      pcVar2 = pcVar2 + 1;
    }
  }
  return dest;
}



