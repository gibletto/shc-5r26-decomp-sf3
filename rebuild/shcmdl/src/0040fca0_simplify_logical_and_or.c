#include "decls.h"
#include "imports.h"

// entry: 0040fca0
// name : simplify_logical_and_or
// size : 348
// sig  : il_node * simplify_logical_and_or(il_node * node)


il_node * __cdecl simplify_logical_and_or(il_node *node)

{
  uint is_const;
  il_node *piVar1;
  short filn;
  ushort line;
  short listno;
  il_op op;
  
  filn = node->filn;
  line = node->line;
  op = node->op;
  listno = node->listno;
  piVar1 = node->child;
  if (piVar1->op != IL_CONST) {
    if (op == IL_OR) {
      node = merge_or_of_bit_tests(node);
      node->filn = filn;
      node->line = line;
      node->listno = listno;
    }
    return node;
  }
  if (op == IL_AND) {
    is_const = is_const_value(piVar1,0,piVar1->type);
    if (is_const != 0) goto LAB_0040fd0d;
  }
  if (node->op == IL_OR) {
    is_const = is_const_value(node->child,0,node->child->type);
    if (is_const == 0) {
LAB_0040fd0d:
      piVar1 = new_const_node(node->type,(uint)(op != IL_AND));
      piVar1->filn = filn;
      piVar1->line = line;
      piVar1->listno = listno;
      replace_and_free_node(node,piVar1);
      return piVar1;
    }
  }
  piVar1 = node->child->next;
  if (piVar1->op == IL_CONST) {
    is_const = is_const_value(piVar1,0,piVar1->type);
    piVar1 = new_const_node(node->type,(uint)(is_const == 0));
  }
  else {
    piVar1 = copy_tree(0,piVar1);
    piVar1 = make_node(IL_NOT,node->type,piVar1,(il_node *)0x0,(il_node *)0x0);
    piVar1 = make_node(IL_NOT,node->type,piVar1,(il_node *)0x0,(il_node *)0x0);
  }
  piVar1->filn = filn;
  piVar1->line = line;
  piVar1->listno = listno;
  replace_and_free_node(node,piVar1);
  return piVar1;
}



