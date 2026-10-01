#include "decls.h"
#include "imports.h"

// entry: 00410520
// name : cast_type_rank
// size : 143
// sig  : int cast_type_rank(int mode, uchar type)


int __cdecl cast_type_rank(int mode,uchar type)

{
  int rank;
  byte kind;
  
  rank = 0;
  if ((type & 0xe0) == 0x20) {
    if ((type & 0x18) == 0x10) {
      return 6;
    }
    if ((type & 0x18) == 0x18) {
      return 7;
    }
  }
  if (((type & 0xe0) == 0x20) && ((type & 0x18) == 8)) {
    return 5 - (uint)(mode == 0);
  }
  kind = type & 0xf8;
  if (((kind == 0x10) || (kind == 0x18)) || (kind == 0x40)) {
    rank = 4;
  }
  else {
    if (kind == 8) {
      return 3;
    }
    if (kind == 0) {
      return 2;
    }
    if (kind == 0x50) {
      return 1;
    }
  }
  return rank;
}



