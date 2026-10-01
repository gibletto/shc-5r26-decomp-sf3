#include "decls.h"
#include "imports.h"

// entry: 004353a0
// name : stock_initterm
// size : 32
// sig  : undefined stock_initterm(undefined4 * param_1, undefined4 * param_2)


int __cdecl stock_initterm(undefined4 *param_1,undefined4 *param_2)

{
  for (; param_1 < param_2; param_1 = param_1 + 1) {
    if ((code *)*param_1 != 0) {
      (*(code *)*param_1)();
    }
  }
  return;
}



