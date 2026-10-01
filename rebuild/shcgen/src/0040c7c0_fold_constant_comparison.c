#include "decls.h"
#include "imports.h"

// entry: 0040c7c0
// name : fold_constant_comparison
// size : 1357
// sig  : short fold_constant_comparison(char op, gen_node * left, gen_node * right, gen_node * node)


short __cdecl fold_constant_comparison(char op,gen_node *left,gen_node *right,gen_node *node)

{
  char bool_result;
  short result;
  undefined3 extraout_var = 0;
  undefined3 extraout_var_00 = 0;
  undefined3 extraout_var_01 = 0;
  undefined3 extraout_var_02 = 0;
  undefined3 extraout_var_03 = 0;
  undefined3 extraout_var_04 = 0;
  int int_result;
  undefined3 extraout_var_05 = 0;
  undefined3 extraout_var_06 = 0;
  byte type_class;
  byte type_bits;
  
  result = 0;
  switch(op) {
  case '`':
    type_bits = left->type;
    type_class = type_bits & 0xe0;
    if (type_class != 0x20) {
      if ((((type_bits & 4) == 0) && (type_class != 0x80)) && (type_class != 0x40)) {
        int_result = fold_int_eq(&(left->desc->value).disp,&(right->desc->value).disp,
                                 &(node->desc->value).disp);
        return (short)int_result;
      }
      int_result = fold_eq_unsigned(&(left->desc->value).disp,&(right->desc->value).disp,
                                    &(node->desc->value).disp);
      return (short)int_result;
    }
    type_bits = type_bits & 0xf8;
    if (type_bits == 0x28) {
      int_result = fold_float_eq((uint *)&(left->desc->value).disp,
                                 (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)int_result;
    }
    if ((type_bits == 0x30) || (type_bits == 0x38)) {
      int_result = fold_double_eq((uint *)&(left->desc->value).disp,
                                  (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)int_result;
    }
    break;
  case 'a':
    type_bits = left->type;
    type_class = type_bits & 0xe0;
    if (type_class != 0x20) {
      if ((((type_bits & 4) == 0) && (type_class != 0x80)) && (type_class != 0x40)) {
        int_result = fold_int_ne(&(left->desc->value).disp,&(right->desc->value).disp,
                                 &(node->desc->value).disp);
        return (short)int_result;
      }
      int_result = fold_ne_unsigned(&(left->desc->value).disp,&(right->desc->value).disp,
                                    &(node->desc->value).disp);
      return (short)int_result;
    }
    type_bits = type_bits & 0xf8;
    if (type_bits == 0x28) {
      int_result = fold_float_ne((uint *)&(left->desc->value).disp,
                                 (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)int_result;
    }
    if ((type_bits == 0x30) || (type_bits == 0x38)) {
      int_result = fold_double_ne((uint *)&(left->desc->value).disp,
                                  (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)int_result;
    }
    break;
  case 'd':
    type_bits = left->type;
    type_class = type_bits & 0xe0;
    if (type_class != 0x20) {
      if ((((((type_bits & 4) == 0) && (type_class != 0x80)) && (type_class != 0x40)) &&
          (((type_bits & 0xf8) != 0x40 && ((type_bits & 0xf8) != 0x48)))) && (type_class != 0x80)) {
        int_result = fold_int_lt(&(left->desc->value).disp,&(right->desc->value).disp,
                                 &(node->desc->value).disp);
        return (short)int_result;
      }
      int_result = fold_lt_unsigned((uint *)&(left->desc->value).disp,
                                    (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)int_result;
    }
    type_bits = type_bits & 0xf8;
    if (type_bits == 0x28) {
      bool_result = fold_float_lt((uint *)&(left->desc->value).disp,
                                  (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)CONCAT31(extraout_var,bool_result);
    }
    if ((type_bits == 0x30) || (type_bits == 0x38)) {
      bool_result = fold_double_lt((uint *)&(left->desc->value).disp,
                                   (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)CONCAT31(extraout_var_00,bool_result);
    }
    break;
  case 'e':
    type_bits = left->type;
    type_class = type_bits & 0xe0;
    if (type_class != 0x20) {
      if ((((((type_bits & 4) == 0) && (type_class != 0x80)) && (type_class != 0x40)) &&
          (((type_bits & 0xf8) != 0x40 && ((type_bits & 0xf8) != 0x48)))) && (type_class != 0x80)) {
        int_result = fold_int_le(&(left->desc->value).disp,&(right->desc->value).disp,
                                 &(node->desc->value).disp);
        return (short)int_result;
      }
      int_result = fold_le_unsigned((uint *)&(left->desc->value).disp,
                                    (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)int_result;
    }
    type_bits = type_bits & 0xf8;
    if (type_bits == 0x28) {
      bool_result = fold_float_le((uint *)&(left->desc->value).disp,
                                  (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)CONCAT31(extraout_var_01,bool_result);
    }
    if ((type_bits == 0x30) || (type_bits == 0x38)) {
      bool_result = fold_double_le((uint *)&(left->desc->value).disp,
                                   (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)CONCAT31(extraout_var_02,bool_result);
    }
    break;
  case 'f':
    type_bits = left->type;
    type_class = type_bits & 0xe0;
    if (type_class != 0x20) {
      if (((((type_bits & 4) == 0) && (type_class != 0x80)) && (type_class != 0x40)) &&
         ((((type_bits & 0xf8) != 0x40 && ((type_bits & 0xf8) != 0x48)) && (type_class != 0x80)))) {
        int_result = fold_int_gt(&(left->desc->value).disp,&(right->desc->value).disp,
                                 &(node->desc->value).disp);
        return (short)int_result;
      }
      int_result = fold_gt_unsigned((uint *)&(left->desc->value).disp,
                                    (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)int_result;
    }
    type_bits = type_bits & 0xf8;
    if (type_bits == 0x28) {
      bool_result = fold_float_gt((uint *)&(left->desc->value).disp,
                                  (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)CONCAT31(extraout_var_03,bool_result);
    }
    if ((type_bits == 0x30) || (type_bits == 0x38)) {
      bool_result = fold_double_gt((uint *)&(left->desc->value).disp,
                                   (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)CONCAT31(extraout_var_04,bool_result);
    }
    break;
  case 'g':
    type_bits = left->type;
    type_class = type_bits & 0xe0;
    if (type_class != 0x20) {
      if ((((((type_bits & 4) == 0) && (type_class != 0x80)) && (type_class != 0x40)) &&
          (((type_bits & 0xf8) != 0x40 && ((type_bits & 0xf8) != 0x48)))) && (type_class != 0x80)) {
        int_result = fold_ge_signed(&(left->desc->value).disp,&(right->desc->value).disp,
                                    &(node->desc->value).disp);
        return (short)int_result;
      }
      int_result = fold_ge_unsigned((uint *)&(left->desc->value).disp,
                                    (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)int_result;
    }
    type_bits = type_bits & 0xf8;
    if (type_bits == 0x28) {
      bool_result = fold_float_ge((uint *)&(left->desc->value).disp,
                                  (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      return (short)CONCAT31(extraout_var_05,bool_result);
    }
    if ((type_bits == 0x30) || (type_bits == 0x38)) {
      bool_result = fold_double_ge((uint *)&(left->desc->value).disp,
                                   (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
      result = (short)CONCAT31(extraout_var_06,bool_result);
    }
  }
  return result;
}



