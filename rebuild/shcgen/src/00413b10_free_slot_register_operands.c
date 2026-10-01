#include "decls.h"
#include "imports.h"

// entry: 00413b10
// name : free_slot_register_operands
// size : 207
// sig  : void free_slot_register_operands(short kind, ea * * operands)


int __cdecl free_slot_register_operands(short kind,ea **operands)

{
  switch(kind) {
  case 1:
    if (operands[2] != (ea *)0x0) {
      free_ea(operands[2]);
    }
    if (operands[3] != (ea *)0x0) {
      free_ea(operands[3]);
    }
    if (operands[4] != (ea *)0x0) {
      free_ea(operands[4]);
    }
    if (operands[5] != (ea *)0x0) {
      free_ea(operands[5]);
    }
    if (operands[6] != (ea *)0x0) {
      free_ea(operands[6]);
      return;
    }
    break;
  case 2:
    if (operands[2] != (ea *)0x0) {
      free_ea(operands[2]);
    }
    if (operands[3] != (ea *)0x0) {
      free_ea(operands[3]);
      return;
    }
    break;
  case 3:
  case 4:
    if (operands[2] != (ea *)0x0) {
      free_ea(operands[2]);
    }
    break;
  default:
    report_codegen_message(0x1237,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return;
  }
  return;
}



