#include "decls.h"
#include "imports.h"

// entry: 00402a50
// name : any_bit_set
// size : 31
// sig  : uchar any_bit_set(uint * set, int nwords)


uchar __cdecl any_bit_set(uint *set,int nwords)

{
  byte any;
  uint w;
  
  any = 0;
  for (; nwords != 0; nwords = nwords + -1) {
    w = *set;
    set = set + 1;
    any = any | w != 0;
  }
  return any;
}



