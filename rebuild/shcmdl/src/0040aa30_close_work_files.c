#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_reg_file
#define g_reg_file (*(FILE * *)(g_sd + 0x1e72c))
#undef g_switch_file
#define g_switch_file (*(FILE * *)(g_sd + 0x1e734))
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))
#undef g_tree_in_file
#define g_tree_in_file (*(FILE * *)(g_sd + 0x26eec))
#undef g_tree_out_file
#define g_tree_out_file (*(FILE * *)(g_sd + 0x26860))


// entry: 0040aa30
// name : close_work_files
// size : 156
// sig  : void close_work_files(void)


int __cdecl close_work_files(void)

{
  int rc;
  
  rc = _fclose(g_sym_file);
  if (rc != 0) {
    fatal_error(0xce5);
  }
  rc = _fclose(g_tree_in_file);
  if (rc != 0) {
    fatal_error(0xce5);
  }
  rc = _fclose(g_tree_out_file);
  if (rc != 0) {
    fatal_error(0xce5);
  }
  rc = _fclose(g_reg_file);
  if (rc != 0) {
    fatal_error(0xce5);
  }
  rc = _fclose(g_switch_file);
  if (rc != 0) {
    fatal_error(0xce5);
  }
  return;
}



