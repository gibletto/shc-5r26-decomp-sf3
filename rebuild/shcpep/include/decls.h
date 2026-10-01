#ifndef DECLS_H
#define DECLS_H
#include "ghidra_stubs.h"
#include "stage_types.h"

/* the stock data image (scaffold-rebuild.py): data globals are lvalues at their stock offsets */
extern unsigned char g_sd[];
#define SD(a) ((unsigned int)(g_sd + ((unsigned int)(a) - 0x424000u)))

extern char * FID_conflict___getenv_lk();
extern char * FID_conflict___mbscpy();
extern int * FID_conflict__memcpy();
extern int _CPtoLCID();
extern BOOL ___crtGetStringTypeA();
extern int ___crtLCMapStringA();
extern int ___wtomb_environ();
extern int __amsg_exit();
extern undefined8 __aulldiv();
extern undefined8 __aullrem();
extern int __exit();
extern uchar * __mbschr();
extern int __mbsnbicoll();
extern int __set_osfhnd();
extern int __setargv();
extern char * __strdup();
extern char * __ultoa();
extern size_t _strncnt();
extern char * _strrchr();
extern ulong _strtoul();
extern int _wctomb();
extern char accumulate_compare_test_record_masks();
extern int accumulate_operand_register_masks();
extern int accumulate_special_register_masks();
extern int accumulate_t_bit_masks();
extern int add_epilogue_register_masks();
extern int add_implicit_register_uses();
extern int add_pool_literal();
extern int adjust_label_sptravel_for_moved_record();
extern int advance_sua_record_stream();
extern int * alloc_from_chunks();
extern int * alloc_zeroed();
extern int * alloc_zeroed_flushing_blocks();
extern char append_pred_edges();
extern int apply_function_register_remap();
extern char block_has_code_records();
extern char block_has_non_marker_records();
extern char build_flow_blocks();
extern char build_tail_call_epilogue_records();
extern char call_register_effect();
extern short check_block_move_branches();
extern short check_label_movable();
extern int check_request_read_result();
extern int check_request_write_result();
extern short classify_branch_rewrite_mode();
extern int clean_records_and_merge_common_code();
extern int clear_block_flags_and_labels();
extern int clear_pool_literal_table();
extern int clear_psd_record();
extern int close_and_delete_temp_files();
extern int collect_enter_exit_register_masks();
extern int collect_pred_blocks_back_to_origin();
extern short common_code_ea_equal();
extern char compare_psd_records();
extern int compute_block_sptravel_delta();
extern int compute_call_register_use_def();
extern short compute_record_code_size();
extern char compute_record_register_masks();
extern char compute_record_register_use_def();
extern int configure_signal_handlers();
extern int convert_test_to_dt();
extern ea * copy_ea();
extern undefined4 * copy_environ();
extern label_ref * copy_label_ref_list();
extern int copy_psd_record();
extern int copy_request_trailer_from_temp();
extern int count_common_tail_records();
extern short count_function_saved_registers();
extern short count_label_ref_markers();
extern int count_label_reference();
extern int count_record_label_references();
extern short count_saved_registers();
extern int count_tail_call_epilogue_nodes();
extern symbol * create_symbol_record();
extern uint decide_literal_pool_placement();
extern int decrement_label_ref_count();
extern int defer_add_after_copy();
extern char defer_memory_post_increment();
extern int defer_movi_add_after_copy();
extern int defer_post_increments();
extern int define_label_at_location_counter();
extern char delay_slot_masks_disjoint();
extern int delete_branch_to_next_label();
extern int delete_dead_labels_from_node_list();
extern int delete_dead_stores();
extern int delete_extensions_before_narrow_stores();
extern char delete_matched_target_prefix();
extern int delete_psd_record();
extern int delete_redundant_extensions();
extern int delete_redundant_loads();
extern int delete_redundant_memory_loads();
extern int delete_repeated_r0_constant_loads();
extern int delete_store_load_pairs();
extern int delete_switch_marker_pair();
extern int delete_switch_markers_from_cursor();
extern int delete_switch_markers_in_block();
extern int delete_trailing_branches_to_label();
extern int delete_unreachable_record();
extern int derive_constant_loads_from_previous();
extern int drop_pr_save_restore_if_no_calls();
extern int dump_case_table_record();
extern int dump_casejmp_record();
extern int dump_ea_label_list();
extern int dump_ea_operand();
extern int dump_hex_line();
extern int dump_label_record();
extern int dump_line_record();
extern int dump_memory_hex();
extern int dump_node_list_debug();
extern int dump_psd_operands();
extern int emit_backend_record_streams();
extern int emit_branch_around_literal_pool();
extern int emit_progress_banner();
extern int expand_tail_calls_into_epilogue_jumps();
extern int fill_branch_delay_slots();
extern int fill_cond_branch_slot_from_target();
extern int fill_psd_record();
extern psd * find_block_final_record();
extern psd * find_block_label_jump();
extern short find_block_with_common_tail();
extern symbol * find_label_symbol();
extern symbol * find_label_symbol_of_label_only_block();
extern code_node * find_last_node_of_block();
extern code_node * find_next_nonempty_block();
extern psd * find_next_psd_record();
extern psd * find_next_stack_adjust();
extern code_node * find_node_containing_record();
extern int find_pool_literal();
extern code_node * find_preceding_nonempty_block();
extern psd * find_previous_psd_record();
extern psd * find_previous_slot_candidate();
extern psd * find_register_overwrite();
extern request_section * find_section_record();
extern char find_shift_op_between_values();
extern psd * find_slot_candidate_after_label();
extern symbol * find_symbol_record();
extern int findenv();
extern int flush_block_to_output();
extern int fold_add_immediates();
extern int fold_address_add_into_following_load();
extern int fold_decrement_test_into_dt();
extern int fold_register_move_into_unary_op();
extern int form_predecrement_postincrement_addressing();
extern int frame_offset_to_sp_displacement();
extern int free_ea();
extern int free_flow_block();
extern int free_node_list();
extern int fuse_and_imm_with_zero_test();
extern int genfname();
extern int getSystemCP();
extern char * get_env_directory();
extern int get_marked_symbol_kind();
extern short get_record_source_labno();
extern int get_symbol_attr_bit5_or_forced();
extern uint get_symbol_attr_low_bits();
extern int handle_fault_signal();
extern int handle_interrupt_signal();
extern int immediates_match_except_value();
extern int increment_label_ref_count();
extern int init_namebuf();
extern int invert_cond_branch_over_jump();
extern int is_movi_feeding_stack_add();
extern uint is_record_volatile();
extern char is_register_scan_barrier();
extern int is_word_symbol_literal();
extern char link_flow_block_targets_and_preds();
extern int load_compare_operand_into_r0();
extern code_node * load_next_code_node();
extern code_node * load_next_code_node_list();
extern request * load_request_record_file();
extern int load_symbol_aux_record_stream();
extern char macro_record_changes_register();
extern char macro_record_references_register();
extern code_node * make_common_code_block();
extern int make_new_label_number();
extern char * make_temp_file_name();
extern char match_common_record_run();
extern char match_leading_records();
extern int merge_common_block_tails();
extern int merge_fallthrough_blocks_and_drop_unused_labels();
extern int merge_repeated_and_or_immediates();
extern int merge_sp_add_flags();
extern psd * move_extension_and_shift_followers();
extern int move_psd_record();
extern int move_record_into_branch_slot();
extern int move_target_block_after_jump();
extern ea * new_ea_operand();
extern flow_block * next_flow_block_dropping_empty();
extern char no_use_after_register_clobbered();
extern FILE * open_shared_file();
extern FILE * open_temp_file();
extern char operand_uses_register();
extern char operands_equal();
extern int optimize_current_node_list();
extern int optimize_flow_graph();
extern int parse_cmdline();
extern int pool_free();
extern int pool_free_in_chunk_list();
extern int pool_literal_matches();
extern alloc_chunk * pool_new_chunk();
extern flow_block * prev_flow_block_dropping_empty();
extern int propagate_r0_constant_to_successors();
extern int psd_operand_size_bytes();
extern psd * psd_overwrites_register();
extern int read_asa_bytes();
extern char * read_asa_counted_string();
extern uint read_file_bytes();
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
extern uint read_sua_bytes();
extern uint read_sua_label_operand();
extern int read_sua_label_refs();
extern uint read_sua_operand();
extern uint read_sua_pseudo_instruction();
extern char read_sua_record();
extern uint read_sua_record_body();
extern uchar record_changes_operand();
extern uchar record_changes_register();
extern char record_has_memory_source();
extern uchar register_referenced_between();
extern int release_label_refs_of_record();
extern int remove_target_prefix_executed_by_preds();
extern char rename_register_until_redefined();
extern int report_compiler_message();
extern int report_fatal_message();
extern short report_message_by_code();
extern int report_message_file_error_and_exit();
extern char retarget_block_branch();
extern int retarget_result_to_copy_destination();
extern int reuse_loaded_constants_and_copies();
extern int rewrite_branch_target_chains();
extern int rewrite_branch_targets_for_node_list();
extern int rewrite_movi_from_previous_value();
extern int rewrite_next_movi_of_register();
extern int rewrite_repeated_movi_per_register();
extern int run_node_optimization_passes();
extern int run_prep_pass_and_emit_backend_files();
extern int save_request_trailer_to_temp();
extern int scan_flow_block_records();
extern char select_delay_slot_record();
extern int select_env_variable_names();
extern int setSBCS();
extern int set_ea_disp_sign_extended();
extern int shcpep_main();
extern int shift_ea_registers();
extern int shift_record_registers();
extern uint siglookup();
extern char simplify_flow_block();
extern int stock_NLG_Notify();
extern int stock_NMSG_WRITE();
extern int stock_alloc_osfhnd();
extern int stock_callnewh();
extern int * stock_calloc();
extern int stock_cinit();
extern int stock_commit();
extern int stock_crtCompareStringA();
extern char * stock_crtGetEnvironmentStringsA();
extern int stock_crtsetenv();
extern int stock_doexit();
extern int stock_dosmaperr();
extern int stock_exit();
extern int stock_fcloseall();
extern int stock_flsall();
extern int stock_fptrap();
extern int stock_free();
extern int stock_free_osfhnd();
extern undefined8 stock_get_int64_arg();
extern int stock_get_int_arg();
extern int stock_get_osfhandle();
extern ushort stock_get_short_arg();
extern int * stock_heap_alloc();
extern int stock_heap_init();
extern int stock_initmbctable();
extern int stock_initterm();
extern int stock_ioinit();
extern uchar stock_isatty();
extern uint stock_lseek();
extern int * stock_malloc();
extern char * stock_mbsrchr();
extern int * stock_nh_malloc();
extern int stock_read();
extern int * stock_realloc();
extern int stock_remove();
extern int stock_rmtmp();
extern int stock_setenvp();
extern int stock_setmbcp();
extern int stock_setmode();
extern uint stock_sopen();
extern char * stock_strchr();
extern char * stock_strlen();
extern char * stock_strncat();
extern char * stock_strncpy();
extern uint stock_strtoxl();
extern int stock_unlink();
extern int stock_write();
extern short store_request_record_file();
extern int string_length();
extern int track_stack_pointer_travel();
extern int * try_alloc_zeroed();
extern int unlink_block_from_target_label_refs();
extern char unlink_from_target_preds();
extern char unlink_unreferenced_flow_block();
extern int write_asb_function_aux_record();
extern int write_asb_label_count_record();
extern int write_asb_symbol_name();
extern int write_asb_symbol_record();
extern int write_asb_tag6_record();
extern int write_asb_trailer_record();
extern uint write_file_bytes();
extern int write_final_literal_pool_flag();
extern int write_ofb_casejmp_record();
extern int write_ofb_ctbl_record();
extern int write_ofb_end_record();
extern int write_ofb_enter_record();
extern int write_ofb_exit_record();
extern int write_ofb_immediate_record();
extern int write_ofb_jump_record();
extern int write_ofb_label_operand_record();
extern int write_ofb_label_record();
extern int write_ofb_mov_loc_record();
extern int write_ofb_mova_lc_record();
extern int write_ofb_op2e_record();
extern int write_ofb_record();
extern int write_ofb_transfer_record();
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
extern int write_sub_bytes();
extern int write_sub_casejmp_record();
extern int write_sub_cent_record();
extern int write_sub_ctbl_record();
extern int write_sub_instruction_record();
extern int write_sub_label_list();
extern int write_sub_label_record();
extern int write_sub_line_record();
extern int write_sub_machine_op_record();
extern int write_sub_op10_record();
extern int write_sub_operand();
extern int write_sub_record();
extern int write_sub_section_record();
extern int xtoa();

