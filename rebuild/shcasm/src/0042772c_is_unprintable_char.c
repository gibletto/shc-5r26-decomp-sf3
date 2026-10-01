#include "decls.h"
#include "imports.h"

// entry: 0042772c
// name : is_unprintable_char
// size : 61
// sig  : short is_unprintable_char(short ch)


short __cdecl is_unprintable_char(short ch)

{
  undefined2 unprintable;
  
  unprintable = 1;
  if ((0x1f < ch) && (ch < 0x7f)) {
    unprintable = 0;
  }
  return unprintable;
}



