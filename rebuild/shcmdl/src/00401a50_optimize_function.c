#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_loop_tree
#define g_loop_tree (*(loop * *)(g_sd + 0x267f0))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 00401a50
// name : optimize_function
// size : 1197
// sig  : void optimize_function(void)


int __cdecl optimize_function(void)

{
  g_suppress_no_effect_warning = '\0';
  opt_exp_all_blocks();
  g_suppress_no_effect_warning = '\x01';
  build_dag_chains('\x01');
  g_opt_exp_identical_only = 1;
  opt_exp_all_blocks();
  g_opt_exp_identical_only = 0;
  free_du_tables();
  optimize_all_block_expressions();
  optimize_tail_calls();
  g_tree_changed = 1;
  if (g_loop_tree != (loop *)0x0) {
    g_do_test_changed = '\0';
    move_increment_out_of_do_test(g_loop_tree);
    if (g_do_test_changed != '\0') {
      rebuild_cfg_and_leaves();
    }
    build_dag_chains('\x01');
    compute_dataflow('\x01');
    g_licm_pass = 0;
    hoist_loop_invariants(g_loop_tree);
    compute_loop_trip_counts(g_loop_tree);
    g_tree_changed = 0;
    optimize_loop_induction(g_loop_tree);
    if (g_tree_changed != 0) {
      free_du_tables();
      reoptimize_loop_expressions(g_loop_tree);
    }
  }
  while (eliminate_dead_stores(), g_tree_changed != 0) {
    opt_exp_all_blocks();
    build_dag_chains('\x01');
    g_opt_exp_identical_only = 1;
    opt_exp_all_blocks();
    g_opt_exp_identical_only = 0;
    free_du_tables();
    optimize_all_block_expressions();
  }
  if (g_loop_tree != (loop *)0x0) {
    free_du_tables();
    reoptimize_loop_expressions(g_loop_tree);
    build_dag_chains('\x01');
    compute_dataflow('\x01');
    g_licm_pass = 1;
    hoist_loop_invariants(g_loop_tree);
    if ((g_options->cpu != 0) && (g_loop_tree != (loop *)0x0)) {
      g_dt_opt_changed = 0;
      find_dt_opt_loops(g_loop_tree);
      if (g_dt_opt_changed != 0) {
        free_du_tables();
        optimize_all_block_expressions();
        g_tree_changed = 1;
        eliminate_dead_stores();
        g_tree_changed = 0;
        build_dag_chains('\x01');
        compute_dataflow('\x01');
      }
    }
    if ((g_options->unroll != '\0') && (g_loop_tree != (loop *)0x0)) {
      unroll_counted_loops(g_loop_tree);
      free_du_tables();
      rebuild_cfg_and_leaves();
      build_dag_chains('\x01');
      compute_dataflow('\x01');
      if (g_loop_tree != (loop *)0x0) {
        compute_loop_trip_counts(g_loop_tree);
      }
    }
    select_loops_to_invert(g_loop_tree);
    if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 0x40) != 0) {
      dump_tree(g_func_node,0,s_before_lp_flat___004334dc);
      dump_cfg_blocks();
    }
    g_loops_flattened = '\0';
    if (g_loop_tree != (loop *)0x0) {
      flatten_single_trip_loops(g_loop_tree);
    }
    if (g_loops_flattened != '\0') {
      if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 0x40) != 0) {
        dump_tree(g_func_node,0,s_after_loopflat_S__004334c8);
      }
      remove_unused_parameter_assignments();
      free_du_tables();
      reset_symbol_leaf_numbers();
      free_all_bblocks();
      free_loop_tree(g_loop_tree);
      g_leaf_count = 0;
      g_loop_tree = (loop *)0x0;
      g_leafed_symbols = 0;
      g_leaf_cond_depth = 0;
      build_control_flow_graph(g_func_node->child);
      insert_parameter_self_assignments();
      assign_leaf_numbers(g_func_node);
      if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 0x40) != 0) {
        dump_tree(g_func_node,0,s_after_loopflat_E__004334b4);
      }
      g_tree_changed = 1;
      while (eliminate_dead_stores(), g_tree_changed != 0) {
        opt_exp_all_blocks();
        build_dag_chains('\x01');
        g_opt_exp_identical_only = 1;
        opt_exp_all_blocks();
        g_opt_exp_identical_only = 0;
        free_du_tables();
        optimize_all_block_expressions();
      }
    }
  }
  free_du_tables();
  opt_exp_all_blocks();
  build_dag_chains('\x01');
  g_opt_exp_identical_only = 1;
  opt_exp_all_blocks();
  g_opt_exp_identical_only = 0;
  free_du_tables();
  optimize_all_block_expressions();
  if (g_options->unknown_35 != '\0') {
    g_code_merged = '\0';
    merge_common_code();
    if (g_code_merged != '\0') {
      rebuild_cfg_and_leaves();
    }
  }
  count_global_expressions();
  g_cse_changed = '\0';
  common_subexpression_elimination();
  if (g_cse_changed != '\0') {
    remove_unused_parameter_assignments();
    reset_symbol_leaf_numbers();
    free_all_bblocks();
    free_loop_tree(g_loop_tree);
    g_leaf_count = 0;
    g_loop_tree = (loop *)0x0;
    g_leafed_symbols = 0;
    g_leaf_cond_depth = 0;
    build_control_flow_graph(g_func_node->child);
    insert_parameter_self_assignments();
    assign_leaf_numbers(g_func_node);
    opt_exp_all_blocks();
    optimize_all_block_expressions();
  }
  if ((g_loop_tree != (loop *)0x0) &&
     (((g_loops_flattened != '\0' || (g_cse_changed != '\0')) || (g_code_merged != '\0')))) {
    build_dag_chains('\x01');
    compute_dataflow('\x01');
    compute_loop_trip_counts(g_loop_tree);
    free_du_tables();
  }
  allocate_registers();
  convert_for_loops_to_do(g_loop_tree);
  mark_referenced_functions();
  if (((byte)g_debug_flags & 4) != 0) {
    dump_leaf_table();
  }
  return;
}



