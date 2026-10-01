#include "decls.h"
#include "imports.h"

// entry: 0040cd30
// name : fold_constant_logical
// size : 375
// sig  : short fold_constant_logical(char op, gen_node * left, gen_node * right, gen_node * node)


short __cdecl fold_constant_logical(char op,gen_node *left,gen_node *right,gen_node *node)

{
  unsigned char _frec_8[8];
#define left_truth (*(uint *)(_frec_8 + 0))
#define right_truth (*(uint *)(_frec_8 + 4))
  short result;
  int int_result;
  uint uVar1;
  byte type_class;
  byte type_bits;
  
  result = 0;
  type_bits = left->type;
  type_class = type_bits & 0xe0;
  if (type_class == 0x20) {
    type_bits = type_bits & 0xf8;
    if (type_bits == 0x28) {
      int_result = fold_lnot_float((uint *)&(left->desc->value).disp,(int *)&left_truth);
      result = (short)int_result;
    }
    else if ((type_bits == 0x30) || (type_bits == 0x38)) {
      uVar1 = fold_lnot_double((uint *)&(left->desc->value).disp,(int *)&left_truth);
      result = (short)uVar1;
    }
  }
  else if ((((type_bits & 4) == 0) && (type_class != 0x80)) && (type_class != 0x40)) {
    int_result = fold_int_not(&(left->desc->value).disp,(int *)&left_truth);
    result = (short)int_result;
  }
  else {
    int_result = fold_lnot_unsigned(&(left->desc->value).disp,(int *)&left_truth);
    result = (short)int_result;
  }
  left_truth = left_truth ^ 1;
  if (((op == 'h') && (left_truth != 0)) || ((uVar1 = left_truth, op == 'i' && (left_truth == 0))))
  {
    type_bits = right->type;
    type_class = type_bits & 0xe0;
    if (type_class == 0x20) {
      type_bits = type_bits & 0xf8;
      if (type_bits == 0x28) {
        int_result = fold_lnot_float((uint *)&(right->desc->value).disp,(int *)&right_truth);
        result = (short)int_result;
      }
      else if ((type_bits == 0x30) || (type_bits == 0x38)) {
        uVar1 = fold_lnot_double((uint *)&(right->desc->value).disp,(int *)&right_truth);
        result = (short)uVar1;
      }
    }
    else if ((((type_bits & 4) == 0) && (type_class != 0x80)) && (type_class != 0x40)) {
      int_result = fold_int_not(&(right->desc->value).disp,(int *)&right_truth);
      result = (short)int_result;
    }
    else {
      int_result = fold_lnot_unsigned(&(right->desc->value).disp,(int *)&right_truth);
      result = (short)int_result;
    }
    uVar1 = right_truth ^ 1;
    if (op == 'h') {
      if ((left_truth == 0) || ((right_truth ^ 1) == 0)) {
        left_truth = 0;
        uVar1 = left_truth;
      }
      else {
        left_truth = 1;
        uVar1 = left_truth;
      }
    }
  }
  left_truth = uVar1;
  (node->desc->value).disp = left_truth;
  return result;
#undef left_truth
#undef right_truth
}



