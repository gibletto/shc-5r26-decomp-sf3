#include "decls.h"
#include "imports.h"

// entry: 0042f170
// name : close_and_delete_temp_files
// size : 158
// sig  : void close_and_delete_temp_files(void)


int __cdecl close_and_delete_temp_files(void)

{
  int iVar1;
  int i;
  temp_file *tf;
  
  if (0 < g_temp_file_count) {
    i = 0;
    tf = g_temp_files;
    do {
      iVar1 = _fclose(tf->file);
      if (iVar1 != 0) {
        report_message_by_code((char *)0x0,0,0xce5,(char *)0x0);
        stock_exit(9);
      }
      iVar1 = stock_unlink(tf->path);
      if (iVar1 != 0) {
        report_message_by_code((char *)0x0,0,0xce8,(char *)0x0);
        stock_exit(9);
      }
      if (tf->path != (char *)0x0) {
        stock_free(tf->path);
      }
      iVar1 = g_temp_file_count;
      i = i + 1;
      tf->file = (FILE *)0x0;
      tf = tf + 1;
    } while (i < iVar1);
    g_temp_file_count = 0;
  }
  return;
}
