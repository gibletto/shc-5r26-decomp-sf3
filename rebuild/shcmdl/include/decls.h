#ifndef DECLS_H
#define DECLS_H
#include "ghidra_stubs.h"
#include "stage_types.h"

/* the stock data image (scaffold-rebuild.py): data globals are lvalues at their stock offsets */
extern unsigned char g_sd[];
#define SD(a) ((unsigned int)(g_sd + ((unsigned int)(a) - 0x432000u)))

extern size_t _strncnt();
extern int abort_function_optimization();
extern int add_block_to_life_area();
extern int add_block_to_successor_group();
extern int add_clashes_for_range();
extern int add_constant_to_hash();
extern il_node * add_continue_to_first_child();
extern int add_edges_from_list_and_free();
extern int add_induction_factor();
extern int add_inline_map_entry();
extern int add_lreg_clash();
extern int add_member_to_scope();
extern int add_memory_frequency_record();
extern int add_memory_lregs();
extern int add_memory_reference();
extern int add_multiword();
extern int add_operator_to_hash();
extern il_node * add_return_one_pair();
extern int add_scope_to_enclosing_block();
extern int add_to_gen_use_sets();
extern il_node * alloc_inline_node();
extern il_node * alloc_node();
extern il_node * alloc_node_blocks();
extern il_node * alloc_node_or_null();
extern int allocate_block_registers();
extern int allocate_il_node_block();
extern int allocate_registers();
extern uchar any_bit_set();
extern int append_callee_scopes();
extern int append_input_tail();
extern int append_list_item();
extern node_list * append_node_list();
extern il_node * apply_pattern_rule();
extern uint argument_register_index();
extern uint argument_register_index_sh4();
extern int assign_argument_registers();
extern int assign_final_value_after_loop();
extern int assign_float_registers();
extern int assign_leaf_numbers();
extern int assign_parameter_registers();
extern int assign_physical_registers();
extern int assign_registers_without_allocation();
extern int bitset_and();
extern int bitset_or();
extern int bitsets_differ();
extern char block_has_no_other_var_ref();
extern int build_block_dag_chain();
extern int build_control_flow_graph();
extern int build_dag();
extern int build_dag_chains();
extern int build_induction_increment();
extern int build_kill_or_def_set();
extern int build_lreg_clash_lists();
extern int build_register_allocation_order();
extern il_node * build_spec_change_tree();
extern il_node * build_tree_from_terms();
extern int build_ud_du_chains();
extern int cast_operands_to_node_type();
extern int cast_type_rank();
extern int cfg_add_edge();
extern int cfg_add_statement();
extern int cfg_append_statement();
extern int cfg_break();
extern int cfg_case_label();
extern int cfg_continue();
extern int cfg_goto();
extern int cfg_label();
extern int cfg_out_of_memory();
extern int cfg_return();
extern int cfg_start_block();
extern uint check_arith_overflow();
extern int check_induction_entry();
extern int check_inline_call_args();
extern uint check_loop_test_replacement();
extern int check_read_result();
extern int check_test_variables();
extern int check_value_range();
extern int check_write_result();
extern int choose_const_dominator();
extern int classify_add_operands();
extern short classify_div_operands();
extern int classify_mul_operands();
extern int classify_size_conversion();
extern int clear_bytes();
extern int clear_common_links();
extern int clear_induction_marks();
extern int clear_induction_numbers();
extern int clear_inline_maps();
extern int clear_line_info();
extern int clear_symbol();
extern int clear_unlinked_block_statements();
extern int close_work_files();
extern int coalesce_copy_webs();
extern int collect_memory_frequencies();
extern int collect_nested_block_scopes();
extern int collect_reassociation_terms();
extern int collect_register_candidate();
extern int commit_updated_symbol_info();
extern il_op common_bitop_pair();
extern il_node * common_expression_to_temp();
extern int common_subexpression_elimination();
extern uint compare_blocks();
extern short compare_double_constants();
extern short compare_float_constants();
extern ushort compare_long_double_constants();
extern int compare_multiword();
extern uint compare_statements_backward();
extern int compute_const_life_area();
extern int compute_dataflow();
extern int compute_dominators();
extern int compute_loop_trip_count();
extern int compute_loop_trip_counts();
extern int compute_lreg_priorities_and_life_areas();
extern int compute_lreg_profits();
extern int compute_web_node_life_area();
extern char condition_defs_block_inversion();
extern int const_out_of_range();
extern int const_value_size();
extern int constants_equal();
extern int convert_constant();
extern uint convert_double_to_float();
extern uint convert_double_to_int();
extern uint convert_double_to_ldouble();
extern int convert_double_to_uint();
extern uint convert_float_to_double();
extern uint convert_float_to_int();
extern uint convert_float_to_ldouble();
extern int convert_float_to_uint();
extern int convert_for_loops_to_do();
extern int convert_int_to_double();
extern int convert_int_to_float();
extern int convert_int_to_ldouble();
extern uint convert_ldouble_to_double();
extern uint convert_ldouble_to_float();
extern uint convert_ldouble_to_int();
extern int convert_ldouble_to_uint();
extern int convert_loop_to_decrement_test();
extern int convert_self_tail_call_to_jump();
extern int convert_uint_to_double();
extern short convert_uint_to_float();
extern int convert_uint_to_ldouble();
extern uint copy_file_basename();
extern int copy_loop_body_blocks();
extern int copy_string();
extern short * copy_symbol_info();
extern il_node * copy_tree();
extern il_node * copy_tree_unlinked();
extern int count_block_expressions();
extern int count_common_expression();
extern int count_conditional_operands();
extern int count_enclosing_loops();
extern int count_expression_tree();
extern int count_global_expressions();
extern int count_matching_leaf_nodes();
extern int count_shift_add_terms();
extern int count_variable_reference();
extern int cse_abort_out_of_memory();
extern int cse_add_constant();
extern int cse_add_expression();
extern int cse_add_to_split_class();
extern il_node * cse_append_temp_assign();
extern il_node * cse_check_common_expression();
extern int cse_clear_node();
extern int cse_clear_value_number();
extern int cse_count_leaf_redefinition();
extern il_node * cse_drop_class_head();
extern il_node * cse_eliminate_node();
extern il_node * cse_find_arith_match();
extern bblock * cse_find_common_block();
extern il_node * cse_find_constant();
extern il_node * cse_find_expression();
extern il_node * cse_find_using_stmt();
extern int cse_free_hash_tables();
extern int cse_free_tables();
extern int cse_global_block();
extern il_node * cse_global_tree();
extern int cse_hash_arith_expr();
extern int cse_hash_constant();
extern int cse_join_class();
extern int cse_join_value_class();
extern int cse_mark_subtree_skipped();
extern int cse_mark_unchained_blocks();
extern int cse_new_class();
extern int cse_new_value_number();
extern int cse_note_assignment();
extern int cse_number_arith_expr();
extern int cse_number_conditional();
extern int cse_number_constant();
extern int cse_number_expression();
extern int cse_number_identifier();
extern int cse_number_memory_ref();
extern int cse_number_operator();
extern int cse_number_statements();
extern int cse_out_of_memory();
extern int cse_paths_kill_expr();
extern int cse_record_leaf_definition();
extern int cse_record_memory_ref();
extern int cse_record_variable();
extern int cse_reinsert_class();
extern int cse_replace_in_block();
extern int cse_replace_in_blocks();
extern il_node * cse_replace_in_tree();
extern il_node * cse_replace_with_temp();
extern il_node * cse_replace_with_temporary();
extern short cse_single_definition_status();
extern int dag_assignment();
extern int dag_conditional();
extern int dag_constant();
extern int dag_indirection();
extern int dag_operator();
extern int dag_variable();
extern int definition_outside_life_areas();
extern int delete_operand();
extern il_node * discard_unused_values();
extern int dump_bitset();
extern int dump_block_list();
extern int dump_block_numbers();
extern int dump_block_table();
extern int dump_cfg_blocks();
extern int dump_constant_value();
extern int dump_dag_chain_node();
extern int dump_du_chain();
extern int dump_du_chains();
extern int dump_du_chains_in_tree();
extern int dump_ilnode_list();
extern int dump_leaf_table();
extern int dump_live_sets();
extern int dump_logical_register_list();
extern int dump_loop_table();
extern int dump_loop_tree();
extern int dump_loop_tree_titled();
extern int dump_lreg();
extern int dump_qualify_fields();
extern int dump_reaching_sets();
extern int dump_tree();
extern int dump_tree_node();
extern int dump_tree_rec();
extern int dump_type();
extern int dump_value_bytes();
extern int dump_web_chain();
extern il_node * eliminate_dead_store();
extern int eliminate_dead_stores();
extern il_node * eliminate_dead_stores_in_tree();
extern il_node * expand_float_to_unsigned();
extern int expand_inline_call();
extern int expand_inline_calls();
extern int expand_inline_calls_in_expr();
extern int expand_inline_calls_in_stmt();
extern il_node * expand_unsigned_float_assign();
extern il_node * expand_unsigned_to_float();
extern il_node * expression_root();
extern int extend_const_life_area_backward();
extern int fatal_error();
extern int fatal_error_exit();
extern int find_basename_offset();
extern int find_basic_induction_vars();
extern bblock * find_common_dominator();
extern int find_common_tails();
extern il_node * find_constant_value();
extern int find_derived_induction_vars();
extern int find_dt_opt_loops();
extern il_node * find_enclosing_stmt();
extern il_node * find_equal_constant();
extern il_node * find_equal_operator();
extern int find_identical_predecessor_blocks();
extern int find_inline_calls();
extern inline_map_entry * find_inline_map_entry();
extern int find_keyed_offset();
extern label_rec * find_label_record();
extern int find_loop_induction();
extern int find_loop_induction_in_block();
extern dutbl * find_single_definition();
extern switch_case * find_switch_case();
extern switch_table * find_switch_table();
extern int flatten_single_trip_loops();
extern il_node * float_div_by_const_to_mul();
extern uint fold_add_double();
extern uint fold_add_float();
extern uint fold_add_ldouble();
extern uint fold_add_unsigned();
extern uint fold_and_check_overflow();
extern uint fold_and_signed();
extern uint fold_and_unsigned();
extern uint fold_bnot_unsigned();
extern il_node * fold_constants();
extern int fold_div_double();
extern uint fold_div_float();
extern uint fold_div_ldouble();
extern int fold_div_unsigned();
extern int fold_double_eq();
extern char fold_double_ge();
extern char fold_double_gt();
extern char fold_double_le();
extern char fold_double_lt();
extern int fold_double_ne();
extern int fold_eq_unsigned();
extern int fold_float_eq();
extern char fold_float_ge();
extern char fold_float_gt();
extern char fold_float_le();
extern char fold_float_lt();
extern int fold_float_ne();
extern int fold_ge_signed();
extern int fold_ge_unsigned();
extern int fold_gt_unsigned();
extern uint fold_int_add();
extern uint fold_int_cmpl();
extern int fold_int_div();
extern int fold_int_eq();
extern int fold_int_gt();
extern int fold_int_le();
extern int fold_int_lt();
extern int fold_int_mod();
extern uint fold_int_mul();
extern int fold_int_ne();
extern uint fold_int_neg();
extern int fold_int_not();
extern uint fold_int_sub();
extern int fold_le_unsigned();
extern uint fold_lnot_double();
extern int fold_lnot_float();
extern uint fold_lnot_ldouble();
extern int fold_lnot_unsigned();
extern int fold_long_double_eq();
extern char fold_long_double_ge();
extern char fold_long_double_gt();
extern char fold_long_double_le();
extern char fold_long_double_lt();
extern int fold_long_double_ne();
extern int fold_lt_unsigned();
extern int fold_mod_unsigned();
extern uint fold_mul_double();
extern uint fold_mul_float();
extern uint fold_mul_ldouble();
extern uint fold_mul_unsigned();
extern int fold_ne_unsigned();
extern uint fold_neg_double();
extern uint fold_neg_float();
extern uint fold_neg_ldouble();
extern uint fold_neg_unsigned();
extern uint fold_or_signed();
extern uint fold_or_unsigned();
extern uint fold_shl_signed();
extern uint fold_shl_unsigned();
extern uint fold_shr_signed();
extern uint fold_shr_unsigned();
extern uint fold_sub_double();
extern uint fold_sub_float();
extern uint fold_sub_ldouble();
extern uint fold_sub_unsigned();
extern uint fold_xor_signed();
extern uint fold_xor_unsigned();
extern int forward_member_constant_store();
extern int free_all_bblocks();
extern int free_bblock();
extern int free_dag_node_list();
extern int free_def_tables_and_abort();
extern int free_du_tables();
extern int free_induction_tables();
extern int free_inline_calls();
extern int free_inline_group();
extern int free_list_cells();
extern int free_loop_tree();
extern int free_merge_tables();
extern int free_merge_tables_and_abort();
extern int free_node();
extern int free_node_blocks();
extern int free_register_allocation_tables();
extern int free_released_nodes();
extern int free_switch_tables();
extern int free_symbols();
extern int free_term_list();
extern int free_tree();
extern char * get_env_directory();
extern il_node * get_increment_target();
extern short get_lreg_symx();
extern int group_blocks_by_successor();
extern int has_side_effect_or_indirection();
extern int hash_common_expression_candidate();
extern int hoist_invariants_in_block();
extern int hoist_invariants_in_tree();
extern int hoist_loop_invariants();
extern int in_conditional_operator();
extern int induction_step();
extern int init_il_node_pool();
extern int initialize_optimizer();
extern int inline_calls_in_do();
extern int inline_calls_in_for();
extern int inline_calls_in_if();
extern int inline_calls_in_switch();
extern int inline_calls_in_while();
extern int inline_redirect_continue();
extern int inner_cast_kind_ok();
extern int inner_cast_rank_ok();
extern int insert_after();
extern int insert_before();
extern il_node * insert_entry_label();
extern int insert_in_loop_preheader();
extern int insert_induction_increment();
extern int insert_operands();
extern int insert_parameter_self_assignments();
extern int insert_parent();
extern int insert_two_if_nodes();
extern int install_signal_handlers();
extern il_node * instantiate_inline_body();
extern int invalidate_memory_leaf_values();
extern int invert_loop_to_guarded_do();
extern int is_builtin_name();
extern int is_condition_operand();
extern char is_conditionally_evaluated();
extern uint is_const_value();
extern int is_immediate_operand();
extern int is_mac_builtin_name();
extern int is_memory_safe_builtin();
extern char is_not_control_condition();
extern int is_sole_def_in_loop();
extern int join_related_webs();
extern il_node * last_operand();
extern il_node * last_statement_of_list();
extern int link_blocks_reverse_postorder();
extern int link_common_chain();
extern int link_def_use_webs();
extern int link_def_use_webs_in_tree();
extern int link_derived_induction();
extern int link_merged_block();
extern int link_node_blocks();
extern int link_ud_du_chains();
extern int load_inline_bodies();
extern int loop_tree_contains();
extern int lreg_conflicts_with_call();
extern il_node * lreg_node();
extern int lreg_ref_in_statement();
extern int lreg_spans_call();
extern il_node * make_empty_block();
extern il_node * make_goto_entry_label();
extern il_node * make_id_equals_const();
extern int * make_life_area_entry();
extern il_node * make_node();
extern char * make_temp_file_name();
extern il_node * make_unrolled_limit();
extern int mark_block_register_use();
extern int mark_const_uses_on_paths();
extern int mark_fr0_fmac_uses();
extern int mark_induction_variable();
extern int mark_referenced_functions();
extern int mark_referenced_functions_in_tree();
extern int mark_web_allocatable();
extern uint match_predecessor_lists();
extern int match_spec_compare();
extern int match_spec_load();
extern int match_spec_scale();
extern int match_spec_zero_test();
extern int match_statement_tails();
extern int materialize_constant_lreg();
extern int memory_lreg_frequency();
extern int merge_bound_lreg();
extern int merge_common_code();
extern int merge_common_tails();
extern int merge_identical_blocks();
extern il_node * merge_or_of_bit_tests();
extern char mirror_or_negate_relop();
extern int mk_cfg_do();
extern int mk_cfg_for();
extern int mk_cfg_if();
extern int mk_cfg_switch();
extern int mk_cfg_while();
extern int move_def_use_links();
extern int move_increment_out_of_do_test();
extern int move_positive_term_first();
extern il_node * narrow_bit_test_to_char();
extern il_node * narrow_compound_assignment();
extern il_node * narrow_expression_size();
extern int negate_multiword();
extern int negate_step_operator();
extern bblock * new_bblock();
extern il_node * new_const_node();
extern il_node * new_glabel_stmt();
extern inline_group * new_inline_group();
extern int new_label_number();
extern label_rec * new_label_record();
extern int new_leaf();
extern block_list * new_list_cell();
extern loop * new_loop();
extern il_node * new_node();
extern lreg * new_register_candidate();
extern uint new_symbol();
extern int new_symbol_number();
extern il_node * new_temp_id();
extern int new_temporary_leaf();
extern int new_web();
extern int node_type_rank();
extern il_node * nth_operand();
extern int number_expps();
extern int number_loops();
extern FILE * open_temp_file();
extern int open_work_files();
extern int operand_index();
extern il_node * opt_exp();
extern int opt_exp_all_blocks();
extern int opt_exp_block();
extern int optimize_all_block_expressions();
extern il_node * optimize_array_index();
extern int optimize_block_expressions();
extern il_node * optimize_expression_tree();
extern int optimize_function();
extern int optimize_loop_induction();
extern il_node * optimize_shift_chain();
extern int optimize_tail_calls();
extern int optimizer_main();
extern int order_params_stack_then_register();
extern il_node * overwrite_with_constant();
extern int pack_round_double();
extern uint pack_round_float();
extern uint parameter_register_index();
extern uint parameter_register_index_sh4();
extern int parent_is_control_statement();
extern int path_avoids_block();
extern int * pool_alloc();
extern int pool_free();
extern int pool_release_free_lists();
extern il_node * postfix_to_prefix_incdec();
extern int power_of_two_index();
extern int prepare_function_for_optimization();
extern int prepare_register_allocation();
extern int print_phase_banner();
extern int process_function_expressions_only();
extern int process_function_op0_inline();
extern int process_input_functions();
extern il_node * propagate_constants();
extern loop * prune_loops();
extern int push_list_item();
extern uint read_bytes();
extern uint read_count_or_fail();
extern int read_counted_string();
extern int read_cpp_block();
extern int read_function_info();
extern il_node * read_il_node();
extern il_node * read_il_operands();
extern il_node * read_il_tree();
extern int read_ila_bytes();
extern option_record * read_intermediate_file();
extern int read_loop_initial_value();
extern int read_loop_limit();
extern int read_loop_step();
extern int read_named_record_list();
extern int read_node_type();
extern int read_option_record();
extern int read_option_strings_and_lists();
extern int read_or_fail();
extern int read_record11_list();
extern int read_record12_list();
extern int read_scope_info();
extern int read_sized_string_list();
extern int read_string_list();
extern int read_string_list_c();
extern int read_switch_cases();
extern short read_switch_short();
extern int read_switch_table();
extern char read_symbol_byte_06();
extern int read_symbol_extension();
extern char read_symbol_kind();
extern short read_symbol_kind_short();
extern char * read_symbol_name();
extern char read_symbol_name_length();
extern int read_symbol_table();
extern char read_symbol_type();
extern int read_tagged_string_list();
extern int read_type_size();
extern il_node * reassociate_expression();
extern int rebuild_cfg_and_leaves();
extern int record_block_use();
extern int record_common_tail();
extern int record_defined_leaf();
extern int record_definition();
extern int record_identical_blocks();
extern int record_induction_use();
extern int record_register_variable_use();
extern int redirect_block_to_function_entry();
extern int reduce_induction_variable();
extern int reflect_register_numbers();
extern int * regalloc_alloc();
extern int remap_inlined_scope_members();
extern int remember_leafed_symbol();
extern int remove_temp_files();
extern int remove_unused_parameter_assignments();
extern int renumber_inline_body();
extern int reoptimize_loop_expressions();
extern int replace_and_free_node();
extern int replace_breaks_with_goto();
extern int replace_loop_test();
extern int replace_loop_test_copy();
extern int replace_node();
extern int replace_operand();
extern int replace_statement_with_zero();
extern int replace_subtrees_with_constant();
extern int replace_with_register_temp();
extern il_node * replicate_loop_body();
extern int report_error();
extern int report_fold_warnings();
extern int report_message();
extern int reset_il_node_pool();
extern int reset_inline_state();
extern int reset_symbol_leaf_numbers();
extern int resolve_argument_register_clashes();
extern int rewrite_loop_count_down();
extern int round_double_mantissa();
extern int round_float_mantissa();
extern int same_common_expression();
extern int save_input_tail();
extern int scan_derived_induction_expr();
extern int scan_tree_for_regalloc();
extern int select_env_var_names();
extern uchar select_index_type_for_range();
extern int select_loops_to_invert();
extern int set_expression_life();
extern int set_loop_step();
extern int set_node_lreg_number();
extern int set_value_used_flag();
extern int shift_to_power_of_two();
extern il_node * simplify_add();
extern il_node * simplify_add_sub_assign();
extern il_node * simplify_and_or_assign();
extern il_node * simplify_bitand_bitor();
extern il_node * simplify_bitxor();
extern il_node * simplify_cast();
extern il_node * simplify_conditional();
extern il_node * simplify_deref_address();
extern il_node * simplify_div();
extern il_node * simplify_div_assign();
extern il_node * simplify_equality();
extern il_node * simplify_identical_operands();
extern il_node * simplify_logical_and_or();
extern il_node * simplify_mod();
extern il_node * simplify_mod_assign();
extern il_node * simplify_mul();
extern il_node * simplify_mul_assign();
extern il_node * simplify_negate();
extern il_node * simplify_not();
extern il_node * simplify_relational();
extern il_node * simplify_self_assign();
extern il_node * simplify_shift();
extern il_node * simplify_shift_assign();
extern il_node * simplify_sub();
extern il_node * simplify_xor_assign();
extern int solve_live_variables();
extern int solve_reaching_definitions();
extern int sort_and_merge_ranges();
extern int sort_block_statics_by_refcnt();
extern int sort_life_areas();
extern int sort_lregs();
extern int sort_lregs_by_mreg();
extern int sort_lregs_by_profit();
extern int sort_reflect_list_by_frequency();
extern int sort_web_chain_by_pp();
extern char * source_file_name();
extern int special_change();
extern int special_change_body();
extern int start_common_chain();
extern ushort statement_pp();
extern int step_can_be_bypassed();
extern int step_def_unusable();
extern int stmt_clobbers_memory();
extern int stmt_modifies_operands();
extern int stmts_modify_expr();
extern int stock_NMSG_WRITE();
extern int stock_amsg_exit();
extern int stock_callnewh();
extern int * stock_calloc();
extern char ** stock_copy_environ();
extern uint stock_crtCompareStringA();
extern int stock_crtsetenv();
extern int stock_doexit();
extern int stock_dosmaperr();
extern int stock_exit();
extern int stock_findenv();
extern FILE * stock_fopen();
extern int stock_free();
extern char * stock_getenv();
extern int * stock_heap_alloc();
extern int stock_initterm();
extern int * stock_malloc();
extern uchar * stock_mbschr();
extern int stock_mbsnbicoll();
extern int stock_nh_malloc();
extern int * stock_realloc();
extern int stock_remove();
extern char * stock_strchr();
extern char * stock_strcpy();
extern char * stock_strdup();
extern uint stock_strlen();
extern char * stock_strncpy();
extern int stock_unlink();
extern int stock_wtomb_environ();
extern int strength_reduce_induction_vars();
extern int strip_negations();
extern int strip_operand_casts();
extern int sub_multiword();
extern int subtree_has_symbol_attr_2e();
extern int swap_operands();
extern int terminate_optimizer();
extern il_node * tree_contains_node();
extern int tree_has_conditional_op();
extern int tree_has_float();
extern char tree_has_no_other_var_ref();
extern int tree_has_temp_id();
extern uint trees_differ();
extern char trip_span_covers_step();
extern int try_auto_increment_access();
extern int type_arith_class();
extern uint type_limit();
extern int unlink_def_use_links();
extern int unlink_from_common_expression_chains();
extern uint unpack_double();
extern int unpack_float();
extern int unroll_counted_loops();
extern int unroll_loop_by_four();
extern int warn_uninlined_calls();
extern int weigh_common_expression_candidates();
extern int wrap_in_block_pair();
extern int wrap_stmt_in_scope();
extern uint write_bytes();
extern int write_counted_string();
extern int write_cpp_block();
extern int write_error_record();
extern int write_function_and_free();
extern int write_il_node();
extern int write_il_tree();
extern int write_ilb_bytes();
extern uint write_intermediate_file();
extern int write_lreg_expression_ranges();
extern int write_lreg_numbers();
extern int write_lreg_symbols();
extern int write_named_record_list();
extern int write_node_type();
extern int write_option_record();
extern int write_option_strings_and_lists();
extern int write_record11_list();
extern int write_record12_list();
extern int write_reg_header();
extern int write_reg_trailer();
extern int write_register_allocation_table();
extern int write_sized_string_list();
extern int write_string_list();
extern int write_string_list_c();
extern int write_switch_cases();
extern int write_switch_tables();
extern int write_symbol_aggregate_size();
extern int write_symbol_byte_06();
extern int write_symbol_bytes();
extern int write_symbol_class();
extern int write_symbol_class10_lists();
extern int write_symbol_class_short();
extern int write_symbol_file();
extern int write_symbol_function_info();
extern int write_symbol_init_info();
extern int write_symbol_name();
extern int write_symbol_name_length();
extern int write_symbol_type();
extern int write_tagged_string_list();

