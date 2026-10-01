#include "decls.h"
#include "imports.h"

// entry: 00419270
// name : check_value_range
// size : 141
// sig  : int check_value_range(uchar type, uint value)


int __cdecl check_value_range(uchar type,uint value)

{
  uint uVar1;
  int result;
  char size_code;
  
  uVar1 = 0;
  result = 0;
  if ((type & 0xf8) == 0) {
    size_code = '\0';
    uVar1 = 0xffffff00;
  }
  else if ((type & 0xf8) == 8) {
    size_code = '\b';
    uVar1 = 0xffff0000;
  }
  if (((type & 0xe0) == 0) && ((type & 4) != 0)) {
    if ((value & uVar1) != 0) {
      return 1;
    }
  }
  else {
    uVar1 = type_limit(0,(int)size_code);
    if ((int)uVar1 < (int)value) {
      return 1;
    }
    uVar1 = type_limit(1,(int)size_code);
    if ((int)value < (int)uVar1) {
      result = 2;
    }
  }
  return result;
}



