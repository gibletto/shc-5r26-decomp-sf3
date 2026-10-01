#include "decls.h"
#include "imports.h"

// entry: 0043abe0
// name : stock_strchr
// size : 24
// sig  : char * stock_strchr(char * str, char ch)


char * __cdecl stock_strchr(char *str,char ch)

{
  while( true ) {
    if (ch == *str) {
      return str;
    }
    if (*str == '\0') break;
    str = str + 1;
  }
  return (char *)0x0;
}



