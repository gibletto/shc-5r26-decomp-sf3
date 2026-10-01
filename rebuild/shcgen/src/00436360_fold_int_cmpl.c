#include "decls.h"
#include "imports.h"

// entry: 00436360
// name : fold_int_cmpl
// size : 18
// sig  : uint fold_int_cmpl(uint * a, uint * result)


uint __cdecl fold_int_cmpl(uint *a,uint *result)

{
  *result = ~*a;
  return (uint)result & 0xffff0000;
}



