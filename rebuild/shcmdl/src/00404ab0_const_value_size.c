#include "decls.h"
#include "imports.h"

// entry: 00404ab0
// name : const_value_size
// size : 38
// sig  : int const_value_size(int type_class)


int __cdecl const_value_size(int type_class)

{
  if (type_class == 0x30) {
    return 8;
  }
  if (type_class != 0x38) {
    if (type_class != 0x40) {
      return 4;
    }
    return 4;
  }
  return 0xc;
}



