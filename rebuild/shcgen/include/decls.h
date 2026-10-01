#ifndef DECLS_H
#define DECLS_H
#include "ghidra_stubs.h"
#include "stage_types.h"

/* the stock data image (scaffold-rebuild.py): data globals are lvalues at their stock offsets */
extern unsigned char g_sd[];
#define SD(a) ((unsigned int)(g_sd + ((unsigned int)(a) - 0x440000u)))

extern size_t _strncnt();
extern int add_multiword();
extern int add_pool_literal();
extern int advance_sud_location_counter();
extern int align_sud_location_counter();
extern short alloc_descending_extended_reg();
extern short alloc_descending_general_reg();
extern short alloc_descending_paired_reg();
extern short alloc_extended_reg_from_low_mask();
extern int * alloc_from_chunks();
extern gen_node * alloc_gen_node();
extern short alloc_general_reg_from_low_mask();
extern short alloc_paired_reg_from_low_mask();
extern int * alloc_zeroed();
extern int allocate_local_frame_offset();
extern int allocate_static_variables_and_write_sud();
extern int allocate_temp_frame_slot();
extern int append_sud_bytes();
extern int apply_template_operand_constraints();
extern int apply_template_to_node();
extern int assign_argument_registers();
extern int assign_block_local_storage();
extern int assign_condition_value_registers();
extern int assign_function_storage();
extern int assign_lreg_storage();
extern int assign_move_entry_registers();
extern int assign_parameter_home();
extern int assign_parameter_storage();
extern int assign_template_slot_registers();
extern gen_node * attach_ilb_argument();
extern gen_node * attach_ilb_argument_end();
extern gen_node * attach_ilb_block();
extern gen_node * attach_ilb_block_end();
extern gen_node * attach_ilb_file_end();
extern gen_node * attach_ilb_function();
extern gen_node * attach_ilb_jump_statement();
extern gen_node * attach_ilb_leaf_operand();
extern gen_node * attach_ilb_node();
extern gen_node * attach_ilb_operator();
extern gen_node * attach_ilb_statement();
extern int begin_function_code();
extern gen_node * begin_ilb_file();
extern int begin_sud_dc_record();
extern int bit_field_byte_offset();
extern int bit_field_word_offset();
extern int call_arguments_use_stack();
extern int check_builtin_immediate_argument();
extern int check_request_read_result();
extern int check_request_write_result();
extern int check_trapa_svc_arguments();
extern int choose_call_registers();
extern short choose_float_register();
extern short choose_float_register_pair();
extern short choose_general_register();
extern ushort choose_move_entry_register();
extern int classify_add_operands();
extern short classify_address_operand();
extern short classify_div_operands();
extern int classify_indexed_address_operands();
extern int classify_mul_operands();
extern int clear_pool_literal_table();
extern int close_and_delete_temp_files();
extern int close_stage_files();
extern int collect_macro_operand_list();
extern label_ref * combine_label_ref_lists();
extern short compare_double_constants();
extern short compare_float_constants();
extern int compare_multiword();
extern int compute_record_code_size();
extern int configure_signal_handlers();
extern int constant_condition_is_zero();
extern uint convert_double_to_float();
extern ea * copy_ea();
extern int copy_ea_into();
extern label_ref * copy_label_ref_list();
extern int copy_request_trailer_from_temp();
extern int copy_words();
extern int count_clear_mask_bits();
extern short count_constant_shift_steps();
extern int count_deref_use();
extern int count_indexed_address_operands();
extern short count_label_ref_markers();
extern int count_label_refs();
extern int count_leading_bits_equal();
extern int count_operands();
extern int cut_r0_ranges_at_serials();
extern short dc_size_code_of_type();
extern uint decide_literal_pool_placement();
extern int delete_unreachable_record();
extern int dispatch_and_finalize_code_node();
extern short displacement_aligned_for_type();
extern short displacement_ok_for_dereference();
extern int double_bits_to_int();
extern int double_bits_to_uint();
extern int drop_saved_register_contents();
extern int ea_label_list_too_long();
extern short ea_operands_equal();
extern uint ea_register_mask();
extern int emit_add_constant_minus_one();
extern int emit_block_copy_macro();
extern int emit_branch_on_node_value();
extern int emit_call_node();
extern int emit_comma_node();
extern int emit_comparison_node();
extern int emit_conditional_node();
extern int emit_double_to_unsigned();
extern int emit_fabs_or_fsqrt();
extern int emit_float_arith_op();
extern int emit_float_compare();
extern int emit_float_multiply_add();
extern int emit_float_to_unsigned();
extern int emit_logical_and_or_node();
extern int emit_logical_not_node();
extern int emit_mac_builtin_records();
extern int emit_movt_result();
extern int emit_node_code();
extern int emit_node_operands_and_template();
extern int emit_operand_moves_to_target_registers();
extern int emit_operand_transfer();
extern int emit_paired_fmov();
extern int emit_paired_fmov_reverse();
extern int emit_progress_banner();
extern int emit_psd_for_node();
extern int emit_psd_instruction();
extern int emit_psd_record();
extern int emit_push_double_one();
extern int emit_right_shift_by_constant();
extern int emit_sar_r0_by_rotation();
extern int emit_shad_right_by_constant();
extern int emit_shift_by_constant();
extern int emit_single_bit_field_store();
extern ushort emit_switch_compare_chain();
extern ushort emit_switch_jump_table();
extern int emit_symbol_sized_block_copy();
extern int emit_template_record_sequence_for_node();
extern int emit_unsigned_to_double();
extern int emit_unsigned_to_float();
extern int end_function_code();
extern int evict_oldest_register_content();
extern int expand_multiply_by_constant();
extern int fill_case_table_record();
extern int fill_ea();
extern int fill_label_record();
extern int fill_label_ref();
extern int fill_line_record();
extern int fill_psd_record();
extern int fill_psd_record_at_line();
extern int fill_psd_record_without_sptravel();
extern int fill_section_record();
extern deref_count * find_deref_count();
extern request_entry * find_keyed_entry();
extern int find_keyed_offset();
extern short find_lreg_register();
extern int find_pool_literal();
extern gen_node * find_previous_operand();
extern short find_register_holding_constant();
extern short find_register_holding_variable();
extern request_section * find_section_record();
extern int find_symbol_request_entry_a();
extern int find_symbol_request_entry_b();
extern short find_template_label();
extern uint float_bits_to_double();
extern int float_bits_to_int();
extern int float_bits_to_uint();
extern short float_mask_to_register();
extern uint fold_add_double();
extern uint fold_add_float();
extern uint fold_add_unsigned();
extern short fold_address_add();
extern short fold_address_add_sub();
extern short fold_address_sub();
extern uint fold_and_signed();
extern uint fold_and_unsigned();
extern uint fold_bnot_unsigned();
extern short fold_constant_arithmetic();
extern short fold_constant_bitwise();
extern short fold_constant_cast();
extern short fold_constant_comparison();
extern short fold_constant_logical();
extern int fold_constant_node();
extern short fold_constant_not();
extern short fold_constant_unary();
extern uint fold_div_double();
extern uint fold_div_float();
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
extern short fold_large_displacement_into_r0_index();
extern int fold_le_unsigned();
extern uint fold_lnot_double();
extern int fold_lnot_float();
extern int fold_lnot_unsigned();
extern int fold_lt_unsigned();
extern int fold_mod_unsigned();
extern uint fold_mul_double();
extern uint fold_mul_float();
extern uint fold_mul_unsigned();
extern int fold_ne_unsigned();
extern uint fold_neg_double();
extern uint fold_neg_float();
extern uint fold_neg_unsigned();
extern uint fold_or_signed();
extern uint fold_or_unsigned();
extern uint fold_shl_signed();
extern uint fold_shl_unsigned();
extern uint fold_shr_signed();
extern uint fold_shr_unsigned();
extern uint fold_sub_double();
extern uint fold_sub_float();
extern uint fold_sub_unsigned();
extern uint fold_xor_signed();
extern uint fold_xor_unsigned();
extern int forget_register_copies_of_variable();
extern int frame_operand_sp_displacement();
extern int free_ea();
extern int free_gen_node();
extern int free_gen_node_subtree();
extern int free_label_ref_list();
extern int free_macro_operand_list();
extern int free_node_descriptor_tree();
extern int free_slot_register_operands();
extern int gen_break_statement();
extern int gen_continue_statement();
extern int gen_goto_statement();
extern int gen_label_statement();
extern int gen_return_statement();
extern int generate_argument_list_node();
extern int generate_assign_node();
extern int generate_block_statement();
extern int generate_call_node();
extern int generate_comma_node();
extern int generate_conditional_node();
extern int generate_do_statement();
extern int generate_float_multiply_add();
extern int generate_for_statement();
extern int generate_function();
extern int generate_if_statement();
extern int generate_ilb_stream();
extern int generate_logical_and_node();
extern int generate_logical_or_node();
extern int generate_operator_by_template();
extern int generate_ordinary_call();
extern int generate_statement();
extern int generate_statement_expression();
extern int generate_switch_statement();
extern int generate_while_statement();
extern char * get_env_directory();
extern int get_marked_symbol_kind();
extern char get_symbol_attr_bit5_or_forced();
extern uchar get_symbol_attr_low_bits();
extern int has_free_register_pair();
extern short ilb_node_operands_full();
extern short init_gen_node_pool();
extern int initialize_node_descriptor_and_operand_slots();
extern int int_to_double_bits();
extern int int_to_float_bits();
extern int invalidate_register_contents();
extern uint invalidate_regs_written_by_entry();
extern int invalidate_slot_registers();
extern int invalidate_variable_register_contents();
extern int is_16bit_multiplier_constant();
extern int is_register_parameter_of_current_function();
extern char is_short_constant_shift();
extern int is_unreserved_function_name();
extern int is_word_symbol_literal();
extern short label_lists_equal();
extern gen_node * last_operand();
extern int live_range_lists_overlap();
extern int load_node_address_register();
extern ushort load_operand_address_into_new_register();
extern int load_request_and_open_stage_files();
extern request * load_request_record_file();
extern int load_slot_register_operands();
extern int lookup_builtin_function_id();
extern ea * make_call_routine_operand();
extern ea * make_label_operand();
extern short make_new_label_number();
extern char * make_temp_file_name();
extern int make_template_labels();
extern int map_code_node_opcode_to_late_handler_index();
extern int mark_arg_register_lregs_holding_parameters();
extern int mark_node_clobbering_r0();
extern short mask_to_register();
extern ea * materialize_operand_record_from_descriptor();
extern int * merge_and_sort_lreg_entries();
extern reg_range * merge_live_range_lists();
extern int * merge_r0_use_lists();
extern int move_builtin_arguments_clobbered_by_later_ones();
extern int move_node_result_to_destination();
extern int move_operand_to_new_float_register();
extern int move_operand_to_new_general_register();
extern int move_parameters_to_storage();
extern int move_r0_variable_operand_into_r0();
extern ushort move_saved_value_to_new_register();
extern int mul_fits_16bit_multiply();
extern short multiplier_shift_count();
extern int negate_multiword();
extern ea * new_ea_operand_with_flags();
extern ea * new_label_operand();
extern int node_value_size();
extern gen_node * nth_operand();
extern FILE * open_temp_file();
extern int operand_access_needs_r0();
extern int operand_position();
extern short operand_type_class();
extern int pack_round_double();
extern uint pack_round_float();
extern int pool_free();
extern int pool_free_in_chunk_list();
extern int pool_literal_matches();
extern alloc_chunk * pool_new_chunk();
extern int pop_fpscr_pr_state();
extern int prepare_address_of_node();
extern int prepare_bit_field_node();
extern int prepare_cast_node();
extern int prepare_comparison_node();
extern int prepare_constant_node();
extern int prepare_dereference_node();
extern int prepare_identifier_node();
extern int prepare_logical_not_node();
extern int prepare_member_node();
extern int prepare_unary_plus_node();
extern int prepend_operand();
extern int protect_fmac_operand_registers();
extern uchar psd_size_code_of_node();
extern int push_fpscr_pr_state();
extern int r0_result_left_to_chooser();
extern short rank_register_choice();
extern short rank_register_pair_choice();
extern int read_bytes_or_fail();
extern uint read_count_or_fail();
extern uint read_file_bytes();
extern int read_function_info();
extern int * read_function_scope_list();
extern int read_ilb_aggregate_call_node();
extern int read_ilb_aggregate_node();
extern int read_ilb_aggregate_qualify_node();
extern int read_ilb_asm_node();
extern int read_ilb_bit_qualify_node();
extern int read_ilb_call_node();
extern int read_ilb_double_const_node();
extern int read_ilb_incdec_node();
extern int read_ilb_long_double_const_node();
extern gen_node * read_ilb_node();
extern int read_ilb_pointer_const_node();
extern int read_ilb_qualify_node();
extern int read_ilb_symbol_node();
extern gen_node * read_ilb_tree();
extern int read_ilb_typed_node();
extern int read_ilb_untyped_node();
extern int read_ilb_word_const_node();
extern int * read_parameter_list();
extern int read_reg_file_lreg_table();
extern reg_range * read_reg_file_range_list();
extern int read_request_11byte_entry_list();
extern int read_request_12byte_entry_list();
extern int read_request_cpp_block();
extern int read_request_fixed_part();
extern int read_request_section_list();
extern int read_request_sized_string_list();
extern int read_request_source_file_list();
extern int read_request_string();
extern int read_request_string_list_040();
extern int read_request_string_list_048();
extern int read_request_variable_part();
extern int * read_scope_child_list();
extern int read_scope_info();
extern int * read_scope_member_list();
extern int read_switch_case_table();
extern uchar * read_symbol_extension();
extern char * read_symbol_name();
extern int read_symbol_table();
extern int record_constant_in_register();
extern int record_last_operand_copy_in_register();
extern int record_operand_copy_in_register();
extern int record_r0_variable_use_serial();
extern int record_variable_in_register();
extern int release_node_registers();
extern int reload_operand_address_into_register();
extern int remap_register_variables_to_scratch_registers();
extern int remove_serial_from_register_ranges();
extern int report_codegen_message();
extern int report_compiler_message();
extern int report_gen_node_pool_exhausted();
extern uint report_message_by_code();
extern int report_message_file_error_and_exit();
extern int reselect_value_template();
extern int reset_r0_variable_candidates();
extern ushort resolve_macro_psd_op();
extern short resolve_operand_register_conflicts();
extern int restore_fpscr_pr_state();
extern int restore_register_contents();
extern uint result_reg_exclusion_mask();
extern short reusable_operand_register();
extern int reuse_operand_value_for_cast();
extern int round_double_mantissa();
extern int round_float_mantissa();
extern int run_stage_pipeline_and_exit();
extern int save_register_arguments_clobbered_by_later_ones();
extern int save_register_contents();
extern int save_request_trailer_to_temp();
extern tmpl_header * select_aggregate_assign_template();
extern short select_arithmetic_routine();
extern tmpl_header * select_bit_field_assign_template();
extern tmpl_header * select_bit_field_load_template();
extern short select_bitfield_routine();
extern tmpl_header * select_builtin_template();
extern short select_conversion_routine();
extern short select_copy_routine();
extern int select_cpu_variant();
extern short select_cpu_variant_template();
extern int select_env_variable_names();
extern tmpl_header * select_load_address_template();
extern tmpl_header * select_load_template();
extern uchar select_matrix_column();
extern tmpl_header * select_move_template();
extern short select_node_template();
extern tmpl_header * select_push_address_template();
extern tmpl_header * select_push_template();
extern short select_shift_routine();
extern tmpl_header * select_store_template();
extern tmpl_header * select_transfer_template();
extern int set_assignment_result_value();
extern int set_gen_node_exhausted_handler();
extern int set_symbol_address_from_location_counter();
extern int shcgen_main();
extern short single_bit_position();
extern FILE * skip_ilb_function();
extern int skip_int_close_marker();
extern int stock_FF_MSGBANNER();
extern int stock_NMSG_WRITE();
extern int stock_amsg_exit();
extern int stock_callnewh();
extern int * stock_calloc();
extern char ** stock_copy_environ();
extern int stock_crtCompareStringA();
extern int stock_crtsetenv();
extern int stock_dosmaperr();
extern int stock_exit();
extern int stock_findenv();
extern FILE * stock_fopen();
extern int stock_free();
extern char * stock_getenv();
extern int * stock_heap_alloc();
extern int * stock_malloc();
extern uchar * stock_mbschr();
extern int stock_mbsnbicoll();
extern int * stock_nh_malloc();
extern int * stock_realloc();
extern int stock_remove();
extern char * stock_strchr();
extern char * stock_strcpy();
extern char * stock_strdup();
extern uint stock_strlen();
extern int stock_strncmp();
extern uint stock_strncnt();
extern char * stock_strncpy();
extern int stock_unlink();
extern int stock_wtomb_environ();
extern int store_node_value_through_address();
extern uint store_request_record_file();
extern int string_length();
extern int sub_multiword();
extern short template_copy_register();
extern int truncate_register_ranges_at_serial();
extern short try_evaluate_right_operand_first();
extern short two_bit_mask_bit_position();
extern int uint_to_double_bits();
extern short uint_to_float_bits();
extern int unlink_and_free_subtree();
extern uint unpack_double();
extern int unpack_float();
extern int update_register_ranges_after_statement();
extern int update_stack_travel();
extern int write_asa_attribute_byte();
extern int write_asa_data_symbol_record();
extern int write_asa_global_records();
extern int write_asa_global_symbol_record();
extern int write_asa_label_count_record();
extern int write_asa_record();
extern int write_asa_symbol_name();
extern int write_asa_symbol_record();
extern int write_asa_tag6_record();
extern int write_asa_trailer_record();
extern int write_bytes_or_fail();
extern int write_db2_function_locations();
extern int write_db2_lreg_table();
extern int write_db2_scope_locals();
extern uint write_file_bytes();
extern int write_final_literal_pool_flag();
extern int write_ofa_casejmp_record();
extern int write_ofa_ctbl_record();
extern int write_ofa_end_record();
extern int write_ofa_enter_record();
extern int write_ofa_exit_record();
extern int write_ofa_immediate_record();
extern int write_ofa_jump_record();
extern int write_ofa_label_operand_record();
extern int write_ofa_label_record();
extern int write_ofa_mov_loc_record();
extern int write_ofa_mova_lc_record();
extern int write_ofa_op2e_record();
extern int write_ofa_record();
extern int write_ofa_transfer_record();
extern int write_request_11byte_entry_list();
extern int write_request_12byte_entry_list();
extern int write_request_cpp_block();
extern int write_request_fixed_part();
extern int write_request_section_list();
extern int write_request_sized_string_list();
extern int write_request_source_file_list();
extern int write_request_string();
extern int write_request_string_list_040();
extern int write_request_string_list_048();
extern int write_request_variable_part();
extern int write_sua_bytes();
extern int write_sua_casejmp_record();
extern int write_sua_cent_record();
extern int write_sua_ctbl_record();
extern int write_sua_instruction_record();
extern int write_sua_label_list();
extern int write_sua_label_record();
extern int write_sua_line_record();
extern int write_sua_machine_op_record();
extern int write_sua_op10_record();
extern int write_sua_operand();
extern int write_sua_record();
extern int write_sua_section_record();
extern int write_sud_aggregate_initializer();
extern int write_sud_alignment_padding();
extern int write_sud_initialized_data();
extern int write_sud_scalar_initializer();
extern int write_sud_symbol_label();
extern int write_sud_variable_initializer();
extern int zero_words();

