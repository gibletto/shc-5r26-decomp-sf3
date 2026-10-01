#include "decls.h"
#include "imports.h"

// entry: 00423480
// name : forward_member_constant_store
// size : 234
// sig  : void forward_member_constant_store(node_list * stmt)


int __cdecl forward_member_constant_store(node_list *stmt)

{
  il_node *piVar1;
  il_node *tree;
  int effect;
  il_node *assign;
  il_op op;
  
  assign = stmt->node;
  if ((((assign->op == IL_ASSIGN) && (piVar1 = assign->child, piVar1->op == IL_QUALIFY)) &&
      (piVar1->next->op == IL_CONST)) &&
     ((effect = has_side_effect_or_indirection(piVar1), effect != 1 &&
      (piVar1 = assign->child, (piVar1->type & 0xe0) != 0x20)))) {
    for (; piVar1 != (il_node *)0x0; piVar1 = piVar1->child) {
      if ((piVar1->op != IL_ID) && (piVar1->op != IL_QUALIFY)) {
        return;
      }
    }
    if (stmt->next != (node_list *)0x0) {
      piVar1 = stmt->next->node;
      for (tree = piVar1->child; tree != (il_node *)0x0; tree = tree->next) {
        effect = has_side_effect_or_indirection(tree);
        if (effect == 1) {
          return;
        }
      }
      op = piVar1->op;
      if ((op & IL_NON_F8) != IL_PRI) {
        if (('O' < (char)op) && ((char)op < '`')) {
          replace_subtrees_with_constant(piVar1->child->next,assign->child,assign->child->next);
          return;
        }
        if ((((('\x1f' < (char)op) && ((char)op < '5')) && (op != IL_AMPER)) && (op != IL_ASTER)) ||
           ('?' < (char)op)) {
          replace_subtrees_with_constant(piVar1,assign->child,assign->child->next);
        }
      }
    }
  }
  return;
}



