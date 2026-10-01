#include "decls.h"
#include "imports.h"

// entry: 00415c00
// name : free_merge_tables_and_abort
// size : 10
// sig  : void free_merge_tables_and_abort(void)


int __cdecl free_merge_tables_and_abort(void)

{
  free_merge_tables();
  abort_function_optimization();
  return;
}



