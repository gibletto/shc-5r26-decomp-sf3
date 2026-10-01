#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_template_extra_operands
#define g_template_extra_operands (*(ea * *)(g_sd + 0x18aa0))


// entry: 00424c80
// name : apply_template_to_node
// size : 3067
// sig  : void apply_template_to_node(gen_node * node, tmpl_header * tmpl, uchar slot_kind, ea * extra0, ea * extra1, uint operand_regs, gen_node * account_node)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl
apply_template_to_node
          (gen_node *node,tmpl_header *tmpl,uchar slot_kind,ea *extra0,ea *extra1,uint operand_regs,
          gen_node *account_node)

{
  uchar uVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  void *new_ea;
  uint uVar5;
  byte bVar6;
  ushort uVar7;
  undefined4 *extra_slot;
  undefined4 *next_slot;
  ea *opnd_ea;
  gen_node *operand;
  ushort uVar8;
  char base;
  short slot_count;
  gen_node *local_18;
  uint written_regs;
  uint spec;
  char *slot_regs;
  node_desc *desc;
  uchar *flag_byte;
  gen_node *left_opnd;
  ushort *mask_ptr;
  il_op op;
  
  written_regs = 0;
  left_opnd = node->child;
  operand = (gen_node *)0x0;
  if (left_opnd != (gen_node *)0x0) {
    operand = left_opnd->next;
  }
  bVar2 = slot_kind & 0xf0;
  if (((bVar2 == 0x10) && (g_request->cpu == 4)) && (g_request->unknown_155[2] == '\0')) {
    desc = node->desc;
    bVar6 = desc->tmpl->flags2;
    if (((bVar6 & 4) == 0) || ((g_fpscr_pr != '\x01' && (g_fpscr_pr != '\x02')))) {
      if (((bVar6 & 2) != 0) && ((g_fpscr_pr == '\0' || (g_fpscr_pr == '\x02')))) {
        desc->fpu_mode_flags = desc->fpu_mode_flags | 1;
        g_fpscr_pr = '\x01';
      }
    }
    else {
      desc->fpu_mode_flags = desc->fpu_mode_flags | 1;
      g_fpscr_pr = '\0';
    }
  }
  assign_template_slot_registers(node,tmpl,slot_kind,extra0,extra1,operand_regs,account_node);
  if ((bVar2 == 0x10) || (bVar2 == 0x30)) {
    if ((slot_kind & 0xf0) == 0x10) {
      slot_count = 5;
      slot_regs = node->desc->regs_2c;
    }
    else if ((slot_kind & 0xf0) == 0x30) {
      slot_count = 3;
      slot_regs = node->desc->regs_41;
    }
    else {
      slot_count = 0;
      slot_regs = (char *)0x0;
    }
    zero_words((uint *)&g_template_extra_operands,7);
    _g_template_extra_operands = extra0;
    sVar3 = 0;
    _DAT_00458aa4 = extra1;
    extra_slot = &DAT_00458aa8;
    if (slot_count != 0) {
      do {
        next_slot = extra_slot;
        if ((slot_regs != (char *)0x0) && (slot_regs[sVar3] != -1)) {
          next_slot = extra_slot + 1;
          new_ea = alloc_zeroed(0xc);
          *extra_slot = new_ea;
          fill_ea((ea *)*extra_slot,'\x01',slot_regs[sVar3],-1,'\0',0,(label_ref *)0x0);
        }
        sVar3 = sVar3 + 1;
        extra_slot = next_slot;
      } while (sVar3 < slot_count);
    }
    assign_move_entry_registers
              (node,tmpl,slot_kind + '\x10',extra0,extra1,(ushort)operand_regs,account_node);
    if (slot_count != 0) {
      (*(unsigned short *)((char *)&local_18 + 0)) = slot_count;
      extra_slot = &DAT_00458aa8;
      do {
        next_slot = extra_slot;
        if ((ea *)*extra_slot != (ea *)0x0) {
          next_slot = extra_slot + 1;
          free_ea((ea *)*extra_slot);
          *extra_slot = 0;
        }
        (*(unsigned short *)((char *)&local_18 + 0)) = (short)local_18 + -1;
        extra_slot = next_slot;
      } while ((short)local_18 != 0);
    }
  }
  else {
    written_regs = (uint)tmpl->fclobbers << 0x10 | (uint)tmpl->clobbers;
  }
  mask_ptr = &account_node->desc->temp_regs;
  *mask_ptr = *mask_ptr | (ushort)tmpl->clobbers;
  g_used_gpr_mask = g_used_gpr_mask | tmpl->clobbers;
  mask_ptr = &account_node->desc->ftemp_regs;
  *mask_ptr = *mask_ptr | (ushort)tmpl->fclobbers;
  g_used_fpr_mask = g_used_fpr_mask | tmpl->fclobbers;
  if (extra0 != (ea *)0x0) {
    invalidate_register_contents(written_regs);
    if ((written_regs & 1) == 0) {
      return;
    }
    g_r0_used = 1;
    return;
  }
  uVar1 = tmpl->result;
  switch(uVar1) {
  case '\0':
    if ((node->desc->flags2 & 8) != 0) {
      node->desc->opnd_class = '\x03';
    }
    break;
  case '\x01':
  case '\x02':
    if (uVar1 == '\x01') {
      bVar2 = 0;
      desc = left_opnd->desc;
      opnd_ea = desc->mem_ea;
      if (opnd_ea != (ea *)0x0) {
        bVar2 = opnd_ea->type & 0x1f;
      }
      local_18 = left_opnd;
      if (((bVar2 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
         (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        opnd_ea = &desc->value;
      }
    }
    else {
      desc = operand->desc;
      bVar2 = 0;
      opnd_ea = desc->mem_ea;
      if (opnd_ea != (ea *)0x0) {
        bVar2 = opnd_ea->type & 0x1f;
      }
      local_18 = operand;
      if (((bVar2 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
         (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        opnd_ea = &desc->value;
      }
    }
    uVar5 = ea_register_mask(opnd_ea);
    written_regs = written_regs | uVar5;
    bVar2 = opnd_ea->type & 0x1f;
    if (((bVar2 == 2) && (opnd_ea->base == 'l')) || ((bVar2 == 8 && (opnd_ea->base == 'l')))) {
      if (local_18->desc->opnd_class == '\x02') {
        flag_byte = &node->desc->flags3;
        *flag_byte = *flag_byte | 8;
        if (node->desc->tmpl == (tmpl_header *)0x0) {
          flag_byte = &node->desc->flags3;
          *flag_byte = *flag_byte | 0x80;
        }
      }
      node->desc->busy_regs = local_18->desc->busy_regs;
      node->desc->fbusy_regs = local_18->desc->fbusy_regs;
      bVar2 = 0;
      node->desc->frame_top = local_18->desc->frame_top;
      desc = local_18->desc;
      opnd_ea = desc->mem_ea;
      if (opnd_ea != (ea *)0x0) {
        bVar2 = opnd_ea->type & 0x1f;
      }
      if (((bVar2 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
         (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        opnd_ea = &desc->value;
      }
      copy_ea_into(&node->desc->value,opnd_ea);
      node->desc->opnd_class = local_18->desc->opnd_class;
    }
    else {
      if (local_18->desc->opnd_class == '\x02') {
        flag_byte = &node->desc->flags3;
        *flag_byte = *flag_byte | 8;
        if (node->desc->tmpl == (tmpl_header *)0x0) {
          flag_byte = &node->desc->flags3;
          *flag_byte = *flag_byte | 0x80;
        }
      }
      node->desc->busy_regs = local_18->desc->busy_regs;
      node->desc->fbusy_regs = local_18->desc->fbusy_regs;
      bVar2 = 0;
      desc = local_18->desc;
      opnd_ea = desc->mem_ea;
      if (opnd_ea != (ea *)0x0) {
        bVar2 = opnd_ea->type & 0x1f;
      }
      if (((bVar2 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
         (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        opnd_ea = &desc->value;
      }
      copy_ea_into(&node->desc->value,opnd_ea);
      node->desc->opnd_class = local_18->desc->opnd_class;
    }
    break;
  case '\x03':
  case '\x04':
  case '\n':
  case '\f':
  case '\r':
    if (uVar1 == '\x03') {
      spec = tmpl->reg_spec[0];
      sVar3 = (short)node->desc->regs_2c[0];
    }
    else if (uVar1 == '\x04') {
      spec = tmpl->reg_spec[1];
      sVar3 = (short)node->desc->regs_2c[1];
    }
    else if (uVar1 == '\n') {
      spec = tmpl->reg_spec[2];
      sVar3 = (short)node->desc->regs_2c[2];
    }
    else if (uVar1 == '\f') {
      sVar3 = (short)node->desc->regs_2c[3];
      spec = tmpl->reg_spec[3];
    }
    else {
      sVar3 = (short)node->desc->regs_2c[4];
      spec = tmpl->reg_spec[4];
    }
    bVar2 = (byte)sVar3;
    if ((sVar3 < 0x20) && (-1 < sVar3)) {
      uVar5 = 1 << (bVar2 & 0x1f);
    }
    else {
      uVar5 = (1 << (bVar2 - 0x1f & 0x1f) | 1 << (bVar2 - 0x20 & 0x1f)) << 0x10;
    }
    written_regs = written_regs | uVar5;
    if ((sVar3 < 0x20) || (0x2e < sVar3)) {
      if ((sVar3 < 0x10) || (0x1f < sVar3)) {
        uVar8 = 1 << (bVar2 & 0x1f);
        mask_ptr = &node->desc->busy_regs;
        *mask_ptr = *mask_ptr | uVar8;
        g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
        mask_ptr = &node->desc->temp_regs;
        *mask_ptr = *mask_ptr | uVar8;
      }
      else {
        uVar8 = 1 << (bVar2 - 0x10 & 0x1f);
        mask_ptr = &node->desc->fbusy_regs;
        *mask_ptr = *mask_ptr | uVar8;
        g_used_fpr_mask = g_used_fpr_mask | node->desc->fbusy_regs;
        mask_ptr = &node->desc->ftemp_regs;
        *mask_ptr = *mask_ptr | uVar8;
      }
    }
    else {
      uVar7 = 1 << (bVar2 - 0x1f & 0x1f);
      uVar8 = 1 << (bVar2 - 0x20 & 0x1f);
      mask_ptr = &node->desc->fbusy_regs;
      *mask_ptr = *mask_ptr | uVar7 | uVar8;
      g_used_fpr_mask = g_used_fpr_mask | node->desc->fbusy_regs;
      mask_ptr = &node->desc->ftemp_regs;
      *mask_ptr = *mask_ptr | uVar7 | uVar8;
    }
    fill_ea(&node->desc->value,'\x01',bVar2,-1,'\0',0,(label_ref *)0x0);
    if (((spec & 0x2000) != 0) && ((spec & 0x400000) != 0)) {
      desc = node->desc;
      if (((desc->dest).type & 0x1f) == 0) {
        if (desc->target_regs == 0) {
          if (desc->ftarget_regs == 0) {
            sVar4 = -1;
          }
          else {
            sVar4 = float_mask_to_register(desc->ftarget_regs);
          }
        }
        else {
          sVar4 = mask_to_register((int)(short)desc->target_regs);
        }
      }
      else {
        sVar4 = (short)(desc->dest).base;
      }
      sVar4 = reusable_operand_register(node,(ea *)0x0,(ea *)0x0,spec,sVar4,'\x02');
      if (sVar4 == sVar3) {
        node->desc->opnd_class = '\x01';
        break;
      }
    }
    desc = node->desc;
    if ((((desc->dest).type & 0x1f) == 0) || ((desc->dest).base != sVar3)) {
      desc->opnd_class = '\0';
    }
    else {
      desc->opnd_class = '\x01';
    }
    break;
  case '\x05':
    written_regs = written_regs | 1;
    mask_ptr = &node->desc->busy_regs;
    *(byte *)mask_ptr = (byte)*mask_ptr | 1;
    base = '\0';
    g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
    mask_ptr = &node->desc->temp_regs;
    *(byte *)mask_ptr = (byte)*mask_ptr | 1;
    goto LAB_00425547;
  case '\x06':
    bVar2 = node->desc->bit_width;
    uVar5 = (operand->desc->value).disp;
    if (bVar2 < 0x20) {
      uVar5 = uVar5 & (1 << (bVar2 & 0x1f)) - 1U;
    }
    if ((((node->type & 4) == 0) && (bVar6 = node->type & 0xe0, bVar6 != 0x80)) && (bVar6 != 0x40))
    {
      uVar5 = (int)(uVar5 << (0x20 - bVar2 & 0x1f)) >> (0x20 - bVar2 & 0x1f);
    }
    fill_ea(&node->desc->value,'\a',-1,-1,'\0',uVar5,(label_ref *)0x0);
    node->desc->opnd_class = '\x02';
    break;
  case '\a':
    written_regs = written_regs | 4;
    mask_ptr = &node->desc->busy_regs;
    *(byte *)mask_ptr = (byte)*mask_ptr | 4;
    g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
    mask_ptr = &node->desc->temp_regs;
    *(byte *)mask_ptr = (byte)*mask_ptr | 4;
    fill_ea(&node->desc->value,'\b','\x02',-1,'\0',0,(label_ref *)0x0);
    node->desc->opnd_class = '\x03';
    break;
  case '\b':
    bVar2 = node->desc->regs_2c[0];
    if (((char)bVar2 < ' ') && (-1 < (char)bVar2)) {
      uVar5 = 1 << (bVar2 & 0x1f);
    }
    else {
      uVar5 = (1 << (bVar2 - 0x1f & 0x1f) | 1 << (bVar2 - 0x20 & 0x1f)) << 0x10;
    }
    written_regs = written_regs | uVar5;
    uVar8 = 1 << (bVar2 & 0x1f);
    mask_ptr = &node->desc->busy_regs;
    *mask_ptr = *mask_ptr | uVar8;
    g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
    mask_ptr = &node->desc->temp_regs;
    *mask_ptr = *mask_ptr | uVar8;
    fill_ea(&node->desc->value,'\b',bVar2,-1,'\0',0,(label_ref *)0x0);
    opnd_ea = &node->desc->value;
    opnd_ea->type = opnd_ea->type | 0x40;
    node->desc->opnd_class = '\x03';
    break;
  case '\t':
    bVar2 = node->desc->regs_2c[0];
    if (((char)bVar2 < ' ') && (-1 < (char)bVar2)) {
      uVar5 = 1 << (bVar2 & 0x1f);
    }
    else {
      uVar5 = (1 << (bVar2 - 0x1f & 0x1f) | 1 << (bVar2 - 0x20 & 0x1f)) << 0x10;
    }
    written_regs = written_regs | uVar5;
    uVar8 = 1 << (bVar2 & 0x1f);
    mask_ptr = &node->desc->busy_regs;
    *mask_ptr = *mask_ptr | uVar8;
    g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
    mask_ptr = &node->desc->temp_regs;
    *mask_ptr = *mask_ptr | uVar8;
    fill_ea(&node->desc->value,'\b',bVar2,-1,'\0',0,(label_ref *)0x0);
    node->desc->opnd_class = '\x03';
    break;
  case '\v':
    written_regs = written_regs | 0x10000;
    mask_ptr = &node->desc->fbusy_regs;
    *(byte *)mask_ptr = (byte)*mask_ptr | 1;
    base = '\x10';
    g_used_fpr_mask = g_used_fpr_mask | node->desc->fbusy_regs;
    mask_ptr = &node->desc->ftemp_regs;
    *(byte *)mask_ptr = (byte)*mask_ptr | 1;
    goto LAB_00425547;
  case '\x0e':
    written_regs = written_regs | 0x80000;
    mask_ptr = &node->desc->fbusy_regs;
    *(byte *)mask_ptr = (byte)*mask_ptr | 8;
    base = '\x13';
    g_used_fpr_mask = g_used_fpr_mask | node->desc->fbusy_regs;
    mask_ptr = &node->desc->ftemp_regs;
    *(byte *)mask_ptr = (byte)*mask_ptr | 8;
LAB_00425547:
    fill_ea(&node->desc->value,'\x01',base,-1,'\0',0,(label_ref *)0x0);
    node->desc->opnd_class = '\0';
  }
  if ((((tmpl->flags2 & 8) != 0) && (node->parent != (gen_node *)0x0)) &&
     ((node->parent->op != IL_ASSIGN && (operand->desc->opnd_class == '\x02')))) {
    copy_ea_into(&node->desc->value,&operand->desc->value);
    node->desc->frame_top = operand->desc->frame_top;
    node->desc->busy_regs = operand->desc->busy_regs;
    node->desc->fbusy_regs = operand->desc->fbusy_regs;
    node->desc->opnd_class = operand->desc->opnd_class;
  }
  invalidate_register_contents(written_regs);
  if (((written_regs & 1) != 0) || ((tmpl->clobbers & 1) != 0)) {
    g_r0_used = 1;
  }
  op = node->op;
  if (((('7' < (char)op) && ((char)op < '>')) || (('O' < (char)op && ((char)op < '_')))) &&
     (left_opnd->op == IL_ID)) {
    forget_register_copies_of_variable(left_opnd);
  }
  uVar1 = tmpl->opnd_spec_left;
  if (uVar1 != '\0') {
    if ((((left_opnd->op == IL_ID) && (tmpl->opnd_spec_right != '\0')) && (operand->op == IL_ID)) &&
       (operand->symx == left_opnd->symx)) {
      sVar3 = template_copy_register(node,tmpl->opnd_spec_right);
      sVar4 = template_copy_register(node,uVar1);
      record_last_operand_copy_in_register(node,tmpl,sVar4,sVar3,left_opnd);
      goto LAB_00425751;
    }
    if (((uVar1 != '\0') && (((left_opnd->desc->value).type & 0x1f) == 7)) &&
       ((tmpl->opnd_spec_right != '\0' &&
        ((((operand->desc->value).type & 0x1f) == 7 &&
         (sVar3 = ea_operands_equal(&left_opnd->desc->value,&operand->desc->value), sVar3 != 0))))))
    {
      sVar3 = template_copy_register(node,tmpl->opnd_spec_right);
      sVar4 = template_copy_register(node,tmpl->opnd_spec_left);
      record_last_operand_copy_in_register(node,tmpl,sVar4,sVar3,left_opnd);
      goto LAB_00425751;
    }
  }
  if ((tmpl->opnd_spec_right != '\0') &&
     ((operand->op == IL_ID || (((operand->desc->value).type & 0x1f) == 7)))) {
    uVar8 = 0xaa;
    sVar3 = template_copy_register(node,tmpl->opnd_spec_right);
    record_operand_copy_in_register(node,tmpl,sVar3,uVar8,operand);
  }
  if ((tmpl->opnd_spec_left != '\0') &&
     ((left_opnd->op == IL_ID || (((left_opnd->desc->value).type & 0x1f) == 7)))) {
    uVar8 = 0xa9;
    sVar3 = template_copy_register(node,tmpl->opnd_spec_left);
    record_operand_copy_in_register(node,tmpl,sVar3,uVar8,left_opnd);
  }
LAB_00425751:
  if ((tmpl->flags & 2) != 0) {
    make_template_labels(node,tmpl);
  }
  if ((tmpl->flags & 4) != 0) {
    flag_byte = &node->desc->flags2;
    *flag_byte = *flag_byte | 0x20;
  }
  if ((tmpl->flags2 & 0x80) != 0) {
    flag_byte = &node->desc->flags3;
    *flag_byte = *flag_byte | 1;
  }
  uVar8 = 0;
  g_avoid_reg_mask = 0;
  sVar3 = 0;
  do {
    bVar2 = node->desc->regs_2c[sVar3];
    if (bVar2 == 0xff) break;
    g_avoid_reg_mask = g_avoid_reg_mask | 1 << (bVar2 & 0x1f);
    sVar4 = sVar3 + 1;
    uVar8 = 1 << (node->desc->regs_2c[sVar3] & 0x1fU);
    sVar3 = sVar4;
  } while (sVar4 < 5);
  sVar3 = 0;
  uVar7 = 0;
  do {
    bVar2 = node->desc->regs_34[sVar3];
    if (bVar2 != 0xff) {
      g_avoid_reg_mask = g_avoid_reg_mask | 1 << (bVar2 & 0x1f);
      uVar7 = 1 << (node->desc->regs_34[sVar3] & 0x1fU);
    }
    sVar3 = sVar3 + 1;
  } while (sVar3 < 4);
  opnd_ea = &node->desc->value;
  if ((opnd_ea->type & 0x1f) != 0) {
    uVar5 = ea_register_mask(opnd_ea);
    g_avoid_reg_mask = g_avoid_reg_mask | (ushort)uVar5;
  }
  g_avoid_reg_mask = g_avoid_reg_mask & 0xf;
  if (g_avoid_reg_mask != 0xf) {
    return;
  }
  uVar5 = ea_register_mask(&node->desc->value);
  if (uVar7 != 0) {
    g_avoid_reg_mask = (ushort)uVar5 | uVar7;
    return;
  }
  g_avoid_reg_mask = (ushort)uVar5 | uVar8;
  return;
}



