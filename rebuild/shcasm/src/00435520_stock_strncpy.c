#include "decls.h"
#include "imports.h"

// entry: 00435520
// name : stock_strncpy
// size : 36
// sig  : char * stock_strncpy(char * dest, char * source, int count)


char * __cdecl stock_strncpy(char *dest,char *source,int count)

{
  char *cur;
  char *next;
  
  cur = dest;
  if (count != 0) {
    do {
      next = cur;
      if (*source == '\0') break;
      next = cur + 1;
      *cur = *source;
      count = count + -1;
      source = source + 1;
      cur = next;
    } while (count != 0);
    for (; count != 0; count = count + -1) {
      *next = '\0';
      next = next + 1;
    }
  }
  return dest;
}



