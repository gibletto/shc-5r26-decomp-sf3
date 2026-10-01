#include "decls.h"
#include "imports.h"

// entry: 00423670
// name : trees_differ
// size : 261
// sig  : uint trees_differ(il_node * a, il_node * b)


uint __cdecl trees_differ(il_node *a,il_node *b)

{
  uint diff;
  uint result;
  il_node *a_operand;
  il_node *b_operand;
  
  result = 0;
  if (b->op != a->op) {
    return 1;
  }
  if (a->boff != b->boff) {
    return 1;
  }
  if (b->bsiz != a->bsiz) {
    return 1;
  }
  if (b->type == a->type) {
    if (b->symx != a->symx) {
      return 1;
    }
    if (((b->val == a->val) && (b->val2 == a->val2)) && (b->val3 == a->val3)) {
      if ((a->child != (il_node *)0x0) && (b->child != (il_node *)0x0)) {
        result = trees_differ(a->child,b->child);
        a_operand = a->child->next;
        if ((a_operand != (il_node *)0x0) &&
           (b_operand = b->child->next, b_operand != (il_node *)0x0)) {
          diff = trees_differ(a_operand,b_operand);
          result = result | diff;
          a_operand = a->child->next->next;
          if ((a_operand != (il_node *)0x0) &&
             (b_operand = b->child->next->next, b_operand != (il_node *)0x0)) {
            for (; (a_operand != (il_node *)0x0 && (b_operand != (il_node *)0x0));
                b_operand = b_operand->next) {
              diff = trees_differ(a_operand,b_operand);
              if ((result | diff) != 0) {
                return result | diff;
              }
              a_operand = a_operand->next;
              result = 0;
            }
          }
        }
      }
      return result;
    }
    return 1;
  }
  return 1;
}



