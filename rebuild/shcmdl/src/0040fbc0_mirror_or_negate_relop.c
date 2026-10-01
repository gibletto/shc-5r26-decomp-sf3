#include "decls.h"
#include "imports.h"

// entry: 0040fbc0
// name : mirror_or_negate_relop
// size : 104
// sig  : char mirror_or_negate_relop(il_op op, int negate)


char __cdecl mirror_or_negate_relop(il_op op,int negate)

{
  char result;
  
  result = -1;
  switch(op) {
  case IL_EQ:
    return (-(negate == 1) & 0x62U) - 1;
  case IL_NE:
    return (-(negate == 1) & 0x61U) - 1;
  case IL_LT:
    return (negate == 1) + 'f';
  case IL_LE:
    return 'g' - (negate == 1);
  case IL_GT:
    return (negate == 1) + 'd';
  case IL_GE:
    result = 'e' - (negate == 1);
  }
  return result;
}



