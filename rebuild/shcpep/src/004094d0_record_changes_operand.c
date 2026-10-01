#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 004094d0
// name : record_changes_operand
// size : 213
// sig  : uchar record_changes_operand(ea * operand, psd * rec)


uchar __cdecl record_changes_operand(ea *operand,psd *rec)

{
  uchar uVar1;
  psd_op op;
  
  uVar1 = '\0';
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_memchgchk_start__00425b54);
  }
  op = rec->op;
  if (((((op == OP_MOV) || (op == OP_AND)) || (op == OP_OR)) ||
      ((op == OP_XOR || (op == OP_NON_B0)))) && (rec->ea2 != (ea *)0x0)) {
    uVar1 = operands_equal(operand,rec->ea2);
  }
  if ((uVar1 == '\0') && (operand != (ea *)0x0)) {
    switch(operand->type & 0x1f) {
    case 1:
    case 2:
    case 5:
    case 6:
    case 0xf:
    case 0x10:
      uVar1 = operand->base;
      break;
    default:
      goto switchD_0040954e_caseD_3;
    case 8:
    case 10:
    case 0xb:
      uVar1 = operand->base;
      break;
    case 9:
    case 0xc:
      uVar1 = record_changes_register(rec,operand->base);
      if (uVar1 != '\0') goto switchD_0040954e_caseD_3;
      uVar1 = operand->index;
    }
    uVar1 = record_changes_register(rec,uVar1);
  }
switchD_0040954e_caseD_3:
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_memchgchk_end__rc___ld_00425b3c,(int)(char)uVar1);
  }
  return uVar1;
}



