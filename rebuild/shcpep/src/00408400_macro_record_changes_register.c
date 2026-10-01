#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0x5bf0))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00408400
// name : macro_record_changes_register
// size : 1634
// sig  : char macro_record_changes_register(psd * rec, uchar reg)


/* WARNING: Type propagation algorithm not settling */

char __cdecl macro_record_changes_register(psd *rec,uchar reg)

{
  byte mov_dir;
  uint preserved;
  bool changed;
  uint rec_mask_lo;
  uint rec_mask_hi;
  uint reg_mask_lo;
  uint reg_mask_hi;
  short labno;
  char regno;
  
  rec_mask_lo = 0;
  rec_mask_hi = 0;
  reg_mask_lo = 0;
  reg_mask_hi = 0;
  if ((char)reg < '\0') {
    if ('_' < (char)reg) goto code_r0x0040843d;
  }
  else if ((char)reg < '`') {
    reg_mask_lo = g_reg_mask_table[(char)reg];
  }
  else {
code_r0x0040843d:
    reg_mask_hi = g_reg_mask_table[(char)reg];
  }
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_mcrrgchk_start__00425ae8);
  }
  changed = false;
  switch(rec->op) {
  case OP_CASEJMP:
    if ((reg != '\0') && (reg != '\x01')) goto switchD_00408482_caseD_12;
    goto LAB_00408a38;
  default:
    goto switchD_00408482_caseD_12;
  case OP_ENTER:
    if ((reg != '\0') && (reg != '\x0f')) goto switchD_00408482_caseD_12;
    goto LAB_00408a38;
  case OP_EXIT:
  case OP_RETURN:
    if ((('\0' < (char)reg) && ((char)reg < '\x0f')) || (('\x10' < (char)reg && ((char)reg < ' '))))
    {
      if ((char)reg < ' ') {
        preserved = g_current_request->reg_mask_150 & 1 << (reg & 0x1f);
      }
      else if ((char)reg < '/') {
        preserved = (1 << (reg - 0xf & 0x1f) | 1 << (reg - 0x10 & 0x1f)) &
                    g_current_request->reg_mask_150;
      }
      else {
        preserved = 0;
      }
      if (preserved != 0) goto switchD_00408482_caseD_12;
      changed = true;
    }
    if ((('!' < (char)reg) && ((char)reg < '/')) || (('3' < (char)reg && ((char)reg < '=')))) {
      changed = true;
    }
    if ((reg == '\x01') || (reg == '\x0f')) goto LAB_00408a38;
    goto joined_r0x00408a36;
  case OP_CALL:
    labno = rec->ea1->labels->labno1;
    if ((labno == 0x49) || (labno == 0x4a)) {
      if (((char)reg < '\0') || ('\a' < (char)reg)) goto switchD_00408482_caseD_24;
      goto LAB_00408a38;
    }
    if (0xb6 < labno) goto switchD_00408482_caseD_24;
    switch(reg) {
    case '\0':
      changed = (bool)(&g_runtime_call_changes_r0)[labno];
      break;
    case '\x02':
      if ((labno != 0x11) && (labno != 0x12)) break;
      goto LAB_004085d7;
    case '\x10':
    case ' ':
    case '0':
      if ((labno == 0xb2) || (labno == 0xb3)) goto LAB_004085d7;
      goto joined_r0x004085d5;
    case '\x11':
joined_r0x004085d5:
      if (labno == 0xb5) {
LAB_004085d7:
        changed = true;
      }
    }
    if (changed != false) goto switchD_00408482_caseD_12;
switchD_00408482_caseD_24:
    regno = rec->tmp;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x00408a07;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x00408a07:
      rec_mask_hi = g_reg_mask_table[regno];
    }
    if (((rec_mask_lo & reg_mask_lo) != 0) || ((rec_mask_hi & reg_mask_hi) != 0)) {
      changed = true;
    }
    if (reg != 'k') {
joined_r0x00408a36:
      if (reg != 'f') goto switchD_00408482_caseD_12;
    }
    goto LAB_00408a38;
  case OP_JUMP:
  case OP_JUMPT:
  case OP_JUMPF:
    goto switchD_00408482_caseD_24;
  case OP_MOV_LOC:
    mov_dir = rec->misc & 0x80;
    if (mov_dir == 0x80) {
      regno = rec->tmp;
      if (regno < '\0') {
        if ('_' < regno) goto code_r0x0040864a;
      }
      else if (regno < '`') {
        rec_mask_lo = g_reg_mask_table[regno];
      }
      else {
code_r0x0040864a:
        rec_mask_hi = g_reg_mask_table[regno];
      }
      if (((rec_mask_lo & reg_mask_lo) != 0) || ((rec_mask_hi & reg_mask_hi) != 0)) {
        changed = true;
      }
    }
    if (mov_dir != 0) goto switchD_00408482_caseD_12;
    regno = rec->tmp;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x004086a0;
    }
    else if (regno < '`') {
      rec_mask_lo = rec_mask_lo | g_reg_mask_table[regno];
    }
    else {
code_r0x004086a0:
      rec_mask_hi = rec_mask_hi | g_reg_mask_table[regno];
    }
    regno = rec->ea2->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x004086dc;
    }
    else if (regno < '`') {
      rec_mask_lo = rec_mask_lo | g_reg_mask_table[regno];
    }
    else {
code_r0x004086dc:
      rec_mask_hi = rec_mask_hi | g_reg_mask_table[regno];
    }
    break;
  case OP_MOVA_LC:
    regno = rec->ea2->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x00408735;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x00408735:
      rec_mask_hi = g_reg_mask_table[regno];
    }
    goto joined_r0x004087a0;
  case OP_MOVA_PC:
    regno = rec->ea2->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x0040878a;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x0040878a:
      rec_mask_hi = g_reg_mask_table[regno];
    }
