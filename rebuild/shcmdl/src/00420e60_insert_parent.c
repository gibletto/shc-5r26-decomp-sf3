#include "decls.h"
#include "imports.h"

// entry: 00420e60
// name : insert_parent
// size : 186
// sig  : void insert_parent(il_node * node, il_node * parent)


int __cdecl insert_parent(il_node *node,il_node *parent)

{
  ushort old_flags;
  ushort flags;
  il_node *prev;
  il_node *next;
  il_node *outer;
  
  if ((node == (il_node *)0x0) || (parent == (il_node *)0x0)) {
    fatal_error(0x1071);
  }
  outer = node->parent;
  prev = outer->child;
  if (prev == node) {
    outer->child = parent;
  }
  else if (prev != (il_node *)0x0) {
    do {
      next = prev->next;
      if (next == node) break;
      prev = next;
    } while (next != (il_node *)0x0);
    if (prev != (il_node *)0x0) {
      prev->next = parent;
    }
  }
  parent->parent = outer;
  parent->next = node->next;
  parent->child = node;
  node->parent = parent;
  node->next = (il_node *)0x0;
  parent->nodes = parent->nodes + node->nodes;
  old_flags = parent->flag;
  flags = old_flags & 0xffdf;
  parent->flag = flags;
  flags = (byte)node->flag & 0x20 | flags;
  parent->flag = flags;
  parent->flag = node->flag & 0x800 | flags;
  old_flags = old_flags & 2 | outer->flag;
  outer->flag = old_flags;
  outer->flag = (byte)parent->flag & 0x40 | old_flags;
  set_value_used_flag(node);
  return;
}