#define DAT_00428778 (*(short *)(g_sd + 0x4778))
#define DAT_004287b4 (*(int *)(g_sd + 0x47b4))
#define DAT_004287b8 (*(int *)(g_sd + 0x47b8))
#define DAT_004287bc (*(int *)(g_sd + 0x47bc))
#define DAT_0042896c (*(int *)(g_sd + 0x496c))
#define DAT_00428970 (*(int *)(g_sd + 0x4970))
#define DAT_00428984 (*(unsigned char *)(g_sd + 0x4984))
#define DAT_00428988 (*(unsigned char *)(g_sd + 0x4988))
#define DAT_00428990 (*(unsigned char *)(g_sd + 0x4990))
#define DAT_00428d68 (*(int *)(g_sd + 0x4d68))
#define DAT_00428d94 (*(int *)(g_sd + 0x4d94))
#define DAT_00428db4 (*(unsigned char *)(g_sd + 0x4db4))
#define DAT_00428f38 (*(int *)(g_sd + 0x4f38))
#define DAT_004291b8 (*(int *)(g_sd + 0x51b8))
#define DAT_00429220 (*(unsigned char *)(g_sd + 0x5220))
#define DAT_00429224 (*(unsigned char *)(g_sd + 0x5224))
#define DAT_0042ae54 (*(int *)(g_sd + 0x6e54))
#define PTR_s_DUMMY_00426c68 (*(unsigned char * *)(g_sd + 0x2c68))
#define PTR_s_Internal_error_004283d8 (*(char * *)(g_sd + 0x43d8))
#define _g_block_end_record_bytes (*(int *)(g_sd + 0x6e0c))
#define _g_brsrchk_switch_marker (*(int *)(g_sd + 0x5c30))
#define _g_inc_env_name (*(int *)(g_sd + 0x6e28))
#define _g_lib_env_name_14 (*(int *)(g_sd + 0x6e14))
#define _g_lib_env_name_18 (*(int *)(g_sd + 0x6e18))
#define _g_lib_env_name_20 (*(int *)(g_sd + 0x6e20))
#define _g_lib_env_name_24 (*(int *)(g_sd + 0x6e24))
#define _g_pool_carried_literal_bytes (*(int *)(g_sd + 0x3c6c))
#define _g_pool_pending_literal_bytes (*(int *)(g_sd + 0x3c64))
#define _stock_C_Exit_Done (*(int *)(g_sd + 0x44a4))
#define _stock_errno (*(int *)(g_sd + 0x4460))
#define _stock_pgmptr (*(int *)(g_sd + 0x4498))
#define g_access_size_bytes (*(unsigned char *)(g_sd + 0x28d0))
#define g_after_switch_end (*(short *)(g_sd + 0x6d3c))
#define g_alloc_size_classes (*(alloc_class_table * *)(g_sd + 0x1318))
#define g_asa_input (*(int *)(g_sd + 0x5348))
#define g_asa_read_buffer (*(unsigned char (*)[8])(g_sd + 0x5248))
#define g_asa_trailer_bytes (*(unsigned char *)(g_sd + 0x5c10))
#define g_asa_trailer_value1 (*(short *)(g_sd + 0x5d00))
#define g_asa_trailer_value2 (*(short *)(g_sd + 0x6d48))
#define g_asb_output (*(int *)(g_sd + 0x5d20))
#define g_aux_record_count (*(int *)(g_sd + 0x5bf4))
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))
#define g_block_being_loaded (*(code_node * *)(g_sd + 0x5bb4))
#define g_block_code_count (*(int *)(g_sd + 0x5cf4))
#define g_block_complete (*(int *)(g_sd + 0x5cf0))
#define g_block_flushed_early (*(int *)(g_sd + 0x5bec))
#define g_branch_defs_hi (*(int *)(g_sd + 0x5ba4))
#define g_branch_defs_lo (*(int *)(g_sd + 0x5ba0))
#define g_branch_uses_hi (*(int *)(g_sd + 0x5b9c))
#define g_branch_uses_lo (*(int *)(g_sd + 0x5b98))
#define g_common_tail_a (*(psd * *)(g_sd + 0x5bb0))
#define g_common_tail_b (*(psd * *)(g_sd + 0x5ba8))
#define g_common_tail_count (*(int *)(g_sd + 0x5bac))
#define g_copy_rest_verbatim (*(int *)(g_sd + 0x6df4))
#define g_cur_sptravel (*(int *)(g_sd + 0x5c34))
#define g_current_aux_index (*(int *)(g_sd + 0x5d04))
#define g_current_block (*(code_node * *)(g_sd + 0x5c38))
#define g_current_input_record (*(int *)(g_sd + 0x5bbc))
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#define g_current_request (*(request * *)(g_sd + 0x5bf0))
#define g_current_section (*(request_section * *)(g_sd + 0x5d0c))
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))
#define g_ea_template (*(ea *)(g_sd + 0x6d30))
#define g_empty_psd (*(int *)(g_sd + 0x5bd0))
#define g_entry_arg_move_pending (*(int *)(g_sd + 0x6d6c))
#define g_env_directory (*(char (*)[118])(g_sd + 0x53d8))
#define g_extra_symbol_blocks (*(int *)(g_sd + 0x1c9c))
#define g_flow_blocks (*(flow_block * *)(g_sd + 0x6e08))
#define g_frame_offset_literal_table (*(literal_table *)(g_sd + 0x5990))
#define g_in_program_section (*(int *)(g_sd + 0x5d14))
#define g_in_unreachable_code (*(int *)(g_sd + 0x3648))
#define g_input_finished (*(int *)(g_sd + 0x6d24))
#define g_label_alloc_disabled (*(int *)(g_sd + 0x5bf8))
#define g_label_ref_template (*(label_ref *)(g_sd + 0x5d18))
#define g_last_allocation (*(int *)(g_sd + 0x6d44))
#define g_last_block (*(code_node * *)(g_sd + 0x5bc4))
#define g_last_labno (*(short *)(g_sd + 0x5be8))
#define g_last_line_filno (*(short *)(g_sd + 0x2720))
#define g_last_line_linno (*(short *)(g_sd + 0x2724))
#define g_last_loaded_node (*(code_node * *)(g_sd + 0x5bb8))
#define g_last_symbol_record (*(symbol * *)(g_sd + 0x5d28))
#define g_line_kind5 (*(unsigned char *)(g_sd + 0x21f8))
#define g_lit_output (*(int *)(g_sd + 0x6df8))
#define g_literal_label_serial (*(short *)(g_sd + 0x3c60))
#define g_loaded_request (*(request * *)(g_sd + 0x6e34))
#define g_location_counter (*(int *)(g_sd + 0x6dfc))
#define g_long_literal_table (*(literal_table *)(g_sd + 0x5780))
#define g_message_number_text (*(unsigned char *)(g_sd + 0x53d0))
#define g_mov_loc_size_table (*(unsigned char *)(g_sd + 0x3e80))
#define g_node_list_word_00429c08 (*(int *)(g_sd + 0x5c08))
#define g_ofb_output (*(int *)(g_sd + 0x5cf8))
#define g_ofb_record_out (*(int *)(g_sd + 0x5358))
#define g_op_code_size_table (*(short (*)[256])(g_sd + 0x3c80))
#define g_op_dest_operand (*(unsigned char *)(g_sd + 0x1320))
#define g_op_is_code_record (*(unsigned char *)(g_sd + 0x2520))
#define g_op_is_macro (*(unsigned char *)(g_sd + 0x1520))
#define g_op_reachability_class (*(unsigned char *)(g_sd + 0x3548))
#define g_pid_digit_count (*(int *)(g_sd + 0x4310))
#define g_pool_carried_code_bytes (*(int *)(g_sd + 0x3c70))
#define g_pool_carried_has_word (*(unsigned char *)(g_sd + 0x3c74))
#define g_pool_carried_literal_bytes (*(short *)(g_sd + 0x3c6c))
#define g_pool_code_bytes (*(int *)(g_sd + 0x3c68))
#define g_pool_flush_pending (*(int *)(g_sd + 0x3c7c))
#define g_pool_segment_has_word (*(unsigned char *)(g_sd + 0x3c78))
#define g_process_id (*(int *)(g_sd + 0x4314))
#define g_progress_banner_table (*(unsigned char * *)(g_sd + 0x42b8))
#define g_pushed_back_record (*(psd * *)(g_sd + 0x5bc0))
#define g_rec_def_mask_hi (*(int *)(g_sd + 0x6d5c))
#define g_rec_def_mask_lo (*(int *)(g_sd + 0x6d58))
#define g_rec_use_mask_hi (*(int *)(g_sd + 0x5c44))
#define g_rec_use_mask_lo (*(int *)(g_sd + 0x5c40))
#define g_reg_mask_table (*(unsigned int (*)[128])(g_sd + 0x1ff8))
#define g_reg_remap_expno (*(int *)(g_sd + 0x6df0))
#define g_reg_remap_table (*(unsigned char *)(g_sd + 0x6d80))
#define g_request (*(request * *)(g_sd + 0x6e04))
#define g_request_being_loaded (*(request * *)(g_sd + 0x5368))
#define g_request_cpp_block_size (*(short *)(g_sd + 0x6e3a))
#define g_request_fixed_size (*(short *)(g_sd + 0x6e3c))
#define g_request_record_path (*(int *)(g_sd + 0x6e2c))
#define g_request_result_0d4 (*(int *)(g_sd + 0x6e00))
#define g_request_trailer_file (*(int *)(g_sd + 0x6e30))
#define g_request_version_mismatch (*(short *)(g_sd + 0x6e38))
#define g_reuse_input_record (*(int *)(g_sd + 0x5d08))
#define g_runtime_call_changes_r0 (*(unsigned char *)(g_sd + 0x1897))
#define g_runtime_call_reads_r0 (*(unsigned char *)(g_sd + 0x171f))
#define g_runtime_call_reads_r1 (*(unsigned char *)(g_sd + 0x17df))
#define g_runtime_call_sptravel (*(unsigned char *)(g_sd + 0x1d1c))
#define g_scratch_ea (*(ea *)(g_sd + 0x40a8))
#define g_section_end (*(int *)(g_sd + 0x6d40))
#define g_shift_op_for_value_ratio (*(unsigned char *)(g_sd + 0x28c8))
#define g_stage_flags (*(int *)(g_sd + 0x6d64))
#define g_stream_func_aux_index (*(int *)(g_sd + 0x5cfc))
#define g_string_pool_block (*(int *)(g_sd + 0x5354))
#define g_string_pool_cursor (*(int *)(g_sd + 0x534c))
#define g_string_pool_end (*(int *)(g_sd + 0x5350))
#define g_sua_input (*(int *)(g_sd + 0x5c00))
#define g_sua_op_format (*(unsigned char *)(g_sd + 0x1118))
#define g_sua_read_file (*(int *)(g_sd + 0x5238))
#define g_sua_record_class (*(unsigned char *)(g_sd + 0x2320))
#define g_sub_filno (*(short *)(g_sd + 0x535c))
#define g_sub_linno (*(short *)(g_sd + 0x5360))
#define g_sub_output (*(int *)(g_sd + 0x5bfc))
#define g_sub_record_format_table (*(unsigned char (*)[484])(g_sd + 0x3ec0))
#define g_sub_report_extra_arg (*(short *)(g_sd + 0x5364))
#define g_switch_brackets_end (*(int *)(g_sd + 0x5c54))
#define g_switch_marker_depth (*(int *)(g_sd + 0x6d60))
#define g_switch_marker_pairs (*(int *)(g_sd + 0x5c50))
#define g_switch_scan_block (*(code_node * *)(g_sd + 0x5c04))
#define g_switch_scan_single_block (*(int *)(g_sd + 0x5d24))
#define g_symbol_hash (*(symbol * (*)[1021])(g_sd + 0x5d30))
#define g_symbol_record_base (*(symbol * *)(g_sd + 0x6e10))
#define g_symbol_records (*(symbol * *)(g_sd + 0x5d10))
#define g_symbol_sequence_counter (*(int *)(g_sd + 0x5240))
#define g_tail_merge_in_list (*(int *)(g_sd + 0x6d68))
#define g_temp_file_count (*(int *)(g_sd + 0x5374))
#define g_temp_files (*(temp_file (*)[8])(g_sd + 0x5378))
#define g_temp_name_buffer (*(int *)(g_sd + 0x430c))
#define g_temp_name_counter (*(int *)(g_sd + 0x4318))
#define g_temp_path_in_progress (*(int *)(g_sd + 0x53cc))
#define g_tmp_env_name (*(int *)(g_sd + 0x6e1c))
#define g_word_literal_table (*(literal_table *)(g_sd + 0x5570))
#define s_Base_Next_Block______d_____00427158 (*(char (*)[28])(g_sd + 0x3158))
#define s_Base_Next_Node______d_____00427138 (*(char (*)[31])(g_sd + 0x3138))
#define s_Copyright__c__1992_1996_Hitachi__00425cd0 (*(char (*)[76])(g_sd + 0x1cd0))
#define s_EA__d_TABLE_00427384 (*(char (*)[24])(g_sd + 0x3384))
#define s_LABTBL_NO_d_004273c4 (*(char (*)[27])(g_sd + 0x33c4))
#define s_LISTTBL_chained_node_pointer___0_00427a20 (*(char (*)[37])(g_sd + 0x3a20))
#define s_Microsoft_Visual_C___Runtime_Lib_00428d6c (*(char (*)[37])(g_sd + 0x4d6c))
#define s_PSEUDO_CODE_TABLE_DUMP___________00427104 (*(char (*)[49])(g_sd + 0x3104))
#define s_Runtime_Error__Program__00428d98 (*(char (*)[28])(g_sd + 0x4d98))
#define s_SHCPP_INC_0042843c (*(char (*)[10])(g_sd + 0x443c))
#define s_SHCPP_LIB_00428430 (*(char (*)[10])(g_sd + 0x4430))
#define s_SHCPP_TMP_00428424 (*(char (*)[10])(g_sd + 0x4424))
#define s_SHC_INC_00428458 (*(char (*)[8])(g_sd + 0x4458))
#define s_SHC_LIB_00428450 (*(char (*)[8])(g_sd + 0x4450))
#define s_SHC_TMP_00428448 (*(char (*)[8])(g_sd + 0x4448))
#define s_SH_SERIES_C_Compiler_Ver__5_0_Re_00425ca0 (*(char (*)[44])(g_sd + 0x1ca0))
#define s_SWBGN___SWEND_delete__00427b28 (*(char (*)[23])(g_sd + 0x3b28))
#define s_TST_code_0042508c (*(char (*)[11])(g_sd + 0x108c))
#define s__02x_00427c58 (*(char (*)[6])(g_sd + 0x3c58))
#define s__08lx__00427c04 (*(char (*)[7])(g_sd + 0x3c04))
#define s__0____004283e4 (*(char (*)[7])(g_sd + 0x43e4))
#define s_______after_register_shift__ea1__004267e0 (*(char (*)[41])(g_sd + 0x27e0))
#define s_______after_register_shift__ea2__004267b4 (*(char (*)[41])(g_sd + 0x27b4))
#define s_______before_register_shift__ea1_0042689c (*(char (*)[42])(g_sd + 0x289c))
#define s_______before_register_shift__ea2_0042681c (*(char (*)[42])(g_sd + 0x281c))
#define s_____after_reg_____00426728 (*(char (*)[20])(g_sd + 0x2728))
#define s_____before_reg_____0042673c (*(char (*)[20])(g_sd + 0x273c))
#define s_____end_expno_____0042675c (*(char (*)[20])(g_sd + 0x275c))
#define s_____function_name_____s_____00426794 (*(char (*)[29])(g_sd + 0x2794))
#define s_____start_expno_____00426780 (*(char (*)[20])(g_sd + 0x2780))
#define s___caslab_max_min___x_004273e0 (*(char (*)[23])(g_sd + 0x33e0))
#define s___casmin__x_004273f8 (*(char (*)[13])(g_sd + 0x33f8))
#define s___default_lab__x_00427408 (*(char (*)[18])(g_sd + 0x3408))
#define s___eabase__d_004271a4 (*(char (*)[23])(g_sd + 0x31a4))
#define s___eadisp__x_00427174 (*(char (*)[14])(g_sd + 0x3174))
#define s___eaindex__d_00427194 (*(char (*)[14])(g_sd + 0x3194))
#define s___eamisc__x_00427184 (*(char (*)[13])(g_sd + 0x3184))
#define s___labno2__x_0042739c (*(char (*)[14])(g_sd + 0x339c))
#define s___psddmy1__x_00427450 (*(char (*)[14])(g_sd + 0x3450))
#define s___psddmy2__x_00427440 (*(char (*)[15])(g_sd + 0x3440))
#define s___psddmy3__x_004274a4 (*(char (*)[15])(g_sd + 0x34a4))
#define s___psdexpno__d_00427090 (*(char (*)[16])(g_sd + 0x3090))
#define s___psdfilno__x_00427518 (*(char (*)[15])(g_sd + 0x3518))
#define s___psdflg__x_004270d8 (*(char (*)[13])(g_sd + 0x30d8))
#define s___psdlabno__x_00427460 (*(char (*)[16])(g_sd + 0x3460))
#define s___psdlinno__d_0042706c (*(char (*)[16])(g_sd + 0x306c))
#define s___psdlinno__x_004274e4 (*(char (*)[15])(g_sd + 0x34e4))
#define s___psdmisc__x_004270c8 (*(char (*)[14])(g_sd + 0x30c8))
#define s___psdstate__x_004274d4 (*(char (*)[16])(g_sd + 0x34d4))
#define s___psdswexit__x_00427470 (*(char (*)[16])(g_sd + 0x3470))
#define s___psdtmp__x_004270b8 (*(char (*)[14])(g_sd + 0x30b8))
#define s__s_d__d_00428328 (*(char (*)[8])(g_sd + 0x4328))
#define s_ab_004283dc (*(char (*)[3])(g_sd + 0x43dc))
#define s_basereg__d_00426858 (*(char (*)[14])(g_sd + 0x2858))
#define s_br_brchg_cp___08lx__004276cc (*(char (*)[21])(g_sd + 0x36cc))
#define s_br_brchg_end__0042765c (*(char (*)[15])(g_sd + 0x365c))
#define s_br_brchg_end__cp___08lx__00427694 (*(char (*)[26])(g_sd + 0x3694))
#define s_br_brchg_start__004276e4 (*(char (*)[17])(g_sd + 0x36e4))
#define s_br_brchg_wcp___08lx__0042766c (*(char (*)[22])(g_sd + 0x366c))
#define s_brsrchk_end__cp__08lx_00427ae8 (*(char (*)[24])(g_sd + 0x3ae8))
#define s_brsrchk_end__return_0_00427b00 (*(char (*)[23])(g_sd + 0x3b00))
#define s_check_register_number___d_00425aa0 (*(char (*)[27])(g_sd + 0x1aa0))
#define s_clear_node_pointer___08lx_00427a04 (*(char (*)[27])(g_sd + 0x3a04))
#define s_cnext_end__psdtbl___08lx__00425b78 (*(char (*)[27])(g_sd + 0x1b78))
#define s_cnext_end_not_find___00425b94 (*(char (*)[22])(g_sd + 0x1b94))
#define s_cnext_start__psdtbl___08lx__node_00425bac (*(char (*)[44])(g_sd + 0x1bac))
#define s_cnode_start__psdtbl___08lx__node_004250ec (*(char (*)[44])(g_sd + 0x10ec))
#define s_code_counter___d_0042781c (*(char (*)[18])(g_sd + 0x381c))
#define s_code_pointer___08lx_00426240 (*(char (*)[21])(g_sd + 0x2240))
#define s_compare_code_pointer___08lx_00426220 (*(char (*)[29])(g_sd + 0x2220))
#define s_cp___08lx_0042503c (*(char (*)[11])(g_sd + 0x103c))
#define s_cpyea_end__eap__08lx_0042790c (*(char (*)[22])(g_sd + 0x390c))
#define s_cpyea_start__eaptr__08lx_00427940 (*(char (*)[26])(g_sd + 0x3940))
#define s_cpylab_end__newlp___08lx_0042795c (*(char (*)[26])(g_sd + 0x395c))
#define s_cpylab_start__lp___08lx_00427998 (*(char (*)[25])(g_sd + 0x3998))
#define s_d_comcd_end__00427734 (*(char (*)[14])(g_sd + 0x3734))
#define s_d_comcd_start__00427744 (*(char (*)[16])(g_sd + 0x3744))
#define s_d_condbr_start__00427ba4 (*(char (*)[17])(g_sd + 0x3ba4))
#define s_dc_bcode_end__np__08lx_scp__08lx_004279b4 (*(char (*)[34])(g_sd + 0x39b4))
#define s_dc_bcode_start__bp__08lx_004279d8 (*(char (*)[26])(g_sd + 0x39d8))
#define s_dc_cmp_end__common_code_number___004277a0 (*(char (*)[37])(g_sd + 0x37a0))
#define s_dc_cmp_start__004277e0 (*(char (*)[15])(g_sd + 0x37e0))
#define s_dc_cpycd___input_psdtbl_dmp_004278c8 (*(char (*)[28])(g_sd + 0x38c8))
#define s_dc_cpycd___output_psdtbl_dmp_004278a8 (*(char (*)[29])(g_sd + 0x38a8))
#define s_dc_cpycd_end__00427898 (*(char (*)[15])(g_sd + 0x3898))
#define s_dc_cpycd_start__inp__08lx__outp__004278e4 (*(char (*)[39])(g_sd + 0x38e4))
#define s_dc_eacmp_end__rc___d_004277f0 (*(char (*)[22])(g_sd + 0x37f0))
#define s_dc_eacmp_start__00427808 (*(char (*)[17])(g_sd + 0x3808))
#define s_dc_lbchk_end__rc___d_00427788 (*(char (*)[22])(g_sd + 0x3788))
#define s_dc_lbchk_end__rc__d_00427754 (*(char (*)[21])(g_sd + 0x3754))
#define s_dc_mklab_end__labno___ld_0042785c (*(char (*)[26])(g_sd + 0x385c))
#define s_dc_mklab_start__g_labno___ld_00427878 (*(char (*)[31])(g_sd + 0x3878))
#define s_declab_start__004259b0 (*(char (*)[15])(g_sd + 0x19b0))
#define s_decriment_labno___d__004259d8 (*(char (*)[22])(g_sd + 0x19d8))
#define s_delaymov_end__00427bb8 (*(char (*)[15])(g_sd + 0x3bb8))
#define s_delaymov_start__00427bc8 (*(char (*)[17])(g_sd + 0x3bc8))
#define s_delcode_end__delete_code_pointer_00425958 (*(char (*)[41])(g_sd + 0x1958))
#define s_delcode_start__current_code_poin_00425984 (*(char (*)[44])(g_sd + 0x1984))
#define s_delete_code___08lx__exit_number__00427b54 (*(char (*)[37])(g_sd + 0x3b54))
#define s_dellab_end__labno__d_004276f8 (*(char (*)[22])(g_sd + 0x36f8))
#define s_delload_end__00426210 (*(char (*)[14])(g_sd + 0x2210))
#define s_delload_start__node_pointer___08_00426258 (*(char (*)[36])(g_sd + 0x2258))
#define s_delmemld_end__0042627c (*(char (*)[15])(g_sd + 0x227c))
#define s_delmemld_start__node_pointer___0_0042628c (*(char (*)[37])(g_sd + 0x228c))
#define s_delstld_end__004262b4 (*(char (*)[14])(g_sd + 0x22b4))
#define s_delstld_start__node_pointer___08_004262c4 (*(char (*)[36])(g_sd + 0x22c4))
#define s_delstore_end__004262e8 (*(char (*)[15])(g_sd + 0x22e8))
#define s_delstore_start__node_pointer___0_004262f8 (*(char (*)[37])(g_sd + 0x22f8))
#define s_dot_00427c4c (*(char (*)[2])(g_sd + 0x3c4c))
#define s_dot_tmp_00428320 (*(char (*)[5])(g_sd + 0x4320))
#define s_eatbl_1_00425c80 (*(char (*)[8])(g_sd + 0x1c80))
#define s_eatbl_2_00425c78 (*(char (*)[8])(g_sd + 0x1c78))
#define s_empty_004281bc (*(char (*)[1])(g_sd + 0x41bc))
#define s_expno___d_____00426878 (*(char (*)[16])(g_sd + 0x2878))
#define s_imadd_end__00425030 (*(char (*)[12])(g_sd + 0x1030))
#define s_imadd_start__cp___08lx_00425054 (*(char (*)[24])(g_sd + 0x1054))
#define s_imadd_start__nodeptr___08lx_0042506c (*(char (*)[29])(g_sd + 0x106c))
#define s_imandor_end__004268d4 (*(char (*)[14])(g_sd + 0x28d4))
#define s_imandor_start__cp___08lx_004268e4 (*(char (*)[26])(g_sd + 0x28e4))
#define s_imandor_start__nodeptr___08lx_00426900 (*(char (*)[31])(g_sd + 0x2900))
#define s_inclad_start__labno___d__00425a40 (*(char (*)[26])(g_sd + 0x1a40))
#define s_incriment_labno___d__00425a28 (*(char (*)[22])(g_sd + 0x1a28))
#define s_indexreg__d_0042680c (*(char (*)[14])(g_sd + 0x280c))
#define s_indexreg__d_00426848 (*(char (*)[15])(g_sd + 0x2848))
#define s_input_eatbl_00427934 (*(char (*)[12])(g_sd + 0x3934))
#define s_input_labtbl_00427988 (*(char (*)[13])(g_sd + 0x3988))
#define s_labchk_end__rc__d_00427aa8 (*(char (*)[19])(g_sd + 0x3aa8))
#define s_labchk_start__labno___d__00427acc (*(char (*)[26])(g_sd + 0x3acc))
#define s_label_reference_count___ld_004259f0 (*(char (*)[28])(g_sd + 0x19f0))
#define s_labelno___d_00427684 (*(char (*)[13])(g_sd + 0x3684))
#define s_labelno___d__savelab___d_004276b0 (*(char (*)[26])(g_sd + 0x36b0))
#define s_labld_end__00425098 (*(char (*)[12])(g_sd + 0x1098))
#define s_labld_start__cp___08lx_004250b4 (*(char (*)[24])(g_sd + 0x10b4))
#define s_labld_start__nodeptr___08lx_004250cc (*(char (*)[29])(g_sd + 0x10cc))
#define s_labno___d__00425a1c (*(char (*)[12])(g_sd + 0x1a1c))
#define s_labno___d__reference_count___ld_00427710 (*(char (*)[33])(g_sd + 0x3710))
#define s_labtype___d_00427abc (*(char (*)[13])(g_sd + 0x3abc))
#define s_labtype___d__00425a0c (*(char (*)[14])(g_sd + 0x1a0c))
#define s_make_LISTTBL_blkptr___08lx_0042776c (*(char (*)[28])(g_sd + 0x376c))
#define s_make_LISTTBL_node_pointer___08lx_00427a48 (*(char (*)[34])(g_sd + 0x3a48))
#define s_make_node_number___d_00427844 (*(char (*)[22])(g_sd + 0x3844))
#define s_mcrrfchk_end__rc___d_00425b24 (*(char (*)[22])(g_sd + 0x1b24))
#define s_mcrrgchk_end__rc___d_00425ad0 (*(char (*)[22])(g_sd + 0x1ad0))
#define s_mcrrgchk_start__00425ae8 (*(char (*)[17])(g_sd + 0x1ae8))
#define s_memchgchk_end__rc___ld_00425b3c (*(char (*)[24])(g_sd + 0x1b3c))
#define s_memchgchk_start__00425b54 (*(char (*)[18])(g_sd + 0x1b54))
#define s_mvcode_end__00427bdc (*(char (*)[13])(g_sd + 0x3bdc))
#define s_mvcode_start__00427bec (*(char (*)[15])(g_sd + 0x3bec))
#define s_ncp___08lx_00425048 (*(char (*)[12])(g_sd + 0x1048))
#define s_nl_00427c48 (*(char (*)[2])(g_sd + 0x3c48))
#define s_nl_sp_sp_004283ec (*(char (*)[4])(g_sd + 0x43ec))
#define s_nncp___08lx_004250a4 (*(char (*)[13])(g_sd + 0x10a4))
#define s_node_number___d_00427830 (*(char (*)[17])(g_sd + 0x3830))
#define s_nodetbl__08lx_00425c08 (*(char (*)[15])(g_sd + 0x1c08))
#define s_nodetbl___08lx_00425b68 (*(char (*)[16])(g_sd + 0x1b68))
#define s_nxtbrdel_start__code_pointer___0_00427b7c (*(char (*)[37])(g_sd + 0x3b7c))
#define s_opeacmp_end__rc___d_00425c60 (*(char (*)[21])(g_sd + 0x1c60))
#define s_opeacmp_start__00425c88 (*(char (*)[16])(g_sd + 0x1c88))
#define s_open_mode_rb (*(unsigned char *)(g_sd + 0x1c98))
#define s_open_mode_wb (*(unsigned char *)(g_sd + 0x21fc))
#define s_opvolchk_end__rc___ld_00425a5c (*(char (*)[23])(g_sd + 0x1a5c))
#define s_opvolchk_start__00425a74 (*(char (*)[17])(g_sd + 0x1a74))
#define s_output_eatbl_00427924 (*(char (*)[13])(g_sd + 0x3924))
#define s_output_labtbl_00427978 (*(char (*)[14])(g_sd + 0x3978))
#define s_pct_c_00427c50 (*(char (*)[3])(g_sd + 0x3c50))
#define s_pct_d_004283f0 (*(char (*)[3])(g_sd + 0x43f0))
#define s_prdecea_end__00426920 (*(char (*)[14])(g_sd + 0x2920))
#define s_prdecea_start__cp___08lx_00426930 (*(char (*)[26])(g_sd + 0x2930))
#define s_prdecea_start__nodeptr___08lx_0042694c (*(char (*)[31])(g_sd + 0x294c))
#define s_prefind_end__nodetbl__08lx__00425be8 (*(char (*)[29])(g_sd + 0x1be8))
#define s_prefind_end__psdtbl__08lx_00425c18 (*(char (*)[26])(g_sd + 0x1c18))
#define s_prefind_start__nodetbl__08lx__ps_00425c34 (*(char (*)[44])(g_sd + 0x1c34))
#define s_psd_f (*(char (*)[6])(g_sd + 0x2200))
#define s_psdfilno__d_0042707c (*(char (*)[20])(g_sd + 0x307c))
#define s_psdop___x_____00426888 (*(char (*)[17])(g_sd + 0x2888))
#define s_psdsptravel__x_004270a0 (*(char (*)[23])(g_sd + 0x30a0))
#define s_psdtbl__08lx_00425bd8 (*(char (*)[14])(g_sd + 0x1bd8))
#define s_reference_count___ld_004259c0 (*(char (*)[22])(g_sd + 0x19c0))
#define s_refgchk_end__rc___d_00425afc (*(char (*)[21])(g_sd + 0x1afc))
#define s_refgchk_start__00425b14 (*(char (*)[16])(g_sd + 0x1b14))
#define s_regchgchk_end__rc___d_00425a88 (*(char (*)[23])(g_sd + 0x1a88))
#define s_regchgchk_start__00425abc (*(char (*)[18])(g_sd + 0x1abc))
#define s_rp___08lx__r1___08lx_004277c8 (*(char (*)[22])(g_sd + 0x37c8))
#define s_sc_brchk_end__rc___d_00427a7c (*(char (*)[22])(g_sd + 0x3a7c))
#define s_sc_brchk_start__00427a94 (*(char (*)[17])(g_sd + 0x3a94))
#define s_sp_004283e0 (*(char (*)[2])(g_sd + 0x43e0))
#define s_sp_pct_s_nl_00427bfc (*(char (*)[5])(g_sd + 0x3bfc))
#define s_sp_sp_sp_00427c54 (*(char (*)[4])(g_sd + 0x3c54))
#define s_str_00426750 (*(char (*)[12])(g_sd + 0x2750))
#define s_str_00426770 (*(char (*)[13])(g_sd + 0x2770))
#define s_str_004270e8 (*(char (*)[25])(g_sd + 0x30e8))
#define s_str_004271bc (*(char (*)[30])(g_sd + 0x31bc))
#define s_str_004271dc (*(char (*)[33])(g_sd + 0x31dc))
#define s_str_00427200 (*(char (*)[33])(g_sd + 0x3200))
#define s_str_00427224 (*(char (*)[31])(g_sd + 0x3224))
#define s_str_00427244 (*(char (*)[32])(g_sd + 0x3244))
#define s_str_00427264 (*(char (*)[31])(g_sd + 0x3264))
#define s_str_00427284 (*(char (*)[30])(g_sd + 0x3284))
#define s_str_004272a4 (*(char (*)[32])(g_sd + 0x32a4))
#define s_str_004272c4 (*(char (*)[32])(g_sd + 0x32c4))
#define s_str_004272e4 (*(char (*)[32])(g_sd + 0x32e4))
#define s_str_00427304 (*(char (*)[32])(g_sd + 0x3304))
#define s_str_00427324 (*(char (*)[32])(g_sd + 0x3324))
#define s_str_00427344 (*(char (*)[31])(g_sd + 0x3344))
#define s_str_00427364 (*(char (*)[30])(g_sd + 0x3364))
#define s_str_004273ac (*(char (*)[24])(g_sd + 0x33ac))
#define s_str_0042741c (*(char (*)[33])(g_sd + 0x341c))
#define s_str_00427480 (*(char (*)[34])(g_sd + 0x3480))
#define s_str_004274b4 (*(char (*)[32])(g_sd + 0x34b4))
#define s_str_004274f4 (*(char (*)[33])(g_sd + 0x34f4))
#define s_str_00427528 (*(char (*)[30])(g_sd + 0x3528))
#define s_str_00427c0c (*(char (*)[58])(g_sd + 0x3c0c))
#define s_str_00428db8 (*(char (*)[24])(g_sd + 0x4db8))
#define s_str_chg_end__004279f4 (*(char (*)[14])(g_sd + 0x39f4))
#define s_str_chg_start__00427a6c (*(char (*)[16])(g_sd + 0x3a6c))
#define s_sw_delete_end__00427b18 (*(char (*)[16])(g_sd + 0x3b18))
#define s_sw_delete_start__00427b40 (*(char (*)[18])(g_sd + 0x3b40))
#define s_sym_f (*(char (*)[6])(g_sd + 0x2208))
#define s_tempreg__d_00426868 (*(char (*)[13])(g_sd + 0x2868))
#define s_wb_plus_0042831c (*(char (*)[4])(g_sd + 0x431c))
#define s_wcp___08lx__0042764c (*(char (*)[13])(g_sd + 0x364c))
#define stock_XcptActTab (*(unsigned char *)(g_sd + 0x47c0))
#define stock_XcptActTabCount (*(int *)(g_sd + 0x4840))
#define stock_acmdln (*(int *)(g_sd + 0x7f60))
#define stock_aenvptr (*(int *)(g_sd + 0x44a8))
#define stock_aexit_rtn (*(char * *)(g_sd + 0x44b0))
#define stock_app_type (*(int *)(g_sd + 0x44b8))
#define stock_argc (*(int *)(g_sd + 0x447c))
#define stock_argv (*(int *)(g_sd + 0x4480))
#define stock_badioinfo (*(unsigned char *)(g_sd + 0x4a70))
#define stock_crtheap (*(int *)(g_sd + 0x6f50))
#define stock_doserrno (*(int *)(g_sd + 0x4464))
#define stock_environ (*(int *)(g_sd + 0x4488))
#define stock_error_mode (*(int *)(g_sd + 0x44b4))
#define stock_errtable (*(int *)(g_sd + 0x4dd0))
#define stock_exitflag (*(unsigned char *)(g_sd + 0x44a0))
#define stock_fSystemSet (*(int *)(g_sd + 0x4974))
#define stock_f_use_CompareString (*(int *)(g_sd + 0x522c))
#define stock_f_use_GetEnvironmentStrings (*(int *)(g_sd + 0x4850))
#define stock_f_use_GetStringType (*(int *)(g_sd + 0x521c))
#define stock_f_use_LCMapString (*(int *)(g_sd + 0x5234))
#define stock_fmode (*(int *)(g_sd + 0x5214))
#define stock_fpinit (*(int *)(g_sd + 0x7f68))
#define stock_initenv (*(int *)(g_sd + 0x448c))
#define stock_lc_codepage (*(int *)(g_sd + 0x51c8))
#define stock_mb_cur_max (*(int *)(g_sd + 0x5154))
#define stock_mbcodepage (*(int *)(g_sd + 0x495c))
#define stock_mbctype (*(int *)(g_sd + 0x4858))
#define stock_mblcid (*(int *)(g_sd + 0x4960))
#define stock_mbulinfo (*(int *)(g_sd + 0x4968))
#define stock_namebuf0 (*(int *)(g_sd + 0x4758))
#define stock_namebuf1 (*(unsigned char *)(g_sd + 0x4768))
#define stock_newmode (*(int *)(g_sd + 0x47a8))
#define stock_nhandle (*(int *)(g_sd + 0x6e40))
#define stock_nstream (*(int *)(g_sd + 0x6f54))
#define stock_onexitbegin (*(int *)(g_sd + 0x7f6c))
#define stock_onexitend (*(int *)(g_sd + 0x7f64))
#define stock_pctype (*(char * *)(g_sd + 0x4f48))
#define stock_pgmname (*(unsigned char *)(g_sd + 0x5460))
#define stock_piob (*(int *)(g_sd + 0x6f58))
#define stock_pioinfo (*(int *)(g_sd + 0x6e50))
#define stock_pnhHeap (*(int *)(g_sd + 0x5458))
#define stock_rgcode_page_info (*(int *)(g_sd + 0x4980))
#define stock_rgctypeflag (*(unsigned char *)(g_sd + 0x4978))
#define stock_rterrs (*(int *)(g_sd + 0x4ce0))
#define stock_stderr (*(unsigned char *)(g_sd + 0x4510))
#define stock_stdout (*(unsigned char *)(g_sd + 0x44f0))
#define stock_umaskval (*(int *)(g_sd + 0x4468))
#define stock_wenviron (*(int *)(g_sd + 0x4490))
#define stock_xc_a (*(unsigned char *)(g_sd + 0x1000))
#define stock_xc_z (*(unsigned char *)(g_sd + 0x1004))
#define stock_xi_a (*(unsigned char *)(g_sd + 0x1008))
#define stock_xi_z (*(unsigned char *)(g_sd + 0x1010))
#define stock_xp_a (*(unsigned char *)(g_sd + 0x1014))
#define stock_xp_z (*(unsigned char *)(g_sd + 0x1020))
#define stock_xt_a (*(unsigned char *)(g_sd + 0x1024))
#define stock_xt_z (*(unsigned char *)(g_sd + 0x1028))

#endif
