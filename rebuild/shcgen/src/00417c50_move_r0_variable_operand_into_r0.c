#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_r0_variable
#define g_r0_variable (*(short * *)(g_sd + 0x1f9a8))


// entry: 00417c50
// name : move_r0_variable_operand_into_r0
// size : 640
// sig  : void move_r0_variable_operand_into_r0(gen_node * node, gen_node * left, gen_node * right)


int __cdecl move_r0_variable_operand_into_r0(gen_node *node,gen_node *left,gen_node *right)

{
  short same;
  int kind;
  uint uVar1;
  uint uVar2;
  ea *src_value;
  gen_node *pgVar3;
  gen_node *extra;
  node_desc *desc;
  il_op grand_op;
  ushort *regs_ptr;
  
  kind = classify_indexed_address_operands(left,right);
  if (kind == 0) {
    return;
  }
  pgVar3 = node->parent->parent;
  grand_op = pgVar3->op;
  if ((char)grand_op < '8') {
LAB_00417c8c:
    if (((char)grand_op < 'P') || ('_' < (char)grand_op)) goto LAB_00417ca6;
  }
  else {
    if ((char)grand_op < '>') goto LAB_00417ca6;
    if (((char)grand_op < '8') || ('=' < (char)grand_op)) goto LAB_00417c8c;
  }
  if (((pgVar3->desc->flags7 & 0x20) != 0) && (pgVar3->child == node->parent)) {
    return;
  }
LAB_00417ca6:
  if (((right->symx == *g_r0_variable) &&
      (uVar2 = (int)right->lreg >> 0x1f, ((int)right->lreg ^ uVar2) - uVar2 == (int)g_r0_variable[1]
      )) && (((left->desc->value).type & 0x1f) == 1)) {
    desc = right->desc;
    if (((((desc->value).type & 0x1f) != 1) || ((desc->value).base != '\0')) &&
       ((left->desc->temp_regs & 1) == 0)) {
      fill_ea(&desc->dest,'\x01','\0',-1,'\0',0,(label_ref *)0x0);
      src_value = &left->desc->value;
      desc = right->desc;
      pgVar3 = right;
      uVar2 = ea_register_mask(src_value);
      uVar1 = ea_register_mask(src_value);
      emit_operand_transfer
                (&desc->value,&desc->dest,'0',right,0xc00,right->type,
                 uVar1 | (int)(short)node->desc->busy_regs,uVar2,(int)pgVar3);
      record_variable_in_register(right,0);
      regs_ptr = &right->desc->busy_regs;
      *(byte *)regs_ptr = (byte)*regs_ptr | 1;
      g_used_gpr_mask = g_used_gpr_mask | right->desc->busy_regs;
      regs_ptr = &right->desc->temp_regs;
      *(byte *)regs_ptr = (byte)*regs_ptr | 1;
    }
    g_r0_index_loaded = 1;
    return;
  }
  pgVar3 = left;
  if (kind != 1) {
    pgVar3 = left->child;
  }
  if (((pgVar3->symx == *g_r0_variable) &&
      (uVar2 = (int)pgVar3->lreg >> 0x1f,
      ((int)pgVar3->lreg ^ uVar2) - uVar2 == (int)g_r0_variable[1])) &&
     (((right->desc->value).type & 0x1f) == 1)) {
    if ((left->op == IL_ASSIGN) &&
       (same = ea_operands_equal(&left->desc->value,&pgVar3->desc->value), same == 0)) {
      copy_ea_into(&left->desc->value,&pgVar3->desc->value);
    }
    desc = left->desc;
    if (((((desc->value).type & 0x1f) != 1) || ((desc->value).base != '\0')) &&
       ((right->desc->temp_regs & 1) == 0)) {
      fill_ea(&desc->dest,'\x01','\0',-1,'\0',0,(label_ref *)0x0);
      src_value = &right->desc->value;
      extra = left;
      uVar2 = ea_register_mask(src_value);
      uVar1 = ea_register_mask(src_value);
      emit_operand_transfer
                (&left->desc->value,&left->desc->dest,'0',left,0xc00,left->type,
                 uVar1 | (int)(short)node->desc->busy_regs,uVar2,(int)extra);
      record_variable_in_register(pgVar3,0);
      regs_ptr = &node->desc->cached_regs;
      *regs_ptr = *regs_ptr | pgVar3->desc->cached_regs;
      regs_ptr = &left->desc->busy_regs;
      *(byte *)regs_ptr = (byte)*regs_ptr | 1;
      g_used_gpr_mask = g_used_gpr_mask | left->desc->busy_regs;
      regs_ptr = &left->desc->temp_regs;
      *(byte *)regs_ptr = (byte)*regs_ptr | 1;
    }
    g_r0_index_loaded = 1;
  }
  return;
}



