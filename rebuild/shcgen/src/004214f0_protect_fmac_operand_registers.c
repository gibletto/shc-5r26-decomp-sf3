#include "decls.h"
#include "imports.h"

// entry: 004214f0
// name : protect_fmac_operand_registers
// size : 924
// sig  : void protect_fmac_operand_registers(gen_node * node, gen_node * * operands)


int __cdecl protect_fmac_operand_registers(gen_node *node,gen_node **operands)

{
  char base;
  short new_reg;
  uint mask32;
  uint excluded;
  ea *peVar1;
  uint uVar2;
  ushort uVar3;
  int *frame_field;
  byte bVar4;
  gen_node **opnd_ptr;
  ushort macro;
  ushort uStack_18;
  undefined2 uStack_16;
  uint done_temp;
  uint busy32;
  ea *xfer_dst;
  int i;
  node_desc *desc;
  ushort done_freused;
  uchar *flags_ptr;
  int low;
  ushort *mask_ptr;
  gen_node *opnd;
  ushort opnd_ftemp;
  
  uStack_18 = 0;
  uStack_16 = 0;
  done_temp = 0;
  done_freused = 0;
  busy32 = result_reg_exclusion_mask(node);
  i = 2;
  opnd_ptr = operands + 2;
  do {
    mask32 = ea_register_mask(&(*opnd_ptr)->desc->value);
    uVar2 = CONCAT22(uStack_16,uStack_18) | mask32;
    uStack_18 = (ushort)uVar2;
    uStack_16 = (undefined2)(uVar2 >> 0x10);
    if (((*opnd_ptr)->desc->flags2 & 2) != 0) {
      flags_ptr = &node->desc->flags2;
      *flags_ptr = *flags_ptr | 2;
    }
    mask_ptr = &node->desc->cached_regs;
    *mask_ptr = *mask_ptr | (*opnd_ptr)->desc->cached_regs;
    mask_ptr = &node->desc->reused_regs;
    *mask_ptr = *mask_ptr | (*opnd_ptr)->desc->reused_regs;
    mask_ptr = &node->desc->fcached_regs;
    *mask_ptr = *mask_ptr | (*opnd_ptr)->desc->fcached_regs;
    mask_ptr = &node->desc->freused_regs;
    *mask_ptr = *mask_ptr | (*opnd_ptr)->desc->freused_regs;
    frame_field = &(*opnd_ptr)->desc->frame_low;
    low = node->desc->frame_low;
    if (low < *frame_field) {
      *frame_field = low;
    }
    if (((*opnd_ptr)->desc->flags3 & 1) != 0) {
      flags_ptr = &node->desc->flags3;
      *flags_ptr = *flags_ptr | 1;
    }
    if (((mask32 & ~((int)(short)g_var_fpr_mask << 0x10) & (int)(short)~g_var_gpr_mask & done_temp)
         != 0) || ((((*opnd_ptr)->desc->fpref_regs & 1) == 0 && ((mask32 & 0x10000) != 0)))) {
      new_reg = -1;
      if ((*opnd_ptr)->desc->usage != '\x03') {
        new_reg = choose_float_register
                            ((ushort)(done_temp >> 0x10) | done_freused,
                             (*opnd_ptr)->desc->fpref_regs);
      }
      base = (char)new_reg;
      if (new_reg == -1) {
        macro = 0x1500;
        xfer_dst = &g_ea_push;
        flags_ptr = &(*opnd_ptr)->desc->flags2;
        *flags_ptr = *flags_ptr | 8;
        g_stmt_pushed_operand = '\x01';
      }
      else {
        macro = 0xc00;
        fill_ea(&(*opnd_ptr)->desc->dest,'\x01',base,-1,'\0',0,(label_ref *)0x0);
        mask_ptr = &(*opnd_ptr)->desc->ftemp_regs;
        *mask_ptr = *mask_ptr | 1 << (base - 0x10U & 0x1f);
        xfer_dst = &(*opnd_ptr)->desc->dest;
      }
      desc = (*opnd_ptr)->desc;
      if (desc->usage == '\x03') {
        bVar4 = 0x40;
        peVar1 = &desc->value;
        peVar1->type = peVar1->type | 0x40;
      }
      else {
        bVar4 = (*opnd_ptr)->type & 0xf8;
      }
      opnd = *opnd_ptr;
      mask32 = result_reg_exclusion_mask(opnd);
      excluded = result_reg_exclusion_mask(*opnd_ptr);
      emit_operand_transfer
                (&(*opnd_ptr)->desc->value,xfer_dst,'0',*opnd_ptr,macro,bVar4,excluded,mask32,
                 (int)opnd);
      if (new_reg == -1) {
        (*opnd_ptr)->desc->opnd_class = '\x03';
      }
      else if ((1 << (base - 0x10U & 0x1f) & (int)(short)~g_var_fpr_mask) == 0) {
        (*opnd_ptr)->desc->opnd_class = '\x01';
      }
      else {
        (*opnd_ptr)->desc->opnd_class = '\0';
      }
      if ((*opnd_ptr)->desc->usage == '\x03') {
        new_reg = choose_general_register(uStack_18,(*opnd_ptr)->desc->pref_regs,'\0');
        uVar3 = 1 << ((byte)new_reg & 0x1f);
        mask_ptr = &(*opnd_ptr)->desc->busy_regs;
        *mask_ptr = *mask_ptr | uVar3;
        g_used_gpr_mask = g_used_gpr_mask | (*opnd_ptr)->desc->busy_regs;
        mask_ptr = &(*opnd_ptr)->desc->temp_regs;
        *mask_ptr = *mask_ptr | uVar3;
        peVar1 = alloc_zeroed(0xc);
        (*opnd_ptr)->desc->addr_reg_ea = peVar1;
        fill_ea((*opnd_ptr)->desc->addr_reg_ea,'\x01',(byte)new_reg,-1,'\0',0,(label_ref *)0x0);
        opnd = *opnd_ptr;
        emit_operand_transfer
                  (&g_ea_pop,opnd->desc->addr_reg_ea,'P',opnd,0xc00,'@',uVar2,uVar2,(int)opnd);
        desc = (*opnd_ptr)->desc;
        peVar1 = copy_ea(desc->addr_reg_ea);
        desc->mem_ea = peVar1;
        peVar1 = (*opnd_ptr)->desc->mem_ea;
        peVar1->type = peVar1->type & 0xf8 | 8;
      }
    }
    bVar4 = 0;
    desc = (*opnd_ptr)->desc;
    peVar1 = desc->mem_ea;
    if (peVar1 != (ea *)0x0) {
      bVar4 = peVar1->type & 0x1f;
    }
    if (((bVar4 == 0) && (peVar1 = &desc->dest, (peVar1->type & 0x1f) == 0)) &&
       (peVar1 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      peVar1 = &desc->value;
    }
    uVar2 = ea_register_mask(peVar1);
    busy32 = busy32 | uVar2;
    desc = (*opnd_ptr)->desc;
    uVar3 = desc->temp_regs;
    done_freused = done_freused | desc->freused_regs;
    opnd_ftemp = desc->ftemp_regs;
    mask_ptr = &node->desc->temp_regs;
    *mask_ptr = *mask_ptr | uVar3;
    done_temp = done_temp | (int)(short)opnd_ftemp << 0x10 | (int)(short)uVar3;
    mask_ptr = &node->desc->ftemp_regs;
    *mask_ptr = *mask_ptr | (*opnd_ptr)->desc->ftemp_regs;
    i = i + -1;
    opnd_ptr = opnd_ptr + -1;
  } while (-1 < i);
  node->desc->busy_regs = (ushort)busy32;
  node->desc->fbusy_regs = (ushort)(busy32 >> 0x10);
  return;
}



