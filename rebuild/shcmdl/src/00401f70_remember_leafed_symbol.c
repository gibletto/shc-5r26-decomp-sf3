#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_leafed_symbols
#define g_leafed_symbols (*(int * *)(g_sd + 0x1e4dc))


// entry: 00401f70
// name : remember_leafed_symbol
// size : 46
// sig  : void remember_leafed_symbol(short symx)


int __cdecl remember_leafed_symbol(short symx)

{
  undefined4 *cell;
  
  cell = pool_alloc(8);
  if (cell == (undefined4 *)0x0) {
    abort_function_optimization();
  }
  *(short *)(cell + 1) = symx;
  *cell = g_leafed_symbols;
  g_leafed_symbols = cell;
  return;
}



