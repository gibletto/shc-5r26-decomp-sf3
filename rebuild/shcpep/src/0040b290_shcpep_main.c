#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asb_output
#define g_asb_output (*(FILE * *)(g_sd + 0x5d20))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0x5bf0))
#undef g_lit_output
#define g_lit_output (*(FILE * *)(g_sd + 0x6df8))
#undef g_ofb_output
#define g_ofb_output (*(FILE * *)(g_sd + 0x5cf8))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x6e04))
#undef g_stage_flags
#define g_stage_flags (*(unsigned int *)(g_sd + 0x6d64))
#undef g_sua_input
#define g_sua_input (*(FILE * *)(g_sd + 0x5c00))
#undef g_sub_output
#define g_sub_output (*(FILE * *)(g_sd + 0x5bfc))


// entry: 0040b290
// name : shcpep_main
// size : 719
// sig  : void shcpep_main(int argc, char * * argv)


int __cdecl shcpep_main(int argc,char **argv)

{
  short store_rc;
  int rc;
  request_section *section;
  
  emit_progress_banner(3);
  configure_signal_handlers(0);
  g_current_request = load_request_record_file(3,argv[1]);
  if (g_current_request == (request *)0x0) {
    report_fatal_message(0,0,0x125c);
  }
  g_request = g_current_request;
  g_stage_flags = g_current_request->stage_flags;
  if ((g_stage_flags & 0x10000) == 0) {
    load_symbol_aux_record_stream(g_current_request->asa_path,g_current_request);
    g_sua_input = open_shared_file(g_current_request->sua_path,&s_open_mode_rb);
  }
  else {
    load_symbol_aux_record_stream(s_sym_f,g_current_request);
    g_sua_input = open_shared_file(s_psd_f,&s_open_mode_rb);
  }
  if (g_sua_input == (FILE *)0x0) {
    report_fatal_message(0,0,0xce4);
  }
  g_sub_output = open_shared_file(g_current_request->sub_path,&s_open_mode_wb);
  if (g_sub_output == (FILE *)0x0) {
    report_fatal_message(0,0,0xce4);
  }
  g_ofb_output = open_shared_file(g_current_request->ofb_path,&s_open_mode_wb);
  if (g_ofb_output == (FILE *)0x0) {
    report_fatal_message(0,0,0xce4);
  }
  g_asb_output = open_shared_file(g_current_request->asb_path,&s_open_mode_wb);
  if (g_asb_output == (FILE *)0x0) {
    report_fatal_message(0,0,0xce4);
  }
  g_lit_output = open_shared_file(g_current_request->lit_path,&s_open_mode_wb);
  if (g_lit_output == (FILE *)0x0) {
    report_fatal_message(0,0,0xce4);
  }
  for (section = g_current_request->sections; section != (request_section *)0x0;
      section = section->next) {
    section->unknown_08 = 0;
  }
  run_prep_pass_and_emit_backend_files();
  rc = _fclose(g_asb_output);
  if (rc != 0) {
    report_fatal_message(0,0,0xce5);
  }
  rc = _fclose(g_ofb_output);
  if (rc != 0) {
    report_fatal_message(0,0,0xce5);
  }
  rc = _fclose(g_sub_output);
  if (rc != 0) {
    report_fatal_message(0,0,0xce5);
  }
  rc = _fclose(g_sua_input);
  if (rc != 0) {
    report_fatal_message(0,0,0xce5);
  }
  write_final_literal_pool_flag(g_lit_output);
  rc = _fclose(g_lit_output);
  if (rc != 0) {
    report_fatal_message(0,0,0xce5);
  }
  g_current_request->label_count = (int)g_last_labno;
  g_current_request->result_0d4 = g_request_result_0d4;
  store_rc = store_request_record_file(3,argv[1]);
  if (store_rc == -1) {
    report_fatal_message(0,0,0x125c);
  }
  stock_exit(1);
  return;
}



