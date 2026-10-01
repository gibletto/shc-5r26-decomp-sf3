#include "decls.h"
#include "imports.h"

// entry: 00428d70
// name : remove_temp_files
// size : 158
// sig  : void remove_temp_files(void)


int __cdecl remove_temp_files(void)

{
  int iVar1;
  int i;
  undefined4 *entry;
  
  if (0 < g_temp_file_count) {
    i = 0;
    entry = &g_temp_files;
    do {
      iVar1 = _fclose((FILE *)entry[1]);
      if (iVar1 != 0) {
        write_error_record((char *)0x0,0,0xce5,(char *)0x0);
        stock_exit(9);
      }
      iVar1 = stock_unlink((char *)*entry);
      if (iVar1 != 0) {
        write_error_record((char *)0x0,0,0xce8,(char *)0x0);
        stock_exit(9);
      }
      if ((void *)*entry != (void *)0x0) {
        stock_free((void *)*entry);
      }
      iVar1 = g_temp_file_count;
      i = i + 1;
      entry[1] = 0;
      entry = entry + 2;
    } while (i < iVar1);
    g_temp_file_count = 0;
  }
  return;
}



