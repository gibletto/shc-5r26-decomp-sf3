#include "decls.h"
#include "imports.h"

// entry: 00420d30
// name : replace_node
// size : 158
// sig  : void replace_node(il_node * old_node, il_node * new_node)


int __cdecl replace_node(il_node *old_node,il_node *new_node)

{
  ushort flags;
  il_node *prev;
  il_node *next;
  il_node *parent;
  
  if ((old_node == (il_node *)0x0) || (new_node == (il_node *)0x0)) {
    fatal_error(0x106f);
  }
  if (new_node != old_node) {
    parent = old_node->parent;
    prev = parent->child;
    if (old_node == prev) {
      parent->child = new_node;
    }
    else if (prev != (il_node *)0x0) {
      do {
        next = prev->next;
        if (old_node == next) break;
        prev = next;
      } while (next != (il_node *)0x0);
      if (prev != (il_node *)0x0) {
        prev->next = new_node;
      }
    }
    new_node->parent = parent;
    new_node->next = old_node->next;
    old_node->parent = (il_node *)0x0;
    old_node->next = (il_node *)0x0;
    flags = (byte)new_node->flag & 2 | parent->flag;
    parent->flag = flags;
    parent->flag = (byte)new_node->flag & 0x40 | flags;
    flags = new_node->flag & 0xffdf;
    new_node->flag = flags;
    new_node->flag = (byte)old_node->flag & 0x20 | flags;
  }
  return;
}



