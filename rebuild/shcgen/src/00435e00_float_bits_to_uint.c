#include "decls.h"
#include "imports.h"

// entry: 00435e00
// name : float_bits_to_uint
// size : 19
// sig  : int float_bits_to_uint(uint * src, uint * dst)


int __cdecl float_bits_to_uint(uint *src,uint *dst)

{
  int status;
  
  status = float_bits_to_int(src,dst);
  return status;
}



