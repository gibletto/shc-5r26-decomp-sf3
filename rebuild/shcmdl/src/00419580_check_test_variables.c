#include "decls.h"
#include "imports.h"

// entry: 00419580
// name : check_test_variables
// size : 107
// sig  : int check_test_variables(il_node * tree, int leafno)


int __cdecl check_test_variables(il_node *tree,int leafno)

{
  int ok;
  
  ok = 1;
  if ((tree->child != (il_node *)0x0) && (ok = check_test_variables(tree->child,leafno), ok == 0)) {
    return 0;
  }
  if ((tree->next != (il_node *)0x0) && (ok = check_test_variables(tree->next,leafno), ok == 0)) {
    return 0;
  }
  if ((((tree->op == IL_ID) && ((tree->type & 0xe0) != 0x80)) && ((tree->type & 0xf8) != 0x40)) &&
     (tree->nleaf != leafno)) {
    g_test_replace_ok = 0;
  }
  return ok;
}



