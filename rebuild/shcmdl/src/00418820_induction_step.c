#include "decls.h"
#include "imports.h"

// entry: 00418820
// name : induction_step
// size : 245
// sig  : int induction_step(il_node * stmt)


int __cdecl induction_step(il_node *stmt)

{
  il_node *piVar1;
  int step;
  il_op op;
  il_node *rhs;
  
  op = stmt->op;
  if (op == IL_COMMA) {
    step = induction_step(stmt->child);
    return step;
  }
  if (((op == IL_PRI) && ((stmt->type & 0xe0) == 0)) ||
     ((op == IL_POI && ((stmt->type & 0xe0) == 0)))) {
    return 1;
  }
  if (((op == IL_PRD) && ((stmt->type & 0xe0) == 0)) ||
     ((op == IL_POD && ((stmt->type & 0xe0) == 0)))) {
    return -1;
  }
  if (((op == IL_A_ADD) && ((stmt->type & 0xe0) == 0)) &&
     (piVar1 = stmt->child->next, piVar1->op == IL_CONST)) {
    return piVar1->val;
  }
  if (((op == IL_A_SUB) && ((stmt->type & 0xe0) == 0)) &&
     (piVar1 = stmt->child->next, piVar1->op == IL_CONST)) {
    return -piVar1->val;
  }
  if ((op != IL_ASSIGN) || ((stmt->type & 0xe0) != 0)) {
    return 0;
  }
  piVar1 = stmt->child;
  rhs = piVar1->next;
  if (rhs->op != IL_ADD) {
    if (rhs->op != IL_SUB) {
      return 0;
    }
    if ((rhs->child->nleaf == piVar1->nleaf) && (piVar1 = rhs->child->next, piVar1->op == IL_CONST))
    {
      return -piVar1->val;
    }
    return 0;
  }
  rhs = rhs->child;
  if ((rhs->nleaf == piVar1->nleaf) && (rhs->next->op == IL_CONST)) {
    return rhs->next->val;
  }
  if ((rhs->next->nleaf == piVar1->nleaf) && (rhs->op == IL_CONST)) {
    return rhs->val;
  }
  return 0;
}



