#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_switch_tables
#define g_switch_tables (*(switch_table * *)(g_sd + 0x267b4))


// entry: 00420820
// name : find_switch_table
// size : 27
// sig  : switch_table * __cdecl find_switch_table(short number)


switch_table * __cdecl find_switch_table(short number)

{
  switch_table *table;
  
  for (table = g_switch_tables; (table != (switch_table *)0x0 && (table->number != number));
      table = table->next) {
  }
  return table;
}
