#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00408120
// name : record_changes_register
// size : 642
// sig  : uchar record_changes_register(psd * rec, uchar reg)


uchar __cdecl record_changes_register(psd *rec,uchar reg)

{
  char cVar1;
  byte ea1_kind;
  byte ea2_kind;
  byte changed;
  psd_op op;
  
  ea2_kind = 0;
  ea1_kind = 0;
  changed = 0;
  op = rec->op;
  if (((((op == OP_CTBL) || (op == OP_CENT)) || (op == OP_LINE)) ||
      ((op == OP_BBGN || (op == OP_BEND)))) ||
     ((op == OP_NON_10 || ((OP_BEND < op && (op < OP_NON_1C)))))) {
    return '\0';
  }
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_regchgchk_start__00425abc);
  }
  if (((byte)g_stage_flags & 4) != 0) {
    _printf(s_check_register_number___d_00425aa0,(int)(char)reg);
  }
  if (*(short *)(&g_op_is_macro + (uint)rec->op * 2) != 0) {
    changed = macro_record_changes_register(rec,reg);
    goto switchD_00408324_caseD_70;
  }
  if (rec->ea1 != (ea *)0x0) {
    ea1_kind = rec->ea1->type & 0x1f;
  }
  if (rec->ea2 != (ea *)0x0) {
    ea2_kind = rec->ea2->type & 0x1f;
  }
  if (((ea1_kind != 0) &&
      (((ea1_kind == 3 || (ea1_kind == 4)) &&
       (cVar1 = operand_uses_register(rec,reg,'\x01'), cVar1 == '\x01')))) ||
     ((ea2_kind != 0 &&
      (((ea2_kind == 3 || (ea2_kind == 4)) &&
       (cVar1 = operand_uses_register(rec,reg,'\x02'), cVar1 == '\x01')))))) {
    changed = 1;
    goto switchD_00408324_caseD_70;
  }
  if ((ea1_kind == 0) || (ea1_kind != 1)) {
    if (ea2_kind != 0) {
      if (ea2_kind == 1) goto LAB_0040826c;
      goto LAB_004082a9;
    }
  }
  else {
LAB_0040826c:
    if ((*(short *)(&g_op_dest_operand + (uint)rec->op * 2) == 1) && (ea1_kind == 1)) {
      cVar1 = '\x01';
    }
    else {
      if ((*(short *)(&g_op_dest_operand + (uint)rec->op * 2) != 2) || (ea2_kind != 1))
      goto LAB_004082a9;
      cVar1 = '\x02';
    }
    changed = operand_uses_register(rec,reg,cVar1);
LAB_004082a9:
    if ((ea2_kind != 0) &&
       (((((((ea2_kind == 5 && (rec->op == OP_LDC)) || ((ea2_kind == 6 && (rec->op == OP_LDS)))) ||
           ((ea2_kind == 0xf && (rec->op == OP_LDS)))) ||
          ((ea2_kind == 0x10 && (rec->op == OP_LDS)))) ||
         ((ea2_kind == 0xf && ((rec->op == OP_NON_DD || (rec->op == OP_NON_DF)))))) ||
        ((ea2_kind == 0xf && (rec->op == OP_NON_B5)))))) {
      changed = operand_uses_register(rec,reg,'\x02');
    }
  }
  switch(rec->op) {
  case OP_MUL:
    if (reg == 'e') {
      changed = 1;
    }
    break;
  case OP_DT:
    if (reg == 'a') {
      changed = 1;
    }
    break;
  case OP_RTE:
    if ((reg == 'k') || (reg == 'a')) {
      changed = 1;
    }
    break;
  case OP_BSR:
  case OP_JSR:
    if (reg == 'f') {
      changed = 1;
    }
  case OP_BF:
  case OP_BT:
  case OP_BRA:
  case OP_JMP:
  case OP_RTS:
  case OP_BT_S:
  case OP_BF_S:
  case OP_BSRF:
  case OP_BRAF:
  case OP_TRAPA:
    if (reg == 'k') {
      changed = changed | 1;
    }
  }
switchD_00408324_caseD_70:
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_regchgchk_end__rc___d_00425a88,(int)(char)changed);
  }
  return changed;
}



