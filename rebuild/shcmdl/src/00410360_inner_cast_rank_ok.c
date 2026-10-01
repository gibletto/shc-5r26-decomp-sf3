#include "decls.h"
#include "imports.h"

// entry: 00410360
// name : inner_cast_rank_ok
// size : 213
// sig  : int inner_cast_rank_ok(uchar outer, uchar cast, uchar inner)


int __cdecl inner_cast_rank_ok(uchar outer,uchar cast,uchar inner)

{
  int outer_rank;
  int iVar1;
  int inner_rank;
  int iVar2;
  int iVar3;
  int ok;
  
  ok = 0;
  outer_rank = cast_type_rank(0,outer);
  iVar1 = cast_type_rank(0,cast);
  inner_rank = cast_type_rank(0,inner);
  if ((inner_rank <= iVar1) || (outer_rank <= iVar1)) {
    if (outer_rank == iVar1) {
      iVar2 = cast_type_rank(1,cast);
      iVar3 = cast_type_rank(1,outer);
      if (iVar2 != iVar3) {
        return 0;
      }
    }
    if (inner_rank == iVar1) {
      iVar1 = cast_type_rank(1,inner);
      iVar2 = cast_type_rank(1,cast);
      if (iVar1 != iVar2) {
        return 0;
      }
    }
    if (outer_rank == inner_rank) {
      outer_rank = cast_type_rank(1,inner);
      iVar1 = cast_type_rank(1,outer);
      if (outer_rank != iVar1) {
        return 0;
      }
    }
    ok = 1;
  }
  return ok;
}



