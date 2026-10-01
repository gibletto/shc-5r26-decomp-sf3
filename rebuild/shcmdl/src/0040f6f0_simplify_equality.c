#include "decls.h"
#include "imports.h"

// entry: 0040f6f0
// name : simplify_equality
// size : 439
// sig  : il_node * simplify_equality(il_node * node)


il_node * __cdecl simplify_equality(il_node *node)

{
  il_node *piVar1;
  int iVar2;
  uint is_const;
  il_node *piVar3;
  short filn;
  ushort line;
  short listno;
  il_op op;
  
  line = node->line;
  filn = node->filn;
  listno = node->listno;
  op = node->op;
  if (node->child->op == IL_CONST) {
    swap_operands(node);
  }
  piVar1 = node->child;
  if ((((piVar1->op == IL_ID) && ((piVar1->type & 2) == 0)) &&
      (piVar3 = piVar1->next, piVar3->op == IL_ID)) &&
     (((piVar3->type & 2) == 0 && (piVar3->symx == piVar1->symx)))) {
    piVar1 = new_const_node(node->type & 0xfc,(uint)(op == IL_EQ));
    piVar1->filn = filn;
    piVar1->line = line;
    piVar1->listno = listno;
    replace_and_free_node(node,piVar1);
    return piVar1;
  }
  piVar3 = node;
  if (piVar1->next->op == IL_CONST) {
    iVar2 = const_out_of_range(piVar1->next);
    if (iVar2 != 0) {
      node->child->next->val = (uint)(node->op != IL_EQ);
      node->child->next->type = '\x10';
      node->op = IL_COMMA;
      return node;
    }
    piVar1 = node->child->next;
    is_const = is_const_value(piVar1,0,piVar1->type);
    if (is_const != 0) {
      piVar1 = copy_tree(0,node->child);
      iVar2 = is_condition_operand(node);
      if ((((iVar2 != 0) && (piVar1->op == IL_CAST)) &&
          (piVar3 = piVar1->child, piVar3->op == IL_B_QUALIFY)) &&
         ((node->op == IL_NE || ((node->op == IL_EQ && ((piVar3->type & 4) != 0)))))) {
        node->type = piVar3->type;
        piVar3->parent = (il_node *)0x0;
        piVar1->child = (il_node *)0x0;
        free_node(piVar1);
        piVar1 = piVar3;
      }
      piVar3 = make_node(IL_NOT,node->type,piVar1,(il_node *)0x0,(il_node *)0x0);
      if (node->op == IL_NE) {
        piVar3 = make_node(IL_NOT,node->type,piVar3,(il_node *)0x0,(il_node *)0x0);
      }
      piVar3->filn = filn;
      piVar3->line = line;
      piVar3->listno = listno;
      replace_and_free_node(node,piVar3);
    }
  }
  return piVar3;
}



