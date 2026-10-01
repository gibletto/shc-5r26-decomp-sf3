#include "decls.h"
#include "imports.h"

// entry: 0040c1b0
// name : fold_constant_arithmetic
// size : 968
// sig  : short fold_constant_arithmetic(char op, gen_node * left, gen_node * right, gen_node * node)


short __cdecl fold_constant_arithmetic(char op,gen_node *left,gen_node *right,gen_node *node)

{
  byte type_bits;
  short result;
  uint uint_result;
  int int_result;
  byte type_class;
  
  result = 0;
  switch(op) {
  case '@':
    type_bits = left->type;
    type_class = type_bits & 0xe0;
    if (type_class != 0x20) {
      if ((((type_bits & 4) == 0) && (type_class != 0x80)) && (type_class != 0x40)) {
        uint_result = fold_int_add(&(left->desc->value).disp,&(right->desc->value).disp,
                                   &(node->desc->value).disp);
        return (short)uint_result;
      }
      uint_result = fold_add_unsigned(&(left->desc->value).disp,&(right->desc->value).disp,
                                      &(node->desc->value).disp);
      return (short)uint_result;
    }
    type_bits = type_bits & 0xf8;
    if (type_bits == 0x28) {
      uint_result = fold_add_float((uint *)&(left->desc->value).disp,
                                   (uint *)&(right->desc->value).disp,
                                   (uint *)&(node->desc->value).disp);
      return (short)uint_result;
    }
    if ((type_bits == 0x30) || (type_bits == 0x38)) {
      uint_result = fold_add_double((uint *)&(left->desc->value).disp,
                                    (uint *)&(right->desc->value).disp,
                                    (uint *)&(node->desc->value).disp);
      return (short)uint_result;
    }
    break;
  case 'A':
    type_bits = left->type;
    type_class = type_bits & 0xe0;
    if (type_class != 0x20) {
      if ((((type_bits & 4) == 0) && (type_class != 0x80)) && (type_class != 0x40)) {
        uint_result = fold_int_sub(&(left->desc->value).disp,&(right->desc->value).disp,
                                   &(node->desc->value).disp);
        return (short)uint_result;
      }
      uint_result = fold_sub_unsigned(&(left->desc->value).disp,&(right->desc->value).disp,
                                      &(node->desc->value).disp);
      return (short)uint_result;
    }
    type_bits = type_bits & 0xf8;
    if (type_bits == 0x28) {
      uint_result = fold_sub_float((uint *)&(left->desc->value).disp,
                                   (uint *)&(right->desc->value).disp,
                                   (uint *)&(node->desc->value).disp);
      return (short)uint_result;
    }
    if ((type_bits == 0x30) || (type_bits == 0x38)) {
      uint_result = fold_sub_double((uint *)&(left->desc->value).disp,
                                    (uint *)&(right->desc->value).disp,
                                    (uint *)&(node->desc->value).disp);
      return (short)uint_result;
    }
    break;
  case 'D':
    type_bits = left->type;
    type_class = type_bits & 0xe0;
    if (type_class != 0x20) {
      if ((((type_bits & 4) == 0) && (type_class != 0x80)) && (type_class != 0x40)) {
        uint_result = fold_int_mul(&(left->desc->value).disp,&(right->desc->value).disp,
                                   &(node->desc->value).disp);
        return (short)uint_result;
      }
      uint_result = fold_mul_unsigned(&(left->desc->value).disp,&(right->desc->value).disp,
                                      &(node->desc->value).disp);
      return (short)uint_result;
    }
    type_bits = type_bits & 0xf8;
    if (type_bits == 0x28) {
      uint_result = fold_mul_float((uint *)&(left->desc->value).disp,
                                   (uint *)&(right->desc->value).disp,
                                   (uint *)&(node->desc->value).disp);
      return (short)uint_result;
    }
    if ((type_bits == 0x30) || (type_bits == 0x38)) {
      uint_result = fold_mul_double((uint *)&(left->desc->value).disp,
                                    (uint *)&(right->desc->value).disp,
                                    (uint *)&(node->desc->value).disp);
      return (short)uint_result;
    }
    break;
  case 'F':
    type_bits = left->type;
    type_class = type_bits & 0xe0;
    if (type_class != 0x20) {
      if ((((type_bits & 4) == 0) && (type_class != 0x80)) && (type_class != 0x40)) {
        int_result = fold_int_div(&(left->desc->value).disp,&(right->desc->value).disp,
                                  &(node->desc->value).disp);
        return (short)int_result;
      }
      int_result = fold_div_unsigned((uint *)&(left->desc->value).disp,
                                     (uint *)&(right->desc->value).disp,
                                     (uint *)&(node->desc->value).disp);
      return (short)int_result;
    }
    type_bits = type_bits & 0xf8;
    if (type_bits == 0x28) {
      uint_result = fold_div_float((uint *)&(left->desc->value).disp,
                                   (uint *)&(right->desc->value).disp,
                                   (uint *)&(node->desc->value).disp);
      return (short)uint_result;
    }
    if ((type_bits == 0x30) || (type_bits == 0x38)) {
      uint_result = fold_div_double((uint *)&(left->desc->value).disp,
                                    (uint *)&(right->desc->value).disp,
                                    (uint *)&(node->desc->value).disp);
      return (short)uint_result;
    }
    break;
  case 'G':
    if ((((left->type & 4) == 0) && (type_bits = left->type & 0xe0, type_bits != 0x80)) &&
       (type_bits != 0x40)) {
      int_result = fold_int_mod(&(left->desc->value).disp,&(right->desc->value).disp,
                                &(node->desc->value).disp);
      return (short)int_result;
    }
    int_result = fold_mod_unsigned((uint *)&(left->desc->value).disp,
                                   (uint *)&(right->desc->value).disp,&(node->desc->value).disp);
    result = (short)int_result;
  }
  return result;
}



