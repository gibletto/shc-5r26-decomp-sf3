#include "decls.h"
#include "imports.h"

// entry: 00420aa0
// name : replace_operand
// size : 136
// sig  : int replace_operand(il_node * parent, il_node * node, int pos)


int __cdecl replace_operand(il_node *parent,il_node *node,int pos)

{
  int iVar1;
  il_node *cur;
  il_node *next;
  il_node *prev_item;
  
  if ((parent == (il_node *)0x0) || (node == (il_node *)0x0)) {
    fatal_error(0x106c);
  }
  iVar1 = 1;
  cur = parent->child;
  do {
    if (iVar1 == pos) {
      if (iVar1 == 1) {
        parent->child = node;
      }
      else {
        prev_item->next = node;
      }
      node->parent = parent;
      node->next = cur->next;
      cur->next = (il_node *)0x0;
      free_tree(cur);
      return 0;
    }
    next = cur;
    if (cur != (il_node *)0x0) {
      next = cur->next;
    }
    iVar1 = iVar1 + 1;
    prev_item = cur;
    cur = next;
  } while (next != (il_node *)0x0);
  iVar1 = fatal_error(0x106d);
  return iVar1;
}



