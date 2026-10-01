#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asa_file
#define g_asa_file (*(FILE * *)(g_sd + 0x1f988))
#undef g_db2_file
#define g_db2_file (*(FILE * *)(g_sd + 0x1fa24))
#undef g_ilb_file
#define g_ilb_file (*(FILE * *)(g_sd + 0x1f980))
#undef g_int_file
#define g_int_file (*(FILE * *)(g_sd + 0x1f98c))
#undef g_lit_file
#define g_lit_file (*(FILE * *)(g_sd + 0x1fa08))
#undef g_ofa_file
#define g_ofa_file (*(FILE * *)(g_sd + 0x1f9ec))
#undef g_reg_file
#define g_reg_file (*(FILE * *)(g_sd + 0x1fa2c))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_stage_request
#define g_stage_request (*(request * *)(g_sd + 0x1ee88))
#undef g_sua_file
#define g_sua_file (*(FILE * *)(g_sd + 0x1fa30))
#undef g_sud_file
#define g_sud_file (*(FILE * *)(g_sd + 0x1f9f0))
#undef g_swi_file
#define g_swi_file (*(FILE * *)(g_sd + 0x1feec))
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x1f99c))


// entry: 0041a8e0
// name : load_request_and_open_stage_files
// size : 683
// sig  : void load_request_and_open_stage_files(char * request_path)


int __cdecl load_request_and_open_stage_files(char *request_path)

{
  FILE *opened;
  int n;
  undefined4 *word_ptr;
  
  g_stage_request = load_request_record_file(2,request_path);
  g_request = g_stage_request;
  if (0x7f49 < *(int *)g_stage_request->unknown_0b0) {
    report_codegen_message(0xbc8,1,0,0,(char *)0x0);
  }
  g_request->label_count = g_request->label_count + *(int *)g_request->unknown_0b0 + 0xb6;
  word_ptr = (undefined4 *)&g_used_routine_bits;
  for (n = 8; n != 0; n = n + -1) {
    *word_ptr = 0;
    word_ptr = word_ptr + 1;
  }
  g_sym_file = stock_fopen(g_request->sym_path,&g_open_mode_rb);
  if (g_sym_file == (FILE *)0x0) {
    report_codegen_message(0xce4,1,0,0,(char *)0x0);
  }
  g_int_file = stock_fopen(g_request->int_path,&g_open_mode_rb);
  if (g_int_file == (FILE *)0x0) {
    report_codegen_message(0xce4,1,0,0,(char *)0x0);
  }
  g_sua_file = stock_fopen(g_request->sua_path,&g_open_mode_wb);
  if (g_sua_file == (FILE *)0x0) {
    report_codegen_message(0xce4,1,0,0,(char *)0x0);
  }
  g_sud_file = stock_fopen(g_request->sud_path,&g_open_mode_wb);
  if (g_sud_file == (FILE *)0x0) {
    report_codegen_message(0xce4,1,0,0,(char *)0x0);
  }
  if (*(short *)g_request->unknown_004 == 0) {
    g_ofa_file = stock_fopen(g_request->ofa_path,&g_open_mode_wb);
    if (g_ofa_file == (FILE *)0x0) {
      report_codegen_message(0xce4,1,0,0,(char *)0x0);
    }
    g_lit_file = stock_fopen(g_request->lit_path,&g_open_mode_wb);
    opened = g_lit_file;
  }
  else {
    g_reg_file = stock_fopen(g_request->reg_path,&g_open_mode_rb);
    opened = g_reg_file;
  }
  if (opened == (FILE *)0x0) {
    report_codegen_message(0xce4,1,0,0,(char *)0x0);
  }
  g_asa_file = stock_fopen(g_request->asa_path,&g_open_mode_wb);
  if (g_asa_file == (FILE *)0x0) {
    report_codegen_message(0xce4,1,0,0,(char *)0x0);
  }
  g_swi_file = stock_fopen(g_request->swi_path,&g_open_mode_rb);
  if (g_swi_file == (FILE *)0x0) {
    report_codegen_message(0xce4,1,0,0,(char *)0x0);
  }
  g_ilb_file = stock_fopen(g_request->ilb_path,&g_open_mode_rb);
  if (g_ilb_file == (FILE *)0x0) {
    report_codegen_message(0xce4,1,0,0,(char *)0x0);
  }
  if ((*(short *)(g_request->unknown_004 + 0x12) == 1) &&
     (g_db2_file = stock_fopen(g_request->db2_path,&g_open_mode_wb), g_db2_file == (FILE *)0x0)) {
    report_codegen_message(0xce4,1,0,0,(char *)0x0);
  }
  return;
}



