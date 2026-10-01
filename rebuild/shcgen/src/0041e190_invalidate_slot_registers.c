#include "decls.h"
#include "imports.h"

// entry: 0041e190
// name : invalidate_slot_registers
// size : 228
// sig  : void invalidate_slot_registers(gen_node * node, uchar slot_kind, ushort mask)


int __cdecl invalidate_slot_registers(gen_node *node,uchar slot_kind,ushort mask)

{
  uchar *second_regs;
  uchar *first_count;
  ushort slot_mask;
  uchar *second_count;
  uchar *first_regs;
  
  slot_mask = 0;
  if ((slot_kind & 0xf0) == 0x30) {
    first_count = (uchar *)0x3;
    second_count = (uchar *)0x2;
    first_regs = (uchar *)node->desc->regs_41;
    second_regs = (uchar *)node->desc->regs_44;
  }
  else if ((slot_kind & 0xf0) == 0x70) {
    first_count = (uchar *)0x1;
    second_regs = (uchar *)0x0;
    second_count = (uchar *)0x0;
    first_regs = (uchar *)&node->desc->reg_47;
  }
  else {
    report_codegen_message(0x1227,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    first_count = first_regs;
    second_count = first_regs;
    second_regs = first_regs;
  }
  while (first_count != (uchar *)0x0) {
    if (*first_regs != 0xff) {
      slot_mask = slot_mask | 1 << (*first_regs & 0x1f);
    }
    first_regs = first_regs + 1;
    first_count = first_count + -1;
  }
  if (second_regs != (uchar *)0x0) {
    while (second_count != (uchar *)0x0) {
      second_count = second_count + -1;
      if (*second_regs != 0xff) {
        slot_mask = slot_mask | 1 << (*second_regs & 0x1f);
      }
      second_regs = second_regs + 1;
    }
  }
  if ((slot_mask & mask) != 0) {
    invalidate_register_contents((int)(short)(slot_mask & mask));
  }
  return;
}



