#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_rec_def_mask_hi
#define g_rec_def_mask_hi (*(unsigned int *)(g_sd + 0x6d5c))
#undef g_rec_def_mask_lo
#define g_rec_def_mask_lo (*(unsigned int *)(g_sd + 0x6d58))
#undef g_rec_use_mask_hi
#define g_rec_use_mask_hi (*(unsigned int *)(g_sd + 0x5c44))
#undef g_rec_use_mask_lo
#define g_rec_use_mask_lo (*(unsigned int *)(g_sd + 0x5c40))


// entry: 00419060
// name : accumulate_operand_register_masks
// size : 1117
// sig  : void accumulate_operand_register_masks(psd * rec, int which)


int __cdecl accumulate_operand_register_masks(psd *rec,int which)

{
  uchar changes;
  char cVar1;
  ea *operand;
  
  if (which == 1) {
    operand = rec->ea1;
  }
  else {
    if (which != 2) {
      return;
    }
    operand = rec->ea2;
  }
  switch(operand->type & 0x1f) {
  case 1:
  case 5:
  case 6:
  case 0xf:
  case 0x10:
    changes = record_changes_register(rec,operand->base);
    if (changes != '\0') {
      cVar1 = operand->base;
      if ((cVar1 < '\0') || ('_' < cVar1)) {
        if ('_' < operand->base) {
          g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[operand->base];
        }
      }
      else {
        g_rec_def_mask_lo = g_rec_def_mask_lo | g_reg_mask_table[cVar1];
      }
      cVar1 = operand->base;
      if ((cVar1 < '\0') || ('_' < cVar1)) {
        if ('_' < operand->base) {
          g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[operand->base];
        }
      }
      else {
        g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
      }
    }
    cVar1 = operand_uses_register(rec,operand->base,(char)which);
    if (cVar1 != '\0') {
      cVar1 = operand->base;
      if ((-1 < cVar1) && (cVar1 < '`')) {
        g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
        return;
      }
      if ('_' < operand->base) {
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[operand->base];
        return;
      }
    }
    break;
  case 2:
  case 8:
    cVar1 = operand->base;
    if ((-1 < cVar1) && (cVar1 < '`')) {
      g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
      return;
    }
    if ('_' < operand->base) {
      g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[operand->base];
      return;
    }
    break;
  case 3:
    if (which == 2) {
      cVar1 = operand->base;
      if ((cVar1 < '\0') || ('_' < cVar1)) {
        if ('_' < operand->base) {
          g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[operand->base];
        }
      }
      else {
        g_rec_def_mask_lo = g_rec_def_mask_lo | g_reg_mask_table[cVar1];
      }
      cVar1 = operand->base;
      if ((-1 < cVar1) && (cVar1 < '`')) {
        g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
        return;
      }
      if ('_' < operand->base) {
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[operand->base];
        return;
      }
    }
    break;
  case 4:
    cVar1 = operand->base;
    if ((cVar1 < '\0') || ('_' < cVar1)) {
      if ('_' < operand->base) {
        g_rec_def_mask_hi = g_rec_def_mask_hi | g_reg_mask_table[operand->base];
      }
    }
    else {
      g_rec_def_mask_lo = g_rec_def_mask_lo | g_reg_mask_table[cVar1];
    }
    cVar1 = operand->base;
    if ((-1 < cVar1) && (cVar1 < '`')) {
      g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
      return;
    }
    if ('_' < operand->base) {
      g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[operand->base];
      return;
    }
    break;
  case 7:
    break;
  case 9:
    cVar1 = operand->base;
    if ((cVar1 < '\0') || ('_' < cVar1)) {
      if ('_' < operand->base) {
        g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[operand->base];
      }
    }
    else {
      g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
    }
    cVar1 = operand->index;
    if ((-1 < cVar1) && (cVar1 < '`')) {
      g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
      return;
    }
    if ('_' < operand->index) {
      g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[operand->index];
      return;
    }
    break;
  case 10:
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x6b];
    return;
  case 0xb:
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x62];
    return;
  case 0xc:
    g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[0x62];
    cVar1 = operand->index;
    if ((-1 < cVar1) && (cVar1 < '`')) {
      g_rec_use_mask_lo = g_rec_use_mask_lo | g_reg_mask_table[cVar1];
      return;
    }
    if ('_' < operand->index) {
      g_rec_use_mask_hi = g_rec_use_mask_hi | g_reg_mask_table[operand->index];
    }
    break;
  default:
    report_fatal_message(0,0,0x127b);
    return;
  }
  return;
}



