#include "decls.h"
#include "imports.h"

// entry: 0041399e
// name : rewind_size_decision_stream
// size : 172
// sig  : void rewind_size_decision_stream(void)


int __cdecl rewind_size_decision_stream(void)

{
  uint write_status;
  int seek_status;
  
  if (g_output_channels[0].opened == 1) {
    write_status = write_file_bytes(g_output_channels[0].file,g_output_channels[0].buffer,
                                    (int)(short)((short)g_output_channels[0].cursor -
                                                (short)g_output_channels[0].buffer));
    if (write_status == 0xffffffff) {
      report_message_at_source_line(0,0,0xce7,(char *)0x0);
    }
    g_output_channels[0].cursor = g_output_channels[0].end;
    seek_status = stock_fseek(g_output_channels[0].file,0,0);
    if (seek_status != 0) {
      report_message_at_source_line(0,0,0x1356,(char *)0x0);
    }
  }
  else {
    g_output_channels[0].cursor = g_output_channels[0].buffer;
  }
  return;
}
