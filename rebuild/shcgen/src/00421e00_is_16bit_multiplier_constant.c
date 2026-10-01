#include "decls.h"
#include "imports.h"

// entry: 00421e00
// name : is_16bit_multiplier_constant
// size : 151
// sig  : int is_16bit_multiplier_constant(gen_node * node, int is_unsigned)


int __cdecl is_16bit_multiplier_constant(gen_node *node,int is_unsigned)

{
  short bit_pos;
  int fits;
  int *val_ptr;
  
  fits = 0;
  if (node->op != IL_CONST) {
    return 0;
  }
  if (is_unsigned == 0) {
    if ((node->val < -0x8000) || (0x7fff < node->val)) goto LAB_00421e43;
  }
  else if ((node->val < 0) || (0xffff < node->val)) goto LAB_00421e43;
  fits = 1;
LAB_00421e43:
  val_ptr = &node->val;
  if ((fits == 1) &&
     ((((bit_pos = single_bit_position(*val_ptr), bit_pos != -1 ||
        (bit_pos = single_bit_position(*val_ptr - 1), bit_pos != -1)) ||
       (bit_pos = single_bit_position(*val_ptr + 1), bit_pos != -1)) ||
      (bit_pos = two_bit_mask_bit_position(*val_ptr,1), bit_pos != -1)))) {
    fits = 0;
  }
  return fits;
}



