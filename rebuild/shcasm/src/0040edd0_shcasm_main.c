#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_request_copy
#define g_request_copy (*(request * *)(g_sd + 0x129a8))


// entry: 0040edd0
// name : shcasm_main
// size : 364
// sig  : void __cdecl shcasm_main(int argc,char **argv)


int __cdecl shcasm_main(int argc,char **argv)

{
  uint input_flags;
  char *input_path;
  uint catch_signals;
  
  g_max_error_severity = 0;
  emit_progress_banner(4);
  g_current_request = load_request_record_file(4,argv[1]);
  if (g_current_request == (request *)0x0) {
    report_message_at_source_line(0,0,0x1324,(char *)0x0);
  }
  g_request_copy = g_current_request;
  catch_signals = (uint)((g_current_request->back_flags & 0x400) != 0);
  configure_signal_handlers(catch_signals);
  input_flags = g_current_request->back_flags & 0x2040;
  if (input_flags == 0x40) {
    input_path = g_current_request->asb_path;
  }
  else if (input_flags == 0x2000) {
    input_path = g_current_request->asa_path;
  }
  else if (g_current_request->optimize == 0) {
    input_path = g_current_request->asa_path;
  }
  else {
    input_path = g_current_request->asb_path;
  }
  initialize_work_buffers();
  load_intermediate_record_stream(input_path,g_current_request);
  run_layout_passes();
  run_assembler_passes();
  free_work_buffers();
  store_request_record_updates(argv[1]);
  close_and_delete_temp_files();
  stock_exit(g_max_error_severity * 2 + 1);
  return;
}
