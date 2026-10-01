#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0042bc12
// name : pad_listing_page
// size : 74
// sig  : void pad_listing_page(void)


int __cdecl pad_listing_page(void)

{
  short line_no;
  
  for (line_no = g_listing_page_line_count; (int)line_no < g_current_request->list_length;
      line_no = line_no + 1) {
    write_listing_line(&g_listing_blank_line,&g_listing_blank_line);
  }
  return;
}
