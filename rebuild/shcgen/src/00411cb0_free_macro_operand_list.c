#include "decls.h"
#include "imports.h"

// entry: 00411cb0
// name : free_macro_operand_list
// size : 31
// sig  : void free_macro_operand_list(ea * * list)


int __cdecl free_macro_operand_list(ea **list)

{
  ea *operand;
  int n;
  
  n = 1;
  do {
    operand = *list;
    list = list + 1;
    free_ea(operand);
    n = n + -1;
  } while (n != 0);
  return;
}



