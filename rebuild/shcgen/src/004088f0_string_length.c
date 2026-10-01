#include "decls.h"
#include "imports.h"

// entry: 004088f0
// name : string_length
// size : 18
// sig  : int string_length(char * str)


int __cdecl string_length(char *str)

{
  int len;
  char ch;
  
  len = 0;
  ch = *str;
  while (ch != '\0') {
    len = len + 1;
    ch = str[len];
  }
  return len;
}



