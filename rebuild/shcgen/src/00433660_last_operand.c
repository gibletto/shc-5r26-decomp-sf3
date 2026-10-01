#include "decls.h"
#include "imports.h"

// entry: 00433660
// name : last_operand
// size : 31
// sig  : gen_node * last_operand(gen_node * node)


gen_node * __cdecl last_operand(gen_node *node)

{
  gen_node *last;
  gen_node *next;
  
  last = node->child;
  if (last == (gen_node *)0x0) {
    return (gen_node *)0x0;
  }
  next = last->next;
  while (next != (gen_node *)0x0) {
    last = last->next;
    next = last->next;
  }
  return last;
}



