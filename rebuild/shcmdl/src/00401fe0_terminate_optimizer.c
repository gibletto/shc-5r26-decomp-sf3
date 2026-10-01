#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 00401fe0
// name : terminate_optimizer
// size : 89
// sig  : void terminate_optimizer(char * * argv)


int __cdecl terminate_optimizer(char **argv)

{
  write_intermediate_file(1,argv[1]);
  close_work_files();
  free_node_blocks();
  if (((((g_inline_flags & 4) != 0) || (g_options->unknown_35 != '\0')) ||
      (g_unroll_label_added != '\0')) || (g_symbol_table_modified != '\0')) {
    write_symbol_file();
  }
  stock_exit(g_max_error_level * 2 + 1);
  return;
}



