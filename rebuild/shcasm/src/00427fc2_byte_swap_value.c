#include "decls.h"
#include "imports.h"

// entry: 00427fc2
// name : byte_swap_value
// size : 147
// sig  : void __cdecl byte_swap_value(uint *out,uint *in,int size_code)


int __cdecl byte_swap_value(uint *out,uint *in,int size_code)

{
  if (size_code == 1) {
    *out = (uint)CONCAT11((char)(short)*in,*(undefined1 *)((int)in + 1));
  }
  else if (size_code == 2) {
    *out = (*in & 0xff00) << 8 | *in >> 8 & 0xff00 | *in << 0x18 | *in >> 0x18;
  }
  return;
}
