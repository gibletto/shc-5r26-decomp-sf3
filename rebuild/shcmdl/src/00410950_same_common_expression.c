#include "decls.h"
#include "imports.h"

// entry: 00410950
// name : same_common_expression
// size : 187
// sig  : int same_common_expression(il_node * a, il_node * b)


int __cdecl same_common_expression(il_node *a,il_node *b)

{
  int result;
  byte kind;
  il_node *ref;
  il_op op;
  
  result = 0;
  if ((a != (il_node *)0x0) && (b != (il_node *)0x0)) {
    if (((a->parent->op & IL_NON_F0) == IL_A_ADD) &&
       (((op = a->op, op == IL_QUALIFY && (b->op == IL_QUALIFY)) ||
        ((op == IL_ASTER &&
         ((((kind = a->type & 0xf0, kind != 0x80 && (kind != 0x90)) && (b->op == IL_ASTER)) &&
          ((kind = b->type & 0xf0, kind != 0x80 && (kind != 0x90)))))))))) {
      if ((op == IL_QUALIFY) && ((b->op == IL_QUALIFY && (b->val2 != a->val2)))) {
        return 0;
      }
      a = a->child;
      b = b->child;
    }
    if (a->cmnexp == a) {
      ref = a->refchn;
      if (ref != (il_node *)0x0) {
        do {
          if (ref == b) {
            return 1;
          }
          ref = ref->refchn;
        } while (ref != (il_node *)0x0);
        return result;
      }
    }
    else {
      ref = b->refchn;
      if (ref != (il_node *)0x0) {
        while (ref != a) {
          ref = ref->refchn;
          if (ref == (il_node *)0x0) {
            return result;
          }
        }
        result = 1;
      }
    }
  }
  return result;
}



