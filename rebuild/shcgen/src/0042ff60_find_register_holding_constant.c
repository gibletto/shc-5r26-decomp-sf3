#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0042ff60
// name : find_register_holding_constant
// size : 354
// sig  : short find_register_holding_constant(ea * value, uchar type)


short __cdecl find_register_holding_constant(ea *value,uchar type)

{
  byte fpu_mode;
  short sVar1;
  reg_content *contents;
  short reg;
  bool is_fpr;
  
  if ((value->type & 0x1f) != 7) {
    return -1;
  }
  if ((type & 0xf8) == 0x28) {
    if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
      fpu_mode = 1;
    }
    else {
      fpu_mode = -(g_request->cpu == 4) & 2;
    }
    if (fpu_mode != 0) {
      reg = 0;
      contents = g_fpr_contents;
      is_fpr = true;
      do {
        if (((g_fpr_contents[reg].flags & 0x40) != 0) && (g_fpr_contents[reg].value == value->disp))
        {
          if (g_fpr_contents[reg].u.labels == (label_ref *)0x0) {
            if (value->labels == (label_ref *)0x0) {
              sVar1 = 0;
            }
            else {
              sVar1 = value->labels->labno1;
            }
            if (sVar1 == 0) break;
          }
          sVar1 = label_lists_equal(g_fpr_contents[reg].u.labels,value->labels);
          if (sVar1 != 0) break;
        }
        reg = reg + 1;
      } while (reg < 4);
      goto LAB_00430075;
    }
  }
  contents = g_gpr_contents;
  reg = 0;
  is_fpr = false;
  do {
    if (((g_gpr_contents[reg].flags & 0x40) != 0) && (g_gpr_contents[reg].value == value->disp)) {
      if (g_gpr_contents[reg].u.labels == (label_ref *)0x0) {
        if (value->labels == (label_ref *)0x0) {
          sVar1 = 0;
        }
        else {
          sVar1 = value->labels->labno1;
        }
        if (sVar1 == 0) break;
      }
      sVar1 = label_lists_equal(g_gpr_contents[reg].u.labels,value->labels);
      if (sVar1 != 0) break;
    }
    reg = reg + 1;
  } while (reg < 4);
LAB_00430075:
  if (3 < reg) {
    return -1;
  }
  truncate_register_ranges_at_serial(reg,contents[reg].stamp,contents);
  g_content_hit = 1;
  if (!is_fpr) {
    g_content_hit = 1;
    return reg;
  }
  return reg + 0x10;
}



