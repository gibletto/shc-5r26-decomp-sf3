#include "decls.h"
#include "imports.h"

// entry: 00406cb0
// name : bitsets_differ
// size : 56
// sig  : int bitsets_differ(int * a, int * b, int nwords)


int __cdecl bitsets_differ(int *a,int *b,int nwords)

{
  int differ;
  int *next_a;
  int *next_b;
  int a_word;
  int b_word;
  
  differ = 0;
  while (nwords != 0) {
    nwords = nwords + -1;
    next_a = a + 1;
    next_b = b + 1;
    b_word = *b;
    a_word = *a;
    a = next_a;
    b = next_b;
    if (a_word != b_word) {
      differ = 1;
    }
  }
  return differ;
}



