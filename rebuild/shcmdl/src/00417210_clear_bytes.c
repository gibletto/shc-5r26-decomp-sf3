#include "decls.h"
#include "imports.h"

// entry: 00417210
// name : clear_bytes
// size : 27
// sig  : void clear_bytes(char * dst, int count)


int __cdecl clear_bytes(char *dst,int count)

{
  for (; count != 0; count = count + -1) {
    *dst = '\0';
    dst = dst + 1;
  }
  return;
}



