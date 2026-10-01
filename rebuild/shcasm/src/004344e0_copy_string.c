#include "decls.h"
#include "imports.h"

// entry: 004344e0
// name : copy_string
// size : 48
// sig  : int copy_string(char * dest, char * src)


int __cdecl copy_string(char *dest,char *src)

{
  short i;
  char ch;
  
  i = 0;
  ch = *src;
  *dest = ch;
  while (ch != '\0') {
    i = i + 1;
    ch = src[i];
    dest[i] = ch;
  }
  dest[i] = '\0';
  return 0;
}



