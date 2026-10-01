#include "decls.h"
#include "imports.h"

// entry: 00430f00
// name : mask_to_register
// size : 40
// sig  : short mask_to_register(uint mask)


short __cdecl mask_to_register(uint mask)

{
  short reg;
  uint bit;
  
  if (mask != 0) {
    reg = 0;
    bit = mask & 1;
    while (bit == 0) {
      reg = reg + 1;
      bit = mask & 1 << ((byte)reg & 0x1f);
    }
    return reg;
  }
  return -1;
}



