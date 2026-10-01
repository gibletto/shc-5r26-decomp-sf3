#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_object_data_buffer
#define g_object_data_buffer (*(char * *)(g_sd + 0x10c7c))
#undef g_object_data_cursor
#define g_object_data_cursor (*(char * *)(g_sd + 0x10c58))


// entry: 00402ab2
// name : flush_reloc_records
// size : 67
// sig  : void flush_reloc_records(void)


int __cdecl flush_reloc_records(void)

{
  append_object_record_bytes
            ((uchar *)g_object_data_buffer,(int)g_object_data_cursor - (int)g_object_data_buffer,
             0x20);
  g_object_data_cursor = g_object_data_buffer;
  g_object_need_section_select = 1;
  return;
}