#define DAT_00433014 (*(unsigned char *)(g_sd + 0x1014))
#define DAT_00433020 (*(unsigned char *)(g_sd + 0x1020))
#define DAT_00433024 (*(unsigned char *)(g_sd + 0x1024))
#define DAT_00433028 (*(unsigned char *)(g_sd + 0x1028))
#define DAT_00434bd4 (*(unsigned char *)(g_sd + 0x2bd4))
#define DAT_004365d8 (*(unsigned char *)(g_sd + 0x45d8))
#define DAT_004365dc (*(unsigned char *)(g_sd + 0x45dc))
#define DAT_00436c60 (*(int *)(g_sd + 0x4c60))
#define DAT_00436c8c (*(int *)(g_sd + 0x4c8c))
#define DAT_00436cac (*(unsigned char *)(g_sd + 0x4cac))
#define DAT_00436e30 (*(int *)(g_sd + 0x4e30))
#define DAT_004371ea (*(short *)(g_sd + 0x51ea))
#define DAT_0043fc31 (*(unsigned char *)(g_sd + 0xdc31))
#define DAT_0043fca3 (*(unsigned char *)(g_sd + 0xdca3))
#define DAT_0043fca4 (*(unsigned char *)(g_sd + 0xdca4))
#define DAT_0043fcbc (*(int *)(g_sd + 0xdcbc))
#define DAT_0043feb0 (*(unsigned char *)(g_sd + 0xdeb0))
#define DAT_0043ff20 (*(unsigned char *)(g_sd + 0xdf20))
#define DAT_00458ee0 (*(unsigned char *)(g_sd + 0x26ee0))
#define PTR_PTR_00433afc (*(char * *)(g_sd + 0x1afc))
#define PTR_PTR_00433bf8 (*(unsigned char * *)(g_sd + 0x1bf8))
#define PTR___exit_00436354 (*(char * *)(g_sd + 0x4354))
#define PTR_s_Internal_error_00435f90 (*(char * *)(g_sd + 0x3f90))
#define _g_dag_unread_word1 (*(int *)(g_sd + 0x1e4fc))
#define _g_dag_unread_word2 (*(int *)(g_sd + 0x1e710))
#define _g_il_node_pool_count (*(int *)(g_sd + 0x1e4f4))
#define _g_iv_negated_count (*(int *)(g_sd + 0xdf70))
#define _g_loop_limit (*(int *)(g_sd + 0x267bc))
#define _g_spec_sym1 (*(int *)(g_sd + 0xe050))
#define _g_spec_sym2 (*(int *)(g_sd + 0xe052))
#define _stock_C_Exit_Done (*(int *)(g_sd + 0x40a4))
#define _stock_errno (*(int *)(g_sd + 0x4060))
#define _stock_stdout_cnt (*(int *)(g_sd + 0x40ec))
#define g_add_class_table (*(unsigned char *)(g_sd + 0x3e88))
#define g_b_chain (*(bblock * *)(g_sd + 0x267f8))
#define g_block_count (*(int *)(g_sd + 0x26ac0))
#define g_bn_chain (*(bblock * *)(g_sd + 0x26ef8))
#define g_builtin_names (*(char * *)(g_sd + 0x22d0))
#define g_call_list (*(node_cell * *)(g_sd + 0x164b0))
#define g_call_list_tail (*(node_cell * *)(g_sd + 0x51e4))
#define g_candidate_list_tail (*(lreg * *)(g_sd + 0x1626c))
#define g_cfg_break_jumps (*(block_list * *)(g_sd + 0x267b8))
#define g_cfg_continue_jumps (*(block_list * *)(g_sd + 0x26f0c))
#define g_cfg_cur_block (*(bblock * *)(g_sd + 0x26868))
#define g_cfg_cur_loop (*(loop * *)(g_sd + 0x2684c))
#define g_cfg_last_loop (*(loop * *)(g_sd + 0x1e728))
#define g_cfg_last_stmt (*(node_list * *)(g_sd + 0x267ec))
#define g_cfg_next_block (*(bblock * *)(g_sd + 0x26a70))
#define g_cfg_pending_jumps (*(block_list * *)(g_sd + 0x1e718))
#define g_cmnexp_hash (*(const_data * (*)[128])(g_sd + 0x16270))
#define g_code_merged (*(unsigned char *)(g_sd + 0x26ad4))
#define g_common_tail_buckets (*(int *)(g_sd + 0xe010))
#define g_const_data_list (*(const_data * *)(g_sd + 0x16498))
#define g_const_hash (*(node_cell * (*)[16])(g_sd + 0x1e740))
#define g_convert_table (*(unsigned char * *)(g_sd + 0x18f8))
#define g_cpp_block_size (*(short *)(g_sd + 0x27336))
#define g_cse_changed (*(char *)(g_sd + 0x267a1))
#define g_cse_cond_depth (*(char *)(g_sd + 0x1e4f0))
#define g_cse_const_hash (*(node_cell * (*)[16])(g_sd + 0x26800))
#define g_cse_has_goto_or_label (*(char *)(g_sd + 0x267f6))
#define g_cse_nesting (*(char *)(g_sd + 0x26858))
#define g_cse_split_first (*(il_node * *)(g_sd + 0x267d4))
#define g_cse_split_head (*(il_node * *)(g_sd + 0x26f04))
#define g_cse_variables (*(node_list * *)(g_sd + 0x267a4))
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))
#define g_current_lreg (*(lreg * *)(g_sd + 0x1e4c4))
#define g_dag_block (*(bblock * *)(g_sd + 0x1e724))
#define g_dag_unread_word2 (*(unsigned char *)(g_sd + 0x1e710))
#define g_debug_flags (*(unsigned int *)(g_sd + 0x267c0))
#define g_def_count (*(short *)(g_sd + 0x267ac))
#define g_def_nodes (*(il_node * (*)[256])(g_sd + 0x26f10))
#define g_defined_leaves (*(int *)(g_sd + 0x267a8))
#define g_div_class_table (*(unsigned char *)(g_sd + 0x3ec8))
#define g_do_test_changed (*(unsigned char *)(g_sd + 0x267d0))
#define g_dt_loop (*(loop * *)(g_sd + 0x26844))
#define g_dt_opt_changed (*(int *)(g_sd + 0x26acc))
#define g_du_tables (*(dutbl * *)(g_sd + 0x1e788))
#define g_dump_line_info (*(int *)(g_sd + 0xe058))
#define g_env_dir_buffer (*(unsigned char *)(g_sd + 0xdc30))
#define g_env_inc_name (*(char * *)(g_sd + 0x27324))
#define g_env_lib_name_1 (*(char * *)(g_sd + 0x27310))
#define g_env_lib_name_2 (*(char * *)(g_sd + 0x27314))
#define g_env_lib_name_3 (*(char * *)(g_sd + 0x2731c))
#define g_env_lib_name_4 (*(char * *)(g_sd + 0x27320))
#define g_env_tmp_name (*(char * *)(g_sd + 0x27318))
#define g_error_jmp_buf (*(unsigned char *)(g_sd + 0x26a80))
#define g_exit_block (*(bblock * *)(g_sd + 0x267cc))
#define g_expp_counter (*(int *)(g_sd + 0x1647c))
#define g_expr_hash (*(node_list * (*)[128])(g_sd + 0x26870))
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#define g_fatal_code_text (*(unsigned char *)(g_sd + 0xdc28))
#define g_file_name_buf (*(unsigned char *)(g_sd + 0xdb70))
#define g_first_chain_node (*(char *)(g_sd + 0x1e4d8))
#define g_float_arg_reg_limit (*(int *)(g_sd + 0x16470))
#define g_float_arg_regs (*(int *)(g_sd + 0x1649c))
#define g_float_reg_count (*(int *)(g_sd + 0x16268))
#define g_fmt_3d (*(unsigned char *)(g_sd + 0x35e8))
#define g_fold_op_table (*(unsigned char *)(g_sd + 0x1a68))
#define g_fold_warnings (*(short *)(g_sd + 0x26ef4))
#define g_fpr_alloc_order (*(unsigned char *)(g_sd + 0x22b0))
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#define g_function_aborted (*(int *)(g_sd + 0x2686c))
#define g_function_file_pos (*(int *)(g_sd + 0x1e4e4))
#define g_gpr_alloc_order (*(unsigned char *)(g_sd + 0x22a0))
#define g_has_goto (*(unsigned char *)(g_sd + 0x26840))
#define g_identical_block_buckets (*(int *)(g_sd + 0xdf80))
#define g_il_node_pool (*(il_node * *)(g_sd + 0x1e500))
#define g_il_op_operand_count (*(unsigned char *)(g_sd + 0x14f8))
#define g_in_builtin_call (*(char *)(g_sd + 0x267ae))
#define g_index_type_ranges (*(int *)(g_sd + 0x1854))
#define g_inline_block_map (*(inline_map_entry * (*)[20])(g_sd + 0xde60))
#define g_inline_call_list (*(inline_group * *)(g_sd + 0xdeb8))
#define g_inline_candidates_tail (*(inline_call * *)(g_sd + 0xdf28))
#define g_inline_cond_depth (*(int *)(g_sd + 0xdf2c))
#define g_inline_continue_label (*(short *)(g_sd + 0xde50))
#define g_inline_flags (*(unsigned char *)(g_sd + 0xdec0))
#define g_inline_groups (*(inline_group * *)(g_sd + 0xdec8))
#define g_inline_loop (*(il_node * *)(g_sd + 0xde54))
#define g_inline_new_labels (*(int *)(g_sd + 0xdebc))
#define g_inline_new_symbols (*(int *)(g_sd + 0xdeb4))
#define g_inline_node_free_list (*(il_node * *)(g_sd + 0x1e784))
#define g_inline_pass (*(unsigned int *)(g_sd + 0xdf24))
#define g_inline_scopes_changed (*(unsigned char *)(g_sd + 0xdec1))
#define g_inline_symbol_map (*(inline_map_entry * (*)[20])(g_sd + 0xded0))
#define g_input_tail_file (*(unsigned char * *)(g_sd + 0x2732c))
#define g_int_file_path (*(char * *)(g_sd + 0x27328))
#define g_int_reg_count (*(int *)(g_sd + 0x16494))
#define g_iv_copy_list (*(node_list * *)(g_sd + 0x3a00))
#define g_iv_count (*(int *)(g_sd + 0x267dc))
#define g_iv_cur_block (*(bblock * *)(g_sd + 0xdb64))
#define g_iv_negated_count (*(unsigned char *)(g_sd + 0xdf70))
#define g_iv_reduced_count (*(int *)(g_sd + 0x39f8))
#define g_iv_table (*(iv_entry (*)[4])(g_sd + 0xdf30))
#define g_iv_test_type_table (*(unsigned char *)(g_sd + 0x3a08))
#define g_iv_tested_count (*(int *)(g_sd + 0x39fc))
#define g_iv_update_stmt (*(il_node * *)(g_sd + 0x26ac4))
#define g_label_hash (*(label_rec * (*)[256])(g_sd + 0x26ae0))
#define g_last_loop_number (*(short *)(g_sd + 0x267f4))
#define g_last_warned_line (*(short *)(g_sd + 0x267e6))
#define g_leaf_cond_depth (*(int *)(g_sd + 0x51e0))
#define g_leaf_count (*(short *)(g_sd + 0x267e4))
#define g_leaf_def_hash (*(int *)(g_sd + 0x1e510))
#define g_leaf_table (*(leaf (*)[2049])(g_sd + 0x1e790))
#define g_leafed_symbols (*(int *)(g_sd + 0x1e4dc))
#define g_licm_pass (*(unsigned int *)(g_sd + 0x26848))
#define g_lifehash_buckets (*(lifetbl * (*)[8192])(g_sd + 0x164c0))
#define g_loop_count (*(short *)(g_sd + 0x267e8))
#define g_loop_init (*(int *)(g_sd + 0x267e0))
#define g_loop_limit (*(unsigned char *)(g_sd + 0x267bc))
#define g_loop_test (*(il_node * *)(g_sd + 0x26854))
#define g_loop_test_copy (*(il_node * *)(g_sd + 0x1e4f8))
#define g_loop_tree (*(loop * *)(g_sd + 0x267f0))
#define g_loops_flattened (*(char *)(g_sd + 0x267d8))
#define g_lreg_count (*(int *)(g_sd + 0x164ac))
#define g_lreg_list (*(lreg * *)(g_sd + 0x16264))
#define g_lreg_table (*(lreg * (*)[8192])(g_sd + 0xe260))
#define g_mac_builtin_names (*(char * *)(g_sd + 0x2398))
#define g_make_du (*(char *)(g_sd + 0x26850))
#define g_max_error_level (*(int *)(g_sd + 0x1e4e0))
#define g_mem_freq_list (*(mem_freq * *)(g_sd + 0x164a0))
#define g_mem_lreg_count (*(int *)(g_sd + 0x16474))
#define g_mem_object_lists (*(const_data * (*)[128])(g_sd + 0xe060))
#define g_memory_clobbered (*(int *)(g_sd + 0x2685c))
#define g_memory_refs (*(node_list * *)(g_sd + 0x1e780))
#define g_memory_safe_builtins (*(char * *)(g_sd + 0x3bb0))
#define g_merge_id (*(short *)(g_sd + 0xe002))
#define g_merge_match_depth (*(int *)(g_sd + 0xdf74))
#define g_merge_pair_count (*(int *)(g_sd + 0xdf78))
#define g_merge_whole_blocks (*(unsigned char *)(g_sd + 0xe000))
#define g_mode_rb (*(unsigned char *)(g_sd + 0x2f84))
#define g_mode_rb_plus (*(unsigned char *)(g_sd + 0x2f80))
#define g_mode_wb (*(unsigned char *)(g_sd + 0x14f0))
#define g_mul_class_table (*(unsigned char *)(g_sd + 0x3ea8))
#define g_negation_count (*(int *)(g_sd + 0x1e4d4))
#define g_next_lregno (*(int *)(g_sd + 0x16490))
#define g_noalloc_leaf_regs (*(int *)(g_sd + 0x16488))
#define g_node_alloc_hook (*(int *)(g_sd + 0x1e4ec))
#define g_node_block_count (*(int *)(g_sd + 0x5b60))
#define g_node_block_table (*(il_node * (*)[8192])(g_sd + 0x5b64))
#define g_node_free_list (*(il_node * *)(g_sd + 0x26864))
#define g_op_class (*(unsigned char *)(g_sd + 0x3320))
#define g_op_names (*(unsigned char * *)(g_sd + 0x2668))
#define g_op_names_upper (*(char * *)(g_sd + 0x1270))
#define g_opt_exp_identical_only (*(int *)(g_sd + 0x26f08))
#define g_opt_exp_pass (*(int *)(g_sd + 0x26ef0))
#define g_option_record (*(option_record * *)(g_sd + 0xdc20))
#define g_option_record_size (*(short *)(g_sd + 0x27338))
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#define g_options_for_errors (*(option_record * *)(g_sd + 0x27330))
#define g_pattern_rules (*(unsigned char *)(g_sd + 0x1c68))
#define g_phase_banners (*(unsigned char * *)(g_sd + 0x3dd0))
#define g_pid_digit_count (*(int *)(g_sd + 0x4040))
#define g_pool_bytes_in_use (*(int *)(g_sd + 0x1e504))
#define g_pool_classes (*(pool_class * *)(g_sd + 0x39f4))
#define g_pow2_table (*(unsigned char *)(g_sd + 0x3a88))
#define g_pp_count (*(int *)(g_sd + 0x16478))
#define g_preg_map_double (*(int *)(g_sd + 0x16480))
#define g_preg_map_float (*(int *)(g_sd + 0x164a8))
#define g_preg_map_general (*(int *)(g_sd + 0x16484))
#define g_reassoc_side_effect (*(unsigned int *)(g_sd + 0x1e4cc))
#define g_reg_file (*(unsigned char * *)(g_sd + 0x1e72c))
#define g_regalloc_block (*(bblock * *)(g_sd + 0x1648c))
#define g_regalloc_phase (*(int *)(g_sd + 0x164a4))
#define g_released_nodes (*(il_node * *)(g_sd + 0x1e4d0))
#define g_return_preds (*(block_list * *)(g_sd + 0x26ee4))
#define g_saved_label_count (*(short *)(g_sd + 0xdec6))
#define g_saved_switch_count (*(short *)(g_sd + 0xdecc))
#define g_saved_symbol_count (*(short *)(g_sd + 0xdec4))
#define g_single_iv_use (*(unsigned char *)(g_sd + 0x26851))
#define g_spec_index_sym (*(short *)(g_sd + 0xe054))
#define g_spec_sym1 (*(unsigned char *)(g_sd + 0xe050))
#define g_str_block_number_comma (*(unsigned char *)(g_sd + 0x168c))
#define g_str_char (*(unsigned char *)(g_sd + 0x2aec))
#define g_str_close_brace_newline (*(unsigned char *)(g_sd + 0x37c4))
#define g_str_close_bracket (*(unsigned char *)(g_sd + 0x2a70))
#define g_str_dot_tmp (*(int *)(g_sd + 0x4050))
#define g_str_empty (*(unsigned char *)(g_sd + 0x2650))
#define g_str_exit (*(unsigned char *)(g_sd + 0x1794))
#define g_str_func (*(unsigned char *)(g_sd + 0x2648))
#define g_str_ggg (*(unsigned char *)(g_sd + 0x2f5c))
#define g_str_int (*(unsigned char *)(g_sd + 0x2ae0))
#define g_str_long (*(unsigned char *)(g_sd + 0x2ad8))
#define g_str_loop_tree_bar (*(unsigned char *)(g_sd + 0x2d24))
#define g_str_mode_ab (*(unsigned char *)(g_sd + 0x3f94))
#define g_str_mode_wbplus (*(unsigned char *)(g_sd + 0x404c))
#define g_str_newline (*(unsigned char *)(g_sd + 0x15f8))
#define g_str_newline_indent (*(unsigned char *)(g_sd + 0x3fa4))
#define g_str_percent_02x (*(unsigned char *)(g_sd + 0x2a74))
#define g_str_percent_1d (*(unsigned char *)(g_sd + 0x1694))
#define g_str_percent_5d_colon (*(unsigned char *)(g_sd + 0x2f54))
#define g_str_percent_d (*(unsigned char *)(g_sd + 0x2bcc))
#define g_str_percent_s_close_bracket (*(unsigned char *)(g_sd + 0x2a84))
#define g_str_percent_s_comma (*(unsigned char *)(g_sd + 0x1688))
#define g_str_plus_percent_s (*(unsigned char *)(g_sd + 0x2a18))
#define g_str_semicolon_newline (*(unsigned char *)(g_sd + 0x2b3c))
#define g_str_setjmp (*(unsigned char *)(g_sd + 0x32b0))
#define g_str_space (*(unsigned char *)(g_sd + 0x3f98))
#define g_str_target_function_name (*(unsigned char *)(g_sd + 0x2438))
#define g_str_temp (*(int *)(g_sd + 0x3290))
#define g_str_temp_nul (*(unsigned char *)(g_sd + 0x3294))
#define g_str_temp_upper (*(int *)(g_sd + 0x2bd0))
#define g_str_tree_bar (*(unsigned char *)(g_sd + 0x2a1c))
#define g_str_tree_space (*(unsigned char *)(g_sd + 0x2a20))
#define g_str_ttt (*(unsigned char *)(g_sd + 0x3c1c))
#define g_str_void (*(unsigned char *)(g_sd + 0x2a94))
#define g_successor_groups (*(int *)(g_sd + 0xdfc0))
#define g_suppress_no_effect_warning (*(char *)(g_sd + 0x26ee8))
#define g_switch_block (*(bblock * *)(g_sd + 0x1e4e8))
#define g_switch_depth (*(int *)(g_sd + 0xdbf8))
#define g_switch_file (*(unsigned char * *)(g_sd + 0x1e734))
#define g_switch_has_default (*(short *)(g_sd + 0x267b0))
#define g_switch_number_stack (*(int *)(g_sd + 0xdc00))
#define g_switch_number_stack_m1 (*(unsigned char *)(g_sd + 0xdbfe))
#define g_switch_tables (*(switch_table * *)(g_sd + 0x267b4))
#define g_sym_file (*(unsigned char * *)(g_sd + 0x267c4))
#define g_symbol_count (*(int *)(g_sd + 0x1e71c))
#define g_symbol_limit (*(short *)(g_sd + 0xdec2))
#define g_symbol_table_modified (*(char *)(g_sd + 0x1e508))
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))
#define g_temp_counter (*(int *)(g_sd + 0x4048))
#define g_temp_file_count (*(int *)(g_sd + 0xdcb4))
#define g_temp_files (*(int *)(g_sd + 0xdcb8))
#define g_temp_name_buffer (*(char * *)(g_sd + 0x403c))
#define g_temp_name_pending (*(char * *)(g_sd + 0xdd0c))
#define g_temp_pid (*(int *)(g_sd + 0x4044))
#define g_temp_symx (*(short *)(g_sd + 0x1e720))
#define g_term_list (*(term * *)(g_sd + 0x1e4c8))
#define g_test_replace_ok (*(int *)(g_sd + 0xdb68))
#define g_tree_changed (*(int *)(g_sd + 0x26f00))
#define g_tree_dump_more (*(short *)(g_sd + 0x51e8))
#define g_tree_in_file (*(unsigned char * *)(g_sd + 0x26eec))
#define g_tree_out_file (*(unsigned char * *)(g_sd + 0x26860))
#define g_unroll_label_added (*(unsigned char *)(g_sd + 0x267a0))
#define g_use_count (*(short *)(g_sd + 0x267c8))
#define g_value_number (*(short *)(g_sd + 0x1e730))
#define g_version_mismatch (*(short *)(g_sd + 0x27334))
#define s_ADDRESS_CONST_004358a4 (*(char (*)[14])(g_sd + 0x38a4))
#define s_BRC_No__d_004337a4 (*(char (*)[11])(g_sd + 0x17a4))
#define s_B_d__00433620 (*(char (*)[6])(g_sd + 0x1620))
#define s_B_d__004337c8 (*(char (*)[6])(g_sd + 0x17c8))
#define s_CONST_DATA_00435948 (*(char (*)[11])(g_sd + 0x3948))
#define s_Copyright__c__1992_1996_Hitachi__00433220 (*(char (*)[76])(g_sd + 0x1220))
#define s_Current_Basic_Block_Def_00435110 (*(char (*)[24])(g_sd + 0x3110))
#define s_Current_Basic_Block_Gen_004350c8 (*(char (*)[24])(g_sd + 0x30c8))
#define s_Current_Basic_Block_In_00435074 (*(char (*)[23])(g_sd + 0x3074))
#define s_Current_Basic_Block_Kill_0043509c (*(char (*)[25])(g_sd + 0x309c))
#define s_Current_Basic_Block_Out_0043504c (*(char (*)[24])(g_sd + 0x304c))
#define s_Current_Basic_Block_Use_00435138 (*(char (*)[24])(g_sd + 0x3138))
#define s_DAG_chain_end_block_No___d_004353e0 (*(char (*)[29])(g_sd + 0x33e0))
#define s_DAG_chain_start_00435400 (*(char (*)[18])(g_sd + 0x3400))
#define s_DELETE_WEB__00435968 (*(char (*)[12])(g_sd + 0x3968))
#define s_ENTER_0043379c (*(char (*)[6])(g_sd + 0x179c))
#define s_FR0set_00434918 (*(char (*)[8])(g_sd + 0x2918))
#define s_LP_d__004337b0 (*(char (*)[7])(g_sd + 0x17b0))
#define s_MEMORY_ALLOCATED_00435954 (*(char (*)[17])(g_sd + 0x3954))
#define s_Microsoft_Visual_C___Runtime_Lib_00436c64 (*(char (*)[37])(g_sd + 0x4c64))
#define s_NODE___s_00435248 (*(char (*)[10])(g_sd + 0x3248))
#define s_NOT_DOMINATOR_004357f8 (*(char (*)[14])(g_sd + 0x37f8))
#define s_NULL_00434b28 (*(char (*)[7])(g_sd + 0x2b28))
#define s_NULL_00434e44 (*(char (*)[6])(g_sd + 0x2e44))
#define s_NUMBER_CONST_00435894 (*(char (*)[13])(g_sd + 0x3894))
#define s_No__d__00433660 (*(char (*)[8])(g_sd + 0x1660))
#define s_Runtime_Error__Program__00436c90 (*(char (*)[28])(g_sd + 0x4c90))
#define s_SHCPP_INC_00435fec (*(char (*)[10])(g_sd + 0x3fec))
#define s_SHCPP_LIB_00435fe0 (*(char (*)[10])(g_sd + 0x3fe0))
#define s_SHCPP_TMP_00435fd4 (*(char (*)[10])(g_sd + 0x3fd4))
#define s_SHC_INC_00436008 (*(char (*)[8])(g_sd + 0x4008))
#define s_SHC_LIB_00436000 (*(char (*)[8])(g_sd + 0x4000))
#define s_SHC_TMP_00435ff8 (*(char (*)[8])(g_sd + 0x3ff8))
#define s_SH_SERIES_C_Compiler_Ver__5_0_Re_004331f0 (*(char (*)[44])(g_sd + 0x11f0))
#define s_Stopper_Error_00435c50 (*(char (*)[15])(g_sd + 0x3c50))
#define s_WEB_CHAIN_00435974 (*(char (*)[10])(g_sd + 0x3974))
#define s__08x_00435798 (*(char (*)[6])(g_sd + 0x3798))
#define s__0____00435f9c (*(char (*)[7])(g_sd + 0x3f9c))
#define s__5d__00434e24 (*(char (*)[6])(g_sd + 0x2e24))
#define s__8X__8d__8X__8X__8X__8d__s_00435464 (*(char (*)[29])(g_sd + 0x3464))
#define s__LASTUSE__00434930 (*(char (*)[10])(g_sd + 0x2930))
#define s___00434f48 (*(char (*)[12])(g_sd + 0x2f48))
#define s___004357d4 (*(char (*)[17])(g_sd + 0x37d4))
#define s___004358b4 (*(char (*)[20])(g_sd + 0x38b4))
#define s___02x__00434ad0 (*(char (*)[7])(g_sd + 0x2ad0))
#define s___3d__3d__004357c8 (*(char (*)[10])(g_sd + 0x37c8))
#define s___4d__4d___15s__5d__04X__010lX___004351a8 (*(char (*)[39])(g_sd + 0x31a8))
#define s___4d____13s___5d__04X__08lX__08l_00434ba8 (*(char (*)[36])(g_sd + 0x2ba8))
#define s___4s__4s___15s__5s__04X__010lX___00435180 (*(char (*)[39])(g_sd + 0x3180))
#define s___6d__6d__6X__00435504 (*(char (*)[15])(g_sd + 0x3504))
#define s___CUR_0x_08x__00434d14 (*(char (*)[15])(g_sd + 0x2d14))
#define s___CUR_0x_08x__blk_0x_08x____d_____0043569c (*(char (*)[52])(g_sd + 0x369c))
#define s___CUR_number__d__address_0x_08x_00434ec4 (*(char (*)[33])(g_sd + 0x2ec4))
#define s___LF_CNDASS_00434b50 (*(char (*)[13])(g_sd + 0x2b50))
#define s___LF_EXPVOL_00434b70 (*(char (*)[13])(g_sd + 0x2b70))
#define s___LF_IMPVOL_00434b60 (*(char (*)[13])(g_sd + 0x2b60))
#define s___LF_INDVAR_00434b80 (*(char (*)[13])(g_sd + 0x2b80))
#define s___LF_NODEF_00434b90 (*(char (*)[12])(g_sd + 0x2b90))
#define s___LF_STATIC_00434b40 (*(char (*)[13])(g_sd + 0x2b40))
#define s___No___id_name__symno_flag__gen___00434bd8 (*(char (*)[53])(g_sd + 0x2bd8))
#define s___No__b_No__id_name__symno_flag__004351d0 (*(char (*)[60])(g_sd + 0x31d0))
#define s____08x__08x__08x__08x__08x__08x___00434d7c (*(char (*)[49])(g_sd + 0x2d7c))
#define s____0x_08x_lregno__d__pregno__d__s_0043591c (*(char (*)[41])(g_sd + 0x391c))
#define s_____Basic_Block_No_0ld_____004350f0 (*(char (*)[30])(g_sd + 0x30f0))
#define s_____Basic_Block_No_0ld_____00435160 (*(char (*)[31])(g_sd + 0x3160))
#define s_____LEAF_TABLE_____00434c48 (*(char (*)[38])(g_sd + 0x2c48))
#define s_____LOGICAL_REGISTER_LIST________00435744 (*(char (*)[38])(g_sd + 0x3744))
#define s_____Make_Block_NO_ld_DEF_____00435028 (*(char (*)[33])(g_sd + 0x3028))
#define s_____Make_Block_NO_ld_KILL_____00435004 (*(char (*)[34])(g_sd + 0x3004))
#define s_____REGISTER_ALLOCCATION_TABLE___00435544 (*(char (*)[37])(g_sd + 0x3544))
#define s______REGISTER_ALLOCATION_NOT_RUN_00434460 (*(char (*)[39])(g_sd + 0x2460))
#define s_______0043573c (*(char (*)[6])(g_sd + 0x373c))
#define s____________00434c70 (*(char (*)[12])(g_sd + 0x2c70))
#define s______________004342c0 (*(char (*)[13])(g_sd + 0x22c0))
#define s______________________DU_CHAIN_TA_00435254 (*(char (*)[60])(g_sd + 0x3254))
#define s_______________________TREE_DUMP__0043487c (*(char (*)[56])(g_sd + 0x287c))
#define s________________________0043552c (*(char (*)[24])(g_sd + 0x352c))
#define s__________________________________00434c10 (*(char (*)[53])(g_sd + 0x2c10))
#define s__________________________________00434ee8 (*(char (*)[42])(g_sd + 0x2ee8))
#define s__________________________________0043520c (*(char (*)[60])(g_sd + 0x320c))
#define s__________________________________004356f0 (*(char (*)[74])(g_sd + 0x36f0))
#define s__________freqsort_end__________00435614 (*(char (*)[32])(g_sd + 0x3614))
#define s__________freqsort_start__________00435634 (*(char (*)[34])(g_sd + 0x3634))
#define s__________mregsort_end__________00435658 (*(char (*)[32])(g_sd + 0x3658))
#define s__________mregsort_start__________00435678 (*(char (*)[34])(g_sd + 0x3678))
#define s__________reflect_end__________004355c8 (*(char (*)[31])(g_sd + 0x35c8))
#define s__________reflect_start__________004355f0 (*(char (*)[33])(g_sd + 0x35f0))
#define s________memid_freq________00435b94 (*(char (*)[26])(g_sd + 0x3b94))
#define s_______b_chain_004337b8 (*(char (*)[16])(g_sd + 0x17b8))
#define s_______f_chain_004337d0 (*(char (*)[17])(g_sd + 0x17d0))
#define s_______loop_tbl_______00433638 (*(char (*)[22])(g_sd + 0x1638))
#define s______s_____00433ed0 (*(char (*)[24])(g_sd + 0x1ed0))
#define s_____st__2d_en__3d__00435590 (*(char (*)[25])(g_sd + 0x3590))
#define s____child___LP_d_0043372c (*(char (*)[21])(g_sd + 0x172c))
#define s____domlst___00433810 (*(char (*)[17])(g_sd + 0x1810))
#define s____exit___B_d_00433758 (*(char (*)[20])(g_sd + 0x1758))
#define s____fath___LP_d_00433714 (*(char (*)[21])(g_sd + 0x1714))
#define s____flag___00433698 (*(char (*)[16])(g_sd + 0x1698))
#define s____front___LP_d_004336e4 (*(char (*)[21])(g_sd + 0x16e4))
#define s____ilnode___004335fc (*(char (*)[16])(g_sd + 0x15fc))
#define s____lpnumber_LP_d_004337f8 (*(char (*)[22])(g_sd + 0x17f8))
#define s____lpnumber__004337e4 (*(char (*)[18])(g_sd + 0x17e4))
#define s____lstep____d_004336d0 (*(char (*)[19])(g_sd + 0x16d0))
#define s____nestcnt___d_004336a8 (*(char (*)[19])(g_sd + 0x16a8))
#define s____next___LP_d_004336fc (*(char (*)[21])(g_sd + 0x16fc))
#define s____out___08x__08x__08x__08x__08x_00434d48 (*(char (*)[49])(g_sd + 0x2d48))
#define s____pre___B_d_00433744 (*(char (*)[20])(g_sd + 0x1744))
#define s____prelst___00433838 (*(char (*)[17])(g_sd + 0x1838))
#define s____repet____d_004336bc (*(char (*)[19])(g_sd + 0x16bc))
#define s____start___B_d_0043376c (*(char (*)[20])(g_sd + 0x176c))
#define s____suclst___00433824 (*(char (*)[17])(g_sd + 0x1824))
#define s____tcount____d_0043360c (*(char (*)[20])(g_sd + 0x160c))
#define s____type____s_00433780 (*(char (*)[19])(g_sd + 0x1780))
#define s___b_trelst__00434e18 (*(char (*)[12])(g_sd + 0x2e18))
#define s___bakbind_at_0x_08x_0043576c (*(char (*)[21])(g_sd + 0x376c))
#define s___basic_block_table_dump__depth__00434f14 (*(char (*)[52])(g_sd + 0x2f14))
#define s___bind_at_0x_08x_00435784 (*(char (*)[18])(g_sd + 0x3784))
#define s___bn_next__00434e2c (*(char (*)[11])(g_sd + 0x2e2c))
#define s___chained_nodes___004358c8 (*(char (*)[19])(g_sd + 0x38c8))
#define s___clashed_lregs___004357a0 (*(char (*)[19])(g_sd + 0x37a0))
#define s___contents__s__value__d_00435878 (*(char (*)[25])(g_sd + 0x3878))
#define s___d_in___08x__08x__08x__08x__08x_00434de4 (*(char (*)[49])(g_sd + 0x2de4))
#define s___dominator_block_No____00435808 (*(char (*)[25])(g_sd + 0x3808))
#define s___dominator_type___EX_DOM_00435824 (*(char (*)[26])(g_sd + 0x3824))
#define s___dominator_type___NO_DOM_0043585c (*(char (*)[26])(g_sd + 0x385c))
#define s___dominator_type___SELF_DOM_00435840 (*(char (*)[28])(g_sd + 0x3840))
#define s___exp_area_____004357b4 (*(char (*)[16])(g_sd + 0x37b4))
#define s___l_in___08x__08x__08x__08x__08x_00434db0 (*(char (*)[49])(g_sd + 0x2db0))
#define s___life_area_____004357e8 (*(char (*)[16])(g_sd + 0x37e8))
#define s___local_static_datas__d_00434d2c (*(char (*)[26])(g_sd + 0x2d2c))
#define s___loop_table_dump_____s____00434c7c (*(char (*)[35])(g_sd + 0x2c7c))
#define s___lptbl_0x_08x_00434e9c (*(char (*)[15])(g_sd + 0x2e9c))
#define s___prelist__00434e38 (*(char (*)[11])(g_sd + 0x2e38))
#define s___priori__d__profit__d_004358dc (*(char (*)[25])(g_sd + 0x38dc))
#define s___s__00435980 (*(char (*)[6])(g_sd + 0x3980))
#define s___startcfg_0x_08x____d____exitcf_00434ca0 (*(char (*)[70])(g_sd + 0x2ca0))
#define s___startexpp__d__endexpp__d_00434e80 (*(char (*)[27])(g_sd + 0x2e80))
#define s___startpp__d__endpp__d_00434eac (*(char (*)[23])(g_sd + 0x2eac))
#define s___suclist__00434e4c (*(char (*)[11])(g_sd + 0x2e4c))
#define s___symno__d__leafno__d__name___s__004358f8 (*(char (*)[34])(g_sd + 0x38f8))
#define s___usefreg_0x_08x_00434e58 (*(char (*)[18])(g_sd + 0x2e58))
#define s___usepreg_0x_08x_00434e6c (*(char (*)[18])(g_sd + 0x2e6c))
#define s___web_chain_print___s____004356d0 (*(char (*)[30])(g_sd + 0x36d0))
#define s__builtin_asm_00434050 (*(char (*)[16])(g_sd + 0x2050))
#define s__builtin_strcmp_0043426c (*(char (*)[16])(g_sd + 0x226c))
#define s__builtin_trapa_004340b4 (*(char (*)[16])(g_sd + 0x20b4))
#define s__builtin_trapa_svc_004340a0 (*(char (*)[20])(g_sd + 0x20a0))
#define s__lregno_pregno__type___00435514 (*(char (*)[24])(g_sd + 0x3514))
#define s__num__2d______004355ac (*(char (*)[25])(g_sd + 0x35ac))
#define s__s_d__d_00436058 (*(char (*)[8])(g_sd + 0x4058))
#define s_after_blockreg_004343ac (*(char (*)[15])(g_sd + 0x23ac))
#define s_after_cp_lpblk_00433628 (*(char (*)[15])(g_sd + 0x1628))
#define s_after_esp_optimize_00435298 (*(char (*)[21])(g_sd + 0x3298))
#define s_after_glbx_cnt_tree_00435be0 (*(char (*)[20])(g_sd + 0x3be0))
#define s_after_loopflat_E__004334b4 (*(char (*)[18])(g_sd + 0x14b4))
#define s_after_loopflat_S__004334c8 (*(char (*)[18])(g_sd + 0x14c8))
#define s_after_merge_tree_00435988 (*(char (*)[17])(g_sd + 0x3988))
#define s_after_physicalreg_00434404 (*(char (*)[18])(g_sd + 0x2404))
#define s_after_spec_chg_tree_00435484 (*(char (*)[20])(g_sd + 0x3484))
#define s_array_00434a9c (*(char (*)[6])(g_sd + 0x2a9c))
#define s_asmno__d_004349b0 (*(char (*)[10])(g_sd + 0x29b0))
#define s_asmsize__d_004349a4 (*(char (*)[12])(g_sd + 0x29a4))
#define s_bbnd_free_00433668 (*(char (*)[11])(g_sd + 0x1668))
#define s_before_lp_flat___004334dc (*(char (*)[17])(g_sd + 0x14dc))
#define s_blkflg_ON_0043496c (*(char (*)[11])(g_sd + 0x296c))
#define s_boff__d_bsiz__d_00434a24 (*(char (*)[17])(g_sd + 0x2a24))
#define s_c__08x_s__08x_f__08x_n__08x_004348d4 (*(char (*)[44])(g_sd + 0x28d4))
#define s_cmnexp__08x_004348c4 (*(char (*)[13])(g_sd + 0x28c4))
#define s_cnt_expblk_00433e78 (*(char (*)[11])(g_sd + 0x1e78))
#define s_const_00434b00 (*(char (*)[8])(g_sd + 0x2b00))
#define s_cont__d_00435b58 (*(char (*)[9])(g_sd + 0x3b58))
#define s_d_array___08lX_00435128 (*(char (*)[16])(g_sd + 0x3128))
#define s_double_00434ac0 (*(char (*)[7])(g_sd + 0x2ac0))
#define s_dt_opt_end_00434fbc (*(char (*)[11])(g_sd + 0x2fbc))
#define s_dt_opt_end_00434fc8 (*(char (*)[12])(g_sd + 0x2fc8))
#define s_dt_opt_start_00434fd4 (*(char (*)[13])(g_sd + 0x2fd4))
#define s_dt_opt_start_00434fe4 (*(char (*)[14])(g_sd + 0x2fe4))
#define s_expp__d_00434958 (*(char (*)[9])(g_sd + 0x2958))
#define s_filn__d_line__u_listno__d_004349fc (*(char (*)[27])(g_sd + 0x29fc))
#define s_flag2_0x_04x_00434920 (*(char (*)[14])(g_sd + 0x2920))
#define s_flag_0x_04x_0043493c (*(char (*)[13])(g_sd + 0x293c))
#define s_flag___0_00434b9c (*(char (*)[9])(g_sd + 0x2b9c))
#define s_float_00434ac8 (*(char (*)[6])(g_sd + 0x2ac8))
#define s_folding_00433ec8 (*(char (*)[8])(g_sd + 0x1ec8))
#define s_folding_change_00433eb8 (*(char (*)[15])(g_sd + 0x1eb8))
#define s_free_dpvtp__x_00435424 (*(char (*)[16])(g_sd + 0x3424))
#define s_free_dutbl__x_00435434 (*(char (*)[16])(g_sd + 0x3434))
#define s_free_lptbl_LP_d_00433674 (*(char (*)[18])(g_sd + 0x1674))
#define s_free_upvtp__x_00435414 (*(char (*)[16])(g_sd + 0x3414))
#define s_funcname__s_00434ff4 (*(char (*)[13])(g_sd + 0x2ff4))
#define s_g_array___08lX_004350e0 (*(char (*)[16])(g_sd + 0x30e0))
#define s_i_array___08lX_0043508c (*(char (*)[16])(g_sd + 0x308c))
#define s_invno__d_00434900 (*(char (*)[10])(g_sd + 0x2900))
#define s_ivno__d_0043490c (*(char (*)[9])(g_sd + 0x290c))
#define s_jdgdevlop_end_00434f88 (*(char (*)[15])(g_sd + 0x2f88))
#define s_jdgdevlop_start_00434f98 (*(char (*)[16])(g_sd + 0x2f98))
#define s_jdgdevlop_start_00434fa8 (*(char (*)[17])(g_sd + 0x2fa8))
#define s_k_array___08lX_004350b8 (*(char (*)[16])(g_sd + 0x30b8))
#define s_lastnd___00434b30 (*(char (*)[9])(g_sd + 0x2b30))
#define s_leaf_table_gen_00435c30 (*(char (*)[15])(g_sd + 0x3c30))
#define s_leaf_table_use_00435c20 (*(char (*)[15])(g_sd + 0x3c20))
#define s_level_road_004359b0 (*(char (*)[11])(g_sd + 0x39b0))
#define s_level_road_change_0043599c (*(char (*)[18])(g_sd + 0x399c))
#define s_lifehash_________________________004354d0 (*(char (*)[51])(g_sd + 0x34d0))
#define s_lifetbl__d___d__004354b8 (*(char (*)[21])(g_sd + 0x34b8))
#define s_long_double_00434ab4 (*(char (*)[12])(g_sd + 0x2ab4))
#define s_loop_ind_1_asndp_00435b30 (*(char (*)[17])(g_sd + 0x3b30))
#define s_loop_ind_2_asndp_00435b1c (*(char (*)[17])(g_sd + 0x3b1c))
#define s_loop_ind_3_asndp_00435b08 (*(char (*)[17])(g_sd + 0x3b08))
#define s_lp_flag_0x_08x_00434ce8 (*(char (*)[16])(g_sd + 0x2ce8))
#define s_lreg__d_004349d4 (*(char (*)[9])(g_sd + 0x29d4))
#define s_lregsort__d__d__d__00435b44 (*(char (*)[19])(g_sd + 0x3b44))
#define s_mk_cfg_after_00433650 (*(char (*)[13])(g_sd + 0x1650))
#define s_mk_def_00435c40 (*(char (*)[7])(g_sd + 0x3c40))
#define s_mk_kill_00435c48 (*(char (*)[8])(g_sd + 0x3c48))
#define s_mkweb_after_web_00434488 (*(char (*)[16])(g_sd + 0x2488))
#define s_ms_leaf__d_004349c8 (*(char (*)[12])(g_sd + 0x29c8))
#define s_nestcnt__d__lpnumber__d__00434cf8 (*(char (*)[26])(g_sd + 0x2cf8))
#define s_nfiln__d_00434984 (*(char (*)[10])(g_sd + 0x2984))
#define s_nleaf__d_004349bc (*(char (*)[10])(g_sd + 0x29bc))
#define s_nline__u_00434978 (*(char (*)[10])(g_sd + 0x2978))
#define s_node_val_no_cmnexp_refchn_refcnt_004353a0 (*(char (*)[64])(g_sd + 0x33a0))
#define s_o_array___08lX_00435064 (*(char (*)[16])(g_sd + 0x3064))
#define s_ofst__d_00434a38 (*(char (*)[9])(g_sd + 0x2a38))
#define s_op0inline_read_tree_004334a0 (*(char (*)[20])(g_sd + 0x14a0))
#define s_op0inline_write_tree_00433488 (*(char (*)[21])(g_sd + 0x1488))
#define s_opt_array_cahge_00435bf8 (*(char (*)[16])(g_sd + 0x3bf8))
#define s_opt_exp_after_00433e68 (*(char (*)[14])(g_sd + 0x1e68))
#define s_opt_shift_004359e8 (*(char (*)[10])(g_sd + 0x39e8))
#define s_opt_shift_chnage_004359d4 (*(char (*)[17])(g_sd + 0x39d4))
#define s_patren_matching_end_004352b8 (*(char (*)[20])(g_sd + 0x32b8))
#define s_patren_matching_start_004352cc (*(char (*)[22])(g_sd + 0x32cc))
#define s_pointer_00434aac (*(char (*)[8])(g_sd + 0x2aac))
#define s_pp__d_00434964 (*(char (*)[7])(g_sd + 0x2964))
#define s_read_tree_0043347c (*(char (*)[10])(g_sd + 0x147c))
#define s_refchn__08x_004348b4 (*(char (*)[13])(g_sd + 0x28b4))
#define s_refcnt__d_0043494c (*(char (*)[11])(g_sd + 0x294c))
#define s_register_allocation_after_loop_t_004343bc (*(char (*)[37])(g_sd + 0x23bc))
#define s_register_allocation_after_tree_004343e4 (*(char (*)[31])(g_sd + 0x23e4))
#define s_register_allocation_before_tree_00434418 (*(char (*)[32])(g_sd + 0x2418))
#define s_relnode__08x__name__s_004359bc (*(char (*)[23])(g_sd + 0x39bc))
#define s_set_block_gen__08x_def_no__d_00435444 (*(char (*)[31])(g_sd + 0x3444))
#define s_set_block_use__08x_use_no__d_00434f60 (*(char (*)[31])(g_sd + 0x2f60))
#define s_setdata__d_pregno__d_lregno__d_f_00435b64 (*(char (*)[45])(g_sd + 0x3b64))
#define s_setexlife_1_00435584 (*(char (*)[12])(g_sd + 0x3584))
#define s_setexlife_2_00435578 (*(char (*)[12])(g_sd + 0x3578))
#define s_setexlife_3_0043556c (*(char (*)[12])(g_sd + 0x356c))
#define s_short_00434ae4 (*(char (*)[6])(g_sd + 0x2ae4))
#define s_short_size_change_00435c08 (*(char (*)[18])(g_sd + 0x3c08))
#define s_size__d_00434990 (*(char (*)[9])(g_sd + 0x2990))
#define s_str_00433e84 (*(char (*)[52])(g_sd + 0x1e84))
#define s_str_00434868 (*(char (*)[19])(g_sd + 0x2868))
#define s_str_00434b10 (*(char (*)[10])(g_sd + 0x2b10))
#define s_str_00434b1c (*(char (*)[10])(g_sd + 0x2b1c))
#define s_str_004352e4 (*(char (*)[26])(g_sd + 0x32e4))
#define s_str_00435300 (*(char (*)[28])(g_sd + 0x3300))
#define s_str_00436cb0 (*(char (*)[24])(g_sd + 0x4cb0))
#define s_struct_00434aa4 (*(char (*)[7])(g_sd + 0x2aa4))
#define s_symx__d_004349f0 (*(char (*)[9])(g_sd + 0x29f0))
#define s_symx__d___s___004349e0 (*(char (*)[15])(g_sd + 0x29e0))
#define s_tail___0043499c (*(char (*)[8])(g_sd + 0x299c))
#define s_tend__d_offs__d_00434a44 (*(char (*)[17])(g_sd + 0x2a44))
#define s_type__00434b08 (*(char (*)[7])(g_sd + 0x2b08))
#define s_u_array___08lX_00435150 (*(char (*)[16])(g_sd + 0x3150))
#define s_unsigned_00434a88 (*(char (*)[10])(g_sd + 0x2a88))
#define s_used_lreg_0x_08x___d___00435498 (*(char (*)[32])(g_sd + 0x3498))
#define s_val__00434a7c (*(char (*)[6])(g_sd + 0x2a7c))
#define s_val__d__00434a58 (*(char (*)[9])(g_sd + 0x2a58))
#define s_val__u__00434a64 (*(char (*)[9])(g_sd + 0x2a64))
#define s_volatile_00434af4 (*(char (*)[12])(g_sd + 0x2af4))
#define s_write_tree_00433470 (*(char (*)[11])(g_sd + 0x1470))
#define stock_app_type (*(int *)(g_sd + 0x435c))
#define stock_compare_string_mode (*(int *)(g_sd + 0x4ef8))
#define stock_crtheap (*(int *)(g_sd + 0x2733c))
#define stock_doserrno (*(unsigned int *)(g_sd + 0x4064))
#define stock_environ (*(int *)(g_sd + 0x4088))
#define stock_environ_initial (*(int *)(g_sd + 0x408c))
#define stock_error_mode (*(int *)(g_sd + 0x4358))
#define stock_errtable (*(int *)(g_sd + 0x4cc8))
#define stock_exitflag (*(unsigned char *)(g_sd + 0x40a0))
#define stock_lc_codepage (*(unsigned int *)(g_sd + 0x45f8))
#define stock_mbcodepage (*(unsigned int *)(g_sd + 0x447c))
#define stock_mbctype (*(int *)(g_sd + 0x4378))
#define stock_mblcid (*(unsigned int *)(g_sd + 0x4480))
#define stock_newmode (*(int *)(g_sd + 0x48dc))
#define stock_onexitbegin (*(int *)(g_sd + 0x28464))
#define stock_onexitend (*(int *)(g_sd + 0x28460))
#define stock_pioinfo (*(int *)(g_sd + 0x27350))
#define stock_pnhHeap (*(int *)(g_sd + 0xdd14))
#define stock_rterrs (*(int *)(g_sd + 0x4bd8))
#define stock_stderr (*(unsigned char *)(g_sd + 0x4108))
#define stock_stdout (*(int *)(g_sd + 0x40e8))
#define stock_wenviron (*(int *)(g_sd + 0x4090))

#endif
