#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00408b10
// name : operand_uses_register
// size : 654
// sig  : char operand_uses_register(psd * rec, uchar reg, char which)


char __cdecl operand_uses_register(psd *rec,uchar reg,char which)

{
  byte kind;
  ea *opnd;
  uint opnd_mask_lo;
  uint opnd_mask_hi;
  char uses;
  ea *reg_mask_lo;
  uint reg_mask_hi;
  psd_op op;
  char regno;
  
  opnd_mask_lo = 0;
  opnd_mask_hi = 0;
  uses = '\0';
  reg_mask_lo = (ea *)0x0;
  reg_mask_hi = 0;
  if ((char)reg < '\0') {
    if ('_' < (char)reg) goto code_r0x00408b53;
  }
  else if ((char)reg < '`') {
    reg_mask_lo = (ea *)g_reg_mask_table[(char)reg];
  }
  else {
code_r0x00408b53:
    reg_mask_hi = g_reg_mask_table[(char)reg];
  }
  op = rec->op;
  if ((((((op == OP_CTBL) || (op == OP_CENT)) || (op == OP_LINE)) ||
       ((op == OP_BBGN || (op == OP_BEND)))) || ((OP_BEND < op && (op < OP_NON_1C)))) ||
     (((op == OP_NON_10 || (op == OP_SWBGN)) || (op == OP_SWEND)))) {
    return '\0';
  }
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_refgchk_start__00425b14);
  }
  if (((byte)g_stage_flags & 4) != 0) {
    _printf(s_check_register_number___d_00425aa0,(int)(char)reg);
  }
  if (*(short *)(&g_op_is_macro + (uint)rec->op * 2) != 0) {
    uses = macro_record_references_register(rec,reg);
    goto LAB_00408d6e;
  }
  if (((which != '\x01') || (rec->op != OP_NON_CC)) ||
     ((reg != '\x10' && ((reg != ' ' && (reg != '0')))))) {
    if (which == '\x01') {
      opnd = rec->ea1;
    }
    else if (which == '\x02') {
      opnd = rec->ea2;
    }
    else {
      report_fatal_message(0,0,0x127a);
      opnd = reg_mask_lo;
    }
    if (((opnd == (ea *)0x0) || (kind = opnd->type & 0x1f, kind == 7)) || (kind == 0xd))
    goto LAB_00408d6e;
    if (kind == 10) {
      if (reg != 'k') goto LAB_00408d6e;
    }
    else if (kind == 0xb) {
LAB_00408d62:
      if (reg != 'b') goto LAB_00408d6e;
    }
    else if (kind == 0xc) {
      regno = opnd->index;
      if (regno < '\0') {
        if ('_' < regno) goto code_r0x00408d4c;
      }
      else if (regno < '`') {
        opnd_mask_lo = g_reg_mask_table[regno];
      }
      else {
code_r0x00408d4c:
        opnd_mask_hi = g_reg_mask_table[regno];
      }
      if ((((uint)reg_mask_lo & opnd_mask_lo) == 0) && ((reg_mask_hi & opnd_mask_hi) == 0))
      goto LAB_00408d62;
    }
    else {
      regno = opnd->base;
      if (regno < '\0') {
        if ('_' < regno) goto code_r0x00408cc6;
      }
      else if (regno < '`') {
        opnd_mask_lo = g_reg_mask_table[regno];
      }
      else {
code_r0x00408cc6:
        opnd_mask_hi = g_reg_mask_table[regno];
      }
      if ((((uint)reg_mask_lo & opnd_mask_lo) != 0) || ((reg_mask_hi & opnd_mask_hi) != 0))
      goto LAB_00408d69;
      if (kind != 9) goto LAB_00408d6e;
      regno = opnd->index;
      if (regno < '\0') {
        if ('_' < regno) goto code_r0x00408d0c;
      }
      else if (regno < '`') {
        opnd_mask_lo = opnd_mask_lo | g_reg_mask_table[regno];
      }
      else {
code_r0x00408d0c:
        opnd_mask_hi = opnd_mask_hi | g_reg_mask_table[regno];
      }
      if ((((uint)reg_mask_lo & opnd_mask_lo) == 0) && ((reg_mask_hi & opnd_mask_hi) == 0))
      goto LAB_00408d6e;
    }
  }
LAB_00408d69:
  uses = '\x01';
LAB_00408d6e:
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_refgchk_end__rc___d_00425afc,(int)uses);
  }
  return uses;
}



