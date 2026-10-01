#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0042bb89
// name : copy_string_to_line_width
// size : 137
// sig  : short copy_string_to_line_width(char * src, char * dst, short column)


short __cdecl copy_string_to_line_width(char *src,char *dst,short column)

{
  short copied;
  int line_width;
  
  copied = 0;
  if (g_current_request->list_width == 0) {
    line_width = 0x84;
  }
  else {
    line_width = g_current_request->list_width;
  }
  for (; (*src != '\0' && ((int)copied < line_width - column)); copied = copied + 1) {
    *dst = *src;
    src = src + 1;
    dst = dst + 1;
  }
  *dst = *src;
  return copied;
}



