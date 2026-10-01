#include "decls.h"
#include "imports.h"

// entry: 00422750
// name : classify_size_conversion
// size : 251
// sig  : int classify_size_conversion(uchar narrow_type, uchar op_type, uchar inner_type)


int __cdecl classify_size_conversion(uchar narrow_type,uchar op_type,uchar inner_type)

{
  int kind;
  int sign_b;
  int sign_a;
  
  kind = 0;
  if ((inner_type == 0xff) || (((inner_type ^ narrow_type) & 0xf8) == 0)) {
    if ((((narrow_type & 0xf8) == 0) && ((op_type & 0xe0) == 0)) ||
       (((narrow_type & 0xf8) == 8 && (((op_type & 0xf8) == 0x10 || ((op_type & 0xf8) == 0x18))))))
    {
      kind = 1;
    }
  }
  else if ((narrow_type & 0xf8) == 0) {
    if ((((op_type & 0xf8) == 0x10) || ((op_type & 0xf8) == 0x18)) && ((inner_type & 0xf8) == 8)) {
      kind = 3;
    }
  }
  else if (((narrow_type & 0xf8) == 8) &&
          ((((op_type & 0xf8) == 0x10 || ((op_type & 0xf8) == 0x18)) && ((inner_type & 0xf8) == 0)))
          ) {
    kind = 5;
  }
  if (kind != 0) {
    if (((narrow_type & 0xe0) != 0) || (sign_a = 1, (narrow_type & 4) == 0)) {
      sign_a = 0;
    }
    if (((op_type & 0xe0) != 0) || (sign_b = 1, (op_type & 4) == 0)) {
      sign_b = 0;
    }
    if (sign_a == sign_b) {
      if (inner_type == 0xff) {
        return 2;
      }
      if (((narrow_type & 0xe0) != 0) || (sign_a = 1, (narrow_type & 4) == 0)) {
        sign_a = 0;
      }
      if (((inner_type & 0xe0) != 0) || (sign_b = 1, (inner_type & 4) == 0)) {
        sign_b = 0;
      }
      if (sign_a == sign_b) {
        kind = kind + 1;
      }
    }
  }
  return kind;
}



