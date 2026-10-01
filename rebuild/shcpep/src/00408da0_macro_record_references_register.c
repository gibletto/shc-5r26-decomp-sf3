#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0x5bf0))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00408da0
// name : macro_record_references_register
// size : 1655
// sig  : char macro_record_references_register(psd * rec, uchar reg)


/* WARNING: Type propagation algorithm not settling */

char __cdecl macro_record_references_register(psd *rec,uchar reg)

{
  byte mov_dir;
  uint rec_mask_lo;
  uint rec_mask_hi;
  uint uVar1;
  bool has_tmp;
  bool refs;
  uint reg_mask_hi;
  int disp;
  short labno;
  char regno;
  
  rec_mask_lo = 0;
  rec_mask_hi = 0;
  uVar1 = 0;
  reg_mask_hi = 0;
  if ((char)reg < '\0') {
    if ('_' < (char)reg) goto code_r0x00408dd4;
  }
  else if ((char)reg < '`') {
    uVar1 = g_reg_mask_table[(char)reg];
  }
  else {
code_r0x00408dd4:
    reg_mask_hi = g_reg_mask_table[(char)reg];
  }
  refs = false;
  switch(rec->op) {
  case OP_CASEJMP:
    if ((reg != '\0') && (reg != '\x01')) goto switchD_00408e11_caseD_12;
    goto LAB_004093ea;
  default:
    goto switchD_00408e11_caseD_12;
  case OP_ENTER:
    if (reg != '\0') {
joined_r0x00408ed2:
      if (reg != '\x0f') goto switchD_00408e11_caseD_12;
    }
    goto LAB_004093ea;
  case OP_EXIT:
  case OP_RETURN:
    if (((char)reg < '\b') || ('\x0e' < (char)reg)) {
      if (((g_current_request->scratch_bank_reg_count + 0x14 <= (int)(char)reg) && ((char)reg < ' ')
          ) || ((g_current_request->scratch_bank_reg_count + 0x24 <= (int)(char)reg &&
                ((char)reg < '/')))) goto LAB_00408e75;
LAB_00408e92:
      uVar1 = 0;
      if ((char)reg < '/') {
        uVar1 = (1 << (reg - 0xf & 0x1f) | 1 << (reg - 0x10 & 0x1f)) &
                g_current_request->reg_mask_150;
      }
    }
    else {
LAB_00408e75:
      if ('\x1f' < (char)reg) goto LAB_00408e92;
      uVar1 = g_current_request->reg_mask_150 & 1 << (reg & 0x1f);
    }
    if (uVar1 != 0) goto switchD_00408e11_caseD_12;
    if (reg != '\x01') goto joined_r0x00408ed2;
    goto LAB_004093ea;
  case OP_CALL:
    labno = rec->ea1->labels->labno1;
    if ((labno == 0x49) || (labno == 0x4a)) {
      if (((char)reg < '\x04') || ('\a' < (char)reg)) goto switchD_00408e11_caseD_24;
      goto LAB_004093ea;
    }
    if (0xb6 < labno) goto switchD_00408e11_caseD_24;
    switch(reg) {
    case '\0':
      refs = (bool)(&g_runtime_call_reads_r0)[labno];
      break;
    case '\x01':
      refs = (bool)(&g_runtime_call_reads_r1)[labno];
      break;
    case '\x02':
      if ((((labno < 0x11) || (0x1e < labno)) && (labno != 0xaf)) && (labno != 0xb0)) break;
      goto LAB_00408f83;
    case '\x10':
    case ' ':
    case '0':
      if ((labno == 0xb1) || (labno == 0xb4)) goto LAB_00408f83;
      goto joined_r0x00408f81;
    case '\x11':
joined_r0x00408f81:
      if (labno == 0xb6) {
LAB_00408f83:
        refs = true;
      }
    }
    if (refs != false) goto switchD_00408e11_caseD_12;
switchD_00408e11_caseD_24:
    regno = rec->tmp;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x004093d6;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x004093d6:
      rec_mask_hi = g_reg_mask_table[regno];
    }
    break;
  case OP_JUMP:
  case OP_JUMPT:
  case OP_JUMPF:
    goto switchD_00408e11_caseD_24;
  case OP_MOV_LOC:
    regno = rec->tmp;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x00408fe6;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x00408fe6:
      rec_mask_hi = g_reg_mask_table[regno];
    }
    rec_mask_lo = rec_mask_lo | g_reg_mask_table[0xf];
    rec_mask_hi = rec_mask_hi | g_reg_mask_table[0x6b];
    mov_dir = rec->misc & 0x80;
    if (mov_dir == 0x80) {
      regno = rec->ea1->base;
      if (regno < '\0') {
        if ('_' < regno) goto code_r0x00409029;
      }
      else if (regno < '`') {
        rec_mask_lo = rec_mask_lo | g_reg_mask_table[regno];
      }
      else {
code_r0x00409029:
        rec_mask_hi = rec_mask_hi | g_reg_mask_table[regno];
      }
    }
    else {
      if (mov_dir != 0) goto switchD_00408e11_caseD_12;
      regno = rec->ea2->base;
      if (regno < '\0') {
        if ('_' < regno) goto code_r0x00409074;
      }
      else if (regno < '`') {
        rec_mask_lo = rec_mask_lo | g_reg_mask_table[regno];
      }
      else {
code_r0x00409074:
        rec_mask_hi = rec_mask_hi | g_reg_mask_table[regno];
      }
    }
    break;
  case OP_MOVA_LC:
    regno = rec->ea2->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x004090b7;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x004090b7:
      rec_mask_hi = g_reg_mask_table[regno];
    }
    rec_mask_lo = rec_mask_lo | g_reg_mask_table[0xf];
    rec_mask_hi = rec_mask_hi | g_reg_mask_table[0x6b];
    break;
  case OP_MOVA_PC:
    regno = rec->ea2->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x00409106;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x00409106:
      rec_mask_hi = g_reg_mask_table[regno];
    }
    goto joined_r0x0040921e;
  case OP_MOVI:
    regno = rec->ea2->base;
    if ((regno < '\0') || ('_' < regno)) {
      if ('_' < regno) {
        rec_mask_hi = g_reg_mask_table[regno];
      }
    }
    else {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    disp = rec->ea1->disp;
    if (((disp < -0x80) || (0x7f < disp)) ||
       (((uVar1 & rec_mask_lo) == 0 && ((reg_mask_hi & rec_mask_hi) == 0)))) {
      rec_mask_hi = rec_mask_hi | g_reg_mask_table[0x6b];
    }
    else {
      refs = true;
    }
    if (((disp < -0x80) || (0x7f < disp)) &&
       (((uVar1 & rec_mask_lo) != 0 || ((reg_mask_hi & rec_mask_hi) != 0)))) {
      refs = true;
    }
    if ((rec->ea1->labels == (label_ref *)0x0) || (reg != 'k')) goto switchD_00408e11_caseD_12;
    goto LAB_004093ea;
  case OP_MOVA_FC:
    regno = rec->tmp;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x004091e0;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x004091e0:
      rec_mask_hi = g_reg_mask_table[regno];
    }
    regno = rec->ea2->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x0040920c;
    }
    else if (regno < '`') {
      rec_mask_lo = rec_mask_lo | g_reg_mask_table[regno];
    }
    else {
code_r0x0040920c:
      rec_mask_hi = rec_mask_hi | g_reg_mask_table[regno];
    }
