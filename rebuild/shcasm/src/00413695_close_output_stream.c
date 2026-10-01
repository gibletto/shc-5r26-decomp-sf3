#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_object_data_buffer
#define g_object_data_buffer (*(char * *)(g_sd + 0x10c7c))
#undef g_object_expr_buffer
#define g_object_expr_buffer (*(char * *)(g_sd + 0x128cc))


// entry: 00413695
// name : close_output_stream
// size : 136
// sig  : void __cdecl close_output_stream(short stream)


int __cdecl close_output_stream(short stream)

{
  int close_status;
  
  stock_free(g_output_channels[stream].buffer);
  if (stream == 1) {
    stock_free(g_object_data_buffer);
    stock_free(g_object_expr_buffer);
  }
  close_status = _fclose(g_output_channels[stream].file);
  if (close_status == -1) {
    report_message_at_source_line(0,0,0xce5,(char *)0x0);
  }
  return;
}
