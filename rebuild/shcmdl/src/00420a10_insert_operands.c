#include "decls.h"
#include "imports.h"

// entry: 00420a10
// name : insert_operands
// size : 139
// sig  : void insert_operands(il_node * parent, il_node * list, int pos)


int __cdecl insert_operands(il_node *parent,il_node *list,int pos)

{
  int index;
  il_node *cur;
  il_node *next;
  il_node *prev;
  
  if (((parent == (il_node *)0x0) || (list == (il_node *)0x0)) || (pos < 1)) {
    fatal_error(0x106a);
  }
  index = 1;
  next = parent->child;
  prev = (il_node *)0x0;
  do {
    cur = next;
    if (index == pos) {
      if (index == 1) {
        parent->child = list;
      }
      else {
        prev->next = list;
      }
      list->parent = parent;
      next = list->next;
      while (next != (il_node *)0x0) {
        list->next->parent = parent;
        list = list->next;
        next = list->next;
      }
      list->next = cur;
      return;
    }
    next = cur;
    if (cur != (il_node *)0x0) {
      next = cur->next;
    }
    index = index + 1;
    prev = cur;
  } while (next != (il_node *)0x0);
  fatal_error(0x106b);
  return;
}



