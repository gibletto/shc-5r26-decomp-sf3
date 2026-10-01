#include "decls.h"
#include "imports.h"

// entry: 00412fe0
// name : build_spec_change_tree
// size : 669
// sig  : il_node * build_spec_change_tree(il_node * body, short sym1, short sym2)


il_node * __cdecl build_spec_change_tree(il_node *body,short sym1,short sym2)

{
  il_node *result;
  il_node *piVar1;
  il_node *piVar2;
  il_node *piVar3;
  il_node *piVar4;
  
  result = alloc_node();
  result->op = IL_IF;
  piVar1 = alloc_node();
  piVar1->op = IL_EMPTY;
  result->child = piVar1;
  piVar1->parent = result;
  piVar2 = make_empty_block();
  insert_before(piVar1,piVar2);
  piVar1 = new_node(IL_ID,'\x10');
  piVar3 = new_node(IL_ID,'\x10');
  piVar4 = make_node(IL_NE,'\x10',piVar1,piVar3,(il_node *)0x0);
  piVar1->symx = sym1;
  piVar3->symx = sym2;
  insert_before(piVar2,piVar4);
  piVar1 = alloc_node();
  piVar1->op = IL_IF;
  piVar2 = last_operand(piVar2);
  insert_before(piVar2,piVar1);
  piVar2 = alloc_node();
  piVar2->op = IL_IF;
  piVar1->child = piVar2;
  piVar2->parent = piVar1;
  piVar1 = make_empty_block();
  insert_before(piVar2,piVar1);
  piVar3 = make_id_equals_const(sym1,2);
  insert_before(piVar1,piVar3);
  piVar3 = last_operand(piVar1);
  insert_two_if_nodes(piVar3);
  piVar3 = add_continue_to_first_child(piVar1);
  piVar4 = make_id_equals_const(sym2,0);
  insert_before(piVar3,piVar4);
  piVar1 = add_return_one_pair(piVar1->child->next);
  piVar3 = new_node(IL_ID,'\x10');
  piVar3->symx = sym2;
  piVar4 = new_const_node('\x10',0);
  piVar3 = make_node(IL_LT,'\x10',piVar4,piVar3,(il_node *)0x0);
  insert_before(piVar1,piVar3);
  piVar1 = make_empty_block();
  piVar2->child = piVar1;
  piVar1->parent = piVar2;
  piVar3 = make_empty_block();
  insert_before(piVar1,piVar3);
  piVar1 = make_id_equals_const(sym2,2);
  insert_before(piVar3,piVar1);
  piVar1 = last_operand(piVar3);
  insert_two_if_nodes(piVar1);
  piVar1 = add_continue_to_first_child(piVar3);
  piVar4 = make_id_equals_const(sym1,0);
  insert_before(piVar1,piVar4);
  piVar1 = add_return_one_pair(piVar3->child->next);
  piVar3 = new_node(IL_ID,'\x10');
  piVar3->symx = sym1;
  piVar4 = new_const_node('\x10',0);
  piVar3 = make_node(IL_LT,'\x10',piVar3,piVar4,(il_node *)0x0);
  insert_before(piVar1,piVar3);
  piVar1 = last_operand(piVar2->child->next->next);
  piVar2 = alloc_node();
  piVar2->op = IL_IF;
  insert_before(piVar1,piVar2);
  piVar1 = add_return_one_pair(piVar2);
  piVar2 = new_node(IL_ID,'\x10');
  piVar2->symx = sym1;
  piVar3 = new_node(IL_ID,'\x10');
  piVar3->symx = sym2;
  piVar2 = make_node(IL_LT,'\x10',piVar2,piVar3,(il_node *)0x0);
  insert_before(piVar1,piVar2);
  return result;
}



