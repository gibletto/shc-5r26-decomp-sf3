#include "decls.h"
#include "imports.h"

// entry: 004138e9
// name : record_size_decision_byte
// size : 181
// sig  : void __cdecl record_size_decision_byte(char value)


int __cdecl record_size_decision_byte(char value)

{
  uint write_status;
  
  if (g_output_channels[0].end <= g_output_channels[0].cursor) {
    if (g_output_channels[0].opened == 0) {
      g_output_channels[0].file = open_temp_file();
      if (g_output_channels[0].file == (FILE *)0x0) {
        report_message_at_source_line(0,0,0xce4,(char *)0x0);
      }
      g_output_channels[0].opened = 1;
    }
    write_status = write_file_bytes(g_output_channels[0].file,g_output_channels[0].buffer,
                                    (int)g_output_channels[0].size);
    if (write_status == 0xffffffff) {
      report_message_at_source_line(0,0,0xce7,(char *)0x0);
    }
    g_output_channels[0].cursor = g_output_channels[0].buffer;
  }
  *g_output_channels[0].cursor = value;
  g_output_channels[0].cursor = g_output_channels[0].cursor + 1;
  return;
}
