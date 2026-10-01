#include "decls.h"
#include "imports.h"

// entry: 00419110
// name : fold_and_check_overflow
// size : 350
// sig  : uint fold_and_check_overflow(il_node * node)


uint __cdecl fold_and_check_overflow(il_node *node)

{
  byte ty;
  uint result;
  il_node *piVar1;
  il_op op;
  
  if (node->child == (il_node *)0x0) {
    return 0;
  }
  result = fold_and_check_overflow(node->child);
  if ((result == 1) || (result == 2)) {
    return result;
  }
  piVar1 = node->child->next;
  if ((piVar1 != (il_node *)0x0) &&
     ((result = fold_and_check_overflow(piVar1), result == 1 || (result == 2)))) {
    return result;
  }
  op = node->op;
  if ((((op & IL_NON_F0) == IL_CAST) || ((op & IL_NON_F0) == IL_CALL)) && (op != IL_CALL)) {
    piVar1 = node->child;
    if ((op == IL_CAST) && (piVar1->op == IL_CONST)) {
      ty = piVar1->type;
      if ((((((ty & 0xe0) == 0) && ((ty & 4) != 0)) &&
           (((node->type & 0xe0) != 0 || ((node->type & 4) == 0)))) ||
          ((((ty & 0xe0) != 0 || ((ty & 4) == 0)) &&
           (((node->type & 0xe0) == 0 && ((node->type & 4) != 0)))))) &&
         ((piVar1->val & 0x80000000U) != 0)) {
        result = 1;
      }
    }
    fold_constants(node);
    return result;
  }
  if (((*(int *)(&g_fold_op_table + (char)op * 4) != 0) && (node->child->op == IL_CONST)) &&
     (node->child->next->op == IL_CONST)) {
    piVar1 = copy_tree(0,node);
    piVar1 = fold_constants(piVar1);
    ty = node->type & 0xf8;
    if ((ty == 0) || (ty == 8)) {
      result = check_value_range(node->type,piVar1->val);
    }
    else if ((ty == 0x10) || (ty == 0x18)) {
      result = check_arith_overflow(node,piVar1->val);
    }
    if (result != 0) {
      free_tree(piVar1);
      return result;
    }
    replace_and_free_node(node,piVar1);
    return 0;
  }
  return 3;
}



