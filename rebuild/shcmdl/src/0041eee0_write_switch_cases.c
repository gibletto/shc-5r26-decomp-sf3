#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_switch_file
#define g_switch_file (*(FILE * *)(g_sd + 0x1e734))


// entry: 0041eee0
// name : write_switch_cases
// size : 67
// sig  : void write_switch_cases(switch_table * table, short count)


int __cdecl write_switch_cases(switch_table *table,short count)

{
  switch_case *buf;
  
  buf = table->cases;
  if (0 < count) {
    do {
      write_symbol_bytes(g_switch_file,(char *)buf,4);
      write_symbol_bytes(g_switch_file,(char *)&buf->label,2);
      count = count + -1;
      buf = buf + 1;
    } while (count != 0);
  }
  return;
}



