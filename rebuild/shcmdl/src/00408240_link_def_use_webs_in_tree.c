#include "decls.h"
#include "imports.h"

// entry: 00408240
// name : link_def_use_webs_in_tree
// size : 262
// sig  : void link_def_use_webs_in_tree(il_node * node)


int __cdecl link_def_use_webs_in_tree(il_node *node)

{
  il_node *piVar1;
  byte type_class;
  node_list *cell;
  il_op op;
  
  for (piVar1 = node->child; piVar1 != (il_node *)0x0; piVar1 = piVar1->next) {
    link_def_use_webs_in_tree(piVar1);
  }
  op = node->op;
  if (((op == IL_ID) && (type_class = node->type & 0xf0, type_class != 0x80)) &&
     (type_class != 0x90)) {
    if ((node != node->cmnexp) && (node->duptr != (dutbl *)0x0)) {
      switch(node->cmnexp->op) {
      case IL_PRI:
      case IL_PRD:
      case IL_POI:
      case IL_POD:
      case IL_A_ADD:
      case IL_A_SUB:
      case IL_A_MUL:
      case IL_A_DIV:
      case IL_A_MOD:
      case IL_A_SL:
      case IL_A_SR:
      case IL_A_AND:
      case IL_A_XOR:
      case IL_A_OR:
      case IL_ASSIGN:
        piVar1 = node->refchn;
        while (piVar1 != (il_node *)0x0) {
          node = node->refchn;
          piVar1 = node->refchn;
        }
        cell = regalloc_alloc(8);
        cell->next = node->duptr->links;
        node->duptr->links = cell;
        node->duptr->links->node = node->cmnexp;
        node->duptr->kind = 1;
        cell = regalloc_alloc(8);
        cell->next = node->cmnexp->duptr->links;
        node->cmnexp->duptr->links = cell;
        node->cmnexp->duptr->links->node = node;
        node->cmnexp->duptr->kind = 2;
        return;
      }
    }
  }
  else if ((((op & IL_NON_F0) == IL_A_ADD) || ((op & IL_NON_F8) == IL_PRI)) &&
          (node->duptr != (dutbl *)0x0)) {
    node->duptr->kind = 2;
  }
  return;
}



