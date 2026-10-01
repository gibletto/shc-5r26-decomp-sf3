#include "decls.h"
#include "imports.h"

// entry: 0041be70
// name : free_node_descriptor_tree
// size : 235
// sig  : void free_node_descriptor_tree(gen_node * node)


int __cdecl free_node_descriptor_tree(gen_node *node)

{
  label_ref *list;
  byte ea_kind;
  gen_node *child;
  node_desc *desc;
  ea *opnd_ea;
  
  opnd_ea = node->desc->saved_ea;
  if (opnd_ea != (ea *)0x0) {
    free_ea(opnd_ea);
  }
  opnd_ea = node->desc->saved_reg_ea;
  if (opnd_ea != (ea *)0x0) {
    free_ea(opnd_ea);
  }
  opnd_ea = node->desc->mem_ea;
  if (opnd_ea != (ea *)0x0) {
    free_ea(opnd_ea);
  }
  opnd_ea = node->desc->addr_reg_ea;
  if (opnd_ea != (ea *)0x0) {
    free_ea(opnd_ea);
  }
  opnd_ea = node->desc->ea_54;
  if (opnd_ea != (ea *)0x0) {
    free_ea(opnd_ea);
  }
  desc = node->desc;
  ea_kind = (desc->value).type & 0x1f;
  if ((ea_kind == 0xd) || ((ea_kind == 7 && ((desc->value).labels != (label_ref *)0x0)))) {
    free_label_ref_list((desc->value).labels);
  }
  desc = node->desc;
  ea_kind = (desc->dest).type & 0x1f;
  if ((ea_kind == 0xd) || ((ea_kind == 7 && ((desc->dest).labels != (label_ref *)0x0)))) {
    free_label_ref_list((desc->dest).labels);
  }
  list = node->desc->template_labels;
  if (list != (label_ref *)0x0) {
    free_label_ref_list(list);
  }
  pool_free(node->desc,0x84);
  for (child = node->child; child != (gen_node *)0x0; child = child->next) {
    free_node_descriptor_tree(child);
  }
  return;
}



