#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 0041e630
// name : find_common_dominator
// size : 113
// sig  : bblock * __cdecl find_common_dominator(bblock *a,bblock *b)


bblock * __cdecl find_common_dominator(bblock *a,bblock *b)

{
  unsigned char _frec_20[32];
#define common (*(uint (*)[8])(_frec_20 + 0))
  uint *puVar1;
  uint *next_dst;
  uint *b_bits;
  uint *puVar2;
  uint bits;
  bblock *blk;
  bool equal;
  
  b_bits = b->domlst;
  puVar1 = common;
  puVar2 = a->domlst;
  do {
    bits = *b_bits;
    b_bits = b_bits + 1;
    next_dst = puVar1 + 1;
    *puVar1 = bits & *puVar2;
    puVar1 = next_dst;
    puVar2 = puVar2 + 1;
  } while (next_dst < (void *)(_frec_20 + 0x20));
  blk = g_f_chain->f_next;
  do {
    if (blk == (bblock *)0x0) {
      return (bblock *)0x0;
    }
    equal = true;
    puVar2 = common;
    puVar1 = blk->domlst;
    do {
      if (*puVar1 != *puVar2) {
        equal = false;
        break;
      }
      puVar2 = puVar2 + 1;
      puVar1 = puVar1 + 1;
    } while (puVar2 < (void *)(_frec_20 + 0x20));
    if (equal) {
      return blk;
    }
    blk = blk->f_next;
  } while( true );
#undef common
}
