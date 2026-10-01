#include "decls.h"
#include "imports.h"

// entry: 00420dd0
// name : insert_before
// size : 137
// sig  : void insert_before(il_node * pos, il_node * node)


int __cdecl insert_before(il_node *pos,il_node *node)

{
  ushort flags;
  il_node *prev;
  il_node *next;
  il_node *parent;
  
  if ((pos == (il_node *)0x0) || (node == (il_node *)0x0)) {
    fatal_error(0x1070);
  }
  parent = pos->parent;
  prev = parent->child;
  if (pos == prev) {
    parent->child = node;
  }
  else if (prev != (il_node *)0x0) {
    do {
      next = prev->next;
      if (pos == next) break;
      prev = next;
    } while (next != (il_node *)0x0);
    if (prev != (il_node *)0x0) {
      prev->next = node;
    }
  }
  node->parent = parent;
  node->next = pos;
  flags = (byte)node->flag & 2 | parent->flag;
  parent->flag = flags;
  flags = (byte)node->flag & 0x40 | flags;
  parent->flag = flags;
  parent->flag = node->flag & 0x800 | flags;
  set_value_used_flag(node);
  return;
}



