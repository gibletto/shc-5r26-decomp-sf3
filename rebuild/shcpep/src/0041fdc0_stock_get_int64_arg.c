#include "decls.h"
#include "imports.h"

// entry: 0041fdc0
// name : stock_get_int64_arg
// size : 21
// sig  : undefined8 stock_get_int64_arg(int * param_1)


undefined8 __cdecl stock_get_int64_arg(int *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  *param_1 = (int)(puVar1 + 1);
  return *puVar1;
}



