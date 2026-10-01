#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_listing_code_field
#define g_listing_code_field (*(char * *)(g_sd + 0x13150))
#undef g_listing_continuation_mark
#define g_listing_continuation_mark (*(char * *)(g_sd + 0x128e0))
#undef g_listing_location_field
#define g_listing_location_field (*(char * *)(g_sd + 0xcc98))
#undef g_listing_section_field
#define g_listing_section_field (*(char * *)(g_sd + 0x13140))
#undef g_object_data_buffer
#define g_object_data_buffer (*(char * *)(g_sd + 0x10c7c))
#undef g_object_data_cursor
#define g_object_data_cursor (*(char * *)(g_sd + 0x10c58))
#undef g_object_data_end
#define g_object_data_end (*(char * *)(g_sd + 0x10c60))
#undef g_object_expr_buffer
#define g_object_expr_buffer (*(char * *)(g_sd + 0x128cc))
#undef g_object_expr_cursor
#define g_object_expr_cursor (*(char * *)(g_sd + 0x10ca8))


// entry: 004131a0
// name : open_output_stream
// size : 1158
// sig  : void __cdecl open_output_stream(short stream)


/* WARNING: Heritage AFTER dead removal. Example location: r0x0043ced4 : 0x00413541 */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

int __cdecl open_output_stream(short stream)

{
  char *path;
  char *new_buffer;
  FILE *fp;
  uint size;
  short line_width;
  char *p;
  short i;
  
  if (g_current_request->list_width == 0) {
    line_width = 0x84;
  }
  else {
    line_width = (short)g_current_request->list_width;
  }
  g_output_channels[3].size = line_width + 2;
  path = get_output_stream_path(stream);
  new_buffer = stock_malloc((int)g_output_channels[stream].size);
  g_output_channels[stream].buffer = new_buffer;
  if (g_output_channels[stream].buffer == (char *)0x0) {
    report_message_at_source_line(0,0,0xbcd,(char *)0x0);
  }
  g_output_channels[stream].end = g_output_channels[stream].buffer + g_output_channels[stream].size;
  fp = stock_fopen(path,g_output_channels[stream].mode);
  g_output_channels[stream].file = fp;
  if (g_output_channels[stream].file == (FILE *)0x0) {
    report_message_at_source_line(0,0,0xce4,(char *)0x0);
  }
  g_output_channels[stream].opened = 1;
  g_output_channels[stream].unknown_0e = 0;
  if (*g_output_channels[stream].mode == 'r') {
    g_output_channels[stream].cursor = g_output_channels[stream].end;
  }
  else {
    g_output_channels[stream].cursor = g_output_channels[stream].buffer;
  }
  if (stream == 1) {
    g_output_channels[1].end = g_output_channels[1].end + -1;
    size = (int)g_output_channels[1].size - 3;
    g_object_data_cursor = stock_malloc(size);
    g_object_data_buffer = g_object_data_cursor;
    if (g_object_data_cursor == (char *)0x0) {
      report_message_at_source_line(0,0,0xbcd,(char *)0x0);
    }
    g_object_data_end = g_object_data_cursor + size;
    g_object_expr_cursor = stock_malloc(size);
    g_object_expr_buffer = g_object_expr_cursor;
    if (g_object_expr_cursor == (char *)0x0) {
      report_message_at_source_line(0,0,0xbcd,(char *)0x0);
    }
    g_object_expr_end = (int)(g_object_expr_cursor + size);
  }
  if (stream == 2) {
    g_output_channels[2].end = g_output_channels[2].end + -2;
    p = g_output_channels[2].buffer;
    for (i = 0; i < g_output_channels[2].size; i = i + 1) {
      *p = ' ';
      p = p + 1;
    }
    g_column_starts[0] = g_output_channels[2].buffer;
    g_column_starts[1] = g_output_channels[2].buffer + 10;
    g_column_starts[2] = g_output_channels[2].buffer + 0x16;
    g_column_starts[3] = g_output_channels[2].buffer + 0x21;
  }
  if (stream == 3) {
    g_output_channels[3].end = g_output_channels[3].end + -2;
    p = g_output_channels[3].buffer;
    for (i = 0; i < g_output_channels[3].size; i = i + 1) {
      *p = ' ';
      p = p + 1;
    }
    g_listing_section_field = g_output_channels[3].buffer;
    g_listing_location_field = g_output_channels[3].buffer + 4;
    g_listing_code_field = g_output_channels[3].buffer + 0xd;
    g_listing_continuation_mark = g_output_channels[3].buffer + 0x18;
    g_column_starts[0] = g_output_channels[3].buffer + 0x1a;
    g_column_starts[1] = g_output_channels[3].buffer + 0x24;
    g_column_starts[2] = g_output_channels[3].buffer + 0x30;
    g_column_starts[3] = g_output_channels[3].buffer + 0x3b;
    g_listing_code_row_last = -1;
    g_listing_code_row_next = 0;
    g_listing_code_column_pos = 10;
    g_listing_page_number = 0;
    g_listing_page_line_count = (short)g_current_request->list_length + -4;
  }
  return;
}