#define DAT_00449e4c (*(unsigned char *)(g_sd + 0x9e4c))
#define DAT_00458aa8 (*(int *)(g_sd + 0x18aa8))
#define DAT_0045c3a1 (*(unsigned char *)(g_sd + 0x1c3a1))
#define DAT_0045c9a0 (*(unsigned char *)(g_sd + 0x1c9a0))
#define DAT_0045c9ac (*(unsigned char *)(g_sd + 0x1c9ac))
#define DAT_0045c9b0 (*(unsigned char *)(g_sd + 0x1c9b0))
#define DAT_0045d4d0 (*(int *)(g_sd + 0x1d4d0))
#define DAT_0045d7ec (*(unsigned char *)(g_sd + 0x1d7ec))
#define DAT_0045d7f0 (*(unsigned char *)(g_sd + 0x1d7f0))
#define DAT_0045d81a (*(unsigned char *)(g_sd + 0x1d81a))
#define DAT_0045e4b9 (*(unsigned char *)(g_sd + 0x1e4b9))
#define DAT_0045e5f1 (*(unsigned char *)(g_sd + 0x1e5f1))
#define DAT_0045e5f2 (*(unsigned char *)(g_sd + 0x1e5f2))
#define DAT_0045e5f3 (*(unsigned char *)(g_sd + 0x1e5f3))
#define DAT_0045e5f4 (*(unsigned char *)(g_sd + 0x1e5f4))
#define DAT_0045e601 (*(unsigned char *)(g_sd + 0x1e601))
#define DAT_0045e602 (*(unsigned char *)(g_sd + 0x1e602))
#define DAT_0045e603 (*(unsigned char *)(g_sd + 0x1e603))
#define DAT_0045e604 (*(unsigned char *)(g_sd + 0x1e604))
#define DAT_0045e605 (*(unsigned char *)(g_sd + 0x1e605))
#define DAT_0045e606 (*(unsigned char *)(g_sd + 0x1e606))
#define DAT_0045e607 (*(unsigned char *)(g_sd + 0x1e607))
#define DAT_0045e608 (*(unsigned char *)(g_sd + 0x1e608))
#define DAT_0045e609 (*(unsigned char *)(g_sd + 0x1e609))
#define DAT_0045e60a (*(unsigned char *)(g_sd + 0x1e60a))
#define DAT_0045e60b (*(unsigned char *)(g_sd + 0x1e60b))
#define DAT_0045e611 (*(unsigned char *)(g_sd + 0x1e611))
#define DAT_0045e612 (*(unsigned char *)(g_sd + 0x1e612))
#define DAT_0045e613 (*(unsigned char *)(g_sd + 0x1e613))
#define DAT_0045e614 (*(unsigned char *)(g_sd + 0x1e614))
#define DAT_0045e615 (*(unsigned char *)(g_sd + 0x1e615))
#define DAT_0045e641 (*(unsigned char *)(g_sd + 0x1e641))
#define DAT_0045e642 (*(unsigned char *)(g_sd + 0x1e642))
#define DAT_0045e643 (*(unsigned char *)(g_sd + 0x1e643))
#define DAT_0045e644 (*(unsigned char *)(g_sd + 0x1e644))
#define DAT_0045e645 (*(unsigned char *)(g_sd + 0x1e645))
#define DAT_0045e646 (*(unsigned char *)(g_sd + 0x1e646))
#define DAT_0045e647 (*(unsigned char *)(g_sd + 0x1e647))
#define DAT_0045e648 (*(unsigned char *)(g_sd + 0x1e648))
#define DAT_0045e649 (*(unsigned char *)(g_sd + 0x1e649))
#define DAT_0045e64a (*(unsigned char *)(g_sd + 0x1e64a))
#define DAT_0045e64b (*(unsigned char *)(g_sd + 0x1e64b))
#define DAT_0045e64c (*(unsigned char *)(g_sd + 0x1e64c))
#define DAT_0045e64d (*(unsigned char *)(g_sd + 0x1e64d))
#define DAT_0045e64e (*(unsigned char *)(g_sd + 0x1e64e))
#define DAT_0045e64f (*(unsigned char *)(g_sd + 0x1e64f))
#define DAT_0045e650 (*(unsigned char *)(g_sd + 0x1e650))
#define DAT_0045e651 (*(unsigned char *)(g_sd + 0x1e651))
#define DAT_0045e674 (*(int *)(g_sd + 0x1e674))
#define DAT_0045e6d1 (*(unsigned char *)(g_sd + 0x1e6d1))
#define DAT_0045e743 (*(unsigned char *)(g_sd + 0x1e743))
#define DAT_0045e744 (*(unsigned char *)(g_sd + 0x1e744))
#define PTR_DAT_0045c120 (*(char * *)(g_sd + 0x1c120))
#define _DAT_00458aa4 (*(int *)(g_sd + 0x18aa4))
#define _g_assigned_symbol_count (*(int *)(g_sd + 0x1ee98))
#define _g_lreg_entry_count (*(int *)(g_sd + 0x1fa4e))
#define _g_pool_label_sptravel (*(int *)(g_sd + 0x1b620))
#define _g_template_extra_operands (*(int *)(g_sd + 0x18aa0))
#define _stock_errno (*(int *)(g_sd + 0x1ca20))
#define g_add_class_table (*(unsigned char *)(g_sd + 0x1c618))
#define g_add_fold_kind (*(unsigned char *)(g_sd + 0x9fe0))
#define g_alloc_size_classes (*(int *)(g_sd + 0x17b0))
#define g_amv_block_templates (*(unsigned char * *)(g_sd + 0x1c160))
#define g_amv_copy_templates (*(unsigned char * *)(g_sd + 0x1c170))
#define g_asa_defined_count (*(short *)(g_sd + 0x1d80c))
#define g_asa_external_count (*(short *)(g_sd + 0x1d810))
#define g_asa_file (*(unsigned char * *)(g_sd + 0x1f988))
#define g_assign_double_select (*(char * *)(g_sd + 0x9738))
#define g_assign_double_select_alt (*(char * *)(g_sd + 0x97d0))
#define g_assigned_symbol_count (*(unsigned char *)(g_sd + 0x1ee98))
#define g_aux_records (*(int *)(g_sd + 0x1f9bc))
#define g_avoid_reg_mask (*(short *)(g_sd + 0x1f93e))
#define g_bitfield_extract_routines (*(unsigned char *)(g_sd + 0x18680))
#define g_bitfield_store_routines (*(unsigned char *)(g_sd + 0x186a0))
#define g_break_label (*(short *)(g_sd + 0x1ee9c))
#define g_builtin_function_ids (*(short *)(g_sd + 0x1226))
#define g_builtin_function_names (*(char * *)(g_sd + 0x1220))
#define g_builtin_ids (*(unsigned char *)(g_sd + 0x183e8))
#define g_builtin_info (*(unsigned char *)(g_sd + 0x9e48))
#define g_builtin_names (*(char * *)(g_sd + 0x18320))
#define g_builtin_names_end (*(unsigned char *)(g_sd + 0x183e4))
#define g_case_restores_contents (*(unsigned char *)(g_sd + 0x1f991))
#define g_cast_select (*(char * *)(g_sd + 0x7e58))
#define g_chooser_extra_excluded (*(char *)(g_sd + 0x1f9a0))
#define g_close_status (*(int *)(g_sd + 0x1f9c4))
#define g_compare_eq_select (*(char * *)(g_sd + 0x9500))
#define g_compare_rel_select (*(char * *)(g_sd + 0x9588))
#define g_content_hit (*(int *)(g_sd + 0x1fe54))
#define g_continue_label (*(short *)(g_sd + 0x1fa04))
#define g_current_aux_record (*(int *)(g_sd + 0x1f950))
#define g_current_function (*(short *)(g_sd + 0x1eea8))
#define g_current_section (*(request_section * *)(g_sd + 0x1f9b8))
#define g_db2_file (*(unsigned char * *)(g_sd + 0x1fa24))
#define g_db2_local_record (*(unsigned char *)(g_sd + 0x1e610))
#define g_db2_lreg_record (*(unsigned char *)(g_sd + 0x1e5f0))
#define g_db2_param_record (*(unsigned char *)(g_sd + 0x1e600))
#define g_deref_count_cursor (*(int *)(g_sd + 0x1fa18))
#define g_deref_counts (*(short *)(g_sd + 0x1fa50))
#define g_deref_total (*(int *)(g_sd + 0x1eea4))
#define g_div_class_table (*(unsigned char *)(g_sd + 0x1c658))
#define g_double_one_hi (*(int *)(g_sd + 0x9808))
#define g_double_one_lo (*(int *)(g_sd + 0x980c))
#define g_ea_imm0 (*(ea *)(g_sd + 0x15c0))
#define g_ea_imm1 (*(ea *)(g_sd + 0x15cc))
#define g_ea_imm8 (*(unsigned char *)(g_sd + 0x15e4))
#define g_ea_imm_minus8 (*(unsigned char *)(g_sd + 0x15fc))
#define g_ea_pop (*(ea *)(g_sd + 0x97e0))
#define g_ea_postinc_r15 (*(unsigned char *)(g_sd + 0x1614))
#define g_ea_predec_r15 (*(unsigned char *)(g_sd + 0x1608))
#define g_ea_push (*(ea *)(g_sd + 0x97f0))
#define g_ea_r0 (*(unsigned char *)(g_sd + 0x15d8))
#define g_ea_r15 (*(unsigned char *)(g_sd + 0x15f0))
#define g_emit_handler_by_op (*(unsigned char *)(g_sd + 0x15a0))
#define g_empty_string (*(unsigned char *)(g_sd + 0x1c71c))
#define g_env_directory (*(unsigned char *)(g_sd + 0x1e6d0))
#define g_exit_record_dropped (*(unsigned char *)(g_sd + 0x1f941))
#define g_fixed_operands (*(unsigned char *)(g_sd + 0x18428))
#define g_float_one_bits (*(int *)(g_sd + 0x97fc))
#define g_float_zero_bits (*(int *)(g_sd + 0x9800))
#define g_fpr_contents (*(reg_content (*)[4])(g_sd + 0x1fe70))
#define g_fpr_contents_flags_by_reg (*(unsigned char *)(g_sd + 0x1fcf9))
#define g_fpr_contents_stack (*(int *)(g_sd + 0x1f998))
#define g_fpr_contents_stamp_by_pair (*(unsigned char *)(g_sd + 0x1fb7c))
#define g_fpr_contents_stamp_by_pair_hi (*(unsigned char *)(g_sd + 0x1fb94))
#define g_fpr_contents_stamp_by_reg (*(unsigned char *)(g_sd + 0x1fcfc))
#define g_fpscr_pr (*(char *)(g_sd + 0x1f9f8))
#define g_fpscr_pr_stack (*(int *)(g_sd + 0x1f984))
#define g_frame_end (*(int *)(g_sd + 0x1ee94))
#define g_frame_offset_literal_table (*(int *)(g_sd + 0x1ec80))
#define g_function_count (*(short *)(g_sd + 0x1ee9a))
#define g_gbr_base_label_ref (*(unsigned char *)(g_sd + 0x9810))
#define g_gen_node_exhausted_handler (*(int *)(g_sd + 0x1ff94))
#define g_gen_node_free_head (*(gen_node * *)(g_sd + 0x1e62c))
#define g_gen_node_free_tail (*(gen_node * *)(g_sd + 0x1e628))
#define g_gen_node_size (*(int *)(g_sd + 0x1e634))
#define g_gpr_contents (*(reg_content (*)[4])(g_sd + 0x1ff00))
#define g_gpr_contents_stack (*(int *)(g_sd + 0x1fef0))
#define g_il_op_arity (*(unsigned char *)(g_sd + 0x1c598))
#define g_ilb_cursor (*(gen_node * *)(g_sd + 0x1ff90))
#define g_ilb_depth (*(int *)(g_sd + 0x1ff98))
#define g_ilb_file (*(unsigned char * *)(g_sd + 0x1f980))
#define g_ilb_operand_counts (*(int *)(g_sd + 0x1ffa0))
#define g_ilb_record_buffer (*(unsigned char *)(g_sd + 0x1e640))
#define g_in_unreachable_code (*(int *)(g_sd + 0x18bc8))
#define g_inc_env_name (*(char * *)(g_sd + 0x1ff78))
#define g_int_file (*(unsigned char * *)(g_sd + 0x1f98c))
#define g_int_nesting_depth (*(int *)(g_sd + 0x1fed4))
#define g_internal_error_text (*(char * *)(g_sd + 0x1c998))
#define g_last_case_label (*(short *)(g_sd + 0x1fe50))
#define g_last_chosen_reg (*(char *)(g_sd + 0x1f93c))
#define g_last_goto_label (*(short *)(g_sd + 0x1fa4c))
#define g_last_stmt_jumps (*(short *)(g_sd + 0x1f948))
#define g_late_handler_index_by_op (*(unsigned char * *)(g_sd + 0x98e8))
#define g_late_handler_kind (*(unsigned char *)(g_sd + 0x9818))
#define g_late_handler_table (*(unsigned char * *)(g_sd + 0x9848))
#define g_lib_env_name_14 (*(char * *)(g_sd + 0x1ff64))
#define g_lib_env_name_18 (*(char * *)(g_sd + 0x1ff68))
#define g_lib_env_name_20 (*(char * *)(g_sd + 0x1ff70))
#define g_lib_env_name_24 (*(char * *)(g_sd + 0x1ff74))
#define g_lit_file (*(unsigned char * *)(g_sd + 0x1fa08))
#define g_literal_label_serial (*(short *)(g_sd + 0x1c124))
#define g_loaded_request (*(request * *)(g_sd + 0x1ff84))
#define g_local_frame_size (*(int *)(g_sd + 0x1fa14))
#define g_long_copy_templates (*(unsigned char * *)(g_sd + 0x1c180))
#define g_long_literal_table (*(unsigned char *)(g_sd + 0x1ea70))
#define g_lreg_entry_count (*(unsigned char *)(g_sd + 0x1fa4e))
#define g_lreg_table (*(int *)(g_sd + 0x1fa10))
#define g_mac_regs_used (*(unsigned char *)(g_sd + 0x1f9e8))
#define g_macro_written_operands (*(unsigned char *)(g_sd + 0x189a8))
#define g_max_sptravel (*(unsigned int *)(g_sd + 0x1fa34))
#define g_max_temp_frame (*(unsigned int *)(g_sd + 0x1fa3c))
#define g_message_number_text (*(unsigned char *)(g_sd + 0x1e6c8))
#define g_message_severity (*(int *)(g_sd + 0x1f9fc))
#define g_msg_filn (*(short *)(g_sd + 0x1fee8))
#define g_msg_line (*(unsigned short *)(g_sd + 0x1f9ea))
#define g_msg_listno (*(short *)(g_sd + 0x1fa20))
#define g_mul_class_table (*(unsigned char *)(g_sd + 0x1c638))
#define g_nested_operand_emit (*(char *)(g_sd + 0x1fee6))
#define g_no_reg_ranges (*(char *)(g_sd + 0x1f940))
#define g_not_select (*(char * *)(g_sd + 0x9640))
#define g_ofa_file (*(unsigned char * *)(g_sd + 0x1f9ec))
#define g_ofa_record_out (*(unsigned char * *)(g_sd + 0x1e5e8))
#define g_op_code_size_table (*(unsigned char *)(g_sd + 0x1c1a0))
#define g_op_reachability_class (*(unsigned char *)(g_sd + 0x18ac8))
#define g_open_mode_ab (*(unsigned char *)(g_sd + 0x1c99c))
#define g_open_mode_rb (*(unsigned char *)(g_sd + 0x17b4))
#define g_open_mode_wb (*(unsigned char *)(g_sd + 0x1831c))
#define g_open_mode_wb_plus (*(unsigned char *)(g_sd + 0x1c8dc))
#define g_operand_desc_table (*(unsigned int (*)[264])(g_sd + 0x9968))
#define g_pid_digit_count (*(int *)(g_sd + 0x1c8d0))
#define g_pool_after_enter (*(char *)(g_sd + 0x1c140))
#define g_pool_after_exit (*(char *)(g_sd + 0x1c144))
#define g_pool_carried_code_bytes (*(int *)(g_sd + 0x1c134))
#define g_pool_carried_has_word (*(char *)(g_sd + 0x1c138))
#define g_pool_carried_literal_bytes (*(int *)(g_sd + 0x1c130))
#define g_pool_code_bytes (*(int *)(g_sd + 0x1c12c))
#define g_pool_flush_pending (*(int *)(g_sd + 0x1c148))
#define g_pool_label_sptravel (*(short *)(g_sd + 0x1b620))
#define g_pool_pending_literal_bytes (*(int *)(g_sd + 0x1c128))
#define g_pool_segment_has_word (*(char *)(g_sd + 0x1c13c))
#define g_process_id (*(int *)(g_sd + 0x1c8d4))
#define g_progress_banner_table (*(unsigned char * *)(g_sd + 0x1c818))
#define g_psd_op_template_info (*(unsigned char *)(g_sd + 0x186c0))
#define g_psd_op_written_operand (*(unsigned char *)(g_sd + 0x188a8))
#define g_psd_scratch (*(unsigned char *)(g_sd + 0x1f9d0))
#define g_push_long_copy_templates (*(char * *)(g_sd + 0x1c150))
#define g_push_short_copy_templates (*(char * *)(g_sd + 0x1c158))
#define g_r0_index_loaded (*(int *)(g_sd + 0x1f94c))
#define g_r0_used (*(int *)(g_sd + 0x1f9a4))
#define g_r0_variable (*(int *)(g_sd + 0x1f9a8))
#define g_reg_file (*(unsigned char * *)(g_sd + 0x1fa2c))
#define g_request (*(request * *)(g_sd + 0x1eea0))
#define g_request_being_loaded (*(request * *)(g_sd + 0x1e660))
#define g_request_cpp_block_size (*(short *)(g_sd + 0x1ff8a))
#define g_request_fixed_size (*(short *)(g_sd + 0x1ff8c))
#define g_request_record_path (*(char * *)(g_sd + 0x1ff7c))
#define g_request_trailer_file (*(unsigned char * *)(g_sd + 0x1ff80))
#define g_request_version_mismatch (*(short *)(g_sd + 0x1ff88))
#define g_return_label (*(short *)(g_sd + 0x1fa00))
#define g_return_label_used (*(char *)(g_sd + 0x1f990))
#define g_return_record_dropped (*(unsigned char *)(g_sd + 0x1fa28))
#define g_routine_clobbers (*(unsigned char *)(g_sd + 0x189e8))
#define g_routine_stack_adjust (*(int *)(g_sd + 0xa10c))
#define g_runtime_routine_names (*(char * *)(g_sd + 0x1be4c))
#define g_saved_sys_mask (*(unsigned char *)(g_sd + 0x1fe60))
#define g_short_copy_templates (*(unsigned char * *)(g_sd + 0x1c190))
#define g_sptravel (*(int *)(g_sd + 0x1f944))
#define g_stack_param_offset (*(int *)(g_sd + 0x1fa38))
#define g_stage_request (*(request * *)(g_sd + 0x1ee88))
#define g_stmt_invalidate_mask (*(short *)(g_sd + 0x1fa02))
#define g_stmt_pushed_operand (*(char *)(g_sd + 0x1f9b4))
#define g_stmt_serial (*(unsigned int *)(g_sd + 0x1fedc))
#define g_stmt_temp_regs (*(short *)(g_sd + 0x1fed0))
#define g_string_pool_block (*(char * *)(g_sd + 0x1fa40))
#define g_string_pool_cursor (*(char * *)(g_sd + 0x1fa48))
#define g_sua_file (*(unsigned char * *)(g_sd + 0x1fa30))
#define g_sua_filno (*(short *)(g_sd + 0x1e61c))
#define g_sua_frame_disp_operand (*(ea *)(g_sd + 0x1c588))
#define g_sua_linno (*(unsigned short *)(g_sd + 0x1e620))
#define g_sua_record_format_table (*(unsigned char *)(g_sd + 0x1c3a0))
#define g_sua_report_extra_arg (*(short *)(g_sd + 0x1e624))
#define g_sub_fold_kind (*(unsigned char *)(g_sd + 0xa038))
#define g_sud_buffer (*(unsigned char *)(g_sd + 0x1eeb0))
#define g_sud_buffer_cursor (*(char * *)(g_sd + 0x1f9f4))
#define g_sud_buffer_holds_data (*(char *)(g_sd + 0x1fa0c))
#define g_sud_buffer_start (*(char * *)(g_sd + 0x1fe64))
#define g_sud_const_dc_count (*(int *)(g_sd + 0x1fa44))
#define g_sud_const_dc_count_field (*(char * *)(g_sd + 0x1fe58))
#define g_sud_const_section (*(short *)(g_sd + 0x1e4c0))
#define g_sud_data_dc_count (*(int *)(g_sd + 0x1f994))
#define g_sud_data_dc_count_field (*(char * *)(g_sd + 0x1fa1c))
#define g_sud_data_section (*(short *)(g_sd + 0x1e4c4))
#define g_sud_dc_elem_type (*(unsigned short *)(g_sd + 0x1e2a8))
#define g_sud_dc_header (*(unsigned char *)(g_sd + 0x1e4b8))
#define g_sud_dc_run_closed (*(char *)(g_sd + 0x1e2a4))
#define g_sud_dc_unit (*(int *)(g_sd + 0x1e4bc))
#define g_sud_file (*(unsigned char * *)(g_sd + 0x1f9f0))
#define g_sud_hold_buffer (*(unsigned char *)(g_sd + 0x1d818))
#define g_sud_hold_length (*(int *)(g_sd + 0x1eeac))
#define g_sud_string_buffer (*(unsigned char *)(g_sd + 0x1e2b0))
#define g_sud_symx (*(short *)(g_sd + 0x1e4c8))
#define g_swi_file (*(unsigned char * *)(g_sd + 0x1feec))
#define g_switch_case_count (*(short *)(g_sd + 0x1fed8))
#define g_switch_cases (*(int *)(g_sd + 0x1fee0))
#define g_switch_default_label (*(short *)(g_sd + 0x1f9c0))
#define g_switch_max_case (*(int *)(g_sd + 0x1ee8c))
#define g_switch_min_case (*(int *)(g_sd + 0x1ee90))
#define g_sym_file (*(unsigned char * *)(g_sd + 0x1f99c))
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))
#define g_temp_file_count (*(int *)(g_sd + 0x1e66c))
#define g_temp_file_suffix (*(int *)(g_sd + 0x1c8e0))
#define g_temp_files (*(int *)(g_sd + 0x1e670))
#define g_temp_name_buffer (*(char * *)(g_sd + 0x1c8cc))
#define g_temp_name_counter (*(int *)(g_sd + 0x1c8d8))
#define g_temp_path_in_progress (*(char * *)(g_sd + 0x1e6c4))
#define g_template_extra_operands (*(unsigned char *)(g_sd + 0x18aa0))
#define g_template_value_unused (*(int *)(g_sd + 0x1fe5c))
#define g_test_double_fpu_entries (*(unsigned char *)(g_sd + 0x3cd8))
#define g_test_double_soft_entries (*(unsigned char *)(g_sd + 0x3ba8))
#define g_test_float_fpu_entries (*(unsigned char *)(g_sd + 0x3c98))
#define g_test_float_soft_mem_entries (*(unsigned char *)(g_sd + 0x3c40))
#define g_test_float_soft_reg_entries (*(unsigned char *)(g_sd + 0x3c18))
#define g_test_int_mem_entries (*(unsigned char *)(g_sd + 0x3bf0))
#define g_test_int_reg_entries (*(unsigned char *)(g_sd + 0x3b90))
#define g_test_short_fixed_reg_entries (*(unsigned char *)(g_sd + 0x3c70))
#define g_test_short_mem_entries (*(unsigned char *)(g_sd + 0x3b68))
#define g_test_short_reg_entries (*(unsigned char *)(g_sd + 0x3b40))
#define g_tmp_env_name (*(char * *)(g_sd + 0x1ff6c))
#define g_tmpl_aamper001 (*(unsigned char *)(g_sd + 0x15418))
#define g_tmpl_aamper002 (*(unsigned char *)(g_sd + 0x15488))
#define g_tmpl_aassgn016 (*(unsigned char *)(g_sd + 0x16560))
#define g_tmpl_aassgn017 (*(unsigned char *)(g_sd + 0x16608))
#define g_tmpl_aassgn018 (*(unsigned char *)(g_sd + 0x166b0))
#define g_tmpl_aassgn019 (*(unsigned char *)(g_sd + 0x16738))
#define g_tmpl_aassgn020 (*(unsigned char *)(g_sd + 0x16a78))
#define g_tmpl_aassgn021 (*(unsigned char *)(g_sd + 0x16b00))
#define g_tmpl_aassgn022 (*(unsigned char *)(g_sd + 0x16b90))
#define g_tmpl_aassgn023 (*(unsigned char *)(g_sd + 0x167b0))
#define g_tmpl_aassgn024 (*(unsigned char *)(g_sd + 0x16828))
#define g_tmpl_aassgn025 (*(unsigned char *)(g_sd + 0x168a0))
#define g_tmpl_aassgn026 (*(unsigned char *)(g_sd + 0x16910))
#define g_tmpl_aassgn027 (*(unsigned char *)(g_sd + 0x16980))
#define g_tmpl_aassgn028 (*(unsigned char *)(g_sd + 0x169f0))
#define g_tmpl_aassgn032 (*(unsigned char *)(g_sd + 0x16d78))
#define g_tmpl_aassgn033 (*(unsigned char *)(g_sd + 0x16e30))
#define g_tmpl_aassgn037 (*(unsigned char *)(g_sd + 0x17018))
#define g_tmpl_aassgn038 (*(unsigned char *)(g_sd + 0x17088))
#define g_tmpl_aassgn039 (*(unsigned char *)(g_sd + 0x170f8))
#define g_tmpl_aassgn040 (*(unsigned char *)(g_sd + 0x17168))
#define g_tmpl_aassgn041 (*(unsigned char *)(g_sd + 0x171e0))
#define g_tmpl_aassgn042 (*(unsigned char *)(g_sd + 0x17268))
#define g_tmpl_aassgn043 (*(unsigned char *)(g_sd + 0x172f0))
#define g_tmpl_aassgn044 (*(unsigned char *)(g_sd + 0x17378))
#define g_tmpl_aassgn045 (*(unsigned char *)(g_sd + 0x173f0))
#define g_tmpl_aassgn046 (*(unsigned char *)(g_sd + 0x17468))
#define g_tmpl_abqual001 (*(unsigned char *)(g_sd + 0x159a8))
#define g_tmpl_abqual002 (*(unsigned char *)(g_sd + 0x15a30))
#define g_tmpl_abqual003 (*(unsigned char *)(g_sd + 0x15ab8))
#define g_tmpl_abqual004 (*(unsigned char *)(g_sd + 0x15b58))
#define g_tmpl_abqual005 (*(unsigned char *)(g_sd + 0x15bd0))
#define g_tmpl_abqual006 (*(unsigned char *)(g_sd + 0x15c58))
#define g_tmpl_abqual007 (*(unsigned char *)(g_sd + 0x15ce0))
#define g_tmpl_abqual008 (*(unsigned char *)(g_sd + 0x15d70))
#define g_tmpl_aid001 (*(unsigned char *)(g_sd + 0x152f8))
#define g_tmpl_ald000 (*(unsigned char *)(g_sd + 0x3d48))
#define g_tmpl_ald001 (*(unsigned char *)(g_sd + 0x3db8))
#define g_tmpl_ald002 (*(unsigned char *)(g_sd + 0x3e30))
#define g_tmpl_ald003 (*(unsigned char *)(g_sd + 0x3e90))
#define g_tmpl_ald005 (*(unsigned char *)(g_sd + 0x3f00))
#define g_tmpl_ald009 (*(unsigned char *)(g_sd + 0x3f70))
#define g_tmpl_ald014 (*(unsigned char *)(g_sd + 0x3fd0))
#define g_tmpl_ald016 (*(unsigned char *)(g_sd + 0x4048))
#define g_tmpl_ald020 (*(unsigned char *)(g_sd + 0x40b8))
#define g_tmpl_ald021 (*(unsigned char *)(g_sd + 0x4128))
#define g_tmpl_ald023 (*(unsigned char *)(g_sd + 0x41e8))
#define g_tmpl_ald024 (*(unsigned char *)(g_sd + 0x4308))
#define g_tmpl_ald025 (*(unsigned char *)(g_sd + 0x4378))
#define g_tmpl_ald026 (*(unsigned char *)(g_sd + 0x43f0))
#define g_tmpl_ald027 (*(unsigned char *)(g_sd + 0x4460))
#define g_tmpl_ald028 (*(unsigned char *)(g_sd + 0x4248))
#define g_tmpl_ald029 (*(unsigned char *)(g_sd + 0x42a8))
#define g_tmpl_ald030 (*(unsigned char *)(g_sd + 0x44d8))
#define g_tmpl_ald031 (*(unsigned char *)(g_sd + 0x45c0))
#define g_tmpl_ald032 (*(unsigned char *)(g_sd + 0x46a0))
#define g_tmpl_ald033 (*(unsigned char *)(g_sd + 0x4710))
#define g_tmpl_ald034 (*(unsigned char *)(g_sd + 0x48f8))
#define g_tmpl_ald035 (*(unsigned char *)(g_sd + 0x4a08))
#define g_tmpl_ald036 (*(unsigned char *)(g_sd + 0x4b18))
#define g_tmpl_ald037 (*(unsigned char *)(g_sd + 0x4550))
#define g_tmpl_ald038 (*(unsigned char *)(g_sd + 0x47f8))
#define g_tmpl_ald039 (*(unsigned char *)(g_sd + 0x4870))
#define g_tmpl_ald040 (*(unsigned char *)(g_sd + 0x4980))
#define g_tmpl_ald041 (*(unsigned char *)(g_sd + 0x4a90))
#define g_tmpl_ald042 (*(unsigned char *)(g_sd + 0x4ba0))
#define g_tmpl_ald043 (*(unsigned char *)(g_sd + 0x4780))
#define g_tmpl_ald044 (*(unsigned char *)(g_sd + 0x4630))
#define g_tmpl_ald045 (*(unsigned char *)(g_sd + 0x4c10))
#define g_tmpl_ald046 (*(unsigned char *)(g_sd + 0x4c80))
#define g_tmpl_alda001 (*(unsigned char *)(g_sd + 0x5950))
#define g_tmpl_alda002 (*(unsigned char *)(g_sd + 0x59b0))
#define g_tmpl_alda003 (*(unsigned char *)(g_sd + 0x5a10))
#define g_tmpl_alda004 (*(unsigned char *)(g_sd + 0x5a80))
#define g_tmpl_alda005 (*(unsigned char *)(g_sd + 0x5af0))
#define g_tmpl_alda006 (*(unsigned char *)(g_sd + 0x5b60))
#define g_tmpl_alda007 (*(unsigned char *)(g_sd + 0x5bd0))
#define g_tmpl_alda008 (*(unsigned char *)(g_sd + 0x5c30))
#define g_tmpl_alda009 (*(unsigned char *)(g_sd + 0x5c90))
#define g_tmpl_alda010 (*(unsigned char *)(g_sd + 0x5d00))
#define g_tmpl_amul005 (*(unsigned char *)(g_sd + 0xdc70))
#define g_tmpl_amul007 (*(unsigned char *)(g_sd + 0xdd60))
#define g_tmpl_amul008 (*(unsigned char *)(g_sd + 0xdde8))
#define g_tmpl_amv003 (*(unsigned char *)(g_sd + 0x60f0))
#define g_tmpl_amv005 (*(unsigned char *)(g_sd + 0x6190))
#define g_tmpl_amv006 (*(unsigned char *)(g_sd + 0x6220))
#define g_tmpl_amv007 (*(unsigned char *)(g_sd + 0x62b0))
#define g_tmpl_amv008 (*(unsigned char *)(g_sd + 0x6338))
#define g_tmpl_amv012 (*(unsigned char *)(g_sd + 0x63c0))
#define g_tmpl_amv014 (*(unsigned char *)(g_sd + 0x6450))
#define g_tmpl_amv016 (*(unsigned char *)(g_sd + 0x6538))
#define g_tmpl_amv018 (*(unsigned char *)(g_sd + 0x6638))
#define g_tmpl_amv019 (*(unsigned char *)(g_sd + 0x66f0))
#define g_tmpl_amv021 (*(unsigned char *)(g_sd + 0x67d8))
#define g_tmpl_amv023 (*(unsigned char *)(g_sd + 0x68d8))
#define g_tmpl_amv024 (*(unsigned char *)(g_sd + 0x6948))
#define g_tmpl_amv025 (*(unsigned char *)(g_sd + 0x69b8))
#define g_tmpl_amv026 (*(unsigned char *)(g_sd + 0x6a28))
#define g_tmpl_apush001 (*(unsigned char *)(g_sd + 0x6a88))
#define g_tmpl_apush002 (*(unsigned char *)(g_sd + 0x6af8))
#define g_tmpl_apush003 (*(unsigned char *)(g_sd + 0x6b88))
#define g_tmpl_apush004 (*(unsigned char *)(g_sd + 0x6c10))
#define g_tmpl_apush005 (*(unsigned char *)(g_sd + 0x6c98))
#define g_tmpl_apush006 (*(unsigned char *)(g_sd + 0x6d20))
#define g_tmpl_apush007 (*(unsigned char *)(g_sd + 0x6da8))
#define g_tmpl_apush008 (*(unsigned char *)(g_sd + 0x6e48))
#define g_tmpl_apush009 (*(unsigned char *)(g_sd + 0x6ee8))
#define g_tmpl_apush010 (*(unsigned char *)(g_sd + 0x6f90))
#define g_tmpl_apush011 (*(unsigned char *)(g_sd + 0x7038))
#define g_tmpl_apush012 (*(unsigned char *)(g_sd + 0x70d8))
#define g_tmpl_apush017 (*(unsigned char *)(g_sd + 0x7380))
#define g_tmpl_apush018 (*(unsigned char *)(g_sd + 0x7408))
#define g_tmpl_apush019 (*(unsigned char *)(g_sd + 0x7490))
#define g_tmpl_apush020 (*(unsigned char *)(g_sd + 0x74f0))
#define g_tmpl_apush021 (*(unsigned char *)(g_sd + 0x7560))
#define g_tmpl_apush022 (*(unsigned char *)(g_sd + 0x75d0))
#define g_tmpl_apush023 (*(unsigned char *)(g_sd + 0x76b8))
#define g_tmpl_apush024 (*(unsigned char *)(g_sd + 0x7640))
#define g_tmpl_apush025 (*(unsigned char *)(g_sd + 0x7730))
#define g_tmpl_apusha001 (*(unsigned char *)(g_sd + 0x5d70))
#define g_tmpl_apusha002 (*(unsigned char *)(g_sd + 0x5de0))
#define g_tmpl_apusha003 (*(unsigned char *)(g_sd + 0x5e40))
#define g_tmpl_apusha004 (*(unsigned char *)(g_sd + 0x5eb8))
#define g_tmpl_apusha005 (*(unsigned char *)(g_sd + 0x5f28))
#define g_tmpl_apusha006 (*(unsigned char *)(g_sd + 0x5f98))
#define g_tmpl_apusha007 (*(unsigned char *)(g_sd + 0x6008))
#define g_tmpl_apusha008 (*(unsigned char *)(g_sd + 0x6080))
#define g_tmpl_aqual001 (*(unsigned char *)(g_sd + 0x15358))
#define g_tmpl_aqual002 (*(unsigned char *)(g_sd + 0x153b8))
#define g_tmpl_ast000 (*(unsigned char *)(g_sd + 0x4ce0))
#define g_tmpl_ast001 (*(unsigned char *)(g_sd + 0x4d50))
#define g_tmpl_ast002 (*(unsigned char *)(g_sd + 0x4db0))
#define g_tmpl_ast003 (*(unsigned char *)(g_sd + 0x4e20))
#define g_tmpl_ast005 (*(unsigned char *)(g_sd + 0x4e90))
#define g_tmpl_ast009 (*(unsigned char *)(g_sd + 0x4f08))
#define g_tmpl_ast010 (*(unsigned char *)(g_sd + 0x4f78))
#define g_tmpl_ast011 (*(unsigned char *)(g_sd + 0x4fd8))
#define g_tmpl_ast012 (*(unsigned char *)(g_sd + 0x5038))
#define g_tmpl_ast013 (*(unsigned char *)(g_sd + 0x50a8))
#define g_tmpl_ast014 (*(unsigned char *)(g_sd + 0x5118))
#define g_tmpl_ast015 (*(unsigned char *)(g_sd + 0x5190))
#define g_tmpl_ast016 (*(unsigned char *)(g_sd + 0x5208))
#define g_tmpl_ast017 (*(unsigned char *)(g_sd + 0x52f0))
#define g_tmpl_ast018 (*(unsigned char *)(g_sd + 0x53d0))
#define g_tmpl_ast019 (*(unsigned char *)(g_sd + 0x5568))
#define g_tmpl_ast020 (*(unsigned char *)(g_sd + 0x5678))
#define g_tmpl_ast021 (*(unsigned char *)(g_sd + 0x5788))
#define g_tmpl_ast022 (*(unsigned char *)(g_sd + 0x5280))
#define g_tmpl_ast023 (*(unsigned char *)(g_sd + 0x5458))
#define g_tmpl_ast024 (*(unsigned char *)(g_sd + 0x54e0))
#define g_tmpl_ast025 (*(unsigned char *)(g_sd + 0x55f0))
#define g_tmpl_ast026 (*(unsigned char *)(g_sd + 0x5700))
#define g_tmpl_ast027 (*(unsigned char *)(g_sd + 0x5810))
#define g_tmpl_ast028 (*(unsigned char *)(g_sd + 0x5360))
#define g_tmpl_ast029 (*(unsigned char *)(g_sd + 0x5880))
#define g_tmpl_ast030 (*(unsigned char *)(g_sd + 0x58f0))
#define g_unlink_parent (*(gen_node * *)(g_sd + 0x1ff9c))
#define g_used_fpr_mask (*(unsigned short *)(g_sd + 0x1f9ac))
#define g_used_gpr_mask (*(unsigned short *)(g_sd + 0x1ff60))
#define g_used_routine_bits (*(unsigned char *)(g_sd + 0x1f960))
#define g_var_fpr_mask (*(unsigned short *)(g_sd + 0x1fee4))
#define g_var_gpr_mask (*(unsigned short *)(g_sd + 0x1f9fa))
#define g_word_literal_table (*(int *)(g_sd + 0x1e860))
#define g_zero_constant (*(unsigned char *)(g_sd + 0x18ac0))
#define s_Copyright__c__1992_1996_Hitachi__0044a0c0 (*(char (*)[76])(g_sd + 0xa0c0))
#define s_Microsoft_Visual_C___Runtime_Lib_0045d304 (*(char (*)[37])(g_sd + 0x1d304))
#define s_Runtime_Error__Program__0045d330 (*(char (*)[28])(g_sd + 0x1d330))
#define s_SHCPP_INC_0045c9fc (*(char (*)[10])(g_sd + 0x1c9fc))
#define s_SHCPP_LIB_0045c9f0 (*(char (*)[10])(g_sd + 0x1c9f0))
#define s_SHCPP_TMP_0045c9e4 (*(char (*)[10])(g_sd + 0x1c9e4))
#define s_SHC_INC_0045ca18 (*(char (*)[8])(g_sd + 0x1ca18))
#define s_SHC_LIB_0045ca10 (*(char (*)[8])(g_sd + 0x1ca10))
#define s_SHC_TMP_0045ca08 (*(char (*)[8])(g_sd + 0x1ca08))
#define s_SH_SERIES_C_Compiler_Ver__5_0_Re_0044a090 (*(char (*)[44])(g_sd + 0xa090))
#define s__0____0045c9a4 (*(char (*)[7])(g_sd + 0x1c9a4))
#define s__builtin__004413b0 (*(char (*)[10])(g_sd + 0x13b0))
#define s__builtin__0045841c (*(char (*)[10])(g_sd + 0x1841c))
#define s__builtin_strcmp_004417a0 (*(char (*)[16])(g_sd + 0x17a0))
#define s__s_d__d_0045c8e8 (*(char (*)[8])(g_sd + 0x1c8e8))
#define s_al008_004595f8 (*(char (*)[6])(g_sd + 0x195f8))
#define s_str_0045d350 (*(char (*)[24])(g_sd + 0x1d350))
#define stock_adbgmsg (*(int *)(g_sd + 0x1d300))
#define stock_aexit_rtn (*(char * *)(g_sd + 0x1ca70))
#define stock_app_type (*(int *)(g_sd + 0x1ca78))
#define stock_crtheap (*(int *)(g_sd + 0x200b0))
#define stock_doserrno (*(int *)(g_sd + 0x1ca24))
#define stock_ellipsis_text (*(unsigned char *)(g_sd + 0x1d34c))
#define stock_environ (*(int *)(g_sd + 0x1ca48))
#define stock_error_mode (*(int *)(g_sd + 0x1ca74))
#define stock_errtable (*(int *)(g_sd + 0x1d368))
#define stock_f_use_CompareString (*(int *)(g_sd + 0x1d7f8))
#define stock_initenv (*(int *)(g_sd + 0x1ca4c))
#define stock_lc_codepage (*(int *)(g_sd + 0x1d778))
#define stock_mbcodepage (*(int *)(g_sd + 0x1cef4))
#define stock_mbctype (*(int *)(g_sd + 0x1cdf0))
#define stock_mblcid (*(int *)(g_sd + 0x1cef8))
#define stock_newline_pair_text (*(int *)(g_sd + 0x1d32c))
#define stock_newmode (*(int *)(g_sd + 0x1cd40))
#define stock_pioinfo (*(int *)(g_sd + 0x1ffb0))
#define stock_pnhHeap (*(int *)(g_sd + 0x1e750))
#define stock_rterrs (*(int *)(g_sd + 0x1d278))
#define stock_stderr (*(unsigned char *)(g_sd + 0x1cad0))
#define stock_stdout (*(unsigned char *)(g_sd + 0x1cab0))
#define stock_wenviron (*(int *)(g_sd + 0x1ca50))

#endif
