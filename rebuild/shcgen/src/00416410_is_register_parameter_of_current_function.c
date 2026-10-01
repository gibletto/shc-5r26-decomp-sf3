#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00416410
// name : is_register_parameter_of_current_function
// size : 100
// sig  : int is_register_parameter_of_current_function(short symno)


int __cdecl is_register_parameter_of_current_function(short symno)

{
  uint uVar1;
  short param_sym;
  int found;
  undefined4 *blk;
  
  uVar1 = (int)g_current_function >> 0x1f;
  param_sym = 0;
  found = 0;
  blk = (undefined4 *)g_symbol_table[((int)g_current_function ^ uVar1) - uVar1].size;
  do {
    if ((blk == (undefined4 *)0x0) || (param_sym == -1)) {
      return found;
    }
    uVar1 = 0;
    do {
      param_sym = *(short *)((int)blk + uVar1 * 2 + 8);
      if (param_sym == -1) break;
      if ((param_sym == symno) && ((*(byte *)((int)blk + uVar1 + 0x10) & 1) != 0)) {
        found = 1;
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < 4);
    blk = (undefined4 *)*blk;
  } while( true );
}



