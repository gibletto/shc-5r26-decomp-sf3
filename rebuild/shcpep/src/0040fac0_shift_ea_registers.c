#include "decls.h"
#include "imports.h"

// entry: 0040fac0
// name : shift_ea_registers
// size : 31
// sig  : void shift_ea_registers(ea * operand)


int __cdecl shift_ea_registers(ea *operand)

{
  operand->base = (&g_reg_remap_table)[operand->base];
  operand->index = (&g_reg_remap_table)[operand->index];
  return;
}



