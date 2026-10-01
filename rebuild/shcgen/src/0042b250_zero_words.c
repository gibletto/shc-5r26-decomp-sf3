#include "decls.h"
#include "imports.h"

// entry: 0042b250
// name : zero_words
// size : 19
// sig  : void zero_words(uint * dst, int count)


int __cdecl zero_words(uint *dst,int count)

{
  if (0 < count) {
    for (; count != 0; count = count + -1) {
      *dst = 0;
      dst = dst + 1;
    }
  }
  return;
}



