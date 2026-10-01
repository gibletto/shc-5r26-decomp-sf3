#include "decls.h"
#include "imports.h"

// entry: 0041fde0
// name : choose_float_register_pair
// size : 487
// sig  : short choose_float_register_pair(ushort excluded, short preferred)


short __cdecl choose_float_register_pair(ushort excluded,short preferred)

{
  unsigned char _frec_10[16];
#define pass (*(short *)(_frec_10 + 0))
#define local_e (*(short (*)[7])(_frec_10 + 2))
  ushort mask;
  short reg;
  short scan_last;
  short rank;
  int iVar1;
  short scan_step;
  char chosen;
  short rank_holder;
  
  mask = g_var_fpr_mask & 0xfff0;
  local_e[0] = -1;
  reg = 0;
  do {
    iVar1 = (int)reg;
    reg = reg + 1;
    local_e[iVar1 + 1] = -1;
  } while (reg < 6);
  pass = 0;
  do {
    if (local_e[0] != -1) goto LAB_0041ff68;
    if (pass == 1) {
      reg = 0x22;
      scan_last = 0x20;
      scan_step = -2;
    }
    else {
      reg = 0x24;
      scan_last = 0x2e;
      scan_step = 2;
    }
    while (((int)reg != (int)scan_step + (int)scan_last && (local_e[0] == -1))) {
      if (((int)(short)(excluded | mask) &
          (1 << ((char)reg - 0x1fU & 0x1f) | 1 << ((char)reg - 0x20U & 0x1f))) == 0) {
        rank = rank_register_pair_choice(reg + -0x20,preferred,g_fpr_contents);
        if (rank == 0) {
          local_e[0] = reg;
        }
        else if (((rank == 1) || (rank == 4)) || (rank == 5)) {
          rank_holder = local_e[rank];
          if (rank_holder != -1) {
            iVar1 = rank_holder * 0x18;
            if ((*(uint *)(&g_fpr_contents_stamp_by_pair + iVar1) <=
                 *(uint *)(&g_fpr_contents_stamp_by_pair + reg * 0x18)) ||
               (*(uint *)(&g_fpr_contents_stamp_by_pair_hi + iVar1) <=
                *(uint *)(&g_fpr_contents_stamp_by_pair_hi + reg * 0x18))) goto LAB_0041ff18;
          }
          local_e[rank] = reg;
        }
        else if (local_e[rank] == -1) {
          local_e[rank] = reg;
        }
      }
LAB_0041ff18:
      reg = reg + scan_step;
    }
    pass = pass + 1;
  } while (pass < 2);
  if (local_e[0] == -1) {
    reg = 0;
    do {
      if (local_e[reg + 1] != -1) {
        local_e[0] = local_e[reg + 1];
        break;
      }
      reg = reg + 1;
    } while (reg < 6);
LAB_0041ff68:
    if (local_e[0] == -1) {
      return -1;
    }
  }
  chosen = (char)local_e[0];
  invalidate_register_contents
            ((1 << ((char)local_e[0] - 0x20U & 0x1f) | 1 << ((char)local_e[0] - 0x1fU & 0x1f)) <<
             0x10);
  g_used_fpr_mask = g_used_fpr_mask | 1 << (chosen - 0x1fU & 0x1f) | 1 << (chosen - 0x20U & 0x1f);
  g_last_chosen_reg = chosen;
  return local_e[0];
#undef pass
#undef local_e
}



