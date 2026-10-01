#include "decls.h"
#include "imports.h"
int shcgen_knob_tst_r0(void);
int shcgen_knob_mul_l(void);
void regtrace_site(int site, char *node);
char regtrace_chooser_enter(char ascending, unsigned ret);
void regtrace_chooser_exit(unsigned short p1, unsigned short p2, char p3, short *slots, int chosen);
void regtrace_function(char *rec);

// entry: 00421ea0
// name : mul_fits_16bit_multiply
// size : 509
// sig  : int mul_fits_16bit_multiply(gen_node * node)


int __cdecl mul_fits_16bit_multiply(gen_node *node)

{
  byte type_bits;
  int right_unsigned;
  int iVar1;
  gen_node *left_inner;
  gen_node *right_opnd;
  gen_node *right_inner;
  gen_node *left_unsigned;
  gen_node *left;
  bool left_narrow;
  bool right_narrow;
  byte right_type;
  
  left = node->child;
  right_narrow = false;
  left_narrow = false;
  if (left == (gen_node *)0x0) {
    right_opnd = (gen_node *)0x0;
  }
  else {
    right_opnd = left->next;
  }
  left_inner = left_unsigned;
  if (left->op == IL_CAST) {
    left_inner = left->child;
    type_bits = left_inner->type & 0xf8;
    if ((type_bits == 0) || (type_bits == 8)) {
      left_narrow = true;
    }
  }
  if (right_opnd->op == IL_CAST) {
    right_inner = right_opnd->child;
    type_bits = right_inner->type & 0xf8;
    if ((type_bits == 0) || (type_bits == 8)) {
      right_narrow = true;
    }
  }
  if (left_narrow) {
    if (right_narrow) {
      if ((((left_inner->type & 4) != 0) || (type_bits = left_inner->type & 0xe0, type_bits == 0x80)
          ) || (iVar1 = 0, type_bits == 0x40)) {
        iVar1 = 1;
      }
      if ((((right_inner->type & 4) != 0) ||
          (type_bits = right_inner->type & 0xe0, type_bits == 0x80)) ||
         (right_unsigned = 0, type_bits == 0x40)) {
        right_unsigned = 1;
      }
      if (iVar1 == right_unsigned) {
        return 1;
      }
    }
    if (right_narrow) {
      type_bits = left_inner->type;
      if ((((type_bits & 4) == 0) && ((type_bits & 0xe0) != 0x80)) && ((type_bits & 0xe0) != 0x40))
      {
        left_unsigned = (gen_node *)0x0;
      }
      else {
        left_unsigned = (gen_node *)0x1;
      }
      right_type = right_inner->type;
      if ((((right_type & 4) != 0) || ((right_type & 0xe0) == 0x80)) ||
         (iVar1 = 0, (right_type & 0xe0) == 0x40)) {
        iVar1 = 1;
      }
      if ((left_unsigned != (gen_node *)iVar1) &&
         ((((type_bits & 0xf8) != 8 ||
           ((((type_bits & 4) == 0 && ((type_bits & 0xe0) != 0x80)) && ((type_bits & 0xe0) != 0x40))
           )) && (((right_type & 0xf8) != 8 ||
                  ((((right_type & 4) == 0 && ((right_type & 0xe0) != 0x80)) &&
                   ((right_type & 0xe0) != 0x40)))))))) {
        return 1;
      }
    }
  }
  if (left_narrow) {
    if ((((left_inner->type & 4) != 0) || (type_bits = left_inner->type & 0xe0, type_bits == 0x80))
       || (iVar1 = 0, type_bits == 0x40)) {
      iVar1 = 1;
    }
    iVar1 = (shcgen_knob_mul_l() & 1) ? 0 : is_16bit_multiplier_constant(right_opnd,iVar1);
    if (iVar1 != 0) {
      return 1;
    }
  }
  if (right_narrow) {
    if ((((right_inner->type & 4) != 0) || (type_bits = right_inner->type & 0xe0, type_bits == 0x80)
        ) || (iVar1 = 0, type_bits == 0x40)) {
      iVar1 = 1;
    }
    iVar1 = (shcgen_knob_mul_l() & 2) ? 0 : is_16bit_multiplier_constant(left,iVar1);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}



