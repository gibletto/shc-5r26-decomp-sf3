#include "decls.h"
#include "imports.h"

// entry: 0040f190
// name : simplify_bitand_bitor
// size : 703
// sig  : il_node * simplify_bitand_bitor(il_node * node)


il_node * __cdecl simplify_bitand_bitor(il_node *node)

{
  byte type;
  il_node *piVar1;
  il_node *piVar2;
  il_node *piVar3;
  byte kind;
  il_node *piVar4;
  int is_cond;
  uint uVar5;
  uint uVar6;
  short filn;
  ushort line;
  short listno;
  
  filn = node->filn;
  line = node->line;
  listno = node->listno;
  uVar6 = (node->op == IL_B_AND) - 1;
  uVar5 = ~uVar6;
  if (node->child->op == IL_CONST) {
    swap_operands(node);
  }
  piVar4 = node->child;
  if ((((piVar4->op == IL_ID) && ((piVar4->type & 2) == 0)) &&
      (piVar1 = piVar4->next, piVar1->op == IL_ID)) &&
     (((piVar1->type & 2) == 0 && (piVar1->symx == piVar4->symx)))) {
    piVar4 = copy_tree(0,piVar4);
    replace_and_free_node(node,piVar4);
    return piVar4;
  }
  uVar6 = is_const_value(piVar4->next,uVar6,node->type);
  if (uVar6 != 0) {
    node->op = IL_COMMA;
    return node;
  }
  uVar6 = is_const_value(node->child->next,uVar5,node->type);
  if (uVar6 == 0) {
    piVar4 = node;
    if (node->op == IL_B_OR) {
      piVar1 = node->child;
      if ((((piVar1->op == IL_CMPL) && (piVar2 = piVar1->child, piVar2->op == IL_ID)) &&
          (((piVar2->type & 2) == 0 &&
           (((piVar3 = piVar1->next, piVar3->op == IL_ID && ((piVar3->type & 2) == 0)) &&
            (piVar3->symx == piVar2->symx)))))) ||
         (((((piVar1->next->op == IL_CMPL && (piVar1->op == IL_ID)) && ((piVar1->type & 2) == 0)) &&
           ((piVar2 = piVar1->next->child, piVar2->op == IL_ID && ((piVar2->type & 2) == 0)))) &&
          (piVar2->symx == piVar1->symx)))) {
        piVar4 = new_const_node(node->type & 0xfc,0xffffffff);
        piVar4->filn = filn;
        piVar4->line = line;
        piVar4->listno = listno;
        replace_and_free_node(node,piVar4);
        return piVar4;
      }
    }
    else if (node->op == IL_B_AND) {
      if (node->parent->op == IL_CAST) {
        type = node->parent->type;
        kind = type & 0xf8;
        if (((kind == 0) || (kind == 8)) &&
           (uVar5 = is_const_value(node->child->next,uVar5,type), uVar5 != 0)) {
          piVar4 = copy_tree(0,node->child);
          replace_and_free_node(node,piVar4);
          return piVar4;
        }
      }
      piVar4 = node->child->next;
      if (piVar4->op == IL_CAST) {
        piVar4 = piVar4->child;
      }
      uVar5 = is_const_value(piVar4,0xffff,node->type);
      if ((uVar5 == 0) && (uVar6 = is_const_value(piVar4,0xff,node->type), uVar6 == 0)) {
        return node;
      }
      piVar4 = copy_tree(0,node->child);
      piVar4 = make_node(IL_CAST,(-(uVar5 == 0) & 0xf8U) + 0xc,piVar4,(il_node *)0x0,(il_node *)0x0)
      ;
      piVar4 = make_node(IL_CAST,node->type,piVar4,(il_node *)0x0,(il_node *)0x0);
      replace_and_free_node(node,piVar4);
    }
    return piVar4;
  }
  is_cond = is_condition_operand(node);
  if (((is_cond == 0) || (node->child->op != IL_CAST)) ||
     (piVar4 = node->child->child, piVar4->op != IL_B_QUALIFY)) {
    piVar4 = node->child;
  }
  piVar4 = copy_tree(0,piVar4);
  replace_and_free_node(node,piVar4);
  return piVar4;
}



