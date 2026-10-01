#include "decls.h"
#include "imports.h"

// entry: 0040f450
// name : simplify_bitxor
// size : 445
// sig  : il_node * simplify_bitxor(il_node * node)


il_node * __cdecl simplify_bitxor(il_node *node)

{
  il_node *piVar1;
  il_node *piVar2;
  uint is_const;
  il_node *piVar3;
  short filn;
  ushort line;
  short listno;
  
  filn = node->filn;
  line = node->line;
  listno = node->listno;
  if (node->child->op == IL_CONST) {
    swap_operands(node);
  }
  piVar2 = node->child;
  if ((((piVar2->op == IL_ID) && ((piVar2->type & 2) == 0)) &&
      (piVar3 = piVar2->next, piVar3->op == IL_ID)) &&
     (((piVar3->type & 2) == 0 && (piVar3->symx == piVar2->symx)))) {
    piVar2 = new_const_node(node->type,0);
    piVar2->filn = filn;
    piVar2->line = line;
    piVar2->listno = listno;
    replace_and_free_node(node,piVar2);
    return piVar2;
  }
  is_const = is_const_value(piVar2->next,0,node->type);
  if (is_const != 0) {
    piVar2 = copy_tree(0,node->child);
    replace_and_free_node(node,piVar2);
    return piVar2;
  }
  is_const = is_const_value(node->child->next,0xffffffff,node->type);
  if (is_const != 0) {
    piVar2 = copy_tree(0,node->child);
    piVar2 = make_node(IL_CMPL,node->type,piVar2,(il_node *)0x0,(il_node *)0x0);
    piVar2->filn = filn;
    piVar2->line = line;
    piVar2->listno = listno;
    replace_and_free_node(node,piVar2);
    return piVar2;
  }
  piVar2 = node->child;
  if ((((piVar2->op == IL_CMPL) && (piVar3 = piVar2->child, piVar3->op == IL_ID)) &&
      (((piVar3->type & 2) == 0 &&
       (((piVar1 = piVar2->next, piVar1->op == IL_ID && ((piVar1->type & 2) == 0)) &&
        (piVar1->symx == piVar3->symx)))))) ||
     (((piVar3 = node, piVar2->next->op == IL_CMPL && (piVar2->op == IL_ID)) &&
      (((piVar2->type & 2) == 0 &&
       (((piVar1 = piVar2->next->child, piVar1->op == IL_ID && ((piVar1->type & 2) == 0)) &&
        (piVar1->symx == piVar2->symx)))))))) {
    piVar3 = new_const_node(node->type & 0xfc,0xffffffff);
    piVar3->filn = filn;
    piVar3->line = line;
    piVar3->listno = listno;
    replace_and_free_node(node,piVar3);
  }
  return piVar3;
}



