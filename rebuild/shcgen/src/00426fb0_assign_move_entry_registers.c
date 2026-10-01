#include "decls.h"
#include "imports.h"

// entry: 00426fb0
// name : assign_move_entry_registers
// size : 2316
// sig  : void assign_move_entry_registers(gen_node * node, tmpl_header * tmpl, uchar slot_kind, ea * extra0, ea * extra1, ushort operand_regs, gen_node * account_node)


int __cdecl
assign_move_entry_registers
          (gen_node *node,tmpl_header *tmpl,uchar slot_kind,ea *extra0,ea *extra1,
          ushort operand_regs,gen_node *account_node)

{
  byte kind;
  uchar value_type;
  short same;
  ushort uVar1;
  ea *peVar2;
  ea *peVar3;
  gen_node *extra_opnd;
  int count;
  uint uVar4;
  ea *opnd3;
  byte size_bits;
  byte kind_bits;
  int slot_index;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  short slot;
  short entry_index;
  ea *opnd1;
  char *phase1_regs;
  gen_node *right_opnd;
  uint phase1_mask;
  char *slot_regs;
  node_desc *desc;
  tmpl_entry *entries;
  tmpl_entry *entry;
  gen_node *left;
  ushort *mask_ptr;
  char *spec_entry;
  
  left = node->child;
  if (left == (gen_node *)0x0) {
    right_opnd = (gen_node *)0x0;
  }
  else {
    right_opnd = left->next;
  }
  kind = slot_kind & 0xf0;
  if (kind == 0x20) {
    slot_regs = node->desc->regs_34;
    phase1_regs = node->desc->regs_2c;
  }
  else if (kind == 0x40) {
    slot_regs = node->desc->regs_44;
    phase1_regs = node->desc->regs_41;
  }
  else {
    report_codegen_message(0x1227,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  }
  entry_index = 0;
  phase1_mask = 0;
  slot = 0;
  entries = tmpl->entries;
  do {
    slot_index = (int)slot;
    uVar4 = tmpl->reg_spec2[slot_index];
    if (uVar4 == 0) break;
    uVar5 = 0;
    if ((((uVar4 & 0x380000) == 0x100000) || ((uVar4 & 0x380000) == 0x80000)) ||
       ((uVar4 & 0x2000) != 0)) {
      report_codegen_message(0x1227,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    }
    spec_entry = tmpl->spec2_entry + slot_index;
    if (entry_index < *spec_entry) {
      do {
        entry = entries + entry_index;
        uVar1 = entry->op;
        if (((uVar1 < 0x24) || (0x26 < uVar1)) && (uVar1 != 0x18)) {
          if (uVar1 == 0x23) {
            opnd1 = make_call_routine_operand((uint)entry->opnd[0],node);
          }
          else {
            opnd1 = materialize_operand_record_from_descriptor
                              (node,entry->opnd[0],(ea **)&g_template_extra_operands);
          }
        }
        else {
          opnd1 = (ea *)0x0;
        }
        peVar2 = materialize_operand_record_from_descriptor
                           (node,entry->opnd[1],(ea **)&g_template_extra_operands);
        peVar3 = materialize_operand_record_from_descriptor
                           (node,entry->opnd[2],(ea **)&g_template_extra_operands);
        invalidate_regs_written_by_entry(entry->op,opnd1,peVar2,peVar3);
        free_ea(opnd1);
        free_ea(peVar2);
        free_ea(peVar3);
        entry_index = entry_index + 1;
      } while (entry_index < *spec_entry);
    }
    uVar6 = uVar5;
    if (((uVar4 & 0x40000) != 0) && (uVar6 = phase1_mask, (uVar4 & 0x3c000) != 0)) {
      if (((uVar4 & 0x4000) != 0) && (bVar7 = *phase1_regs, bVar7 != 0xff)) {
        if (((char)bVar7 < ' ') && (-1 < (char)bVar7)) {
          uVar5 = 1 << (bVar7 & 0x1f);
        }
        else {
          uVar5 = (1 << (bVar7 - 0x1f & 0x1f) | 1 << (bVar7 - 0x20 & 0x1f)) << 0x10;
        }
      }
      if (((uVar4 & 0x8000) != 0) && (bVar7 = phase1_regs[1], bVar7 != 0xff)) {
        if (((char)bVar7 < ' ') && (-1 < (char)bVar7)) {
          uVar6 = 1 << (bVar7 & 0x1f);
        }
        else {
          uVar6 = (1 << (bVar7 - 0x1f & 0x1f) | 1 << (bVar7 - 0x20 & 0x1f)) << 0x10;
        }
        uVar5 = uVar5 | uVar6;
      }
      if (((uVar4 & 0x10000) != 0) && (phase1_regs[1] != 0xff)) {
        bVar7 = phase1_regs[2];
        if (((char)bVar7 < ' ') && (-1 < (char)bVar7)) {
          uVar6 = 1 << (bVar7 & 0x1f);
        }
        else {
          uVar6 = (1 << (bVar7 - 0x1f & 0x1f) | 1 << (bVar7 - 0x20 & 0x1f)) << 0x10;
        }
        uVar5 = uVar5 | uVar6;
      }
      uVar6 = uVar5;
      if (((uVar4 & 0x20000) != 0) && (phase1_regs[1] != 0xff)) {
        bVar7 = phase1_regs[3];
        if (((char)bVar7 < ' ') && (-1 < (char)bVar7)) {
          uVar6 = 1 << (bVar7 & 0x1f);
        }
        else {
          uVar6 = (1 << (bVar7 - 0x1f & 0x1f) | 1 << (bVar7 - 0x20 & 0x1f)) << 0x10;
        }
        uVar6 = uVar5 | uVar6;
      }
    }
    if (((uVar4 & 0x80) != 0) && (left != (gen_node *)0x0)) {
      desc = left->desc;
      bVar7 = 0;
      peVar2 = desc->mem_ea;
      if (peVar2 != (ea *)0x0) {
        bVar7 = peVar2->type & 0x1f;
      }
      if (((bVar7 == 0) && (peVar2 = &desc->dest, (peVar2->type & 0x1f) == 0)) &&
         (peVar2 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        peVar2 = &desc->value;
      }
      uVar5 = ea_register_mask(peVar2);
      uVar6 = uVar6 | uVar5;
    }
    if (((uVar4 & 0x200) != 0) && (extra0 != (ea *)0x0)) {
      uVar5 = ea_register_mask(extra0);
      uVar6 = uVar6 | uVar5;
    }
    if (((uVar4 & 0x40) != 0) && (right_opnd != (gen_node *)0x0)) {
      desc = right_opnd->desc;
      bVar7 = 0;
      peVar2 = desc->mem_ea;
      if (peVar2 != (ea *)0x0) {
        bVar7 = peVar2->type & 0x1f;
      }
      if (((bVar7 == 0) && (peVar2 = &desc->dest, (peVar2->type & 0x1f) == 0)) &&
         (peVar2 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        peVar2 = &desc->value;
      }
      uVar5 = ea_register_mask(peVar2);
      uVar6 = uVar6 | uVar5;
    }
    if (((uVar4 & 0x100) != 0) && (extra1 != (ea *)0x0)) {
      uVar5 = ea_register_mask(extra1);
      uVar6 = uVar6 | uVar5;
    }
    if (((uVar4 & 0x20) != 0) && (extra_opnd = nth_operand(node,3), extra_opnd != (gen_node *)0x0))
    {
      desc = extra_opnd->desc;
      bVar7 = 0;
      peVar2 = desc->mem_ea;
      if (peVar2 != (ea *)0x0) {
        bVar7 = peVar2->type & 0x1f;
      }
      if (((bVar7 == 0) && (peVar2 = &desc->dest, (peVar2->type & 0x1f) == 0)) &&
         (peVar2 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        peVar2 = &desc->value;
      }
      uVar5 = ea_register_mask(peVar2);
      uVar6 = uVar6 | uVar5;
    }
    if (((uVar4 & 0x10) != 0) && (extra_opnd = nth_operand(node,4), extra_opnd != (gen_node *)0x0))
    {
      desc = extra_opnd->desc;
      bVar7 = 0;
      peVar2 = desc->mem_ea;
      if (peVar2 != (ea *)0x0) {
        bVar7 = peVar2->type & 0x1f;
      }
      if (((bVar7 == 0) && (peVar2 = &desc->dest, (peVar2->type & 0x1f) == 0)) &&
         (peVar2 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        peVar2 = &desc->value;
      }
      uVar5 = ea_register_mask(peVar2);
      uVar6 = uVar6 | uVar5;
    }
    peVar2 = materialize_operand_record_from_descriptor
                       (node,entries[*spec_entry].opnd[0],(ea **)&g_template_extra_operands);
    peVar3 = materialize_operand_record_from_descriptor
                       (node,entries[*spec_entry].opnd[1],(ea **)&g_template_extra_operands);
    same = ea_operands_equal(peVar2,peVar3);
    if (same == 0) {
      invalidate_regs_written_by_entry(entries[entry_index].op,peVar2,peVar3,(ea *)0x0);
      entry_index = entry_index + 1;
    }
    free_ea((ea *)0x0);
    uVar5 = ea_register_mask(peVar2);
    uVar5 = uVar6 | uVar4 & 0xf | uVar5;
    entry = entries + *spec_entry;
    uVar1 = entry->op;
    if (uVar1 == 0x1c00) {
      value_type = '@';
    }
    else if (uVar1 == 0x2b00) {
LAB_00427664:
      value_type = '\x18';
    }
    else if ((uVar1 == 0x2700) || (uVar1 == 0x2800)) {
      bVar7 = node->type;
      kind_bits = bVar7 & 0xe0;
      if ((((kind_bits == 0x60) || (kind_bits == 0x80)) && ((bVar7 & 0x18) == 0x10)) ||
         ((((size_bits = bVar7 & 0xf8, size_bits == 0x10 || (size_bits == 0x18)) ||
           (kind_bits == 0x20)) || (kind_bits == 0x40)))) goto LAB_00427664;
      if ((((kind_bits == 0x60) || (kind_bits == 0x80)) && ((bVar7 & 0x18) == 8)) ||
         (size_bits == 8)) {
        value_type = '\b';
      }
      else {
        value_type = '\0';
      }
    }
    else {
      if (uVar1 == 0xf00) {
        uVar1 = entry->opnd[1];
      }
      else {
        uVar1 = entry->opnd[0];
      }
      uVar4 = g_operand_desc_table[uVar1] & 0xfc000000;
      if (uVar4 == 0x10000000) {
        value_type = node->child->type;
      }
      else if (uVar4 == 0x14000000) {
        if (node->child != (gen_node *)0x0) {
          value_type = node->child->next->type;
        }
        else {
          value_type = (*(unsigned short *)0x00000005);
        }
      }
      else if (uVar4 == 0x1c000000) {
        extra_opnd = nth_operand(node,2);
        value_type = extra_opnd->type;
      }
      else if ((uVar1 & 0x3fff) == 0xf) {
        count = count_operands(node);
        extra_opnd = nth_operand(node,count + -1);
        value_type = extra_opnd->type;
      }
      else if ((uVar1 & 0x3fff) == 0x10) {
        count = count_operands(node);
        extra_opnd = nth_operand(node,count + -2);
        value_type = extra_opnd->type;
      }
      else {
        value_type = node->type;
      }
    }
    bVar7 = (byte)slot | kind;
    uVar1 = choose_move_entry_register
                      (peVar2,peVar3,bVar7,node,entries[*spec_entry].op,value_type,
                       (int)(short)((ushort)uVar5 | operand_regs),account_node);
    if (uVar1 == 0) {
      choose_move_entry_register
                (peVar2,peVar3,bVar7,node,entries[*spec_entry].op,value_type,uVar5,account_node);
    }
    free_ea(peVar2);
    free_ea(peVar3);
    bVar7 = phase1_regs[slot_index];
    if (bVar7 != 0xff) {
      if (((char)bVar7 < ' ') && (-1 < (char)bVar7)) {
        uVar4 = 1 << (bVar7 & 0x1f);
      }
      else {
        uVar4 = (1 << (bVar7 - 0x1f & 0x1f) | 1 << (bVar7 - 0x20 & 0x1f)) << 0x10;
      }
      phase1_mask = phase1_mask | uVar4;
    }
    bVar7 = slot_regs[slot_index];
    if (((char)bVar7 < '\0') || ('\x0f' < (char)bVar7)) {
      if (((char)bVar7 < '\x10') || ('\x1f' < (char)bVar7)) {
        if (('\x1f' < (char)bVar7) && ((char)bVar7 < '/')) {
          mask_ptr = &account_node->desc->ftemp_regs;
          *mask_ptr = *mask_ptr | 1 << (bVar7 - 0x1f & 0x1f) | 1 << (bVar7 - 0x20 & 0x1f);
        }
      }
      else {
        mask_ptr = &account_node->desc->ftemp_regs;
        *mask_ptr = *mask_ptr | 1 << (bVar7 - 0x10 & 0x1f);
      }
    }
    else {
      mask_ptr = &account_node->desc->temp_regs;
      *mask_ptr = *mask_ptr | 1 << (bVar7 & 0x1f);
    }
    slot = slot + 1;
  } while (slot < 4);
  uVar1 = entries[entry_index].op;
  while (uVar1 != 0xff00) {
    entry = entries + entry_index;
    uVar1 = entry->op;
    if (((uVar1 < 0x24) || (0x26 < uVar1)) && (uVar1 != 0x18)) {
      if (uVar1 == 0x23) {
        peVar2 = make_call_routine_operand((uint)entry->opnd[0],node);
      }
      else {
        peVar2 = materialize_operand_record_from_descriptor
                           (node,entry->opnd[0],(ea **)&g_template_extra_operands);
      }
    }
    else {
      peVar2 = (ea *)0x0;
    }
    peVar3 = materialize_operand_record_from_descriptor
                       (node,entry->opnd[1],(ea **)&g_template_extra_operands);
    opnd3 = materialize_operand_record_from_descriptor
                      (node,entry->opnd[2],(ea **)&g_template_extra_operands);
    invalidate_regs_written_by_entry(entry->op,peVar2,peVar3,opnd3);
    free_ea(peVar2);
    free_ea(peVar3);
    free_ea(opnd3);
    entry_index = entry_index + 1;
    uVar1 = entries[entry_index].op;
  }
  return;
}



