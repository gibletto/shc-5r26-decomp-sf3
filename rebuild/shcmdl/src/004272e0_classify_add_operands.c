#include "decls.h"
#include "imports.h"

// entry: 004272e0
// name : classify_add_operands
// size : 114
// sig  : void classify_add_operands(uint sign1, int class1, uint sign2, int class2, int * action, uint * result_sign)


int __cdecl classify_add_operands(uint sign1,int class1,uint sign2,int class2,int *action,uint *result_sign)

{
  int act;
  
  *result_sign = 0;
  act = (int)*(short *)(&g_add_class_table + (class2 + class1 * 4) * 2);
  *action = act;
  if (act == 1) {
    *result_sign = sign2 & sign1;
    return;
  }
  if (act == 2) {
    if (class1 == 2) {
      *result_sign = sign1;
      return;
    }
    *result_sign = sign2;
    return;
  }
  if (act != 4) {
    return;
  }
  if (sign2 != sign1) {
    *action = 3;
    return;
  }
  *action = 2;
  *result_sign = sign1;
  return;
}



