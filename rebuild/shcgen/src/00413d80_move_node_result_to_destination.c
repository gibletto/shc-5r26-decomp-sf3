#include "decls.h"
#include "imports.h"

// entry: 00413d80
// name : move_node_result_to_destination
// size : 1064
// sig  : void move_node_result_to_destination(gen_node * node)


int __cdecl move_node_result_to_destination(gen_node *node)

{
  unsigned char _frec_20[32];
#define opnd0 (*(ea * *)(_frec_20 + 0))
#define opnd1 (*(ea * *)(_frec_20 + 4))
#define opnd2 (*(ea * *)(_frec_20 + 8))
#define opnd3 (*(undefined4 *)(_frec_20 + 12))
#define opnd4 (*(undefined4 *)(_frec_20 + 16))
#define opnd5 (*(undefined4 *)(_frec_20 + 20))
#define opnd6 (*(undefined4 *)(_frec_20 + 24))
#define push8 (*(uint *)(_frec_20 + 28))
  uchar type;
  char base;
  tmpl_header *tmpl;
  byte ea_kind;
  bool single_push;
  uchar type_flags;
  short sVar1;
  node_desc *desc;
  int new_disp;
  char new_index;
  label_ref *new_labels;
  ea *saved;
  char usage;
  
  type = node->type;
  desc = node->desc;
  usage = desc->usage;
  if ((desc->flags3 & 0x10) == 0) {
    saved = desc->saved_ea;
    ea_kind = 0;
    if (saved != (ea *)0x0) {
      ea_kind = saved->type & 0x1f;
    }
    if (ea_kind != 0) {
      ea_kind = 0;
      if (desc->saved_reg_ea != (ea *)0x0) {
        ea_kind = desc->saved_reg_ea->type & 0x1f;
      }
      if (ea_kind != 0) {
        opnd1 = desc->saved_reg_ea;
        opnd0 = saved;
        load_slot_register_operands(3,node,&opnd0);
        tmpl = select_transfer_template(0,0,opnd0,opnd1,opnd2,type,usage,node);
        if (tmpl != (tmpl_header *)0x0) {
          emit_template_record_sequence_for_node(node,tmpl->entries,&opnd0);
        }
        free_slot_register_operands(3,&opnd0);
      }
    }
  }
  else {
    ea_kind = 0;
    if (desc->saved_ea != (ea *)0x0) {
      ea_kind = desc->saved_ea->type & 0x1f;
    }
    if (ea_kind != 0) {
      opnd1 = new_ea_operand_with_flags('\x03','\x0f',-1,0,'\0',(label_ref *)0x0);
      opnd0 = node->desc->saved_ea;
      opnd2 = (ea *)0x0;
      tmpl = select_transfer_template(0,0,opnd0,opnd1,(ea *)0x0,type,usage,node);
      if (tmpl != (tmpl_header *)0x0) {
        opnd3 = 0;
        opnd4 = 0;
        opnd5 = 0;
        opnd6 = 0;
        emit_template_record_sequence_for_node(node,tmpl->entries,&opnd0);
      }
      free_ea(opnd1);
    }
  }
  desc = node->desc;
  if ((desc->flags2 & 0xc) == 0) {
    opnd0 = &desc->value;
    ea_kind = opnd0->type & 0x1f;
    if ((ea_kind != 0) && (((desc->dest).type & 0x1f) != 0)) {
      if ((desc->flags3 & 2) == 0) {
        if (((node->type & 0xe0) == 0x80) &&
           ((node->parent->op != IL_ASSIGN || ((node->parent->type & 0xe0) != 0x80)))) {
          node->type = '@';
        }
      }
      else {
        node->type = node->parent->type;
      }
      opnd1 = &desc->dest;
      load_slot_register_operands(1,node,&opnd0);
      tmpl = select_transfer_template(0,0,opnd0,opnd1,opnd2,node->type,usage,node);
      if (tmpl != (tmpl_header *)0x0) {
        emit_template_record_sequence_for_node(node,tmpl->entries,&opnd0);
      }
      node->type = type;
      free_slot_register_operands(1,&opnd0);
      return;
    }
    if ((ea_kind != 0) && ((desc->target_regs != 0 || (desc->ftarget_regs != 0)))) {
      new_labels = (label_ref *)0x0;
      type_flags = '\0';
      new_disp = 0;
      new_index = -1;
      if (desc->ftarget_regs == 0) {
        sVar1 = single_bit_position((uint)desc->target_regs);
        base = (char)sVar1;
      }
      else {
        sVar1 = float_mask_to_register(desc->ftarget_regs);
        base = (char)sVar1;
      }
      opnd1 = new_ea_operand_with_flags('\x01',base,new_index,new_disp,type_flags,new_labels);
      load_slot_register_operands(1,node,&opnd0);
      tmpl = select_transfer_template(0,0,opnd0,opnd1,opnd2,type,usage,node);
      if (tmpl != (tmpl_header *)0x0) {
        emit_template_record_sequence_for_node(node,tmpl->entries,&opnd0);
      }
      free_ea(opnd1);
      free_slot_register_operands(1,&opnd0);
      return;
    }
  }
  else {
    if (((desc->value).type & 0x1f) != 0) {
      opnd1 = new_ea_operand_with_flags('\x03','\x0f',-1,0,'\0',(label_ref *)0x0);
      opnd0 = &node->desc->value;
      single_push = (node->desc->flags2 & 4) == 0;
      if (single_push) {
        sVar1 = 1;
      }
      else {
        sVar1 = 2;
      }
      push8 = (uint)!single_push;
      load_slot_register_operands(sVar1,node,&opnd0);
      tmpl = select_transfer_template(push8,6,opnd0,opnd1,opnd2,type,usage,node);
      if (tmpl != (tmpl_header *)0x0) {
        emit_template_record_sequence_for_node(node,tmpl->entries,&opnd0);
      }
      free_ea(opnd1);
      free_slot_register_operands(sVar1,&opnd0);
    }
    desc = node->desc;
    opnd1 = &desc->dest;
    if (((opnd1->type & 0x1f) != 0) && ((desc->flags2 & 4) != 0)) {
      opnd0 = &desc->value;
      load_slot_register_operands(1,node,&opnd0);
      tmpl = select_transfer_template(1,3,opnd0,opnd1,opnd2,type,usage,node);
      if (tmpl != (tmpl_header *)0x0) {
        emit_template_record_sequence_for_node(node,tmpl->entries,&opnd0);
      }
      free_slot_register_operands(1,&opnd0);
    }
  }
  return;
#undef opnd0
#undef opnd1
#undef opnd2
#undef opnd3
#undef opnd4
#undef opnd5
#undef opnd6
#undef push8
}



