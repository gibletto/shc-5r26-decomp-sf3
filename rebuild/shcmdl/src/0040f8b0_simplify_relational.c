#include "decls.h"
#include "imports.h"

// entry: 0040f8b0
// name : simplify_relational
// size : 317
// sig  : il_node * simplify_relational(il_node * node)


il_node * __cdecl simplify_relational(il_node *node)

{
  il_op op;
  int iVar1;
  uint uVar2;
  int want_min;
  int result_val;
  il_node *rhs;
  
  if (node->child->op == IL_CONST) {
    op = mirror_or_negate_relop(node->op,0);
    node->op = op;
    swap_operands(node);
  }
  rhs = node->child->next;
  if ((rhs->op == IL_CONST) && (((rhs->type & 0xe0) == 0 || ((rhs->type & 0xf8) == 0x40)))) {
    op = node->op;
    if ((op == IL_LT) || (want_min = 0, op == IL_GE)) {
      want_min = 1;
    }
    if ((op == IL_LT) || (result_val = 1, op == IL_GT)) {
      result_val = 0;
    }
    iVar1 = const_out_of_range(rhs);
    if (iVar1 != 0) {
      node->child->next->type = '\x10';
      op = node->op;
      if (iVar1 != 1) {
        if ((op != IL_LT) && (op != IL_LE)) {
          node->child->next->val = 1;
          node->op = IL_COMMA;
          return node;
        }
        node->child->next->val = 0;
        node->op = IL_COMMA;
        return node;
      }
      if ((op != IL_LT) && (op != IL_LE)) {
        node->child->next->val = 0;
        node->op = IL_COMMA;
        return node;
      }
      node->child->next->val = 1;
      node->op = IL_COMMA;
      return node;
    }
    rhs = node->child->next;
    iVar1 = (int)(char)rhs->type;
    uVar2 = type_limit(want_min,iVar1);
    uVar2 = is_const_value(rhs,uVar2,(uchar)iVar1);
    if (uVar2 != 0) {
      node->child->next->val = result_val;
      node->child->next->type = '\x10';
      node->op = IL_COMMA;
    }
  }
  return node;
}



