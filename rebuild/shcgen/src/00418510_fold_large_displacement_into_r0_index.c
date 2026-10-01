#include "decls.h"
#include "imports.h"

// entry: 00418510
// name : fold_large_displacement_into_r0_index
// size : 665
// sig  : short fold_large_displacement_into_r0_index(gen_node * node, gen_node * left, gen_node * right)


short __cdecl fold_large_displacement_into_r0_index(gen_node *node,gen_node *left,gen_node *right)

{
  short sVar1;
  uint excluded_retry;
  uint uVar2;
  byte bVar3;
  ea *peVar4;
  gen_node *base_node;
  gen_node *r0_node;
  gen_node *pgVar5;
  node_desc *desc;
  int offset;
  il_op op;
  tmpl_header *tmpl;
  bool use_r0;
  
  sVar1 = classify_address_operand(left);
  base_node = right;
  r0_node = left;
  if (sVar1 == 7) {
    base_node = left;
    r0_node = right;
  }
  bVar3 = 0;
  peVar4 = r0_node->desc->mem_ea;
  if (peVar4 != (ea *)0x0) {
    bVar3 = peVar4->type & 0x1f;
  }
  if (((bVar3 == 0) && (peVar4 = &r0_node->desc->dest, (peVar4->type & 0x1f) == 0)) &&
     (peVar4 = &g_ea_pop, (r0_node->desc->flags2 & 8) == 0)) {
    peVar4 = &r0_node->desc->value;
  }
  sVar1 = 0;
  offset = peVar4->disp;
  pgVar5 = node->parent;
  if (pgVar5->desc->usage == '\x03') {
    op = pgVar5->parent->op;
    if ((op == IL_ASSIGN) && ((pgVar5->parent->desc->flags7 & 0x20) != 0)) {
      return 0;
    }
    if (((('7' < (char)op) && ((char)op < '>')) || (('O' < (char)op && ((char)op < '`')))) &&
       ((tmpl = pgVar5->parent->desc->tmpl, tmpl != (tmpl_header *)0x0 &&
        ((tmpl->excluded & 1) != 0)))) {
      return 0;
    }
  }
  bVar3 = pgVar5->type & 0xf8;
  if ((bVar3 == 0) && (peVar4->labels == (label_ref *)0x0)) {
    if (offset < 0x10) {
      return 0;
    }
    if (((base_node->desc->opnd_class == '\0') && (0xf < offset)) && (offset < 0x80)) {
      return 0;
    }
  }
  if ((bVar3 == 8) && (peVar4->labels == (label_ref *)0x0)) {
    if (offset < 0x1f) {
      return 0;
    }
    if (((base_node->desc->opnd_class == '\0') && (0x1e < offset)) && (offset < 0x80)) {
      return 0;
    }
  }
  if (((((bVar3 == 0x10) || (bVar3 == 0x18)) || (bVar3 == 0x28)) || (bVar3 == 0x40)) &&
     (peVar4->labels == (label_ref *)0x0)) {
    if (offset < 0x3d) {
      return 0;
    }
    if (((base_node->desc->opnd_class == '\0') && (0x3c < offset)) && (offset < 0x80)) {
      return 0;
    }
  }
  peVar4 = &r0_node->desc->dest;
  if ((peVar4->type & 0x1f) != 0) {
    return 0;
  }
  if ((node->desc->flags2 & 0x80) == 0) {
    if ((r0_node == left) && (use_r0 = false, (right->desc->temp_regs & 1) != 0)) goto LAB_004186c1;
  }
  else if ((r0_node == right) && ((left->desc->temp_regs & 1) != 0)) {
    use_r0 = false;
    goto LAB_004186c1;
  }
  use_r0 = true;
LAB_004186c1:
  if (use_r0) {
    fill_ea(peVar4,'\x01','\0',-1,'\0',0,(label_ref *)0x0);
    g_r0_used = 1;
    peVar4 = &base_node->desc->value;
    desc = r0_node->desc;
    pgVar5 = r0_node;
    excluded_retry = ea_register_mask(peVar4);
    uVar2 = ea_register_mask(peVar4);
    emit_operand_transfer
              (&desc->value,&desc->dest,'0',r0_node,0xc00,r0_node->type,
               uVar2 | (int)(short)node->desc->busy_regs,excluded_retry,(int)pgVar5);
    desc = base_node->desc;
    bVar3 = 0;
    peVar4 = desc->mem_ea;
    if (peVar4 != (ea *)0x0) {
      bVar3 = peVar4->type & 0x1f;
    }
    if (((bVar3 == 0) && (peVar4 = &desc->dest, (peVar4->type & 0x1f) == 0)) &&
       (peVar4 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      peVar4 = &desc->value;
    }
    copy_words((uint *)&node->desc->value,(uint *)peVar4,3);
    (node->desc->value).index = '\0';
    (node->desc->value).type = (node->desc->value).type & 0xf9 | 9;
    peVar4 = &node->desc->value;
    peVar4->type = peVar4->type | 0x40;
    sVar1 = 1;
  }
  return sVar1;
}



