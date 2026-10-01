#include "decls.h"
#include "imports.h"

// entry: 00410a50
// name : float_div_by_const_to_mul
// size : 172
// sig  : il_node * float_div_by_const_to_mul(il_node * node)


il_node * __cdecl float_div_by_const_to_mul(il_node *node)

{
  il_node *piVar1;
  il_node *piVar2;
  
  piVar1 = node->child->next;
  if ((piVar1->op == IL_CONST) && ((piVar1->type & 0xe0) == 0x20)) {
    piVar1 = copy_tree(1,piVar1);
    piVar2 = new_const_node(node->type & 0xfc,1);
    piVar1 = make_node(IL_DIV,node->type,piVar2,piVar1,(il_node *)0x0);
    piVar1 = make_node(IL_IF,node->type,piVar1,(il_node *)0x0,(il_node *)0x0);
    piVar2 = fold_constants(piVar1->child);
    node->op = node->op - IL_NON_02;
    piVar1->child = (il_node *)0x0;
    piVar2->parent = (il_node *)0x0;
    replace_and_free_node(node->child->next,piVar2);
    free_node(piVar1);
  }
  return node;
}



