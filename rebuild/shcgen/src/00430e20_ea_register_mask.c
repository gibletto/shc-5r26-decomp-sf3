#include "decls.h"
#include "imports.h"

// entry: 00430e20
// name : ea_register_mask
// size : 183
// sig  : uint ea_register_mask(ea * op)


uint __cdecl ea_register_mask(ea *op)

{
  uint mask;
  byte base;
  
  mask = 0;
  switch(op->type & 0x1f) {
  case 9:
  case 0xc:
    mask = 1;
  case 1:
  case 2:
  case 3:
  case 4:
  case 8:
    base = op->base;
    if ((-1 < (char)base) && ((char)base < ' ')) {
      return mask | 1 << (base & 0x1f);
    }
    if (('\x1f' < (char)base) && ((char)base < '/')) {
      return mask | (1 << (base - 0x1f & 0x1f) | 1 << (base - 0x20 & 0x1f)) << 0x10;
    }
    if (('/' < (char)base) && ((char)base < '=')) {
      mask = mask | (1 << (base - 0x2d & 0x1f) | 1 << (base - 0x2e & 0x1f) |
                     1 << (base - 0x2f & 0x1f) | 1 << (base - 0x30 & 0x1f)) << 0x10;
    }
  default:
    return mask;
  }
}



