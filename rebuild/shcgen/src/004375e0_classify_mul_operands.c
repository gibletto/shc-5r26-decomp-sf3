#include "decls.h"
#include "imports.h"

// entry: 004375e0
// name : classify_mul_operands
// size : 40
// sig  : void classify_mul_operands(uint sign1, int class1, uint sign2, int class2, int * action, uint * result_sign)


int __cdecl classify_mul_operands(uint sign1,int class1,uint sign2,int class2,int *action,uint *result_sign)

{
  *action = (int)*(short *)(&g_mul_class_table + (class2 + class1 * 4) * 2);
  *result_sign = sign1 ^ sign2;
  return;
}



