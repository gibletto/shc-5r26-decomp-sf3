#include "decls.h"
#include "imports.h"
int shcgen_knob_tst_r0(void);
int shcgen_knob_mul_l(void);
void regtrace_site(int site, char *node);
char regtrace_chooser_enter(char ascending, unsigned ret);
void regtrace_chooser_exit(unsigned short p1, unsigned short p2, char p3, short *slots, int chosen);
void regtrace_function(char *rec);

// entry: 0041fa30
// name : choose_general_register
// size : 520
// sig  : short choose_general_register(ushort excluded, ushort preferred, char ascending)


short __cdecl choose_general_register(ushort excluded,ushort preferred,char ascending)

{
  unsigned char _frec_10[16];
#define pass (*(short *)(_frec_10 + 0))
#define local_e (*(short (*)[7])(_frec_10 + 2))
  ushort mask;
  short reg;
  short scan_last;
  short rank;
  ushort extra_excluded;
  int slot;
  short scan_step;
  byte chosen;
  short rank_holder;
  
  { unsigned ra_; __asm { mov eax,[ebp+4] } __asm { mov ra_,eax } ascending = regtrace_chooser_enter(ascending,ra_); }
  mask = g_var_gpr_mask & 0xfff0;
  local_e[0] = -1;
  extra_excluded = (ushort)g_chooser_extra_excluded;
  reg = 0;
  do {
    slot = (int)reg;
    reg = reg + 1;
    local_e[slot + 1] = -1;
  } while (reg < 6);
  if (g_r0_variable != 0) {
    g_last_chosen_reg = '\0';
    g_avoid_reg_mask = 1;
  }
  pass = 0;
  do {
    if (local_e[0] != -1) goto LAB_0041fbe3;
    if (pass == 1) {
      if (g_r0_variable == 0) {
        if (ascending == '\x01') {
          reg = 0;
          scan_last = 3;
          goto LAB_0041fae9;
        }
        reg = 3;
        scan_last = 0;
        scan_step = -1;
      }
      else {
        reg = 3;
        scan_last = 0;
        scan_step = -1;
        if ((preferred & 1) != 0) {
          preferred = preferred & 0xfffe;
        }
      }
    }
    else {
      reg = 4;
      scan_last = 0xe;
LAB_0041fae9:
      scan_step = 1;
    }
    while (((int)reg != (int)scan_last + (int)scan_step && (local_e[0] == -1))) {
      if (((int)(short)(excluded | mask | extra_excluded) & 1 << ((byte)reg & 0x1f)) == 0) {
        rank = rank_register_choice(reg,preferred,g_gpr_contents);
        if (rank == 0) {
          local_e[0] = reg;
        }
        else if (((rank == 1) || (rank == 4)) || (rank == 5)) {
          rank_holder = local_e[rank];
          if ((rank_holder == -1) || (g_gpr_contents[reg].stamp < g_gpr_contents[rank_holder].stamp)
             ) {
            local_e[rank] = reg;
          }
        }
        else if (local_e[rank] == -1) {
          local_e[rank] = reg;
        }
      }
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
LAB_0041fbe3:
    if (local_e[0] == -1) goto LAB_0041fc19;
  }
  chosen = (byte)local_e[0];
  mask = 1 << ((byte)local_e[0] & 0x1f);
  invalidate_register_contents((int)(short)mask);
  g_used_gpr_mask = g_used_gpr_mask | mask;
  g_last_chosen_reg = chosen;
LAB_0041fc19:
  if (local_e[0] == 0) {
    g_r0_used = 1;
  }
  regtrace_chooser_exit(excluded,preferred,ascending,local_e,local_e[0]);
  return local_e[0];
#undef pass
#undef local_e
}



