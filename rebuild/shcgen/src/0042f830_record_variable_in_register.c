#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lreg_table
#define g_lreg_table (*(short * *)(g_sd + 0x1fa10))
#undef g_r0_variable
#define g_r0_variable (*(short * *)(g_sd + 0x1f9a8))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0042f830
// name : record_variable_in_register
// size : 530
// sig  : void record_variable_in_register(gen_node * node, short reg)


int __cdecl record_variable_in_register(gen_node *node,short reg)

{
  byte bVar1;
  short lreg_no;
  byte bit;
  short *lreg_row;
  ushort uVar2;
  reg_content *contents;
  ushort *cached;
  node_desc *desc;
  bool is_fpr;
  bool is_r0_variable;
  bool record;
  reg_content *slot;
  
  if ((node->type & 0xf8) == 0x28) {
    if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
      bVar1 = 1;
    }
    else {
      bVar1 = -(g_request->cpu == 4) & 2;
    }
    if (((bVar1 == 0) || (reg < 0x10)) || (0x13 < reg)) goto LAB_0042f8a5;
    contents = g_fpr_contents;
    is_fpr = true;
    reg = reg + -0x10;
  }
  else {
LAB_0042f8a5:
    contents = g_gpr_contents;
    is_fpr = false;
  }
  record = false;
  is_r0_variable = false;
  if (g_content_hit != 0) {
    return;
  }
  if (node->op != IL_ID) {
    return;
  }
  if ((node->type & 2) != 0) {
    return;
  }
  if ((reg < 0x10) || (0x13 < reg)) {
    if (reg < 0) {
      return;
    }
    if (3 < reg) {
      return;
    }
  }
  uVar2 = node->lreg >> 0xf;
  lreg_no = (node->lreg ^ uVar2) - uVar2;
  if (node->lreg != 0) {
    lreg_row = g_lreg_table;
    if (*g_lreg_table == 0) goto LAB_0042f967;
    do {
      if (*lreg_row == lreg_no) break;
      lreg_row = lreg_row + 0x12;
    } while (*lreg_row != 0);
    if (*lreg_row == 0) goto LAB_0042f967;
    if (((g_r0_variable != (short *)0x0) && (node->symx == *g_r0_variable)) &&
       (g_r0_variable[1] == *lreg_row)) {
      record = true;
      is_r0_variable = true;
      goto LAB_0042f967;
    }
    if (-1 < lreg_row[1]) goto LAB_0042f967;
  }
  record = true;
LAB_0042f967:
  if ((record) && ((is_r0_variable || (((node->desc->value).type & 0x1f) != 1)))) {
    bVar1 = (byte)reg;
    bit = bVar1;
    if (is_fpr) {
      bit = bVar1 + 0x10;
    }
    invalidate_register_contents(1 << (bit & 0x1f));
    evict_oldest_register_content(contents);
    slot = contents + reg;
    slot->value = (int)node->symx;
    (slot->u).lreg = lreg_no;
    slot->type = node->type;
    slot->stamp = g_stmt_serial;
    slot->flags = '\0';
    if ((is_r0_variable) && (reg == 0)) {
      contents->flags = contents->flags | 0x20;
    }
    desc = node->desc;
    if (is_fpr) {
      uVar2 = 1 << (bVar1 & 0x1f);
      cached = &desc->fcached_regs;
      *cached = *cached | uVar2;
    }
    else {
      uVar2 = 1 << (bVar1 & 0x1f);
      cached = &desc->cached_regs;
      *cached = *cached | uVar2;
    }
    if ((node->parent != (gen_node *)0x0) && (desc = node->parent->desc, desc != (node_desc *)0x0))
    {
      if (is_fpr) {
        cached = &node->desc->fcached_regs;
        *cached = *cached | uVar2;
        return;
      }
      cached = &desc->cached_regs;
      *cached = *cached | uVar2;
    }
  }
  return;
}



