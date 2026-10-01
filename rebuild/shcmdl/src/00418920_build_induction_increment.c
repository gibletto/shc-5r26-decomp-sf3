#include "decls.h"
#include "imports.h"

// entry: 00418920
// name : build_induction_increment
// size : 150
// sig  : void build_induction_increment(iv_use * use, il_node * step)


int __cdecl build_induction_increment(iv_use *use,il_node *step)

{
  il_node *incr;
  il_node *piVar1;
  il_node *tail;
  node_list *factor;
  
  incr = copy_tree(0,step);
  incr = make_node(IL_CAST,incr->type,incr,(il_node *)0x0,(il_node *)0x0);
  for (factor = use->factors; factor != (node_list *)0x0; factor = factor->next) {
    if (factor->node->type != incr->type) {
      piVar1 = make_node(IL_CAST,incr->type,factor->node,(il_node *)0x0,(il_node *)0x0);
      factor->node = piVar1;
    }
    incr = make_node(IL_MUL,incr->type,incr,factor->node,(il_node *)0x0);
  }
  piVar1 = use->incr;
  if (use->incr == (il_node *)0x0) {
    use->incr = incr;
    return;
  }
  do {
    tail = piVar1;
    piVar1 = tail->child;
  } while (tail->child != (il_node *)0x0);
  tail->child = incr;
  incr->parent = tail;
  return;
}



