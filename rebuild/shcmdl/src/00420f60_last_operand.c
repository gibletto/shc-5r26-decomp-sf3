#include "decls.h"
#include "imports.h"

// entry: 00420f60
// name : last_operand
// size : 49
// sig  : il_node * __cdecl last_operand(il_node *node)


il_node * __cdecl last_operand(il_node *node)

{
  il_node *last;
  il_node *next;
  
  if ((node == (il_node *)0x0) || (node->child == (il_node *)0x0)) {
    fatal_error(0x1073);
  }
  last = node->child;
  next = last->next;
  while (next != (il_node *)0x0) {
    last = last->next;
    next = last->next;
  }
  return last;
}
