#include "decls.h"
#include "imports.h"

// entry: 00417630
// name : has_free_register_pair
// size : 122
// sig  : int has_free_register_pair(ushort used, ushort range)


int __cdecl has_free_register_pair(ushort used,ushort range)

{
  int found;
  int range_end;
  int pair_reg;
  
  found = 0;
  range_end = 0;
  do {
    pair_reg = range_end;
    if (((int)(short)range & 1 << ((byte)range_end & 0x1f)) != 0) break;
    range_end = range_end + 1;
    pair_reg = range_end;
  } while (range_end < 0x10);
  while ((range_end < 0x10 && (((int)(short)range & 1 << ((byte)range_end & 0x1f)) != 0))) {
    range_end = range_end + 1;
  }
  if (pair_reg < range_end + -1) {
    while ((((int)(short)(used & range) & 1 << ((byte)pair_reg & 0x1f)) != 0 ||
           (((int)(short)(used & range) & 1 << ((byte)pair_reg + 1 & 0x1f)) != 0))) {
      pair_reg = pair_reg + 2;
      if (range_end + -1 <= pair_reg) {
        return found;
      }
    }
    found = 1;
  }
  return found;
}



