#include "decls.h"
#include "imports.h"

// entry: 00411f80
// name : get_increment_target
// size : 115
// sig  : il_node * get_increment_target(il_node * def)


il_node * __cdecl get_increment_target(il_node *def)

{
  il_node *result;
  il_node *lhs;
  il_node *rhs;
  
  result = (il_node *)0x0;
  switch(def->op) {
  case IL_PRI:
  case IL_PRD:
  case IL_POI:
  case IL_POD:
  case IL_A_ADD:
  case IL_A_SUB:
    if ((def->type & 0xe0) == 0) {
      return def->child;
    }
    break;
  case IL_ASSIGN:
    if ((def->type & 0xe0) == 0) {
      lhs = def->child;
      rhs = lhs->next;
      if (rhs->op == IL_ADD) {
        if ((rhs->child->nleaf == lhs->nleaf) || (rhs->child->next->nleaf == lhs->nleaf)) {
          return lhs;
        }
      }
      else if ((rhs->op == IL_SUB) && (rhs->child->nleaf == lhs->nleaf)) {
        result = lhs;
      }
    }
  }
  return result;
}



