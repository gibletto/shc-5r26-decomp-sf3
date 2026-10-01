#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 00401750
// name : prepare_function_for_optimization
// size : 243
// sig  : void prepare_function_for_optimization(il_node * func)


int __cdecl prepare_function_for_optimization(il_node *func)

{
  g_inline_pass = (uint)(g_options->inline_passes != '\0');
  g_inline_scopes_changed = '\0';
  if ((int)g_inline_pass <= (int)g_options->inline_passes) {
    do {
      if ((g_inline_flags & 6) == 6) {
        if (((int)g_symbol_limit <= g_options->symbol_count) || (0x7ffe < g_options->label_count)) {
          if ((int)g_inline_pass < 2) {
            g_inline_flags = g_inline_flags & 0xfd;
          }
          goto LAB_004017d7;
        }
        expand_inline_calls(func->child);
      }
      else {
LAB_004017d7:
        warn_uninlined_calls(func->child);
      }
      g_inline_pass = g_inline_pass + 1;
    } while ((int)g_inline_pass <= (int)g_options->inline_passes);
  }
  if (((g_options->optimize != 0) && (g_options->unknown_20 == 1)) &&
     ((g_options->option_bits & 1) != 0)) {
    special_change();
  }
  g_leaf_cond_depth = 0;
  build_control_flow_graph(func->child);
  insert_parameter_self_assignments();
  assign_leaf_numbers(func);
  return;
}



