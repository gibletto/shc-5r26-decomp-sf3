#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00422520
// name : narrow_bit_test_to_char
// size : 466
// sig  : il_node * narrow_bit_test_to_char(il_node * left, il_node * right)


il_node * __cdecl narrow_bit_test_to_char(il_node *left,il_node *right)

{
  il_node *inner;
  il_op inner_op;
  il_node *parent;
  il_node *right_inner;
  int val;
  byte var_type;
  
  parent = left->parent;
  if (left->op == IL_CONST) {
    inner = right->child;
    if (((inner->op == IL_ID) && (0 < inner->symx)) &&
       (((g_symtab[inner->symx].attr & 3) != 0 &&
        (((var_type = inner->type, (var_type & 0xf8) == 0 && (-1 < left->val)) &&
         (left->val < 0x100)))))) {
      left->type = var_type;
      strip_operand_casts(left,right);
      parent->type = var_type;
      return parent;
    }
    return parent;
  }
  if (right->op == IL_CONST) {
    inner = left->child;
    if ((((inner->op == IL_ID) && (0 < inner->symx)) && ((g_symtab[inner->symx].attr & 3) != 0)) &&
       (((var_type = inner->type, (var_type & 0xf8) == 0 && (-1 < right->val)) &&
        (right->val < 0x100)))) {
      right->type = var_type;
      strip_operand_casts(left,right);
      parent->type = var_type;
      return parent;
    }
    return parent;
  }
  inner = left->child;
  inner_op = inner->op;
  if (((inner_op != IL_ID) || (right->child->op != IL_CONST)) &&
     ((inner_op != IL_CONST || (right->child->op != IL_ID)))) {
    return parent;
  }
  if ((((inner_op == IL_ID) && (0 < inner->symx)) && ((g_symtab[inner->symx].attr & 3) != 0)) &&
     (var_type = inner->type, (var_type & 0xf8) == 0)) {
    val = right->child->val;
    if ((-1 < val) && (val < 0x100)) {
      right->child->type = var_type;
      strip_operand_casts(left,right);
      parent->type = var_type;
      return parent;
    }
  }
  right_inner = right->child;
  if (((right_inner->op == IL_ID) &&
      ((0 < right_inner->symx && ((g_symtab[right_inner->symx].attr & 3) != 0)))) &&
     ((var_type = right_inner->type, (var_type & 0xf8) == 0 &&
      ((-1 < inner->val && (inner->val < 0x100)))))) {
    inner->type = var_type;
    strip_operand_casts(left,right);
    parent->type = var_type;
    return parent;
  }
  return parent;
}



