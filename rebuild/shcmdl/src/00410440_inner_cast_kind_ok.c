#include "decls.h"
#include "imports.h"

// entry: 00410440
// name : inner_cast_kind_ok
// size : 210
// sig  : int inner_cast_kind_ok(uchar outer, uchar cast, uchar inner)


int __cdecl inner_cast_kind_ok(uchar outer,uchar cast,uchar inner)

{
  int outer_rank1;
  int cast_rank1;
  int cast_rank;
  int inner_rank;
  byte inner_kind;
  int result;
  
  outer_rank1 = cast_type_rank(1,outer);
  cast_rank1 = cast_type_rank(1,cast);
  cast_rank = cast_type_rank(0,cast);
  result = 0;
  inner_rank = cast_type_rank(0,inner);
  inner_kind = inner & 0xe0;
  if (inner_kind != 0x20) {
    if ((inner & 0xf8) != 0x50) goto LAB_004104b1;
  }
  result = 1;
LAB_004104b1:
  if (((inner_kind == 0) && ((inner & 4) != 0)) || ((inner & 0xf8) == 0x40)) {
    if ((((cast & 0xe0) != 0) || ((cast & 4) != 0)) ||
       ((outer_rank1 <= cast_rank1 || (inner_rank != cast_rank)))) {
      result = 1;
    }
  }
  else if ((inner_kind == 0) &&
          (((((cast & 0xe0) != 0 || ((cast & 4) == 0)) && ((cast & 0xf8) != 0x40)) ||
           (outer_rank1 <= cast_rank1)))) {
    return 1;
  }
  return result;
}



