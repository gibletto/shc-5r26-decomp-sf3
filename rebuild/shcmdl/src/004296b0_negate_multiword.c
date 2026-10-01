#include "decls.h"
#include "imports.h"

// entry: 004296b0
// name : negate_multiword
// size : 54
// sig  : void negate_multiword(uint * value, int nwords)


int __cdecl negate_multiword(uint *value,int nwords)

{
  uint negated;
  uint *p;
  int borrow;
  int i;
  uint old;
  
  borrow = 0;
  i = nwords + -1;
  if (-1 < i) {
    p = value + i;
    do {
      old = *p;
      negated = -(old + borrow);
      *p = negated;
      if (((int)old < 0) || (borrow = 0, (int)negated < 0)) {
        borrow = 1;
      }
      p = p + -1;
      i = i + -1;
    } while (-1 < i);
  }
  return;
}



