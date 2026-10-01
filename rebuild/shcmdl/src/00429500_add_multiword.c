#include "decls.h"
#include "imports.h"

// entry: 00429500
// name : add_multiword
// size : 62
// sig  : void add_multiword(uint * dst, uint * src, int nwords)


int __cdecl add_multiword(uint *dst,uint *src,int nwords)

{
  uint *s;
  uint carry;
  int i;
  uint *d;
  uint old;
  
  carry = 0;
  i = nwords + -1;
  if (-1 < i) {
    d = dst + i;
    s = src + i;
    do {
      if ((*s != 0) || (carry != 0)) {
        old = *d;
        carry = *s + carry + old;
        *d = carry;
        carry = (uint)(carry <= old);
      }
      d = d + -1;
      s = s + -1;
      i = i + -1;
    } while (-1 < i);
  }
  return;
}



