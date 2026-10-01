#include "decls.h"
#include "imports.h"

// entry: 0043f5b0
// name : stock_strncnt
// size : 44
// sig  : uint stock_strncnt(char * str, uint count)


/* Library Function - Single Match
    _strncnt
   
   Library: Visual Studio 1998 Release */

uint __cdecl stock_strncnt(char *str,uint count)

{
  uint remaining;
  char *p;
  
  p = str;
  remaining = count;
  while (remaining != 0) {
    remaining = remaining - 1;
    if (*p == '\0') goto LAB_0043f5d5;
    p = p + 1;
  }
  if (*p == '\0') {
LAB_0043f5d5:
    count = (int)p - (int)str;
  }
  return count;
}



