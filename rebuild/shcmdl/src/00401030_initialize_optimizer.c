#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_node_alloc_hook
#define g_node_alloc_hook (*(unsigned char * *)(g_sd + 0x1e4ec))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 00401030
// name : initialize_optimizer
// size : 178
// sig  : void initialize_optimizer(char * * argv)


int __cdecl initialize_optimizer(char **argv)

{
  il_node *node;
  
  install_signal_handlers(0);
  g_options = read_intermediate_file(1,argv[1]);
  g_debug_flags = *(uint *)(g_options->unknown_125 + 7);
  g_inline_flags = '\0';
  if (g_options->inline_records != (void *)0x0) {
    g_inline_flags = '\x04';
  }
  open_work_files();
  read_symbol_table();
  g_max_error_level = 0;
  init_il_node_pool(0x2000);
  if ((g_inline_flags & 4) != 0) {
    g_inline_flags = g_inline_flags | 2;
    g_float_arg_regs = (int)g_options->unknown_149;
    load_inline_bodies();
  }
  g_node_alloc_hook = alloc_node_or_null;
  node = read_il_node();
  write_il_node(node);
  free_node(node);
  return;
}



