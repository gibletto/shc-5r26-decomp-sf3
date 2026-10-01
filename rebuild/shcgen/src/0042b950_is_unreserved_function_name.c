#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0042b950
// name : is_unreserved_function_name
// size : 141
// sig  : int is_unreserved_function_name(short sym_index)


int __cdecl is_unreserved_function_name(short sym_index)

{
  int sym;
  int cmp;
  undefined **rt_name;
  uint uVar1;
  byte *sym_char;
  byte *rt_char;
  bool below;
  byte c;
  
  uVar1 = (int)sym_index >> 0x1f;
  sym = ((int)sym_index ^ uVar1) - uVar1;
  uVar1 = lookup_builtin_function_id(g_symbol_table[sym].name);
  if (uVar1 != 0) {
    return uVar1 & 0xffff0000;
  }
  rt_name = &g_runtime_routine_names;
  do {
    rt_char = *rt_name;
    sym_char = (byte *)g_symbol_table[sym].name;
    do {
      c = *sym_char;
      below = c < *rt_char;
      if (c != *rt_char) {
LAB_0042b9b8:
        cmp = (1 - (uint)below) - (uint)(below != 0);
        goto LAB_0042b9bd;
      }
      if (c == 0) break;
      c = sym_char[1];
      below = c < rt_char[1];
      if (c != rt_char[1]) goto LAB_0042b9b8;
      sym_char = sym_char + 2;
      rt_char = rt_char + 2;
    } while (c != 0);
    cmp = 0;
LAB_0042b9bd:
    if (cmp == 0) {
      return 0;
    }
    rt_name = rt_name + 1;
    if (&PTR_DAT_0045c120 < rt_name) {
      return CONCAT22((short)((uint)cmp >> 0x10),1);
    }
  } while( true );
}



