#include "decls.h"
#include "imports.h"

// entry: 00418d80
// name : copy_tree_unlinked
// size : 142
// sig  : il_node * copy_tree_unlinked(int mode, il_node * node)


il_node * __cdecl copy_tree_unlinked(int mode,il_node *node)

{
  uchar uVar1;
  uchar uVar2;
  uchar uVar3;
  il_node *copy;
  int n;
  il_node *next_copy;
  il_node *piVar4;
  il_node *children;
  
  next_copy = (il_node *)0x0;
  children = (il_node *)0x0;
  if (node == (il_node *)0x0) {
    return (il_node *)0x0;
  }
  copy = alloc_node_or_null();
  if (copy == (il_node *)0x0) {
    abort_function_optimization();
  }
  if (mode != 0) {
    if (mode == 1) goto LAB_00418de9;
    if (mode != 2) {
      return copy;
    }
    next_copy = copy_tree(2,node->next);
  }
  children = copy_tree(2,node->child);
  for (piVar4 = children; piVar4 != (il_node *)0x0; piVar4 = piVar4->next) {
    piVar4->parent = copy;
  }
LAB_00418de9:
  piVar4 = copy;
  for (n = 0x1a; n != 0; n = n + -1) {
    uVar1 = node->boff;
    uVar2 = node->bsiz;
    uVar3 = node->type;
    piVar4->op = node->op;
    piVar4->boff = uVar1;
    piVar4->bsiz = uVar2;
    piVar4->type = uVar3;
    node = (il_node *)&node->symx;
    piVar4 = (il_node *)&piVar4->symx;
  }
  copy->next = next_copy;
  copy->child = children;
  copy->refchn = (il_node *)0x0;
  copy->duptr = (dutbl *)0x0;
  return copy;
}



