#include "decls.h"
#include "imports.h"

// entry: 00406760
// name : type_arith_class
// size : 128
// sig  : int type_arith_class(uchar type)


int __cdecl type_arith_class(uchar type)

{
  byte kind;
  undefined4 local_4;
  
  kind = type & 0xe0;
  if (((kind == 0) && ((type & 4) != 0)) || ((type & 0xf8) == 0x40)) {
    return 1;
  }
  if (kind == 0) {
    return 0;
  }
  if (kind == 0x20) {
    if ((type & 0x18) == 8) {
      return 2;
    }
    if ((type & 0x18) == 0x10) {
      return 3;
    }
  }
  if (kind != 0x20) {
    return local_4;
  }
  if ((type & 0x18) != 0x18) {
    return local_4;
  }
  return 4;
}



