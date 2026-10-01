#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_switch_file
#define g_switch_file (*(FILE * *)(g_sd + 0x1e734))
#undef g_switch_tables
#define g_switch_tables (*(switch_table * *)(g_sd + 0x267b4))


// entry: 0041edf0
// name : write_switch_tables
// size : 236
// sig  : void write_switch_tables(void)


int __cdecl write_switch_tables(void)

{
  short count;
  switch_table *table;
  undefined4 *rec;
  DWORD pos;
  
  stock_fseek(g_switch_file,0,2);
  for (table = g_switch_tables; table != (switch_table *)0x0; table = table->next) {
    rec = stock_malloc(0x10);
    if (rec == (undefined4 *)0x0) {
      fatal_error(0xbcd);
    }
    rec[1] = (int)table->number;
    pos = stock_ftell(g_switch_file);
    rec[2] = pos;
    *rec = g_options->keyed_offsets;
    g_options->keyed_offsets = rec;
    write_symbol_bytes(g_switch_file,(char *)&table->number,2);
    write_symbol_bytes(g_switch_file,&table->has_default,1);
    if (table->has_default != '\0') {
      write_symbol_bytes(g_switch_file,(char *)&table->default_label,2);
    }
    write_symbol_bytes(g_switch_file,(char *)&table->count,2);
    count = table->count;
    if (count != 0) {
      write_switch_cases(table,count);
    }
  }
  return;
}



