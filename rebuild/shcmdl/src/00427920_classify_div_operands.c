#include "decls.h"
#include "imports.h"

// entry: 00427920
// name : classify_div_operands
// size : 60
// sig  : short classify_div_operands(uint sign1, int class1, uint sign2, int class2, int * action, uint * result_sign)


short __cdecl classify_div_operands(uint sign1,int class1,uint sign2,int class2,int *action,uint *result_sign)

{
  short status;
  
  status = 0;
  *action = (int)*(short *)(&g_div_class_table + (class2 + class1 * 4) * 2);
  *result_sign = sign2 ^ sign1;
  if (*action == 4) {
    status = 4;
    *action = 2;
  }
  return status;
}



