#include "decls.h"
#include "imports.h"

// entry: 004182f0
// name : displacement_aligned_for_type
// size : 109
// sig  : short displacement_aligned_for_type(gen_node * access, uchar disp)


short __cdecl displacement_aligned_for_type(gen_node *access,uchar disp)

{
  short ok;
  byte basic;
  byte category;
  byte type;
  
  ok = 1;
  type = access->type;
  category = type & 0xe0;
  if ((((category == 0x60) || (category == 0x80)) && ((type & 0x18) == 8)) ||
     (basic = type & 0xf8, basic == 8)) {
    if ((disp & 1) != 0) {
      ok = 0;
    }
  }
  else if ((((((category == 0x60) || (category == 0x80)) && ((type & 0x18) == 0x10)) ||
            ((basic == 0x10 || (basic == 0x18)))) || ((category == 0x20 || (category == 0x40)))) &&
          ((disp & 3) != 0)) {
    return 0;
  }
  return ok;
}



