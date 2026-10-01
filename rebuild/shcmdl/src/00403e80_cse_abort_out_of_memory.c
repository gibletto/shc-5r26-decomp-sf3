#include "decls.h"
#include "imports.h"

// entry: 00403e80
// name : cse_abort_out_of_memory
// size : 10
// sig  : void cse_abort_out_of_memory(void)


int __cdecl cse_abort_out_of_memory(void)

{
  cse_free_hash_tables();
  abort_function_optimization();
  return;
}



