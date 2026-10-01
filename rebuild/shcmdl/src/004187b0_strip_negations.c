#include "decls.h"
#include "imports.h"

// entry: 004187b0
// name : strip_negations
// size : 101
// sig  : void strip_negations(il_node * tree)


int __cdecl strip_negations(il_node *tree)

{
  int index;
  il_node *child;
  il_node *next;
  
  child = tree->child;
  while (child != (il_node *)0x0) {
    next = child->next;
    strip_negations(child);
    child = next;
  }
  if (tree->op == IL_MINUS) {
    child = tree->child;
    index = operand_index(tree);
    child->parent = (il_node *)0x0;
    tree->child = (il_node *)0x0;
    insert_operands(tree->parent,child,index);
    index = operand_index(tree);
    delete_operand(tree->parent,index);
  }
  return;
}



