#include "decls.h"
#include "imports.h"

// entry: 0042efb0
// name : store_u16_big_endian
// size : 25
// sig  : uint store_u16_big_endian(ushort * value, ushort * out)


uint __cdecl store_u16_big_endian(ushort *value,ushort *out)

{
  *out = CONCAT11((char)*value,(char)(*value >> 8));
  return (uint)out & 0xffff0000;
}



