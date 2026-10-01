#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_switch_tables
#define g_switch_tables (*(switch_table * *)(g_sd + 0x267b4))


// entry: 00420870
// name : free_switch_tables
// size : 58
// sig  : void free_switch_tables(void)


int __cdecl free_switch_tables(void)

{
  switch_table *next;
  switch_table *table;
  
  table = g_switch_tables;
  while (table != (switch_table *)0x0) {
    next = table->next;
    if (table->cases != (switch_case *)0x0) {
      stock_free(table->cases);
    }
    stock_free(table);
    table = next;
  }
  g_switch_tables = (switch_table *)0x0;
  return;
}