joined_r0x004087a0:
    if ((rec_mask_lo & reg_mask_lo) != 0) goto LAB_00408a38;
    goto joined_r0x004089f4;
  case OP_MOVI:
    regno = rec->ea2->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x004087df;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x004087df:
      rec_mask_hi = g_reg_mask_table[regno];
    }
    break;
  case OP_MOVA_FC:
    regno = rec->tmp;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x00408831;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x00408831:
      rec_mask_hi = g_reg_mask_table[regno];
    }
    regno = rec->ea2->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x00408869;
    }
    else if (regno < '`') {
      rec_mask_lo = rec_mask_lo | g_reg_mask_table[regno];
    }
    else {
code_r0x00408869:
      rec_mask_hi = rec_mask_hi | g_reg_mask_table[regno];
    }
    break;
  case OP_NON_2C:
    regno = rec->tmp;
    changed = regno != '\0' && reg == 'g';
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x004088cd;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x004088cd:
      rec_mask_hi = g_reg_mask_table[regno];
    }
    regno = rec->ea2->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x00408905;
    }
    else if (regno < '`') {
      rec_mask_lo = rec_mask_lo | g_reg_mask_table[regno];
    }
    else {
code_r0x00408905:
      rec_mask_hi = rec_mask_hi | g_reg_mask_table[regno];
    }
    break;
  case OP_NON_2E:
    regno = rec->ea1->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x0040895e;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x0040895e:
      rec_mask_hi = g_reg_mask_table[regno];
    }
    regno = rec->ea2->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x00408996;
    }
    else if (regno < '`') {
      rec_mask_lo = rec_mask_lo | g_reg_mask_table[regno];
    }
    else {
code_r0x00408996:
      rec_mask_hi = rec_mask_hi | g_reg_mask_table[regno];
    }
    rec_mask_lo = rec_mask_lo | g_reg_mask_table[0x30] | g_reg_mask_table[0x34] |
                  g_reg_mask_table[0x38] | g_reg_mask_table[0x3c];
    rec_mask_hi = rec_mask_hi | g_reg_mask_table[0x68];
    break;
  case OP_NON_30:
    if (reg != '`') goto switchD_00408482_caseD_12;
    goto LAB_00408a38;
  }
  if ((rec_mask_lo & reg_mask_lo) == 0) {
joined_r0x004089f4:
    if ((rec_mask_hi & reg_mask_hi) == 0) goto switchD_00408482_caseD_12;
  }
LAB_00408a38:
  changed = true;
switchD_00408482_caseD_12:
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_mcrrgchk_end__rc___d_00425ad0,(int)changed);
  }
  return changed;
}



