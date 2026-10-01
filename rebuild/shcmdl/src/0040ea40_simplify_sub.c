#include "decls.h"
#include "imports.h"

// entry: 0040ea40
// name : simplify_sub
// size : 285
// sig  : il_node * simplify_sub(il_node * node)


il_node * __cdecl simplify_sub(il_node *node)

{
  il_node *piVar1;
  uint is_const;
  short filn;
  ushort line;
  short listno;
  il_node *rhs;
  
  filn = node->filn;
  line = node->line;
  listno = node->listno;
  piVar1 = node->child;
  if ((((piVar1->op == IL_ID) && ((piVar1->type & 2) == 0)) &&
      (rhs = piVar1->next, rhs->op == IL_ID)) &&
     (((rhs->type & 2) == 0 && (rhs->symx == piVar1->symx)))) {
    piVar1 = new_const_node(node->type & 0xfc,0);
    piVar1->filn = filn;
    piVar1->line = line;
    piVar1->listno = listno;
    replace_and_free_node(node,piVar1);
    return piVar1;
  }
  is_const = is_const_value(piVar1,0,node->type);
  if (is_const != 0) {
    piVar1 = copy_tree(0,node->child->next);
    piVar1 = make_node(IL_MINUS,node->type,piVar1,(il_node *)0x0,(il_node *)0x0);
    piVar1->filn = filn;
    piVar1->line = line;
    piVar1->listno = listno;
    replace_and_free_node(node,piVar1);
    return piVar1;
  }
  is_const = is_const_value(node->child->next,0,node->type);
  piVar1 = node;
  if (is_const != 0) {
    piVar1 = copy_tree(0,node->child);
    replace_and_free_node(node,piVar1);
  }
  return piVar1;
}



