#include "decls.h"
#include "imports.h"

// entry: 0040f070
// name : string_length
// size : 22
// sig  : int __cdecl string_length(char *s)


int __cdecl string_length(char *s)

{
  int len;
  char ch;
  
  len = 0;
  if (s != (char *)0x0) {
    ch = *s;
    while (ch != '\0') {
      len = len + 1;
      ch = s[len];
    }
  }
  return len;
}
