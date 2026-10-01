#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00431a30
// name : set_assignment_result_value
// size : 1038
// sig  : void set_assignment_result_value(gen_node * node)


int __cdecl set_assignment_result_value(gen_node *node)

{
  byte bVar1;
  short same;
  ea *operand;
  tmpl_header *tmpl;
  gen_node *right;
  uchar *flags;
  gen_node *left;
  node_desc *left_desc;
  ushort *regs;
  
  right = (gen_node *)0x0;
  left = node->child;
  if (left != (gen_node *)0x0) {
    right = left->next;
  }
  bVar1 = node->type & 0xe0;
  if ((bVar1 != 0x60) && (bVar1 != 0x80)) {
    operand = &right->desc->value;
    if (((operand->type & 0x1f) != 1) &&
       ((right->desc->opnd_class != '\x02' ||
        (((g_request->cpu == 4 || ((node->type & 0xf8) != 0x30)) &&
         ((node->parent != (gen_node *)0x0 && (node->parent->op == IL_ASSIGN)))))))) {
      if (left->desc->opnd_class == '\x02') {
        flags = &node->desc->flags3;
        *flags = *flags | 8;
        if (node->desc->tmpl == (tmpl_header *)0x0) {
          flags = &node->desc->flags3;
          *flags = *flags | 0x80;
        }
      }
      node->desc->busy_regs = left->desc->busy_regs;
      node->desc->fbusy_regs = left->desc->fbusy_regs;
      node->desc->frame_top = left->desc->frame_top;
      bVar1 = 0;
      left_desc = left->desc;
      operand = left_desc->mem_ea;
      if (operand != (ea *)0x0) {
        bVar1 = operand->type & 0x1f;
      }
      if (((bVar1 == 0) && (operand = &left_desc->dest, (operand->type & 0x1f) == 0)) &&
         (operand = &g_ea_pop, (left_desc->flags2 & 8) == 0)) {
        operand = &left_desc->value;
      }
      copy_ea_into(&node->desc->value,operand);
      node->desc->opnd_class = left->desc->opnd_class;
      return;
    }
    copy_ea_into(&node->desc->value,operand);
    node->desc->frame_top = right->desc->frame_top;
    node->desc->busy_regs = right->desc->busy_regs;
    node->desc->fbusy_regs = right->desc->fbusy_regs;
    node->desc->opnd_class = right->desc->opnd_class;
    return;
  }
  operand = &right->desc->value;
  if ((operand->type & 0x1f) != 0) {
    same = ea_operands_equal(&left->desc->value,operand);
    if (same == 0) {
      tmpl = select_move_template(node->type,&right->desc->value,&left->desc->value,right);
      if (((tmpl == (tmpl_header *)&g_tmpl_amv008) || (tmpl == (tmpl_header *)&g_tmpl_amv012)) ||
         (tmpl == (tmpl_header *)&g_tmpl_amv014)) {
        regs = &node->desc->busy_regs;
        *(byte *)regs = (byte)*regs | 4;
        g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
        regs = &node->desc->temp_regs;
        *(byte *)regs = (byte)*regs | 4;
        fill_ea(&node->desc->value,'\b','\x02',-1,'\0',0,(label_ref *)0x0);
        node->desc->opnd_class = '\x03';
        return;
      }
      if (tmpl == (tmpl_header *)&g_tmpl_amv024) {
        if (left->desc->opnd_class == '\x02') {
          flags = &node->desc->flags3;
          *flags = *flags | 8;
          if (node->desc->tmpl == (tmpl_header *)0x0) {
            flags = &node->desc->flags3;
            *flags = *flags | 0x80;
          }
        }
        node->desc->busy_regs = left->desc->busy_regs;
        node->desc->fbusy_regs = left->desc->fbusy_regs;
        node->desc->frame_top = left->desc->frame_top;
        bVar1 = 0;
        left_desc = left->desc;
        operand = left_desc->mem_ea;
        if (operand != (ea *)0x0) {
          bVar1 = operand->type & 0x1f;
        }
        if (((bVar1 == 0) && (operand = &left_desc->dest, (operand->type & 0x1f) == 0)) &&
           (operand = &g_ea_pop, (left_desc->flags2 & 8) == 0)) {
          operand = &left_desc->value;
        }
        copy_ea_into(&node->desc->value,operand);
        node->desc->opnd_class = left->desc->opnd_class;
        return;
      }
      if (((tmpl != (tmpl_header *)&g_tmpl_amv016) && (tmpl != (tmpl_header *)&g_tmpl_amv018)) &&
         ((tmpl != (tmpl_header *)&g_tmpl_amv019 &&
          ((tmpl != (tmpl_header *)&g_tmpl_amv021 && (tmpl != (tmpl_header *)&g_tmpl_amv023)))))) {
        copy_ea_into(&node->desc->value,&right->desc->value);
        node->desc->frame_top = right->desc->frame_top;
        node->desc->busy_regs = right->desc->busy_regs;
        node->desc->fbusy_regs = right->desc->fbusy_regs;
        node->desc->opnd_class = right->desc->opnd_class;
        return;
      }
      regs = &node->desc->busy_regs;
      *regs = *regs | 1 << (right->desc->regs_41[0] & 0x1fU);
      g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
      regs = &node->desc->temp_regs;
      *regs = *regs | 1 << (right->desc->regs_41[0] & 0x1fU);
      fill_ea(&node->desc->value,'\b',right->desc->regs_41[0],-1,'\0',0,(label_ref *)0x0);
      node->desc->opnd_class = '\x03';
      return;
    }
  }
  if (left->desc->opnd_class == '\x02') {
    flags = &node->desc->flags3;
    *flags = *flags | 8;
    if (node->desc->tmpl == (tmpl_header *)0x0) {
      flags = &node->desc->flags3;
      *flags = *flags | 0x80;
    }
  }
  node->desc->busy_regs = left->desc->busy_regs;
  node->desc->fbusy_regs = left->desc->fbusy_regs;
  node->desc->frame_top = left->desc->frame_top;
  bVar1 = 0;
  left_desc = left->desc;
  operand = left_desc->mem_ea;
  if (operand != (ea *)0x0) {
    bVar1 = operand->type & 0x1f;
  }
  if (((bVar1 == 0) && (operand = &left_desc->dest, (operand->type & 0x1f) == 0)) &&
     (operand = &g_ea_pop, (left_desc->flags2 & 8) == 0)) {
    operand = &left_desc->value;
  }
  copy_ea_into(&node->desc->value,operand);
  node->desc->opnd_class = left->desc->opnd_class;
  return;
}



