#include "decls.h"
#include "imports.h"

// entry: 00420080
// name : rank_register_pair_choice
// size : 192
// sig  : short rank_register_pair_choice(short reg, short preferred, reg_content * contents)


short __cdecl rank_register_pair_choice(short reg,short preferred,reg_content *contents)

{
  short rank;
  short high_reg;
  
  high_reg = reg + 1;
  if ((((int)preferred & 1 << ((byte)reg & 0x1f)) == 0) ||
     (((int)preferred & 1 << ((byte)high_reg & 0x1f)) == 0)) {
    if (3 < reg) {
      return 6;
    }
    rank = 2;
    if ((((contents[reg].flags & 0x40) != 0) || ((contents[high_reg].flags & 0x40) != 0)) ||
       (contents[reg].value != 0)) {
      rank = 4;
    }
    if ((int)g_last_chosen_reg - (int)reg == 0x20) {
      rank = rank + 1;
    }
    return rank;
  }
  if ((reg < 4) &&
     ((((contents[reg].flags & 0x40) != 0 || ((contents[high_reg].flags & 0x40) != 0)) ||
      ((contents[reg].value != 0 || (contents[high_reg].value != 0)))))) {
    return 1;
  }
  return 0;
}



