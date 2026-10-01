#include "decls.h"
#include "imports.h"

// entry: 00435f60
// name : double_bits_to_uint
// size : 19
// sig  : int double_bits_to_uint(uint * src, uint * dst)


int __cdecl double_bits_to_uint(uint *src,uint *dst)

{
  int status;
  
  status = double_bits_to_int(src,dst);
  return status;
}



