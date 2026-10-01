#include "decls.h"
#include "imports.h"

// entry: 00431950
// name : apply_template_operand_constraints
// size : 192
// sig  : void apply_template_operand_constraints(gen_node * node)


int __cdecl apply_template_operand_constraints(gen_node *node)

{
  node_desc *desc;
  gen_node *right;
  uchar *flags;
  gen_node *left;
  
  right = (gen_node *)0x0;
  left = node->child;
  if (left != (gen_node *)0x0) {
    right = left->next;
  }
  switch(node->desc->tmpl->push_mode) {
  case '\x01':
    flags = &left->desc->flags2;
    *flags = *flags | 8;
    flags = &right->desc->flags2;
    *flags = *flags | 8;
    break;
  case '\x02':
    flags = &left->desc->flags2;
    *flags = *flags | 4;
    flags = &right->desc->flags2;
    *flags = *flags | 8;
    break;
  case '\x03':
    desc = left->desc;
    goto LAB_004319b1;
  case '\x04':
    flags = &left->desc->flags2;
    *flags = *flags | 4;
    break;
  case '\x05':
    desc = right->desc;
LAB_004319b1:
    desc->flags2 = desc->flags2 | 8;
  }
  if (left != (gen_node *)0x0) {
    left->desc->pref_regs = node->desc->tmpl->pref_left;
    left->desc->fpref_regs = node->desc->tmpl->fpref_left;
    if (right != (gen_node *)0x0) {
      right->desc->pref_regs = node->desc->tmpl->pref_right;
      right->desc->fpref_regs = node->desc->tmpl->fpref_right;
    }
  }
  return;
}



