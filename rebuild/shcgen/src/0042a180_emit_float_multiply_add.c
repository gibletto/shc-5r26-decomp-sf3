#include "decls.h"
#include "imports.h"

// entry: 0042a180
// name : emit_float_multiply_add
// size : 911
// sig  : void emit_float_multiply_add(gen_node * node)


int __cdecl emit_float_multiply_add(gen_node *node)

{
  unsigned char _frec_34[52];
#define addend (*(gen_node * *)(_frec_34 + 0))
#define tmpl_opnd0 (*(ea * *)(_frec_34 + 4))
#define tmpl_opnd1 (*(ea * *)(_frec_34 + 8))
#define tmpl_opnd2 (*(ea * *)(_frec_34 + 12))
#define tmpl_opnd3 (*(ea * *)(_frec_34 + 16))
#define local_20 (*(undefined4 *)(_frec_34 + 20))
#define local_1c (*(undefined4 *)(_frec_34 + 24))
#define local_18 (*(undefined4 *)(_frec_34 + 28))
#define operands (*(gen_node * (*)[3])(_frec_34 + 32))
#define addend_in_memory (*(gen_node * *)(_frec_34 + 44))
#define mac_src (*(ea * *)(_frec_34 + 48))
  byte ea_kind;
  gen_node *pgVar1;
  tmpl_header *tmpl;
  ea *dst;
  gen_node **slot;
  int i;
  bool addend_first;
  node_desc *desc;
  char slot_reg;
  
  addend = node->child;
  if (addend->op == IL_MUL) {
    pgVar1 = addend;
    if (addend == (gen_node *)0x0) {
      addend = (gen_node *)0x0;
      addend_first = false;
    }
    else {
      addend_first = false;
      addend = addend->next;
    }
  }
  else {
    if (addend == (gen_node *)0x0) {
      pgVar1 = (gen_node *)0x0;
    }
    else {
      pgVar1 = addend->next;
    }
    addend_first = true;
  }
  operands[0] = pgVar1->child;
  operands[2] = (gen_node *)0x0;
  if (operands[0] != (gen_node *)0x0) {
    operands[2] = operands[0]->next;
  }
  if (((node->desc->flags2 & 0x40) == 0) || (!addend_first)) {
    operands[1] = operands[2];
    operands[2] = addend;
  }
  else {
    operands[1] = operands[0];
    operands[0] = addend;
  }
  slot = operands;
  do {
    pgVar1 = *slot;
    slot = slot + 1;
    emit_node_code(pgVar1);
  } while (slot < &addend_in_memory);
  if (addend->desc->usage == '\x03') {
    addend_in_memory = (gen_node *)0x1;
    if ((addend->desc->flags2 & 8) != 0) {
      load_node_address_register(addend);
    }
  }
  else {
    addend_in_memory = (gen_node *)0x0;
  }
  tmpl_opnd3 = (ea *)0x0;
  i = 2;
  slot = operands + 2;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  do {
    pgVar1 = *slot;
    ea_kind = 0;
    desc = pgVar1->desc;
    tmpl_opnd0 = desc->mem_ea;
    if (tmpl_opnd0 != (ea *)0x0) {
      ea_kind = tmpl_opnd0->type & 0x1f;
    }
    if ((ea_kind == 0) && (tmpl_opnd0 = &desc->dest, (tmpl_opnd0->type & 0x1f) == 0)) {
      if ((desc->flags2 & 8) == 0) {
        tmpl_opnd0 = &desc->value;
      }
      else {
        tmpl_opnd0 = &g_ea_pop;
      }
    }
    tmpl_opnd1 = new_ea_operand_with_flags('\x01',node->desc->regs_2c[i],-1,0,'\0',(label_ref *)0x0)
    ;
    slot_reg = node->desc->regs_34[i];
    if (slot_reg == -1) {
      tmpl_opnd2 = (ea *)0x0;
    }
    else {
      tmpl_opnd2 = new_ea_operand_with_flags('\x01',slot_reg,-1,0,'\0',(label_ref *)0x0);
    }
    tmpl = select_transfer_template
                     (0,1,tmpl_opnd0,tmpl_opnd1,tmpl_opnd2,pgVar1->type & 0xf8,pgVar1->desc->usage,
                      pgVar1);
    if (tmpl != (tmpl_header *)0x0) {
      emit_template_record_sequence_for_node(pgVar1,tmpl->entries,&tmpl_opnd0);
    }
    if ((addend != pgVar1) && ((pgVar1->desc->fpref_regs & 1) == 0)) {
      mac_src = copy_ea(tmpl_opnd1);
    }
    slot = slot + -1;
    i = i + -1;
    free_ea(tmpl_opnd1);
    free_ea(tmpl_opnd2);
  } while (operands <= slot);
  if ((node->desc->fpu_mode_flags & 1) != 0) {
    tmpl_opnd2 = new_ea_operand_with_flags('\x01',node->desc->regs_2c[3],-1,0,'\0',(label_ref *)0x0)
    ;
    tmpl_opnd3 = new_ea_operand_with_flags('\x01',node->desc->regs_2c[4],-1,0,'\0',(label_ref *)0x0)
    ;
    emit_psd_for_node(0x2e,-1,'\0','\x02',tmpl_opnd2,tmpl_opnd3,node);
  }
  pgVar1 = node;
  dst = copy_ea(&node->desc->value);
  emit_psd_for_node(0xcc,-1,'\0','\x02',mac_src,dst,pgVar1);
  if (addend_in_memory != (gen_node *)0x0) {
    ea_kind = 0;
    tmpl_opnd0 = &node->desc->value;
    desc = addend->desc;
    tmpl_opnd1 = desc->mem_ea;
    if (tmpl_opnd1 != (ea *)0x0) {
      ea_kind = tmpl_opnd1->type & 0x1f;
    }
    if ((ea_kind == 0) && (tmpl_opnd1 = &desc->dest, (tmpl_opnd1->type & 0x1f) == 0)) {
      if ((desc->flags2 & 8) == 0) {
        tmpl_opnd1 = &desc->value;
      }
      else {
        tmpl_opnd1 = &g_ea_pop;
      }
    }
    slot_reg = node->desc->regs_34[3];
    if (slot_reg == -1) {
      tmpl_opnd2 = (ea *)0x0;
    }
    else {
      tmpl_opnd2 = new_ea_operand_with_flags('\x01',slot_reg,-1,0,'\0',(label_ref *)0x0);
    }
    tmpl = select_transfer_template
                     (0,2,tmpl_opnd0,tmpl_opnd1,tmpl_opnd2,addend->type & 0xf8,addend->desc->usage,
                      addend);
    if (tmpl != (tmpl_header *)0x0) {
      emit_template_record_sequence_for_node(addend,tmpl->entries,&tmpl_opnd0);
    }
    free_ea(tmpl_opnd2);
  }
  return;
#undef addend
#undef tmpl_opnd0
#undef tmpl_opnd1
#undef tmpl_opnd2
#undef tmpl_opnd3
#undef local_20
#undef local_1c
#undef local_18
#undef operands
#undef addend_in_memory
#undef mac_src
}



