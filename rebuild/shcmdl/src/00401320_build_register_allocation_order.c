#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 00401320
// name : build_register_allocation_order
// size : 157
// sig  : void build_register_allocation_order(void)


int __cdecl build_register_allocation_order(void)

{
  int iVar1;
  int iVar2;
  int lowest_freg;
  uchar *reserved_mask;
  int reserved;
  
  iVar1 = 0xe;
  reserved = 0;
  iVar2 = 4;
  reserved_mask = g_options->unknown_150;
  do {
    if ((*(uint *)reserved_mask & 1 << ((byte)iVar1 & 0x1f)) == 0) {
      (&g_gpr_alloc_order)[iVar2] = (byte)iVar1;
      iVar2 = iVar2 + 1;
    }
    else {
      reserved = reserved + 1;
      (&g_gpr_alloc_order)[g_int_reg_count - reserved] = 0;
    }
    iVar1 = iVar1 + -1;
  } while (7 < iVar1);
  lowest_freg = g_float_arg_regs + 0x14;
  iVar2 = 0x1f;
  g_int_reg_count = g_int_reg_count - reserved;
  reserved = 0;
  iVar1 = g_float_arg_regs;
  if (lowest_freg < 0x20) {
    do {
      if ((*(uint *)reserved_mask & 1 << ((byte)iVar2 & 0x1f)) == 0) {
        (&g_fpr_alloc_order)[iVar1] = (byte)iVar2;
        iVar1 = iVar1 + 1;
      }
      else {
        reserved = reserved + 1;
        (&g_fpr_alloc_order)[g_float_reg_count - reserved] = 0;
      }
      iVar2 = iVar2 + -1;
    } while (lowest_freg <= iVar2);
  }
  g_float_reg_count = g_float_reg_count - reserved;
  return;
}



