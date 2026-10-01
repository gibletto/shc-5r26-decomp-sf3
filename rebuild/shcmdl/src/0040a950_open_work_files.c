#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
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


// entry: 0040a950
// name : open_work_files
// size : 224
// sig  : void open_work_files(void)


int __cdecl open_work_files(void)

{
  g_sym_file = stock_fopen(g_options->sym_file,&g_mode_rb);
  if (g_sym_file == (FILE *)0x0) {
    fatal_error(0xce4);
  }
  g_tree_in_file = stock_fopen(g_options->work_file_64,&g_mode_rb);
  if (g_tree_in_file == (FILE *)0x0) {
    fatal_error(0xce4);
  }
  g_tree_out_file = stock_fopen(g_options->work_file_68,&g_mode_wb);
  if (g_tree_out_file == (FILE *)0x0) {
    fatal_error(0xce4);
  }
  g_reg_file = stock_fopen(g_options->work_file_80,&g_mode_wb);
  if (g_reg_file == (FILE *)0x0) {
    fatal_error(0xce4);
  }
  g_switch_file = stock_fopen(g_options->work_file_70,&g_mode_rb_plus);
  if (g_switch_file == (FILE *)0x0) {
    fatal_error(0xce4);
  }
  return;
}



