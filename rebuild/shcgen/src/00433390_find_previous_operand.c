#include "decls.h"
#include "imports.h"

// entry: 00433390
// name : find_previous_operand
// size : 62
// sig  : gen_node * find_previous_operand(gen_node * node)


gen_node * __cdecl find_previous_operand(gen_node *node)

{
  gen_node *cur;
  gen_node *prev;
  
  if ((node != (gen_node *)0x0) && (node->parent != (gen_node *)0x0)) {
    prev = node->parent->child;
    if (prev != node) {
      for (cur = prev->next; (cur != (gen_node *)0x0 && (cur != node)); cur = cur->next) {
        prev = cur;
      }
      return (gen_node *)((cur == (gen_node *)0x0) - 1 & (uint)prev);
    }
    return (gen_node *)0x0;
  }
  return (gen_node *)0x0;
}



