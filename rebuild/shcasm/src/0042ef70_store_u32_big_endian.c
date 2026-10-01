#include "decls.h"
#include "imports.h"

// entry: 0042ef70
// name : store_u32_big_endian
// size : 57
// sig  : uint store_u32_big_endian(uint * value, uint * out)


uint __cdecl store_u32_big_endian(uint *value,uint *out)

{
  uint v;
  
  v = *value;
  *out = (v & 0xff00 | v << 0x10) << 8 | (v & 0xff0000) >> 8 | v >> 0x18;
  return (uint)out & 0xffff0000;
}



