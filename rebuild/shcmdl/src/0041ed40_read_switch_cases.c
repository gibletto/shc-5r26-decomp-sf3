#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_switch_file
#define g_switch_file (*(FILE * *)(g_sd + 0x1e734))


// entry: 0041ed40
// name : read_switch_cases
// size : 119
// sig  : void read_switch_cases(switch_table * table, short count)


int __cdecl read_switch_cases(switch_table *table,short count)

{
  unsigned char _frec_4[4];
#define val_read (*(int *)(_frec_4 + 0))
  short label;
  switch_case *cases;
  int idx;
  short i;
  
  i = 0;
  cases = stock_calloc((int)count,8);
  if (cases == (switch_case *)0x0) {
    fatal_error(0xbcd);
  }
  table->cases = cases;
  if (0 < count) {
    do {
      read_or_fail(g_switch_file,(char *)&val_read,4);
      idx = (int)i;
      i = i + 1;
      cases[idx].value = val_read;
      label = read_switch_short();
      cases[idx].label = label;
    } while (i < count);
  }
  return;
#undef val_read
}



