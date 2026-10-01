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
#undef g_sua_file
#define g_sua_file (*(FILE * *)(g_sd + 0x1fa30))
#undef g_sud_file
#define g_sud_file (*(FILE * *)(g_sd + 0x1f9f0))
#undef g_swi_file
#define g_swi_file (*(FILE * *)(g_sd + 0x1feec))
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x1f99c))


// entry: 0042b370
// name : close_stage_files
// size : 698
// sig  : void close_stage_files(void)


int __cdecl close_stage_files(void)

{
  int rc;
  
  if (g_sua_file != (FILE *)0x0) {
    g_close_status = _fclose(g_sua_file);
    if (g_close_status == -1) {
      report_codegen_message(0xce5,1,0,0,(char *)0x0);
    }
    else {
      g_sua_file = (FILE *)0x0;
    }
  }
  if (g_sud_file != (FILE *)0x0) {
    g_close_status = _fclose(g_sud_file);
    if (g_close_status == -1) {
      report_codegen_message(0xce5,1,0,0,(char *)0x0);
    }
    else {
      g_sud_file = (FILE *)0x0;
    }
  }
  if (g_ofa_file != (FILE *)0x0) {
    rc = _fclose(g_ofa_file);
    g_close_status = (int)(char)rc;
    if (g_close_status == -1) {
      report_codegen_message(0xce5,1,0,0,(char *)0x0);
    }
    else {
      g_ofa_file = (FILE *)0x0;
    }
  }
  if (g_asa_file != (FILE *)0x0) {
    rc = _fclose(g_asa_file);
    g_close_status = (int)(char)rc;
    if (g_close_status == -1) {
      report_codegen_message(0xce5,1,0,0,(char *)0x0);
    }
    else {
      g_asa_file = (FILE *)0x0;
    }
  }
  if (g_db2_file != (FILE *)0x0) {
    rc = _fclose(g_db2_file);
    g_close_status = (int)(char)rc;
    if (g_close_status == -1) {
      report_codegen_message(0xce5,1,0,0,(char *)0x0);
    }
    else {
      g_db2_file = (FILE *)0x0;
    }
  }
  if (g_sym_file != (FILE *)0x0) {
    rc = _fclose(g_sym_file);
    g_close_status = (int)(char)rc;
    if (g_close_status == -1) {
      report_codegen_message(0xce5,1,0,0,(char *)0x0);
    }
    else {
      g_sym_file = (FILE *)0x0;
    }
  }
  if (g_ilb_file != (FILE *)0x0) {
    rc = _fclose(g_ilb_file);
    g_close_status = (int)(char)rc;
    if (g_close_status == -1) {
      report_codegen_message(0xce5,1,0,0,(char *)0x0);
    }
    else {
      g_ilb_file = (FILE *)0x0;
    }
  }
  if (g_int_file != (FILE *)0x0) {
    rc = _fclose(g_int_file);
    g_close_status = (int)(char)rc;
    if (g_close_status == -1) {
      report_codegen_message(0xce5,1,0,0,(char *)0x0);
    }
    else {
      g_int_file = (FILE *)0x0;
    }
  }
  if (g_swi_file != (FILE *)0x0) {
    rc = _fclose(g_swi_file);
    g_close_status = (int)(char)rc;
    if (g_close_status == -1) {
      report_codegen_message(0xce5,1,0,0,(char *)0x0);
    }
    else {
      g_swi_file = (FILE *)0x0;
    }
  }
  if (g_reg_file != (FILE *)0x0) {
    rc = _fclose(g_reg_file);
    g_close_status = (int)(char)rc;
    if (g_close_status == -1) {
      report_codegen_message(0xce5,1,0,0,(char *)0x0);
    }
    else {
      g_reg_file = (FILE *)0x0;
    }
  }
  if (g_lit_file != (FILE *)0x0) {
    rc = _fclose(g_lit_file);
    g_close_status = (int)(char)rc;
    if (g_close_status == -1) {
      report_codegen_message(0xce5,1,0,0,(char *)0x0);
      return;
    }
    g_lit_file = (FILE *)0x0;
  }
  return;
}



