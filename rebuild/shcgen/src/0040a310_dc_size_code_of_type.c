#include "decls.h"
#include "imports.h"

// entry: 0040a310
// name : dc_size_code_of_type
// size : 81
// sig  : short dc_size_code_of_type(uchar type)


short __cdecl dc_size_code_of_type(uchar type)

{
  byte type_class;
  
  type_class = type & 0xe0;
  if ((((type_class == 0x60) || (type_class == 0x80)) && ((type & 0x18) == 0)) ||
     ((type & 0xf8) == 0)) {
    return 0;
  }
  if ((((type_class != 0x60) && (type_class != 0x80)) || ((type & 0x18) != 8)) &&
     ((type & 0xf8) != 8)) {
    return 2;
  }
  return 1;
}



