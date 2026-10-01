#include "decls.h"
#include "imports.h"

// entry: 00428aa0
// name : copy_string
// size : 48
// sig  : int copy_string(char * dst, char * src)


int __cdecl copy_string(char *dst,char *src)

{
  short i;
  char ch;
  
  i = 0;
  ch = *src;
  *dst = ch;
  while (ch != '\0') {
    i = i + 1;
    ch = src[i];
    dst[i] = ch;
  }
  dst[i] = '\0';
  return 0;
}



