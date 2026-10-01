#include "decls.h"
#include "imports.h"

// entry: 0041371d
// name : allocate_spool_buffer
// size : 203
// sig  : void allocate_spool_buffer(void)


int __cdecl allocate_spool_buffer(void)

{
  g_output_channels[0].buffer = stock_malloc((int)g_output_channels[0].size);
  g_output_channels[0].cursor = g_output_channels[0].buffer;
  if (g_output_channels[0].buffer == (char *)0x0) {
    report_message_at_source_line(0,0,0xbcd,(char *)0x0);
  }
  g_output_channels[0].end = g_output_channels[0].buffer + g_output_channels[0].size;
  return;
}
