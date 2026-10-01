#include "decls.h"
#include "imports.h"

// entry: 0042b220
// name : copy_words
// size : 33
// sig  : void copy_words(uint * dst, uint * src, int count)


int __cdecl copy_words(uint *dst,uint *src,int count)

{
  uint value;
  
  if (0 < count) {
    do {
      value = *src;
      src = src + 1;
      count = count + -1;
      *dst = value;
      dst = dst + 1;
    } while (count != 0);
  }
  return;
}



