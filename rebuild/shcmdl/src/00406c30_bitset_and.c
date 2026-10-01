#include "decls.h"
#include "imports.h"

// entry: 00406c30
// name : bitset_and
// size : 52
// sig  : void bitset_and(uint * dst, uint * a, uint * b, char nwords)


int __cdecl bitset_and(uint *dst,uint *a,uint *b,char nwords)

{
  uint a_word;
  uint b_word;
  
  for (; nwords != '\0'; nwords = nwords + -1) {
    b_word = *b;
    b = b + 1;
    a_word = *a;
    a = a + 1;
    *dst = b_word & a_word;
    dst = dst + 1;
  }
  return;
}



