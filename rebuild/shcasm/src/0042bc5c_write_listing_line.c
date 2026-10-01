#include "decls.h"
#include "imports.h"

// entry: 0042bc5c
// name : write_listing_line
// size : 79
// sig  : void __cdecl write_listing_line(char *line,char *end)


int __cdecl write_listing_line(char *line,char *end)

{
  int put_status;
  
  *end = '\n';
  end[1] = '\0';
  put_status = _fputs(line,g_output_channels[3].file);
  if (put_status == -1) {
    report_message_at_source_line(0,0,0xce7,(char *)0x0);
  }
  g_listing_page_line_count = g_listing_page_line_count + 1;
  return;
}
