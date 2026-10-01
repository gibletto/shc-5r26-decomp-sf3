#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_source_listing_input
#define g_source_listing_input (*(FILE * *)(g_sd + 0xe744))


// entry: 00427458
// name : copy_source_lines_to_listing
// size : 608
// sig  : void __cdecl copy_source_lines_to_listing(char op,short filno,ushort linno)


int __cdecl copy_source_lines_to_listing(char op,short filno,ushort linno)

{
  unsigned char _frec_94[148];
#define line_buf (*(char (*)[136])(_frec_94 + 0))
#define file_bytes_read (*(uint *)(_frec_94 + 136))
#define reached_line (*(int *)(_frec_94 + 140))
  char *line_read;
  int put_status;
  uint line_bytes_read;
  
  reached_line = 0;
  if (((op != '\x11') && (linno != 0)) &&
     ((g_listing_last_source_file != filno || (g_listing_last_source_line < linno)))) {
    do {
      while( true ) {
        while( true ) {
          if ((g_source_listing_at_end != '\0') ||
             (((uint)g_source_listing_file == (int)filno &&
              ((uint)linno < (uint)g_source_listing_line)))) goto LAB_0042769f;
          line_read = stock_fgets(line_buf,0x86,g_source_listing_input);
          if (line_read == (char *)0x0) {
            report_message_at_source_line(0,0,0xce6,(char *)0x0);
          }
          if ((g_source_listing_file == 1) || ((g_current_request->show & 8) != 0)) {
            g_listing_page_line_count = g_listing_page_line_count + 1;
            if (((g_current_request->list_length + -4 < (int)g_listing_page_line_count) &&
                (g_current_request->list_length != 0)) || (g_listing_page_line_count < 0)) {
              emit_listing_page_header();
            }
            put_status = _fputs(line_buf,g_output_channels[3].file);
            if (put_status == -1) {
              report_message_at_source_line(0,0,0xce7,(char *)0x0);
            }
          }
          if (((reached_line == 0) && ((uint)g_source_listing_file == (int)filno)) &&
             ((uint)linno == g_source_listing_line)) {
            reached_line = 1;
          }
          file_bytes_read = read_file_bytes(g_source_listing_input,(char *)&g_source_listing_file,2)
          ;
          if (file_bytes_read != 0xffffffff) break;
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        if (file_bytes_read != 0) break;
        g_source_listing_at_end = '\x01';
      }
      line_bytes_read = read_file_bytes(g_source_listing_input,(char *)&g_source_listing_line,4);
      if (line_bytes_read == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
    } while ((reached_line != 1) || ((uint)g_source_listing_file == (int)filno));
LAB_0042769f:
    g_listing_last_source_file = filno;
    g_listing_last_source_line = linno;
  }
  return;
#undef line_buf
#undef file_bytes_read
#undef reached_line
}
