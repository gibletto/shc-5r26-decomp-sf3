#include "decls.h"
#include "imports.h"

// entry: 0041ffd0
// name : rank_register_choice
// size : 162
// sig  : short rank_register_choice(short reg, short preferred, reg_content * contents)


short __cdecl rank_register_choice(short reg,short preferred,reg_content *contents)

{
  short rank;
  uint bit;
  int reg_id;
  
  bit = 1 << ((byte)reg & 0x1f);
  if ((bit & (int)preferred) != 0) {
    if ((reg < 4) && (((contents[reg].flags & 0x40) != 0 || (contents[reg].value != 0)))) {
      return 1;
    }
    return 0;
  }
  if (3 < reg) {
    return 6;
  }
  reg_id = (int)reg;
  rank = 2;
  if (((contents[reg_id].flags & 0x40) != 0) || (contents[reg_id].value != 0)) {
    rank = 4;
  }
  if (contents == g_fpr_contents) {
    reg_id = reg_id + 0x10;
  }
  if (g_last_chosen_reg == reg_id) {
    return rank + 1;
  }
  if ((contents != g_fpr_contents) && ((bit & (int)g_avoid_reg_mask) != 0)) {
    rank = rank + 1;
  }
  return rank;
}



