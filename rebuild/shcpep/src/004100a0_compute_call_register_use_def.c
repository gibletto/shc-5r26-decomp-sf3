#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0x5bf0))


// entry: 004100a0
// name : compute_call_register_use_def
// size : 1266
// sig  : void compute_call_register_use_def(psd * rec, uint * uses, uint * defs)


int __cdecl compute_call_register_use_def(psd *rec,uint *uses,uint *defs)

{
  bool bVar1;
  char cVar2;
  short labno;
  symbol *sym;
  byte r;
  uchar reg;
  bool clobbers_all;
  label_ref *lref;
  
  bVar1 = false;
  clobbers_all = false;
  switch(rec->op) {
  case OP_CALL:
    if (defs != (uint *)0x0) {
      cVar2 = rec->tmp;
      if ((cVar2 < '\0') || ('_' < cVar2)) {
        if ((defs != (uint *)0x0) && ('_' < rec->tmp)) {
          defs[1] = defs[1] | g_reg_mask_table[rec->tmp];
        }
      }
      else {
        *defs = *defs | g_reg_mask_table[cVar2];
      }
    }
    lref = rec->ea1->labels;
    labno = lref->labno1;
    if (labno < 0xb7) {
      reg = '\0';
      do {
        if (rec->tmp != reg) {
          cVar2 = macro_record_changes_register(rec,reg);
          if ((cVar2 != '\0') && (defs != (uint *)0x0)) {
            if (((char)reg < '\0') || ('_' < (char)reg)) {
              if ((defs != (uint *)0x0) && ('_' < (char)reg)) {
                defs[1] = defs[1] | g_reg_mask_table[(char)reg];
              }
            }
            else {
              *defs = *defs | g_reg_mask_table[(char)reg];
            }
          }
          cVar2 = macro_record_references_register(rec,reg);
          if (cVar2 != '\0') {
            if (uses != (uint *)0x0) {
              if (((char)reg < '\0') || ('_' < (char)reg)) {
                if ((uses != (uint *)0x0) && ('_' < (char)reg)) {
                  uses[1] = uses[1] | g_reg_mask_table[(char)reg];
                }
              }
              else {
                *uses = *uses | g_reg_mask_table[(char)reg];
              }
            }
            if (defs != (uint *)0x0) {
              if (((char)reg < '\0') || ('_' < (char)reg)) {
                if ((defs != (uint *)0x0) && ('_' < (char)reg)) {
                  defs[1] = defs[1] | g_reg_mask_table[(char)reg];
                }
              }
              else {
                *defs = *defs | g_reg_mask_table[(char)reg];
              }
            }
          }
        }
        reg = reg + '\x01';
      } while ((char)reg < '\x03');
      labno = rec->ea1->labels->labno1;
      if ((labno < 0xb1) || (0xb4 < labno)) {
        if (labno == 0xb5) {
          cVar2 = macro_record_changes_register(rec,' ');
          if ((cVar2 != '\0') && (defs != (uint *)0x0)) {
            *defs = *defs | g_reg_mask_table[0x20];
          }
        }
        else if (labno == 0xb6) {
          cVar2 = macro_record_references_register(rec,' ');
          if (cVar2 != '\0') {
            if (uses != (uint *)0x0) {
              *uses = *uses | g_reg_mask_table[0x20];
            }
            if (defs != (uint *)0x0) {
              *defs = *defs | g_reg_mask_table[0x20];
            }
          }
        }
        else if ((labno == 0x49) || (labno == 0x4a)) {
          *uses = 0xf000000;
          *defs = 0xff000000;
          if (defs != (uint *)0x0) {
            cVar2 = rec->tmp;
            if ((cVar2 < '\0') || ('_' < cVar2)) {
              if ((defs != (uint *)0x0) && ('_' < rec->tmp)) {
                defs[1] = defs[1] | g_reg_mask_table[rec->tmp];
              }
            }
            else {
              *defs = g_reg_mask_table[cVar2] | 0xff000000;
            }
          }
        }
      }
      else {
        cVar2 = macro_record_references_register(rec,'\x10');
        if (cVar2 != '\0') {
          if (uses != (uint *)0x0) {
            *uses = *uses | g_reg_mask_table[0x10];
          }
          if (defs != (uint *)0x0) {
            *defs = *defs | g_reg_mask_table[0x10];
          }
        }
        cVar2 = macro_record_changes_register(rec,'\x10');
        if ((cVar2 != '\0') && (defs != (uint *)0x0)) {
          *defs = *defs | g_reg_mask_table[0x10];
        }
      }
      if (uses != (uint *)0x0) {
        *uses = *uses | g_reg_mask_table[0xf];
      }
      if (defs != (uint *)0x0) {
        *defs = *defs | g_reg_mask_table[0xf];
      }
      if (uses != (uint *)0x0) {
        uses[1] = uses[1] | g_reg_mask_table[0x6b];
      }
      if ((defs != (uint *)0x0) && (defs[1] = defs[1] | g_reg_mask_table[0x6b], defs != (uint *)0x0)
         ) {
        defs[1] = defs[1] | g_reg_mask_table[0x66];
      }
      if (uses != (uint *)0x0) {
        uses[1] = uses[1] | g_reg_mask_table[0x7f];
      }
      if (defs == (uint *)0x0) {
        return;
      }
      defs[1] = defs[1] | g_reg_mask_table[0x7f];
      return;
    }
    if (((rec->ea1 == (ea *)0x0) || (lref == (label_ref *)0x0)) || (labno == 0)) {
      labno = 0;
    }
    sym = find_label_symbol(labno);
    clobbers_all = bVar1;
    if (((sym != (symbol *)0x0) && ((sym->attr & 0x10) == 0)) && ((sym->attr & 0xc) != 0)) {
      clobbers_all = true;
    }
    break;
  default:
    goto switchD_004100c2_caseD_24;
  case OP_BSR:
  case OP_JSR:
  case OP_BSRF:
    clobbers_all = bVar1;
    break;
  case OP_TRAPA:
    goto LAB_00410416;
  }
  if (((rec->op != OP_CALL) && (rec->op != OP_BSR)) && (uses != (uint *)0x0)) {
    cVar2 = rec->ea1->base;
    if ((cVar2 < '\0') || ('_' < cVar2)) {
      if ((uses != (uint *)0x0) && (cVar2 = rec->ea1->base, '_' < cVar2)) {
        uses[1] = uses[1] | g_reg_mask_table[cVar2];
      }
    }
    else {
      *uses = *uses | g_reg_mask_table[cVar2];
    }
  }
LAB_00410416:
  sym = g_symbol_hash[g_current_node_list->labno % 0x3fd];
  if (rec->op == OP_TRAPA) {
    *uses = *uses | 0x8f000000;
    *defs = *defs | 0x80000000;
  }
  else {
    *uses = *uses | 0xf000ff0;
    *defs = *defs | 0xff00fff0;
  }
  if ((clobbers_all) || ((sym != (symbol *)0x0 && ((sym->attr & 8) != 0)))) {
    *uses = *uses | 0xfe000f;
    *defs = *defs | 0xfe000f;
  }
  else {
    r = 8;
    do {
      if ((g_current_request->reg_mask_150 & 1 << (r & 0x1f)) != 0) {
        *uses = *uses | g_reg_mask_table[(char)r];
        *defs = *defs | g_reg_mask_table[(char)r];
      }
      r = r + 1;
    } while ((char)r < '\x0f');
    r = 0x1c;
    do {
      if ((g_current_request->reg_mask_150 & 1 << (r & 0x1f)) != 0) {
        *uses = *uses | g_reg_mask_table[(char)r];
        *defs = *defs | g_reg_mask_table[(char)r];
      }
      r = r + 1;
    } while ((char)r < ' ');
  }
  if (uses != (uint *)0x0) {
    *uses = *uses | g_reg_mask_table[0xf];
  }
  if (defs != (uint *)0x0) {
    *defs = *defs | g_reg_mask_table[0xf];
  }
  if (g_current_request->macsave == '\0') {
    if (uses != (uint *)0x0) {
      uses[1] = uses[1] | g_reg_mask_table[100];
    }
    if (defs != (uint *)0x0) {
      defs[1] = defs[1] | g_reg_mask_table[100];
    }
    if (uses != (uint *)0x0) {
      uses[1] = uses[1] | g_reg_mask_table[0x65];
    }
    if (defs != (uint *)0x0) {
      defs[1] = defs[1] | g_reg_mask_table[0x65];
    }
  }
  if (uses != (uint *)0x0) {
    uses[1] = uses[1] | g_reg_mask_table[0x67];
  }
  if (defs != (uint *)0x0) {
    defs[1] = defs[1] | g_reg_mask_table[0x67];
  }
  if (uses != (uint *)0x0) {
    uses[1] = uses[1] | g_reg_mask_table[0x68];
  }
  if (defs != (uint *)0x0) {
    defs[1] = defs[1] | g_reg_mask_table[0x68];
  }
  if (uses != (uint *)0x0) {
    uses[1] = uses[1] | g_reg_mask_table[0x6b];
  }
  if ((defs != (uint *)0x0) && (defs[1] = defs[1] | g_reg_mask_table[0x6b], defs != (uint *)0x0)) {
    defs[1] = defs[1] | g_reg_mask_table[0x66];
  }
  if (uses != (uint *)0x0) {
    uses[1] = uses[1] | g_reg_mask_table[0x7f];
  }
  if (defs != (uint *)0x0) {
    defs[1] = defs[1] | g_reg_mask_table[0x7f];
  }
switchD_004100c2_caseD_24:
  return;
}



