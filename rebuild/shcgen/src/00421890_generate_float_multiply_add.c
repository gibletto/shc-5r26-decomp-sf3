#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00421890
// name : generate_float_multiply_add
// size : 1386
// sig  : void generate_float_multiply_add(gen_node * node)


int __cdecl generate_float_multiply_add(gen_node *node)

{
  unsigned char _frec_1c[28];
#define live_regs (*(uint *)(_frec_1c + 0))
#define addend (*(gen_node * *)(_frec_1c + 4))
#define operands (*(gen_node * (*)[3])(_frec_1c + 12))
#define addend_slot (*(gen_node * *)(_frec_1c + 24))
  char cVar1;
  byte bVar2;
  short reg;
  ea *operand;
  uint mask32;
  ea *opnd_ea;
  gen_node **opnd_ptr;
  gen_node *pgVar3;
  gen_node **next_ptr;
  ushort uVar4;
  ushort preferred;
  node_desc *desc;
  gen_node *final_slot;
  uchar *flags_ptr;
  ushort *mask_ptr;
  bool mul_is_right;
  
  addend = node->child;
  if (addend->op == IL_MUL) {
    pgVar3 = addend;
    if (addend == (gen_node *)0x0) {
      addend = (gen_node *)0x0;
      mul_is_right = false;
    }
    else {
      mul_is_right = false;
      addend = addend->next;
    }
  }
  else {
    if (addend == (gen_node *)0x0) {
      pgVar3 = (gen_node *)0x0;
    }
    else {
      pgVar3 = addend->next;
    }
    mul_is_right = true;
  }
  operands[1] = pgVar3->child;
  pgVar3 = (gen_node *)0x0;
  if (operands[1] != (gen_node *)0x0) {
    pgVar3 = operands[1]->next;
  }
  if ((operands[1]->val3 & 1) == 0) {
    operands[1]->desc->fpref_regs = 0xe;
    pgVar3->desc->fpref_regs = 1;
  }
  else {
    operands[1]->desc->fpref_regs = 1;
    pgVar3->desc->fpref_regs = 0xe;
  }
  addend->desc->fpref_regs = 0xe;
  if (((node->desc->flags2 & 0x40) == 0) || (!mul_is_right)) {
    operands[2] = addend;
    operands[0] = operands[1];
    operands[1] = pgVar3;
  }
  else {
    operands[0] = addend;
    operands[2] = pgVar3;
  }
  operands[0]->desc->busy_regs = node->desc->busy_regs;
  operands[0]->desc->fbusy_regs = node->desc->fbusy_regs;
  operands[0]->desc->frame_top = node->desc->frame_top;
  flags_ptr = &operands[0]->desc->flags7;
  *flags_ptr = *flags_ptr | node->desc->flags7 & 0x40;
  dispatch_and_finalize_code_node(operands[0]);
  opnd_ptr = operands + 1;
  do {
    next_ptr = opnd_ptr + 1;
    (*opnd_ptr)->desc->busy_regs = opnd_ptr[-1]->desc->busy_regs;
    (*opnd_ptr)->desc->fbusy_regs = opnd_ptr[-1]->desc->fbusy_regs;
    (*opnd_ptr)->desc->frame_top = opnd_ptr[-1]->desc->frame_top;
    flags_ptr = &(*opnd_ptr)->desc->flags7;
    *flags_ptr = *flags_ptr | opnd_ptr[-1]->desc->flags7 & 0x40;
    dispatch_and_finalize_code_node(*opnd_ptr);
    opnd_ptr = next_ptr;
  } while (next_ptr < &addend_slot);
  protect_fmac_operand_registers(node,operands);
  operand = alloc_zeroed(0xc);
  opnd_ptr = operands;
  live_regs = 0x10000;
  do {
    desc = (*opnd_ptr)->desc;
    bVar2 = 0;
    opnd_ea = desc->mem_ea;
    if (opnd_ea != (ea *)0x0) {
      bVar2 = opnd_ea->type & 0x1f;
    }
    if (((bVar2 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
       (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      opnd_ea = &desc->value;
    }
    opnd_ptr = opnd_ptr + 1;
    mask32 = ea_register_mask(opnd_ea);
    live_regs = live_regs | mask32;
  } while (opnd_ptr < &addend_slot);
  opnd_ptr = operands + 2;
  pgVar3 = (gen_node *)0x2;
  do {
    bVar2 = 0;
    desc = (*opnd_ptr)->desc;
    opnd_ea = desc->mem_ea;
    if (opnd_ea != (ea *)0x0) {
      bVar2 = opnd_ea->type & 0x1f;
    }
    if (((bVar2 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
       (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      opnd_ea = &desc->value;
    }
    uVar4 = (ushort)(live_regs >> 0x10);
    if (addend == *opnd_ptr) {
      if (desc->opnd_class == '\0') {
        bVar2 = opnd_ea->base;
      }
      else if ((node->op == IL_A_ADD) && (desc->opnd_class == '\x01')) {
        bVar2 = opnd_ea->base;
      }
      else {
        desc = node->desc;
        bVar2 = (desc->dest).type & 0x1f;
        if ((bVar2 == 0) ||
           ((bVar2 != 1 || (bVar2 = (desc->dest).base, (live_regs & 1 << (bVar2 & 0x1f)) != 0)))) {
          if ((desc->ftarget_regs == 0) ||
             (reg = float_mask_to_register(desc->ftarget_regs), (live_regs & (int)reg) != 0)) {
            reg = choose_float_register(uVar4,0);
            bVar2 = (byte)reg;
          }
          else {
            reg = float_mask_to_register(node->desc->ftarget_regs);
            bVar2 = (byte)reg;
          }
        }
      }
      node->desc->regs_2c[(int)pgVar3] = bVar2;
      fill_ea(operand,'\x01',bVar2,-1,'\0',0,(label_ref *)0x0);
      emit_operand_transfer
                (opnd_ea,operand,(byte)pgVar3 | 0x20,node,0xc00,(*opnd_ptr)->type & 0xf8,live_regs,
                 live_regs,(int)node);
      addend_slot = pgVar3;
    }
    else {
      if ((desc->fpref_regs & 1) == 0) {
        if ((opnd_ea->type & 0x1f) == 1) {
          cVar1 = opnd_ea->base;
        }
        else {
          reg = choose_float_register(uVar4,0);
          cVar1 = (char)reg;
        }
      }
      else {
        cVar1 = '\x10';
      }
      node->desc->regs_2c[(int)pgVar3] = cVar1;
      fill_ea(operand,'\x01',cVar1,-1,'\0',0,(label_ref *)0x0);
      emit_operand_transfer
                (opnd_ea,operand,(byte)pgVar3 | 0x20,node,0xc00,(*opnd_ptr)->type & 0xf8,live_regs,
                 live_regs,(int)node);
    }
    opnd_ptr = opnd_ptr + -1;
    mask32 = ea_register_mask(opnd_ea);
    final_slot = addend_slot;
    mask_ptr = &node->desc->fbusy_regs;
    *mask_ptr = *mask_ptr | 1 << (node->desc->regs_2c[(int)pgVar3] - 0x10U & 0x1f);
    g_used_fpr_mask = g_used_fpr_mask | node->desc->fbusy_regs;
    mask_ptr = &node->desc->ftemp_regs;
    *mask_ptr = *mask_ptr | 1 << (node->desc->regs_2c[(int)pgVar3] - 0x10U & 0x1f);
    live_regs = live_regs ^ mask32 | 1 << (node->desc->regs_2c[(int)pgVar3] & 0x1fU);
    pgVar3 = (gen_node *)((int)&pgVar3[-1].desc + 3);
  } while (operands <= opnd_ptr);
  fill_ea(&node->desc->value,'\x01',node->desc->regs_2c[(int)addend_slot],-1,'\0',0,(label_ref *)0x0
         );
  desc = node->desc;
  cVar1 = desc->regs_2c[(int)final_slot];
  mask32 = (uint)(short)g_var_fpr_mask;
  desc->opnd_class = '\x01';
  if ((mask32 & 1 << (cVar1 - 0x10U & 0x1f)) == 0) {
    desc->opnd_class = '\0';
  }
  if (addend->desc->usage == '\x03') {
    fill_ea(operand,'\x01',node->desc->regs_2c[(int)addend_slot],-1,'\0',0,(label_ref *)0x0);
    emit_operand_transfer
              (operand,opnd_ea,'#',node,0xf00,addend->type & 0xf8,(int)(short)node->desc->busy_regs,
               0,(int)node);
  }
  free_ea(operand);
  if (((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) && (g_fpscr_pr != '\0')) {
    cVar1 = '\0';
    uVar4 = 0;
    mask32 = result_reg_exclusion_mask(node);
    reg = choose_general_register((ushort)mask32,uVar4,cVar1);
    if (reg == -1) {
      reg = choose_general_register(0,0,'\0');
    }
    bVar2 = (byte)reg;
    cVar1 = '\0';
    node->desc->regs_2c[3] = bVar2;
    preferred = 0;
    mask_ptr = &node->desc->temp_regs;
    *mask_ptr = *mask_ptr | 1 << (bVar2 & 0x1f);
    mask32 = result_reg_exclusion_mask(node);
    uVar4 = (ushort)(1 << (bVar2 & 0x1f));
    reg = choose_general_register((ushort)mask32 | uVar4,preferred,cVar1);
    if (reg == -1) {
      reg = choose_general_register(uVar4,0,'\0');
    }
    node->desc->regs_2c[4] = (byte)reg;
    mask_ptr = &node->desc->temp_regs;
    *mask_ptr = *mask_ptr | 1 << ((byte)reg & 0x1f);
    flags_ptr = &node->desc->fpu_mode_flags;
    *flags_ptr = *flags_ptr | 1;
  }
  return;
#undef live_regs
#undef addend
#undef operands
#undef addend_slot
}



