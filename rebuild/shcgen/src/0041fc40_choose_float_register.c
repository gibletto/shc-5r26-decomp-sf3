#include "decls.h"
#include "imports.h"

// entry: 0041fc40
// name : choose_float_register
// size : 406
// sig  : short choose_float_register(ushort excluded, short preferred)


short __cdecl choose_float_register(ushort excluded,short preferred)

{
  unsigned char _frec_10[16];
#define scan_step (*(short *)(_frec_10 + 0))
#define local_e (*(short (*)[7])(_frec_10 + 2))
  ushort mask;
  short reg;
  short scan_last;
  short rank;
  int slot;
  byte chosen;
  short best;
  short next_best;
  short rank_holder;
  
  mask = g_var_fpr_mask & 0xfff0;
  reg = 0;
  best = -1;
  do {
    slot = (int)reg;
    reg = reg + 1;
    local_e[slot + 1] = -1;
  } while (reg < 6);
  local_e[0] = 0;
  do {
    if (best != -1) goto LAB_0041fd9c;
    if (local_e[0] == 1) {
      scan_step = -1;
      reg = 0x13;
      scan_last = 0x10;
    }
    else {
      scan_step = 1;
      reg = 0x14;
      scan_last = 0x1f;
    }
    while (((int)reg != (int)scan_step + (int)scan_last && (best == -1))) {
      next_best = best;
      if (((int)(short)(excluded | mask) & 1 << ((char)reg - 0x10U & 0x1f)) == 0) {
        rank = rank_register_choice(reg + -0x10,preferred,g_fpr_contents);
        next_best = reg;
        if (rank != 0) {
          if (((rank == 1) || (rank == 4)) || (rank == 5)) {
            rank_holder = local_e[rank];
            if ((rank_holder == -1) ||
               (next_best = best,
               *(uint *)(&g_fpr_contents_stamp_by_reg + reg * 0x18) <
               *(uint *)(&g_fpr_contents_stamp_by_reg + rank_holder * 0x18))) {
              local_e[rank] = reg;
              next_best = best;
            }
          }
          else {
            next_best = best;
            if (local_e[rank] == -1) {
              local_e[rank] = reg;
            }
          }
        }
      }
      reg = reg + scan_step;
      best = next_best;
    }
    local_e[0] = local_e[0] + 1;
  } while (local_e[0] < 2);
  if (best == -1) {
    reg = 0;
    do {
      if (local_e[reg + 1] != -1) {
        best = local_e[reg + 1];
        break;
      }
      reg = reg + 1;
    } while (reg < 6);
LAB_0041fd9c:
    if (best == -1) {
      return -1;
    }
  }
  chosen = (byte)best;
  invalidate_register_contents(1 << (chosen & 0x1f));
  g_used_fpr_mask = g_used_fpr_mask | 1 << (chosen - 0x10 & 0x1f);
  g_last_chosen_reg = chosen;
  return best;
#undef scan_step
#undef local_e
}



