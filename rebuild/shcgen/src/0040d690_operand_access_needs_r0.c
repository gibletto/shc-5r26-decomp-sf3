#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0040d690
// name : operand_access_needs_r0
// size : 306
// sig  : int operand_access_needs_r0(ea * operand, uchar type)


int __cdecl operand_access_needs_r0(ea *operand,uchar type)

{
  int sp_disp;
  uint label_symx;
  byte bVar1;
  int needs_r0;
  
  needs_r0 = 0;
  bVar1 = operand->type & 0x1f;
  if (((((bVar1 == 2) || (bVar1 == 8)) && (operand->base != 'l')) &&
      (operand->labels == (label_ref *)0x0)) &&
     (((((type & 0xf8) == 0 && (0 < operand->disp)) && (operand->disp < 0x10)) ||
      ((((type & 0xf8) == 8 && (1 < operand->disp)) && (operand->disp < 0x1f)))))) {
    return 1;
  }
  if (((bVar1 == 2) && (operand->base == 'l')) || ((bVar1 == 8 && (operand->base == 'l')))) {
    sp_disp = frame_operand_sp_displacement(operand);
    if (((((type & 0xf8) == 0) && (0 < sp_disp)) && (sp_disp < 0x10)) ||
       ((((type & 0xf8) == 8 && (1 < sp_disp)) && (sp_disp < 0x1f)))) {
      return 1;
    }
  }
  else if ((bVar1 == 0xd) &&
          ((((type & 0xe0) == 0 || ((type & 0xf8) == 0x40)) || ((type & 0xf8) == 0x28)))) {
    if (operand->labels == (label_ref *)0x0) {
      label_symx = 0;
    }
    else {
      label_symx = (uint)operand->labels->labno1;
    }
    if ((g_symbol_table[(label_symx ^ (int)label_symx >> 0x1f) - ((int)label_symx >> 0x1f)].attr & 3
        ) != 0) {
      if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
        bVar1 = 1;
      }
      else {
        bVar1 = -(g_request->cpu == 4) & 2;
      }
      if ((bVar1 == 0) || ((type & 0xf8) != 0x28)) {
        needs_r0 = 1;
      }
    }
  }
  return needs_r0;
}



