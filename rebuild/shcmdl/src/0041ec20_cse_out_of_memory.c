#include "decls.h"
#include "imports.h"

// entry: 0041ec20
// name : cse_out_of_memory
// size : 10
// sig  : void cse_out_of_memory(void)


int __cdecl cse_out_of_memory(void)

{
  cse_free_tables();
  abort_function_optimization();
  return;
}



