#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_switch_file
#define g_switch_file (*(FILE * *)(g_sd + 0x1e734))
#undef g_switch_tables
#define g_switch_tables (*(switch_table * *)(g_sd + 0x267b4))


// entry: 0041ec30
// name : read_switch_table
// size : 261
// sig  : void read_switch_table(int number)


int __cdecl read_switch_table(int number)

{
  unsigned char _frec_9[9];
#define default_flag (*(char *)(_frec_9 + 0))
#define table_no (*(short *)(_frec_9 + 1))
#define cnt (*(short *)(_frec_9 + 3))
#define offset (*(LONG *)(_frec_9 + 5))
  switch_table *psVar1;
  short default_label;
  switch_table *table;
  switch_table *tail;
  
  default_label = 0;
  find_keyed_offset((char *)g_options,number,&offset);
  stock_fseek(g_switch_file,offset,0);
  table = stock_calloc(1,0x10);
  if (table == (switch_table *)0x0) {
    fatal_error(0xbcd);
  }
  psVar1 = table;
  if (g_switch_tables != (switch_table *)0x0) {
    psVar1 = g_switch_tables->next;
    tail = g_switch_tables;
    while (psVar1 != (switch_table *)0x0) {
      tail = tail->next;
      psVar1 = tail->next;
    }
    tail->next = table;
    psVar1 = g_switch_tables;
  }
  g_switch_tables = psVar1;
  read_or_fail(g_switch_file,(char *)&table_no,2);
  read_or_fail(g_switch_file,&default_flag,1);
  if (default_flag != '\0') {
    default_label = read_switch_short();
  }
  read_or_fail(g_switch_file,(char *)&cnt,2);
  if (cnt != 0) {
    read_switch_cases(table,cnt);
  }
  table->number = table_no;
  table->has_default = default_flag;
  table->default_label = default_label;
  table->count = cnt;
  return;
#undef default_flag
#undef table_no
#undef cnt
#undef offset
}



