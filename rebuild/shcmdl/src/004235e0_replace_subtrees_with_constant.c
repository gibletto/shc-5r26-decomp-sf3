#include "decls.h"
#include "imports.h"

// entry: 004235e0
// name : replace_subtrees_with_constant
// size : 131
// sig  : void replace_subtrees_with_constant(il_node * tree, il_node * pattern, il_node * constant)


int __cdecl replace_subtrees_with_constant(il_node *tree,il_node *pattern,il_node *constant)

{
  il_node *child;
  uint differs;
  int iVar1;
  
  iVar1 = 1;
  child = tree->child;
  while (child != (il_node *)0x0) {
    iVar1 = iVar1 + 1;
    replace_subtrees_with_constant(child,pattern,constant);
    child = nth_operand(iVar1,tree);
  }
  if ((pattern->op == tree->op) && (differs = trees_differ(tree,pattern), differs == 0)) {
    unlink_from_common_expression_chains(tree->child);
    free_tree(tree->child);
    tree->op = IL_CONST;
    tree->val = constant->val;
    tree->val2 = constant->val2;
    iVar1 = constant->val3;
    tree->child = (il_node *)0x0;
    tree->val3 = iVar1;
  }
  return;
}



