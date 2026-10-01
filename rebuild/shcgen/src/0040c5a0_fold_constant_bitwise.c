#include "decls.h"
#include "imports.h"

// entry: 0040c5a0
// name : fold_constant_bitwise
// size : 513
// sig  : short fold_constant_bitwise(char op, gen_node * left, gen_node * right, gen_node * node)


short __cdecl fold_constant_bitwise(char op,gen_node *left,gen_node *right,gen_node *node)

{
  byte type_class;
  uint uint_result;
  
  switch(op) {
  case 'H':
    break;
  case 'I':
    if ((((left->type & 4) == 0) && (type_class = left->type & 0xe0, type_class != 0x80)) &&
       (type_class != 0x40)) {
      uint_result = fold_shr_signed(&(left->desc->value).disp,(uint *)&(right->desc->value).disp,
                                    &(node->desc->value).disp);
      return (short)uint_result;
    }
    uint_result = fold_shr_unsigned((uint *)&(left->desc->value).disp,
                                    (uint *)&(right->desc->value).disp,
                                    (uint *)&(node->desc->value).disp);
    return (short)uint_result;
  default:
    return 0;
  case 'L':
    if ((((left->type & 4) == 0) && (type_class = left->type & 0xe0, type_class != 0x80)) &&
       (type_class != 0x40)) {
      uint_result = fold_and_signed((uint *)&(left->desc->value).disp,
                                    (uint *)&(right->desc->value).disp,
                                    (uint *)&(node->desc->value).disp);
      return (short)uint_result;
    }
    uint_result = fold_and_unsigned((uint *)&(left->desc->value).disp,
                                    (uint *)&(right->desc->value).disp,
                                    (uint *)&(node->desc->value).disp);
    return (short)uint_result;
  case 'M':
    if ((((left->type & 4) == 0) && (type_class = left->type & 0xe0, type_class != 0x80)) &&
       (type_class != 0x40)) {
      uint_result = fold_xor_signed((uint *)&(left->desc->value).disp,
                                    (uint *)&(right->desc->value).disp,
                                    (uint *)&(node->desc->value).disp);
      return (short)uint_result;
    }
    uint_result = fold_xor_unsigned((uint *)&(left->desc->value).disp,
                                    (uint *)&(right->desc->value).disp,
                                    (uint *)&(node->desc->value).disp);
    return (short)uint_result;
  case 'N':
    if ((((left->type & 4) == 0) && (type_class = left->type & 0xe0, type_class != 0x80)) &&
       (type_class != 0x40)) {
      uint_result = fold_or_signed((uint *)&(left->desc->value).disp,
                                   (uint *)&(right->desc->value).disp,
                                   (uint *)&(node->desc->value).disp);
      return (short)uint_result;
    }
    uint_result = fold_or_unsigned((uint *)&(left->desc->value).disp,
                                   (uint *)&(right->desc->value).disp,
                                   (uint *)&(node->desc->value).disp);
    return (short)uint_result;
  }
  if ((((left->type & 4) == 0) && (type_class = left->type & 0xe0, type_class != 0x80)) &&
     (type_class != 0x40)) {
    uint_result = fold_shl_signed(&(left->desc->value).disp,(uint *)&(right->desc->value).disp,
                                  &(node->desc->value).disp);
    return (short)uint_result;
  }
  uint_result = fold_shl_unsigned(&(left->desc->value).disp,(uint *)&(right->desc->value).disp,
                                  &(node->desc->value).disp);
  return (short)uint_result;
}



