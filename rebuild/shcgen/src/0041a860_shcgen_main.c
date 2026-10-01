#include "decls.h"
#include "imports.h"

// entry: 0041a860
// name : shcgen_main
// size : 89
// sig  : void shcgen_main(int argc, char * * argv)


int __cdecl shcgen_main(int argc,char **argv)

{
  emit_progress_banner(2);
  g_message_severity = 0;
  configure_signal_handlers(0);
  load_request_and_open_stage_files(argv[1]);
  set_gen_node_exhausted_handler(report_gen_node_pool_exhausted);
  read_symbol_table();
  allocate_static_variables_and_write_sud();
  generate_ilb_stream();
  run_stage_pipeline_and_exit(argv[1]);
  return;
}



