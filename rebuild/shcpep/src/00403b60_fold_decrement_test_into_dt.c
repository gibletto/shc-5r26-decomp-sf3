#include "decls.h"
#include "imports.h"

// entry: 00403b60
// name : fold_decrement_test_into_dt
// size : 261
// sig  : void fold_decrement_test_into_dt(code_node * node, psd * test)


int __cdecl fold_decrement_test_into_dt(code_node *node,psd *test)

{
  psd *add;
  char test_reg;
  bool is_reg_test;
  psd_op op;
  ea *operand;
  ea *operand2;
  
  is_reg_test = false;
  add = find_previous_psd_record(node,test);
  if (add != (psd *)0x0) {
    op = test->op;
    if (op == OP_CMP_EQ) {
      operand = test->ea1;
      if ((((operand != (ea *)0x0) && ((operand->type & 0x1f) == 7)) && (operand->disp == 0)) &&
         ((operand = test->ea2, operand != (ea *)0x0 && ((operand->type & 0x1f) == 1)))) {
        test_reg = operand->base;
        is_reg_test = true;
      }
    }
    else if (op == OP_CMP_PL) {
      operand = test->ea1;
      if ((operand != (ea *)0x0) && ((operand->type & 0x1f) == 1)) {
        test_reg = operand->base;
        is_reg_test = true;
      }
    }
    else if (((((op == OP_TST) && (operand = test->ea1, operand != (ea *)0x0)) &&
              ((operand->type & 0x1f) == 1)) &&
             ((operand2 = test->ea2, operand2 != (ea *)0x0 && ((operand2->type & 0x1f) == 1)))) &&
            (operand2->base == operand->base)) {
      is_reg_test = true;
      test_reg = operand->base;
    }
    if ((((is_reg_test) && (add->op == OP_ADD)) &&
        ((operand = add->ea1, operand != (ea *)0x0 &&
         ((((operand->type & 0x1f) == 7 && (operand->disp == -1)) &&
          (operand = add->ea2, operand != (ea *)0x0)))))) &&
       (((operand->type & 0x1f) == 1 && (operand->base == test_reg)))) {
      convert_test_to_dt(test,add);
    }
  }
  return;
}



