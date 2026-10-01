#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0040f840
// name : assign_argument_registers
// size : 595
// sig  : void assign_argument_registers(gen_node * args, int skip)


int __cdecl assign_argument_registers(gen_node *args,int skip)

{
  ushort *puVar1;
  short sVar2;
  int arg_count;
  gen_node *arg;
  byte bVar3;
  byte fpu_kind;
  char pair_reg;
  node_desc *desc;
  ushort gpr_bit;
  ushort fpr_bit;
  ushort free_fprs;
  ushort pair_mask;
  short gprs_left;
  ushort free_gprs;
  short fprs_left;
  int stacked_count;
  bool found_pair;
  
  arg_count = count_operands(args);
  sVar2 = args->parent->call_06;
  if ((sVar2 == 0) || ((args->parent->val3 & 1) == 0)) {
    stacked_count = 0;
  }
  else {
    stacked_count = arg_count - sVar2;
  }
  fpr_bit = 1;
  gpr_bit = 1;
  free_gprs = 0xf0;
  gprs_left = 4;
  skip = (arg_count - skip) + -1;
  free_fprs = ((1 << (g_request->scratch_bank_reg_count & 0x1fU)) + -1) * 0x10;
  fprs_left = (short)g_request->scratch_bank_reg_count;
  if (0 < skip) {
    pair_mask = (ushort)stacked_count;
    do {
      arg = nth_operand(args,skip);
      if (arg == (gen_node *)0x0) {
        return;
      }
      if (stacked_count < skip) {
        sVar2 = g_request->cpu;
        if ((sVar2 != 2) || (bVar3 = 1, g_request->fpu_mode != '\x03')) {
          bVar3 = -(sVar2 == 4) & 2;
        }
        if ((((bVar3 == 0) || ((arg->type & 0xf8) != 0x28)) || (args->desc->builtin == '\x1c')) ||
           (fprs_left == 0)) {
          bVar3 = arg->type;
          if ((((bVar3 & 0xe0) == 0) || ((bVar3 & 0xf8) == 0x28)) || ((bVar3 & 0xf8) == 0x40)) {
            if ((sVar2 != 2) || (fpu_kind = 1, g_request->fpu_mode != '\x03')) {
              fpu_kind = -(sVar2 == 4) & 2;
            }
            if ((fpu_kind != 0) && ((bVar3 & 0xf8) == 0x28)) goto LAB_0040f9bd;
LAB_0040f9c9:
            if (gprs_left != 0) {
              for (; (free_gprs & gpr_bit) == 0; gpr_bit = gpr_bit * 2) {
              }
              free_gprs = free_gprs ^ gpr_bit;
              gprs_left = gprs_left + -1;
              arg->desc->target_regs = gpr_bit;
              g_used_gpr_mask = g_used_gpr_mask | gpr_bit;
              goto LAB_0040fa6c;
            }
          }
          else {
LAB_0040f9bd:
            if (((bVar3 & 0xe0) == 0x80) || ((bVar3 & 0xf8) == 0x48)) goto LAB_0040f9c9;
          }
          found_pair = false;
          if (((sVar2 == 4) && ((bVar3 & 0xf8) == 0x30)) && (1 < fprs_left)) {
            pair_mask = 0x30;
            pair_reg = ' ';
            do {
              if ((~free_fprs & pair_mask) == 0) {
                found_pair = true;
                break;
              }
              pair_mask = pair_mask << 2;
              pair_reg = pair_reg + '\x02';
            } while (pair_reg < '+');
          }
          desc = arg->desc;
          if (!found_pair) goto LAB_0040fa68;
          free_fprs = free_fprs ^ pair_mask;
          fprs_left = fprs_left + -2;
          desc->ftarget_regs = pair_mask;
          g_used_fpr_mask = g_used_fpr_mask | pair_mask;
        }
        else {
          for (; (free_fprs & fpr_bit) == 0; fpr_bit = fpr_bit * 2) {
          }
          free_fprs = free_fprs ^ fpr_bit;
          fprs_left = fprs_left + -1;
          arg->desc->ftarget_regs = fpr_bit;
          g_used_fpr_mask = g_used_fpr_mask | fpr_bit;
        }
      }
      else {
        desc = arg->desc;
LAB_0040fa68:
        desc->flags2 = desc->flags2 | 8;
      }
LAB_0040fa6c:
      skip = skip + -1;
      puVar1 = &arg->desc->need_regs;
      *puVar1 = *puVar1 | arg->next->desc->need_regs;
    } while (0 < skip);
  }
  return;
}



