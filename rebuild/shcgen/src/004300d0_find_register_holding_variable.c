#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_r0_variable
#define g_r0_variable (*(short * *)(g_sd + 0x1f9a8))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 004300d0
// name : find_register_holding_variable
// size : 333
// sig  : short find_register_holding_variable(gen_node * node)


short __cdecl find_register_holding_variable(gen_node *node)

{
  byte fpu_mode;
  short lreg_no;
  reg_content *contents;
  short reg;
  bool is_fpr;
  ushort lreg;
  reg_content *slot;
  byte type;
  
  type = node->type;
  if ((type & 0xf8) == 0x28) {
    if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
      fpu_mode = 1;
    }
    else {
      fpu_mode = -(g_request->cpu == 4) & 2;
    }
    if (fpu_mode != 0) {
      is_fpr = true;
      contents = g_fpr_contents;
      goto LAB_00430135;
    }
  }
  is_fpr = false;
  contents = g_gpr_contents;
LAB_00430135:
  lreg = node->lreg;
  lreg_no = (lreg ^ (short)lreg >> 0xf) - ((short)lreg >> 0xf);
  if (lreg == 0) {
    reg = 0;
    do {
      slot = contents + reg;
      if ((((slot->u).lreg == 0) && ((slot->flags & 0x40) == 0)) &&
         (((int)node->symx == slot->value && (slot->type == type)))) break;
      reg = reg + 1;
    } while (reg < 4);
  }
  else {
    reg = 0;
    do {
      slot = contents + reg;
      if ((((contents[reg].u.lreg == lreg_no) && ((slot->flags & 0x40) == 0)) &&
          ((int)node->symx == slot->value)) && (slot->type == type)) break;
      reg = reg + 1;
    } while (reg < 4);
  }
  if (reg < 4) {
    if (((g_r0_variable == (short *)0x0) || (node->symx != *g_r0_variable)) ||
       ((g_r0_variable[1] != lreg_no || ((reg != 0 || ((contents->flags & 0x20) == 0)))))) {
      truncate_register_ranges_at_serial(reg,contents[reg].stamp,contents);
    }
    g_content_hit = 1;
    if (is_fpr) {
      reg = reg + 0x10;
    }
    return reg;
  }
  return -1;
}



