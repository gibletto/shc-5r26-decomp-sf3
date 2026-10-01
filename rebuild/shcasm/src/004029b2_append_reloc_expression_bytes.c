#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_object_expr_buffer
#define g_object_expr_buffer (*(char * *)(g_sd + 0x128cc))
#undef g_object_expr_cursor
#define g_object_expr_cursor (*(char * *)(g_sd + 0x10ca8))


// entry: 004029b2
// name : append_reloc_expression_bytes
// size : 163
// sig  : char * __cdecl append_reloc_expression_bytes(char *data,short len)


char * __cdecl append_reloc_expression_bytes(char *data,short len)

{
  char *pcVar1;
  
  if (data == (char *)0x0) {
    append_reloc_record_bytes
              (g_object_expr_buffer,(short)g_object_expr_cursor - (short)g_object_expr_buffer);
    g_object_expr_cursor = g_object_expr_buffer;
    pcVar1 = g_object_expr_buffer;
  }
  else {
    if (g_object_expr_end - (int)g_object_expr_cursor < (int)len) {
      report_message_at_source_line(0,0,0x1360,(char *)0x0);
    }
    while( true ) {
      pcVar1 = (char *)0x0;
      if (len == 0) break;
      *g_object_expr_cursor = *data;
      data = data + 1;
      g_object_expr_cursor = g_object_expr_cursor + 1;
      len = len + -1;
    }
  }
  return pcVar1;
}
