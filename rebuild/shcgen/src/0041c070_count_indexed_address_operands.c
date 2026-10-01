#include "decls.h"
#include "imports.h"

// entry: 0041c070
// name : count_indexed_address_operands
// size : 102
// sig  : void count_indexed_address_operands(gen_node * cast)


int __cdecl count_indexed_address_operands(gen_node *cast)

{
  int shape;
  gen_node *base;
  gen_node *right;
  gen_node *sum;
  
  sum = cast->child;
  if (sum->op == IL_ADD) {
    base = sum->child;
    right = (gen_node *)0x0;
    if (base != (gen_node *)0x0) {
      right = base->next;
    }
    shape = classify_indexed_address_operands(base,right);
    if (shape != 0) {
      g_deref_total = g_deref_total + 1;
      base = sum->child;
      if (shape != 1) {
        base = base->child;
      }
      count_deref_use(base);
      if (sum->child != (gen_node *)0x0) {
        count_deref_use(sum->child->next);
        return;
      }
      count_deref_use((gen_node *)0x0);
    }
  }
  return;
}



