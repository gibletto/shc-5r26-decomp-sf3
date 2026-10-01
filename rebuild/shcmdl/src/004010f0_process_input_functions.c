#include "decls.h"
#include "imports.h"
#include <setjmp.h>
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_preg_map_double
#define g_preg_map_double (*(char * *)(g_sd + 0x16480))
#undef g_preg_map_float
#define g_preg_map_float (*(unsigned char * *)(g_sd + 0x164a8))
#undef g_preg_map_general
#define g_preg_map_general (*(unsigned char * *)(g_sd + 0x16484))
#undef g_tree_in_file
#define g_tree_in_file (*(FILE * *)(g_sd + 0x26eec))


// entry: 004010f0
// name : process_input_functions
// size : 555
// sig  : void process_input_functions(void)


int __cdecl process_input_functions(void)

{
  il_node *func;
  int err;
  undefined4 unaff_ESI;
  int unaff_EDI;
  il_op op;
  
  g_preg_map_general = &g_gpr_alloc_order;
  g_int_reg_count = 0xb;
  g_preg_map_float = &g_fpr_alloc_order;
  g_preg_map_double = s______________004342c0;
  g_float_reg_count = 0xc;
  g_last_warned_line = 0;
  g_float_arg_regs = (int)g_options->unknown_149;
  g_float_arg_reg_limit = g_float_arg_regs + 1;
  build_register_allocation_order();
  g_function_file_pos = stock_ftell(g_tree_in_file);
  do {
    func = read_il_node();
    op = func->op;
    if ((op != IL_FUNC) && (op != IL_ASM)) {
      write_il_node(func);
      return;
    }
    if (op == IL_ASM) {
      write_il_node(func);
      free_node(func);
    }
    else {
      g_fold_warnings = 0;
      g_opt_exp_pass = 0;
      if ((g_options->optimize == 0) && ((g_inline_flags & 2) == 0)) {
        process_function_expressions_only();
      }
      else {
        g_saved_symbol_count = (short)g_options->symbol_count;
        g_saved_label_count = (short)g_options->label_count;
        g_saved_switch_count = g_options->next_switch_table;
        g_temp_symx = 0;
        g_leafed_symbols = 0;
        g_leaf_count = 0;
        g_function_aborted = 0;
        g_func_node = func;
        err = setjmp(*(jmp_buf *)&g_error_jmp_buf);
        if (err == 0) {
          if ((g_options->optimize == 0) && ((g_inline_flags & 2) != 0)) {
            process_function_op0_inline(func);
          }
          else {
            func = read_il_operands(func);
            if (func == (il_node *)0x0) {
              abort_function_optimization();
            }
            if ((g_debug_flags & 2) != 0) {
              dump_tree(func,0,s_read_tree_0043347c);
            }
            g_pool_bytes_in_use = 0;
            prepare_function_for_optimization(func);
            optimize_function();
            if ((g_debug_flags & 2) != 0) {
              dump_tree(func,0,s_write_tree_00433470);
            }
            write_function_and_free(func);
            if ((g_debug_flags & 0x10000000) == 0) {
              if (g_pool_bytes_in_use < 1) {
                if (-1 < g_pool_bytes_in_use) goto LAB_004012f0;
                err = 0x1092;
              }
              else {
                err = 0x1091;
              }
              fatal_error(err);
            }
          }
        }
        else {
          process_function_expressions_only();
        }
      }
    }
LAB_004012f0:
    g_function_file_pos = stock_ftell(g_tree_in_file);
  } while( true );
}



