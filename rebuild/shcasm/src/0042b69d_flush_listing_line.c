#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_listing_code_field
#define g_listing_code_field (*(char * *)(g_sd + 0x13150))


// entry: 0042b69d
// name : flush_listing_line
// size : 455
// sig  : void flush_listing_line(void)


int __cdecl flush_listing_line(void)

{
  int put_status;
  short i;
  
  if ((g_column_starts[0] < g_output_channels[3].cursor) ||
     (g_listing_code_row_next <= g_listing_code_row_last)) {
    if (g_listing_code_row_next <= g_listing_code_row_last) {
      for (i = 0; i < 10; i = i + 1) {
        g_listing_code_field[i] = (&g_listing_code_rows)[g_listing_code_row_next * 10 + (int)i];
      }
      g_listing_code_row_next = g_listing_code_row_next + 1;
    }
    *g_output_channels[3].cursor = '\n';
    g_output_channels[3].cursor[1] = '\0';
    g_listing_page_line_count = g_listing_page_line_count + 1;
    if (((g_current_request->list_length + -4 < (int)g_listing_page_line_count) &&
        (g_current_request->list_length != 0)) || (g_listing_page_line_count < 0)) {
      emit_listing_page_header();
    }
    put_status = _fputs(g_output_channels[3].buffer,g_output_channels[3].file);
    if (put_status == -1) {
      report_message_at_source_line(0,0,0xce7,(char *)0x0);
    }
    g_output_channels[3].cursor = g_column_starts[0];
    for (i = 0; i < g_output_channels[3].size; i = i + 1) {
      g_output_channels[3].buffer[i] = ' ';
    }
  }
  return;
}