joined_r0x0040921e:
    if ((uVar1 & rec_mask_lo) != 0) goto LAB_004093ea;
    rec_mask_hi = rec_mask_hi | g_reg_mask_table[0x6b];
    goto joined_r0x004093ca;
  case OP_NON_2C:
    has_tmp = rec->tmp != '\0';
    regno = '\0';
    if (has_tmp) {
      regno = rec->tmp;
    }
    refs = has_tmp && reg == 'g';
    if (regno < '\0') {
      if ('_' < rec->tmp) goto code_r0x00409268;
    }
    else if (rec->tmp < '`') {
      rec_mask_lo = g_reg_mask_table[rec->tmp];
    }
    else {
code_r0x00409268:
      rec_mask_hi = g_reg_mask_table[rec->tmp];
    }
    regno = rec->ea2->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x00409295;
    }
    else if (regno < '`') {
      rec_mask_lo = rec_mask_lo | g_reg_mask_table[regno];
    }
    else {
code_r0x00409295:
      rec_mask_hi = rec_mask_hi | g_reg_mask_table[regno];
    }
    rec_mask_hi = rec_mask_hi | g_reg_mask_table[0x6b];
    break;
  case OP_NON_2E:
    regno = rec->ea1->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x004092e1;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x004092e1:
      rec_mask_hi = g_reg_mask_table[regno];
    }
    regno = rec->ea2->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x0040930d;
    }
    else if (regno < '`') {
      rec_mask_lo = rec_mask_lo | g_reg_mask_table[regno];
    }
    else {
code_r0x0040930d:
      rec_mask_hi = rec_mask_hi | g_reg_mask_table[regno];
    }
    rec_mask_hi = rec_mask_hi | g_reg_mask_table[0x68];
    rec_mask_lo = rec_mask_lo | g_reg_mask_table[0x30] | g_reg_mask_table[0x34] |
                  g_reg_mask_table[0x38] | g_reg_mask_table[0x3c];
    break;
  case OP_NON_30:
    regno = rec->ea1->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x0040936e;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x0040936e:
      rec_mask_hi = g_reg_mask_table[regno];
    }
    goto joined_r0x004093c4;
  case OP_NON_31:
    regno = rec->ea2->base;
    if (regno < '\0') {
      if ('_' < regno) goto code_r0x004093ac;
    }
    else if (regno < '`') {
      rec_mask_lo = g_reg_mask_table[regno];
    }
    else {
code_r0x004093ac:
      rec_mask_hi = g_reg_mask_table[regno];
    }
    rec_mask_hi = rec_mask_hi | g_reg_mask_table[0x60];
joined_r0x004093c4:
    if ((uVar1 & rec_mask_lo) != 0) goto LAB_004093ea;
    rec_mask_hi = rec_mask_hi | g_reg_mask_table[0x68];
    goto joined_r0x004093ca;
  }
  if ((uVar1 & rec_mask_lo) == 0) {
joined_r0x004093ca:
    if ((reg_mask_hi & rec_mask_hi) == 0) goto switchD_00408e11_caseD_12;
  }
LAB_004093ea:
  refs = true;
switchD_00408e11_caseD_12:
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_mcrrfchk_end__rc___d_00425b24,(int)refs);
  }
  return refs;
}



