#include "decls.h"
#include "imports.h"

// entry: 0042bd02
// name : flush_src_line
// size : 284
// sig  : void flush_src_line(void)


int __cdecl flush_src_line(void)

{
  int put_status;
  char *fill_cursor;
  
  if (g_output_channels[2].buffer < g_output_channels[2].cursor) {
    *g_output_channels[2].cursor = '\n';
    g_output_channels[2].cursor[1] = '\0';
    put_status = _fputs(g_output_channels[2].buffer,g_output_channels[2].file);
    if (put_status == -1) {
      report_message_at_source_line(0,0,0xce7,(char *)0x0);
    }
    else {
      g_output_channels[2].cursor = g_output_channels[2].buffer;
      for (fill_cursor = g_output_channels[2].buffer; g_output_channels[2].end != fill_cursor;
          fill_cursor = fill_cursor + 1) {
        *fill_cursor = ' ';
      }
    }
  }
  return;
}
