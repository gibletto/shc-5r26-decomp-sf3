#include "decls.h"
#include "imports.h"

// entry: 0041e9c0
// name : cse_append_temp_assign
// size : 400
// sig  : il_node * cse_append_temp_assign(bblock * block, il_node * expr, uchar type)


il_node * __cdecl cse_append_temp_assign(bblock *block,il_node *expr,uchar type)

{
  node_list **head;
  char not_cond;
  il_node *piVar1;
  il_node *assign_node;
  il_node *piVar2;
  undefined3 extraout_var = 0;
  il_node *zero_const;
  node_list *last;
  node_list *next;
  
  piVar1 = copy_tree(0,expr);
  assign_node = new_node(IL_ASSIGN,type);
  assign_node->filn = 0;
  assign_node->line = 0;
  assign_node->listno = 0;
  piVar2 = new_temp_id(type);
  *(byte *)&piVar2->flag2 = (byte)piVar2->flag2 | 0x20;
  insert_parent(piVar1,assign_node);
  insert_before(piVar1,piVar2);
  piVar1 = assign_node->child->next;
  piVar1->cse_head = piVar1;
  assign_node->child->next->cse_next = expr;
  head = &block->ilnode;
  last = *head;
  if (last == (node_list *)0x0) {
    piVar1 = block->suclst->block->lptbl->node;
    if (piVar1->parent->op != IL_BLOCK) {
      wrap_in_block_pair(piVar1);
    }
    insert_before(piVar1,assign_node);
    append_list_item(head,assign_node);
    return assign_node;
  }
  next = last->next;
  while (next != (node_list *)0x0) {
    last = last->next;
    next = last->next;
  }
  piVar1 = last->node;
  not_cond = is_not_control_condition(piVar1);
  if (CONCAT31(extraout_var,not_cond) == 0) {
    piVar2 = new_node(IL_COMMA,piVar1->type);
    *(byte *)&piVar2->flag2 = (byte)piVar2->flag2 | 0x10;
    if (expr == piVar1) {
      assign_node->child->next->cse_next = expr;
    }
    if ((piVar1->op == IL_COMMA) && ((piVar1->flag2 & 0x10) != 0)) {
      piVar1 = piVar1->child;
      insert_parent(piVar1,piVar2);
      insert_after(piVar1,assign_node);
      return assign_node;
    }
    if (piVar1->op == IL_NULL) {
      piVar1->op = IL_NOT;
      piVar1->type = '\x10';
      piVar2->type = '\x10';
      zero_const = new_const_node('\x10',0);
      insert_operands(piVar1,zero_const,1);
    }
    insert_parent(piVar1,piVar2);
    insert_before(piVar1,assign_node);
    last->node = piVar2;
    return assign_node;
  }
  assign_node->next = piVar1->next;
  piVar1->next = assign_node;
  assign_node->parent = piVar1->parent;
  append_list_item(head,assign_node);
  return assign_node;
}



