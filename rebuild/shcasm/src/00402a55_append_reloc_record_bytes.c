#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_object_data_cursor
#define g_object_data_cursor (*(char * *)(g_sd + 0x10c58))
#undef g_object_data_end
#define g_object_data_end (*(char * *)(g_sd + 0x10c60))


// entry: 00402a55
// name : append_reloc_record_bytes
// size : 93
// sig  : void __cdecl append_reloc_record_bytes(char *data,short len)


int __cdecl append_reloc_record_bytes(char *data,short len)

{
  if ((int)g_object_data_end - (int)g_object_data_cursor < (int)len) {
    flush_reloc_records();
  }
  while( true ) {
    if (len == 0) break;
    *g_object_data_cursor = *data;
    data = data + 1;
    g_object_data_cursor = g_object_data_cursor + 1;
    len = len + -1;
  }
  return;
}
