#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_listing_continuation_mark
#define g_listing_continuation_mark (*(char * *)(g_sd + 0x128e0))


// entry: 0042b31e
// name : put_text_at_column
// size : 856
// sig  : void __cdecl put_text_at_column(short channel,char *text,short column)


int __cdecl put_text_at_column(short channel,char *text,short column)

{
  unsigned char _frec_110[272];
#define carry_read (*(char * *)(_frec_110 + 0))
#define carry_end (*(char * *)(_frec_110 + 4))
#define carry_buf (*(char (*)[256])(_frec_110 + 8))
#define break_pos (*(char * *)(_frec_110 + 264))
  int put_status;
  
  if ((g_output_channels[channel].cursor < g_column_starts[column]) && (g_line_wrap_disabled == 0))
  {
    g_output_channels[channel].cursor = g_column_starts[column];
  }
  while (*text != '\0') {
    if (g_output_channels[channel].end <= g_output_channels[channel].cursor) {
      if (g_line_wrap_disabled == 1) {
        *g_output_channels[channel].cursor = '\0';
        put_status = _fputs(g_output_channels[channel].buffer,g_output_channels[channel].file);
        if (put_status == -1) {
          report_message_at_source_line(0,0,0xce7,(char *)0x0);
        }
        else {
          g_output_channels[channel].cursor = g_output_channels[channel].buffer;
        }
      }
      else if (g_line_wrap_disabled == 0) {
        carry_read = carry_buf;
        for (break_pos = g_output_channels[channel].end;
            (*break_pos != ',' && (g_column_starts[2] <= break_pos)); break_pos = break_pos + -1) {
        }
        carry_end = carry_read;
        if (*break_pos == ',') {
          break_pos = break_pos + 1;
          g_output_channels[channel].cursor = break_pos;
          for (; break_pos < g_output_channels[channel].end; break_pos = break_pos + 1) {
            *carry_end = *break_pos;
            carry_end = carry_end + 1;
          }
        }
        else if (channel == 2) {
          report_message_at_source_line(0,0,0xc83,(char *)0x0);
        }
        if (channel == 2) {
          flush_src_line();
          *g_output_channels[2].cursor = '+';
        }
        else {
          flush_listing_line();
          *g_listing_continuation_mark = '+';
        }
        if (g_output_channels[channel].cursor < g_column_starts[column]) {
          g_output_channels[channel].cursor = g_column_starts[column];
        }
        while (carry_read < carry_end) {
          *g_output_channels[channel].cursor = *carry_read;
          carry_read = carry_read + 1;
          g_output_channels[channel].cursor = g_output_channels[channel].cursor + 1;
        }
      }
    }
    *g_output_channels[channel].cursor = *text;
    text = text + 1;
    g_output_channels[channel].cursor = g_output_channels[channel].cursor + 1;
  }
  if ((column == 0) && (g_column_starts[3] <= g_output_channels[channel].cursor)) {
    if (channel == 2) {
      flush_src_line();
    }
    else {
      flush_listing_line();
    }
  }
  return;
#undef carry_read
#undef carry_end
#undef carry_buf
#undef break_pos
}
