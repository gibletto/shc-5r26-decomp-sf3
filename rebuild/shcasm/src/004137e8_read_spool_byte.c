#include "decls.h"
#include "imports.h"

// entry: 004137e8
// name : read_spool_byte
// size : 252
// sig  : short read_spool_byte(void)


short __cdecl read_spool_byte(void)

{
  uint read_status;
  char ch;
  
  if (g_output_channels[0].end <= g_output_channels[0].cursor) {
    read_status = read_file_bytes(g_output_channels[0].file,g_output_channels[0].buffer,
                                  (int)g_output_channels[0].size);
    if (read_status == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    g_output_channels[0].cursor = g_output_channels[0].buffer;
  }
  ch = *g_output_channels[0].cursor;
  g_output_channels[0].cursor = g_output_channels[0].cursor + 1;
  return (short)ch;
}



