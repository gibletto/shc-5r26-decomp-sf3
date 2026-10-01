#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0042faf0
// name : record_constant_in_register
// size : 442
// sig  : void record_constant_in_register(ea * value, short reg, gen_node * node)


int __cdecl record_constant_in_register(ea *value,short reg,gen_node *node)

{
  byte bVar1;
  short sVar2;
  label_ref *labels;
  byte bit;
  ushort mask;
  reg_content *contents;
  ushort *cached;
  bool is_fpr;
  node_desc *parent_desc;
  reg_content *slot;
  
  if ((node->type & 0xf8) == 0x28) {
    if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
      bVar1 = 1;
    }
    else {
      bVar1 = -(g_request->cpu == 4) & 2;
    }
    if (((bVar1 == 0) || (reg < 0x10)) || (0x13 < reg)) goto LAB_0042fb60;
    reg = reg + -0x10;
    is_fpr = true;
    contents = g_fpr_contents;
  }
  else {
LAB_0042fb60:
    contents = g_gpr_contents;
    is_fpr = false;
  }
  if (3 < reg) {
    return;
  }
  if (reg < 0) {
    return;
  }
  if (g_content_hit != 0) {
    return;
  }
  slot = contents + reg;
  if (((slot->flags & 0x40) == 0) || (value->disp != slot->value)) goto LAB_0042fbe8;
  if ((slot->u).labels == (label_ref *)0x0) {
    if (value->labels == (label_ref *)0x0) {
      sVar2 = 0;
    }
    else {
      sVar2 = value->labels->labno1;
    }
    if (sVar2 != 0) goto LAB_0042fbc2;
  }
  else {
LAB_0042fbc2:
    sVar2 = label_lists_equal((slot->u).labels,value->labels);
    if (sVar2 == 0) goto LAB_0042fbe8;
  }
  if (slot->stamp == g_stmt_serial) {
    return;
  }
LAB_0042fbe8:
  bVar1 = (byte)reg;
  bit = bVar1;
  if (is_fpr) {
    bit = bVar1 + 0x10;
  }
  invalidate_register_contents(1 << (bit & 0x1f));
  evict_oldest_register_content(contents);
  slot->value = value->disp;
  sVar2 = 0;
  labels = value->labels;
  if (labels != (label_ref *)0x0) {
    sVar2 = labels->labno1;
  }
  if (sVar2 == 0) {
    (slot->u).labels = (label_ref *)0x0;
  }
  else {
    labels = copy_label_ref_list(labels);
    (slot->u).labels = labels;
  }
  slot->stamp = g_stmt_serial;
  slot->flags = '@';
  if (is_fpr) {
    mask = 1 << (bVar1 & 0x1f);
    cached = &node->desc->fcached_regs;
    *cached = *cached | mask;
  }
  else {
    mask = 1 << (bVar1 & 0x1f);
    cached = &node->desc->cached_regs;
    *cached = *cached | mask;
  }
  if ((node->parent != (gen_node *)0x0) &&
     (parent_desc = node->parent->desc, parent_desc != (node_desc *)0x0)) {
    if (is_fpr) {
      cached = &node->desc->fcached_regs;
      *cached = *cached | mask;
      return;
    }
    cached = &parent_desc->cached_regs;
    *cached = *cached | mask;
  }
  return;
}



