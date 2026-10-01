#include "decls.h"
#include "imports.h"

// entry: 004335c0
// name : prepend_operand
// size : 35
// sig  : int prepend_operand(gen_node * parent, gen_node * operand)


int __cdecl prepend_operand(gen_node *parent,gen_node *operand)

{
  undefined4 in_EAX;
  gen_node *first;
  
  if (operand->next != (gen_node *)0x0) {
    return CONCAT22((short)((uint)in_EAX >> 0x10),0xffff);
  }
  first = parent->child;
  parent->child = operand;
  operand->next = first;
  operand->parent = parent;
  return (uint)parent & 0xffff0000;
}



