#include "decls.h"
#include "imports.h"

// entry: 00422b10
// name : unlink_from_common_expression_chains
// size : 181
// sig  : void unlink_from_common_expression_chains(il_node * node)


int __cdecl unlink_from_common_expression_chains(il_node *node)

{
  il_node *piVar1;
  il_node *piVar2;
  il_node *local_4;
  dutbl *du;
  
  for (piVar1 = node->child; piVar1 != (il_node *)0x0; piVar1 = piVar1->next) {
    unlink_from_common_expression_chains(piVar1);
  }
  piVar1 = node->cmnexp;
  piVar2 = node;
  if (node == piVar1) {
    do {
      piVar1 = piVar2;
      if (piVar1 == (il_node *)0x0) goto LAB_00422b79;
      local_4 = piVar1->refchn;
      piVar2 = local_4;
    } while ((local_4 == (il_node *)0x0) || (local_4->refchn != (il_node *)0x0));
    local_4->cmnexp = local_4;
    local_4->duptr = node->cmnexp->duptr;
    du = local_4->cmnexp->duptr;
    if (du != (dutbl *)0x0) {
      du->node = local_4;
    }
    piVar1->refchn = (il_node *)0x0;
LAB_00422b79:
    piVar1 = node->refchn;
    if (piVar1 != local_4) {
      local_4->refchn = piVar1;
    }
    node->refchn = (il_node *)0x0;
    if (piVar1 != (il_node *)0x0) {
      do {
        piVar1->cmnexp = local_4;
        piVar1 = piVar1->refchn;
      } while (piVar1 != (il_node *)0x0);
      return;
    }
  }
  else if (piVar1 != (il_node *)0x0) {
    while (piVar2 = piVar1, piVar2 != node) {
      piVar1 = piVar2->refchn;
      local_4 = piVar2;
      if (piVar2->refchn == (il_node *)0x0) {
        return;
      }
    }
    local_4->refchn = piVar2->refchn;
  }
  return;
}



