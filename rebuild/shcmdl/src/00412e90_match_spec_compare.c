#include "decls.h"
#include "imports.h"

// entry: 00412e90
// name : match_spec_compare
// size : 330
// sig  : int match_spec_compare(il_node * ifnode, short sym1, short sym2)


int __cdecl match_spec_compare(il_node *ifnode,short sym1,short sym2)

{
  il_node *piVar1;
  il_node *piVar2;
  
  piVar1 = ifnode->child;
  if (((((piVar1->type & 0xf8) != 0x10) || (piVar2 = piVar1->child, piVar2->op != IL_ID)) ||
      (piVar2->symx != sym1)) || ((piVar2->next->op != IL_ID || (piVar2->next->symx != sym2)))) {
    return 0;
  }
  piVar1 = piVar1->next->child;
  if ((piVar1->op != IL_IF) || (piVar1->next->op != IL_E_BLOCK)) {
    return 0;
  }
  piVar1 = piVar1->child;
  if (((piVar1->op != IL_LT) || (piVar2 = piVar1->next, piVar2->op != IL_BLOCK)) ||
     (piVar2->next->op != IL_BLOCK)) {
    return 0;
  }
  if ((((piVar1->type & 0xf8) != 0x10) || (piVar1 = piVar1->child, piVar1->op != IL_ID)) ||
     ((piVar1->symx != sym1 || ((piVar1->next->op != IL_ID || (piVar1->next->symx != sym2)))))) {
    return 0;
  }
  piVar1 = piVar2->child;
  if ((piVar1->op != IL_RETURN) || (piVar1->next->op != IL_E_BLOCK)) {
    return 0;
  }
  piVar1 = piVar1->child;
  if ((((piVar1->op == IL_MINUS) && ((piVar1->type & 0xf8) == 0x10)) &&
      (piVar1->child->op == IL_CONST)) && (piVar1->child->val == 1)) {
    piVar1 = piVar2->next->child;
    if (((piVar1->op == IL_RETURN) && (piVar2 = piVar1->child, piVar2->op == IL_CONST)) &&
       (((piVar2->type & 0xf8) == 0x10 && ((piVar2->val == 1 && (piVar1->next->op == IL_E_BLOCK)))))
       ) {
      return 1;
    }
    return 0;
  }
  return 0;
}



