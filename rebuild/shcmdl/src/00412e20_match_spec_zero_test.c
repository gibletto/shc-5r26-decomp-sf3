#include "decls.h"
#include "imports.h"

// entry: 00412e20
// name : match_spec_zero_test
// size : 103
// sig  : int match_spec_zero_test(il_node * ifnode, short symx)


int __cdecl match_spec_zero_test(il_node *ifnode,short symx)

{
  il_node *cond;
  il_node *var;
  
  cond = ifnode->child;
  if (((((cond->type & 0xf8) != 0x10) || (var = cond->child, var->op != IL_ID)) ||
      (var->symx != symx)) || ((var->next->op != IL_CONST || (var->next->val != 2)))) {
    return 0;
  }
  if ((((cond->next->type & 0xf8) == 0x10) && (cond = cond->next->child, cond->op == IL_ID)) &&
     ((cond->symx == symx && ((cond->next->op == IL_CONST && (cond->next->val == 0)))))) {
    return 1;
  }
  return 0;
}



