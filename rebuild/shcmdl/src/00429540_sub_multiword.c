#include "decls.h"
#include "imports.h"

// entry: 00429540
// name : sub_multiword
// size : 66
// sig  : void sub_multiword(uint * dst, uint * src, int nwords)


int __cdecl sub_multiword(uint *dst,uint *src,int nwords)

{
  uint *s;
  uint *d;
  uint borrow;
  int i;
  uint old;
  
  borrow = 0;
  i = nwords + -1;
  if (-1 < i) {
    d = dst + i;
    s = src + i;
    do {
      if ((*s != 0) || (borrow != 0)) {
        old = *d;
        borrow = (old - borrow) - *s;
        *d = borrow;
        borrow = (uint)(old <= borrow);
      }
      d = d + -1;
      s = s + -1;
      i = i + -1;
    } while (-1 < i);
  }
  return;
}



