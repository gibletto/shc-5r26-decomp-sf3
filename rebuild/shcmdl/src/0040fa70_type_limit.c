#include "decls.h"
#include "imports.h"

// entry: 0040fa70
// name : type_limit
// size : 130
// sig  : uint type_limit(int want_min, int type)


uint __cdecl type_limit(int want_min,int type)

{
  uint limit;
  
  limit = 0;
  switch(type) {
  case 0:
    return (-(uint)(want_min == 0) & 0xff) - 0x80;
  case 4:
    return -(uint)(want_min == 0) & 0xff;
  case 8:
    return (-(uint)(want_min == 0) & 0xffff) - 0x8000;
  case 0xc:
    return -(uint)(want_min == 0) & 0xffff;
  case 0x10:
    return 0x80000000 - (want_min == 0);
  case 0x14:
  case 0x40:
    return -(uint)(want_min == 0);
  case 0x18:
    return 0x80000000 - (want_min == 0);
  case 0x1c:
    limit = -(uint)(want_min == 0);
  }
  return limit;
}



