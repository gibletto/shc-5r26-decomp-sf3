#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040d690
// name : order_params_stack_then_register
// size : 715
// sig  : void order_params_stack_then_register(int func_symx, short * params)


int __cdecl order_params_stack_then_register(int func_symx,short *params)

{
  int iVar1;
  uint uVar2;
  uint words;
  int ofs;
  int iVar3;
  int last;
  int n;
  short *psVar4;
  uint uVar5;
  short *dst;
  char int_regs;
  char float_regs;
  int i;
  short reg_params [12];
  short param;
  byte ptype;
  
  iVar3 = (int)*(char *)((int)g_symtab[func_symx].info + 6);
  last = iVar3 + -1;
  iVar1 = 0;
  if (-1 < last) {
    ofs = 0;
    n = iVar3;
    psVar4 = params;
    do {
      ofs = ofs + 2;
      n = n + -1;
      *psVar4 = *(short *)(*(int *)((int)g_symtab[func_symx].info + 0xc) + -2 + ofs);
      iVar1 = iVar3;
      psVar4 = psVar4 + 1;
    } while (n != 0);
  }
  params[iVar1] = 0;
  uVar5 = (uint)((g_symtab[func_symx].flags & 2) != 0);
  if (((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) || (g_options->cpu == 4)) {
    iVar1 = g_float_arg_regs + 3;
    float_regs = (char)g_float_arg_regs;
  }
  else {
    float_regs = '\0';
    iVar1 = 7;
  }
  int_regs = '\x04';
  iVar3 = iVar1;
  if ((int)uVar5 <= last) {
    psVar4 = params + last;
    i = last;
    do {
      if ((int)float_regs + (int)int_regs == 0) break;
      if ((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) {
        param = *psVar4;
        ptype = g_symtab[param].type;
        if (((ptype & 0xe0) == 0x20) && ((ptype & 0x18) == 8)) {
          if (float_regs != '\0') {
            reg_params[iVar3] = param;
            iVar3 = iVar3 + -1;
            *psVar4 = -1;
            float_regs = float_regs + -1;
          }
        }
        else if (((ptype & 0xe0) == 0) || ((ptype & 0xf8) == 0x40)) goto joined_r0x0040d8bc;
      }
      else {
        param = *psVar4;
        if (g_options->cpu == 4) {
          ptype = g_symtab[param].type;
          if ((ptype & 0xe0) == 0x20) {
            if ((ptype & 0x18) == 8) {
              if (float_regs != '\0') {
                reg_params[iVar3] = param;
                iVar3 = iVar3 + -1;
                *psVar4 = -1;
                float_regs = float_regs + -1;
              }
            }
            else if (((ptype & 0x18) == 0x10) && ('\x01' < float_regs)) {
              reg_params[iVar3] = param;
              iVar3 = iVar3 + -1;
              float_regs = float_regs + -2;
              *psVar4 = -1;
            }
            goto LAB_0040d8cd;
          }
          if ((ptype & 0xe0) != 0) goto joined_r0x0040d8b5;
        }
        else {
          ptype = g_symtab[param].type;
          if (((ptype & 0xe0) != 0) && (((ptype & 0xe0) != 0x20 || ((ptype & 0x18) != 8)))) {
joined_r0x0040d8b5:
            if ((ptype & 0xf8) != 0x40) goto LAB_0040d8cd;
          }
        }
joined_r0x0040d8bc:
        if (int_regs != '\0') {
          reg_params[iVar3] = param;
          iVar3 = iVar3 + -1;
          *psVar4 = -1;
          int_regs = int_regs + -1;
        }
      }
LAB_0040d8cd:
      psVar4 = psVar4 + -1;
      i = i + -1;
    } while ((int)uVar5 <= i);
  }
  do {
    if (last < (int)uVar5) {
LAB_0040d92a:
      if (params[uVar5] != -1) {
        uVar5 = uVar5 + 1;
      }
      iVar3 = iVar3 + 1;
      if (iVar3 <= iVar1) {
        uVar2 = (iVar1 - iVar3) + 1;
        psVar4 = reg_params + iVar3;
        dst = params + uVar5;
        for (words = uVar2 >> 1; words != 0; words = words - 1) {
          *(undefined4 *)dst = *(undefined4 *)psVar4;
          psVar4 = psVar4 + 2;
          dst = dst + 2;
        }
        for (uVar5 = (uint)((uVar2 & 1) != 0); uVar5 != 0; uVar5 = uVar5 - 1) {
          *dst = *psVar4;
          psVar4 = psVar4 + 1;
          dst = dst + 1;
        }
      }
      return;
    }
    psVar4 = params + uVar5;
    dst = psVar4;
    uVar2 = uVar5;
    if (*psVar4 == -1) {
      for (; ((int)uVar2 <= last && (*dst == -1)); dst = dst + 1) {
        uVar2 = uVar2 + 1;
      }
      if (last < (int)uVar2) goto LAB_0040d92a;
      *psVar4 = params[uVar2];
      params[uVar2] = -1;
    }
    uVar5 = uVar5 + 1;
  } while( true );
}



