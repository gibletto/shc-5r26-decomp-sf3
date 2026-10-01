#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0042b864
// name : emit_listing_page_header
// size : 727
// sig  : void emit_listing_page_header(void)


int __cdecl emit_listing_page_header(void)

{
  short header_len;
  short text_len;
  uint name_len;
  short local_10;
  
  g_listing_page_number = g_listing_page_number + 1;
  if (1 < g_listing_page_number) {
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
      write_listing_line(&g_listing_header_buffer,&g_listing_header_buffer);
    }
  }
  g_listing_page_line_count = 1;
  header_len = format_listing_page_header(&g_listing_header_buffer,g_listing_page_number);
  write_listing_line(&g_listing_header_buffer,&g_listing_header_buffer + header_len);
  write_listing_line(&g_listing_header_buffer,&g_listing_header_buffer);
  if (g_listing_page_number == 1) {
    header_len = copy_string_count(s_object_listing_banner,&g_listing_header_buffer);
    write_listing_line(&g_listing_header_buffer,&g_listing_header_buffer + header_len);
    write_listing_line(&g_listing_header_buffer,&g_listing_header_buffer);
    if (g_program_size == 0) {
      header_len = copy_string_count(s_object_program_empty,&g_listing_header_buffer);
      write_listing_line(&g_listing_header_buffer,&g_listing_header_buffer + header_len);
      write_listing_line(&g_listing_header_buffer,&g_listing_header_buffer);
      g_listing_page_line_count = g_listing_page_line_count + -1;
    }
    else {
      header_len = copy_string_count(s_FILE_NAME__00442108,&g_listing_header_buffer);
      name_len = stock_strlen(g_current_request->source_name);
      local_10 = copy_string_to_line_width
                           (g_current_request->source_name,&g_listing_header_buffer + header_len,
                            header_len);
      write_listing_line(&g_listing_header_buffer,&g_listing_header_buffer + header_len + local_10);
      while (local_10 < (short)name_len) {
        header_len = copy_string_to_line_width(s__00442118,&g_listing_header_buffer,0);
        text_len = copy_string_to_line_width
                             (g_current_request->source_name + local_10,
                              &g_listing_header_buffer + header_len,header_len);
        local_10 = local_10 + text_len;
        write_listing_line(&g_listing_header_buffer,&g_listing_header_buffer + header_len + text_len
                          );
      }
    }
  }
  if (g_program_size != 0) {
    write_listing_line(&g_listing_header_buffer,&g_listing_header_buffer);
    header_len = copy_string_count(s_object_listing_header,&g_listing_header_buffer);
    text_len = copy_string_count(s_INSTRUCTION_OPERAND_COMMENT_00442148,
                                 &g_listing_header_buffer + header_len);
    write_listing_line(&g_listing_header_buffer,&g_listing_header_buffer + header_len + text_len);
    write_listing_line(&g_listing_header_buffer,&g_listing_header_buffer);
  }
  return;
}
