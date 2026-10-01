#include "decls.h"
#include "imports.h"

// entry: 00437240
// name : stock_get_int64_arg
// size : 21
// sig  : undefined8 stock_get_int64_arg(int * param_1)


undefined8 __cdecl stock_get_int64_arg(int *param_1)

{
  undefined8 *arg;
  
  arg = (undefined8 *)*param_1;
  *param_1 = (int)(arg + 1);
  return *arg;
}



