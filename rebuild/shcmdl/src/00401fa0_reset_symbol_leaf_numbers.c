#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_leafed_symbols
#define g_leafed_symbols (*(int * *)(g_sd + 0x1e4dc))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00401fa0
// name : reset_symbol_leaf_numbers
// size : 59
// sig  : void reset_symbol_leaf_numbers(void)


int __cdecl reset_symbol_leaf_numbers(void)

{
  undefined4 *cell;
  undefined4 *next_cell;
  
  cell = g_leafed_symbols;
  while (cell != (undefined4 *)0x0) {
    g_symtab[*(short *)(cell + 1)].ms_leaf = 0;
    next_cell = (undefined4 *)*cell;
    pool_free(cell,8);
    cell = next_cell;
  }
  return;
}



