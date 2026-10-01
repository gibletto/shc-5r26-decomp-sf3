#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0x5bf0))


// entry: 00410630
// name : collect_enter_exit_register_masks
// size : 1183
// sig  : void collect_enter_exit_register_masks(psd * rec, uint * uses, uint * defs)


int __cdecl collect_enter_exit_register_masks(psd *rec,uint *uses,uint *defs)

{
  byte reg;
  short saved_count;
  aux_record *aux;
  int reg_num;
  uint bit;
  int hi_reg;
  psd_op op;
  
  aux = g_aux_record_table + g_current_aux_index;
  op = rec->op;
  if (op == OP_ENTER) {
    if (uses != (uint *)0x0) {
      *uses = *uses | g_reg_mask_table[0];
    }
    if (defs != (uint *)0x0) {
      *defs = *defs | g_reg_mask_table[0];
    }
    if (uses != (uint *)0x0) {
      *uses = *uses | g_reg_mask_table[0xf];
    }
    if ((defs != (uint *)0x0) && (*defs = *defs | g_reg_mask_table[0xf], defs != (uint *)0x0)) {
      defs[1] = defs[1] | g_reg_mask_table[0x7f];
    }
    reg = 0;
    do {
      if (((1 << (reg & 0x1f) & (int)g_aux_record_table[g_current_aux_index].saved_regs) != 0) &&
         (uses != (uint *)0x0)) {
        if (((char)reg < '\0') || ('_' < (char)reg)) {
          if ((uses != (uint *)0x0) && ('_' < (char)reg)) {
            uses[1] = uses[1] | g_reg_mask_table[(char)reg];
          }
        }
        else {
          *uses = *uses | g_reg_mask_table[(char)reg];
        }
      }
      reg = reg + 1;
    } while ((char)reg < '\x10');
    reg = 0;
    do {
      if (((1 << (reg & 0x1f) & (int)g_aux_record_table[g_current_aux_index].saved_regs2) != 0) &&
         (uses != (uint *)0x0)) {
        hi_reg = (char)reg + 0x10;
        if ((hi_reg < 0) || (0x5f < hi_reg)) {
          if (uses != (uint *)0x0) {
            hi_reg = (char)reg + 0x10;
            if ((0x5f < hi_reg) && (hi_reg < 0x80)) {
              uses[1] = uses[1] | g_reg_mask_table[(char)reg + 0x10];
            }
          }
        }
        else {
          *uses = *uses | g_reg_mask_table[(char)reg + 0x10];
        }
      }
      reg = reg + 1;
    } while ((char)reg < '\x10');
    if (((aux->saved_mac & 2) != 0) && (uses != (uint *)0x0)) {
      uses[1] = uses[1] | g_reg_mask_table[100];
    }
    if (((aux->saved_mac & 1) != 0) && (uses != (uint *)0x0)) {
      uses[1] = uses[1] | g_reg_mask_table[0x65];
    }
    if (((aux->saved_sys & 1) != 0) && (uses != (uint *)0x0)) {
      uses[1] = uses[1] | g_reg_mask_table[0x67];
    }
    if (((aux->saved_sys & 2) != 0) && (uses != (uint *)0x0)) {
      uses[1] = uses[1] | g_reg_mask_table[0x68];
      return;
    }
  }
  else {
    if (op != OP_EXIT) {
      if (op != OP_RETURN) {
        return;
      }
      saved_count = count_function_saved_registers();
      if (1 < saved_count) {
        if (defs != (uint *)0x0) {
          *defs = *defs | g_reg_mask_table[1];
        }
        if (uses != (uint *)0x0) {
          uses[1] = uses[1] | g_reg_mask_table[0x6b];
        }
        if (defs == (uint *)0x0) {
          return;
        }
        defs[1] = defs[1] | g_reg_mask_table[0x6b];
        return;
      }
    }
    if ((0x7f < aux->sp_adjust + aux->frame_size) && (defs != (uint *)0x0)) {
      *defs = *defs | g_reg_mask_table[1];
    }
    if (((g_aux_record_table[g_current_aux_index].flags & 0x8000) == 0) && (defs != (uint *)0x0)) {
      defs[1] = defs[1] | g_reg_mask_table[0x66];
    }
    if (uses != (uint *)0x0) {
      *uses = *uses | g_reg_mask_table[0xf];
    }
    if (defs != (uint *)0x0) {
      *defs = *defs | g_reg_mask_table[0xf];
    }
    if (uses != (uint *)0x0) {
      uses[1] = uses[1] | g_reg_mask_table[0x7f];
    }
    reg = 0;
    do {
      bit = 1 << (reg & 0x1f);
      if ((bit & (int)g_aux_record_table[g_current_aux_index].saved_regs) == 0) {
        if ((char)reg < ' ') {
          bit = g_current_request->reg_mask_150 & bit;
        }
        else if ((char)reg < '/') {
          bit = (1 << (reg - 0xf & 0x1f) | 1 << (reg - 0x10 & 0x1f)) &
                g_current_request->reg_mask_150;
        }
        else {
          bit = 0;
        }
        if ((bit != 0) && (uses != (uint *)0x0)) {
          if (((char)reg < '\0') || ('_' < (char)reg)) {
            if ((uses != (uint *)0x0) && ('_' < (char)reg)) {
              uses[1] = uses[1] | g_reg_mask_table[(char)reg];
            }
          }
          else {
            *uses = *uses | g_reg_mask_table[(char)reg];
          }
        }
      }
      else if (defs != (uint *)0x0) {
        if (((char)reg < '\0') || ('_' < (char)reg)) {
          if ((defs != (uint *)0x0) && ('_' < (char)reg)) {
            defs[1] = defs[1] | g_reg_mask_table[(char)reg];
          }
        }
        else {
          *defs = *defs | g_reg_mask_table[(char)reg];
        }
      }
      reg = reg + 1;
    } while ((char)reg < '\x10');
    reg = 0;
    do {
      bit = 1 << (reg & 0x1f);
      if ((bit & (int)g_aux_record_table[g_current_aux_index].saved_regs2) == 0) {
        reg_num = (int)(char)reg;
        hi_reg = reg_num + 0x10;
        if (hi_reg < 0x20) {
          bit = 1 << (reg + 0x10 & 0x1f);
LAB_00410a25:
          bit = bit & g_current_request->reg_mask_150;
        }
        else {
          if (hi_reg < 0x2f) {
            bit = 1 << (reg + 1 & 0x1f) | bit;
            goto LAB_00410a25;
          }
          bit = 0;
        }
        if ((bit != 0) && (uses != (uint *)0x0)) {
          if ((hi_reg < 0) || (0x5f < hi_reg)) {
            if (((uses != (uint *)0x0) && (0x5f < hi_reg)) && (hi_reg < 0x80)) {
              uses[1] = uses[1] | g_reg_mask_table[reg_num + 0x10];
            }
          }
          else {
            *uses = *uses | g_reg_mask_table[reg_num + 0x10];
          }
        }
      }
      else if (defs != (uint *)0x0) {
        hi_reg = (char)reg + 0x10;
        if ((hi_reg < 0) || (0x5f < hi_reg)) {
          if (defs != (uint *)0x0) {
            hi_reg = (char)reg + 0x10;
            if ((0x5f < hi_reg) && (hi_reg < 0x80)) {
              defs[1] = defs[1] | g_reg_mask_table[(char)reg + 0x10];
            }
          }
        }
        else {
          *defs = *defs | g_reg_mask_table[(char)reg + 0x10];
        }
      }
      reg = reg + 1;
    } while ((char)reg < '\x10');
    if (((aux->saved_mac & 2) != 0) && (defs != (uint *)0x0)) {
      defs[1] = defs[1] | g_reg_mask_table[100];
    }
    if (((aux->saved_mac & 1) != 0) && (defs != (uint *)0x0)) {
      defs[1] = defs[1] | g_reg_mask_table[0x65];
    }
    if (((aux->saved_sys & 1) != 0) && (defs != (uint *)0x0)) {
      defs[1] = defs[1] | g_reg_mask_table[0x67];
    }
    if (((aux->saved_sys & 2) != 0) && (defs != (uint *)0x0)) {
      defs[1] = defs[1] | g_reg_mask_table[0x68];
    }
  }
  return;
}



