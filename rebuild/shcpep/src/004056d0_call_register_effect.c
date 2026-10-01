#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0x5bf0))


// entry: 004056d0
// name : call_register_effect
// size : 620
// sig  : char call_register_effect(psd * rec, uchar reg, int mode)


/* WARNING: Removing unreachable block (ram,0x00405854) */
/* WARNING: Removing unreachable block (ram,0x00405859) */

char __cdecl call_register_effect(psd *rec,uchar reg,int mode)

{
  char hit;
  uchar changed;
  short labno;
  uint reserved;
  char result;
  label_ref *ref;
  
  result = '\0';
  switch(rec->op) {
  case OP_CALL:
    break;
  default:
    goto switchD_004056f8_caseD_24;
  case OP_BSR:
  case OP_JSR:
  case OP_BSRF:
    goto LAB_00405765;
  case OP_TRAPA:
    if (reg == '\0') {
      return -1;
    }
  }
  if ((rec->op == OP_CALL) && (rec->ea1->labels->labno1 < 0xb7)) {
    hit = macro_record_changes_register(rec,reg);
    if ((hit != '\0') || (hit = macro_record_references_register(rec,reg), hit != '\0')) {
      return '\x01';
    }
  }
  else {
LAB_00405765:
    if ((((char)reg < '\0') || ('\x03' < (char)reg)) &&
       (((((char)reg < '\x10' || ('\x13' < (char)reg)) && (reg != ' ')) && (reg != '\"')))) {
      if (((('\x03' < (char)reg) && ((char)reg < '\b')) ||
          (('\x13' < (char)reg &&
           ((int)(char)reg <= g_current_request->scratch_bank_reg_count + 0x13)))) ||
         (('#' < (char)reg && ((int)(char)reg <= g_current_request->scratch_bank_reg_count + 0x23)))
         ) {
        return -1;
      }
      if (((char)reg < '\b') || ('\x0e' < (char)reg)) {
        if ((((int)(char)reg < g_current_request->scratch_bank_reg_count + 0x14) ||
            ('\x1f' < (char)reg)) &&
           (((int)(char)reg < g_current_request->scratch_bank_reg_count + 0x24 || ('.' < (char)reg))
           )) {
          if ((reg == 'g') || (reg == 'h')) {
            return -1;
          }
          if (g_current_request->macsave != '\0') {
            return '\0';
          }
          if ((reg != 'd') && (reg != 'e')) {
            return '\0';
          }
          return -1;
        }
      }
      if (((rec->ea1 == (ea *)0x0) || (ref = rec->ea1->labels, ref == (label_ref *)0x0)) ||
         (labno = ref->labno1, labno == 0)) {
        labno = 0;
      }
      find_label_symbol(labno);
      if ((char)reg < ' ') {
        reserved = g_current_request->reg_mask_150 & 1 << (reg & 0x1f);
      }
      else if ((char)reg < '/') {
        reserved = (1 << (reg - 0xf & 0x1f) | 1 << (reg - 0x10 & 0x1f)) &
                   g_current_request->reg_mask_150;
      }
      else {
        reserved = 0;
      }
      if (reserved != 0) {
        return -1;
      }
    }
    else if (mode == 0) {
      result = '\x01';
    }
    else {
      changed = record_changes_register(rec,reg);
      if (changed != '\0') {
        return '\x01';
      }
    }
  }
switchD_004056f8_caseD_24:
  return result;
}



