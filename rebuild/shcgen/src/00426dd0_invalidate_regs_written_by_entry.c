#include "decls.h"
#include "imports.h"

// entry: 00426dd0
// name : invalidate_regs_written_by_entry
// size : 443
// sig  : uint invalidate_regs_written_by_entry(ushort op, ea * opnd1, ea * opnd2, ea * opnd3)


uint __cdecl invalidate_regs_written_by_entry(ushort op,ea *opnd1,ea *opnd2,ea *opnd3)

{
  int labno;
  uint regs;
  uint mask;
  byte *written_bits;
  
  mask = 0;
  if ((op < 0x100) && ((&g_psd_op_template_info)[(uint)op * 2] != '\b')) {
    if ((&g_psd_op_written_operand)[op] == '\x01') {
      if ((opnd1 != (ea *)0x0) && ((opnd1->type & 0x1f) == 1)) {
        mask = ea_register_mask(opnd1);
      }
    }
    else if ((((&g_psd_op_written_operand)[op] == '\x02') && (opnd2 != (ea *)0x0)) &&
            ((opnd2->type & 0x1f) == 1)) {
      mask = ea_register_mask(opnd2);
    }
    goto switchD_00426e73_caseD_20;
  }
  switch((uint)op) {
  case 0x20:
  case 0x21:
  case 0x22:
    goto switchD_00426e73_caseD_20;
  case 0x23:
    if (opnd1 != (ea *)0x0) {
      if (opnd1->labels == (label_ref *)0x0) {
        labno = 0;
      }
      else {
        labno = (int)opnd1->labels->labno1;
      }
      mask = (uint)(byte)(&g_routine_clobbers)[labno];
    }
    if ((opnd2 != (ea *)0x0) && ((opnd2->type & 0x1f) == 1)) {
      regs = ea_register_mask(opnd2);
      mask = mask | regs;
    }
    break;
  case 0x24:
  case 0x25:
  case 0x26:
    goto switchD_00426e73_caseD_24;
  case 0x27:
  case 0x28:
  case 0x29:
  case 0x2a:
  case 0x2b:
  case 0x2c:
    if ((opnd2 != (ea *)0x0) && ((opnd2->type & 0x1f) == 1)) {
      mask = ea_register_mask(opnd2);
    }
switchD_00426e73_caseD_24:
    if ((opnd3 == (ea *)0x0) || ((opnd3->type & 0x1f) != 1)) goto switchD_00426e73_caseD_20;
    goto LAB_00426ee3;
  }
  if ((uint)((int)(op - 0x100) >> 8) < 0x3d) {
    written_bits = &g_macro_written_operands + ((ushort)(op - 0x100) >> 8);
    if ((((*written_bits & 0x80) != 0) && (opnd1 != (ea *)0x0)) && ((opnd1->type & 0x1f) == 1)) {
      regs = ea_register_mask(opnd1);
      mask = mask | regs;
    }
    if ((((*written_bits & 0x40) != 0) && (opnd2 != (ea *)0x0)) && ((opnd2->type & 0x1f) == 1)) {
      regs = ea_register_mask(opnd2);
      mask = mask | regs;
    }
    if ((((*written_bits & 0x20) != 0) && (opnd3 != (ea *)0x0)) && ((opnd3->type & 0x1f) == 1)) {
LAB_00426ee3:
      regs = ea_register_mask(opnd3);
      mask = mask | regs;
    }
  }
switchD_00426e73_caseD_20:
  invalidate_register_contents(mask);
  return mask;
}



