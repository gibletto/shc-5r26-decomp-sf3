#include "decls.h"
#include "imports.h"

// entry: 0041cf90
// name : lreg_ref_in_statement
// size : 117
// sig  : int lreg_ref_in_statement(il_node * node, int pp, lreg * lr)


int __cdecl lreg_ref_in_statement(il_node *node,int pp,lreg *lr)

{
  ushort other_pp;
  undefined2 extraout_var = 0;
  int cexp;
  il_node *other;
  void *ref;
  
  ref = lr->chain;
  do {
    if (ref == (void *)0x0) {
      return 0;
    }
    for (cexp = *(int *)((int)ref + 0x10); cexp != 0; cexp = *(int *)(cexp + 0x40)) {
      for (other = *(il_node **)(cexp + 0x3c); other != (il_node *)0x0; other = other->refchn) {
        if ((node != other) &&
           (other_pp = statement_pp(other), CONCAT22(extraout_var,other_pp) == pp)) {
          return 1;
        }
      }
    }
    ref = *(void **)((int)ref + 8);
  } while( true );
}



