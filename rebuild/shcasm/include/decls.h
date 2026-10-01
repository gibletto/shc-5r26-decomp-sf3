#ifndef DECLS_H
#define DECLS_H
#include "ghidra_stubs.h"
#include "stage_types.h"

/* the stock data image (scaffold-rebuild.py): data globals are lvalues at their stock offsets */
extern unsigned char g_sd[];
#define SD(a) ((unsigned int)(g_sd + ((unsigned int)(a) - 0x43b000u)))

extern undefined4 _CPtoLCID();
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
extern int __validdrive();
extern int _strcmp();
extern size_t _strncnt();
extern size_t _strncnt_lcmap();
extern char * _strrchr();
extern ulong _strtoul();
extern int _wctomb();
extern int accumulate_operand_register_mask();
extern int add_literal_to_pool_table();
extern int add_pipeline_dependency_edge();
extern int add_pool_literal();
extern int add_store_memory_order_dependencies();
extern int add_superscalar_entry_read_register();
extern int add_superscalar_entry_written_register();
extern char * alloc_back_reference_string();
extern ea * alloc_ea_operand();
extern int * alloc_from_pool_chunks();
extern layout_record * alloc_layout_record();
extern char * alloc_placeholder_type_string();
extern char * alloc_type_piece_string();
extern int allocate_demangle_string_chunks();
extern int allocate_spool_buffer();
extern int append_listing_object_code();
extern int append_object_record_byte();
extern int append_object_record_bytes();
extern int append_object_record_long();
extern int append_object_record_word();
extern int append_reloc_entry_header();
extern int append_reloc_expression_byte();
extern char * append_reloc_expression_bytes();
extern int append_reloc_expression_long();
extern int append_reloc_expression_word();
extern int append_reloc_record_bytes();
extern int append_sized_value_to_data_record();
extern int append_sized_value_to_repeat_data_record();
extern int append_to_work_buffer();
extern int assemble_instruction();
extern int begin_layout_passes();
extern int build_pipeline_dependency_graph();
extern int build_section_name();
extern int build_section_select_record();
extern int build_superscalar_dependency_graph();
extern int byte_swap_value();
extern int can_schedule_pipeline_entry_now();
extern int check_operand_registers();
extern int check_request_read_result();
extern int check_request_write_result();
extern short classify_mangle_code();
extern int clear_pipeline_entry_and_dependencies();
extern int clear_pool_literal_table();
extern int clear_superscalar_window_analysis();
extern int clear_work_buffer();
extern int close_and_delete_temp_files();
extern int close_debug_scope_range();
extern int close_output_stream();
extern int commit_scheduled_pipeline_entry();
extern int compare_bytes();
extern int compare_order_entries_by_height();
extern int compare_order_entries_by_index();
extern int compare_superscalar_entries_by_issue_order();
extern int compose_type_pieces();
extern int compute_branch_displacement();
extern int compute_enter_expansion_size();
extern uint compute_object_record_checksum();
extern int compute_original_order_issue_cycles();
extern int compute_pipeline_opcode_masks_and_flags();
extern int compute_pipeline_operand_masks();
extern short compute_record_code_size();
extern int configure_signal_handlers();
extern short copy_array_dimension_codes();
extern int copy_cv_qualifier_codes();
extern undefined4 * copy_environ();
extern ushort copy_length_prefixed_name();
extern short copy_member_pointer_code();
extern ushort copy_path_file_name();
extern short copy_qualified_name_code();
extern int copy_request_trailer_from_temp();
extern int copy_source_lines_to_listing();
extern int copy_string();
extern short copy_string_count();
extern short copy_string_to_line_width();
extern int copy_to_counted_string();
extern short copy_type_back_reference_code();
extern int count_import_and_export_symbols();
extern short count_saved_registers();
extern symbol * create_symbol_entry();
extern int decide_literal_pool_placement();
extern ushort demangle_argument_list();
extern short demangle_cpp_symbol_name();
extern int describe_superscalar_window_entry();
extern psd * drain_next_superscalar_scheduled_record();
extern int dump_pipeline_table();
extern int dump_superscalar_window();
extern int emit_alignment_fill();
extern int emit_block_scope_records();
extern ushort emit_branch_disp12_operand();
extern ushort emit_branch_disp8_operand();
extern int emit_dc_record();
extern int emit_debug_information();
extern int emit_dz_record();
extern int emit_export_symbol();
extern uint emit_final_asm_record_stream();
extern int emit_import_symbol();
extern int emit_inline_asm_block();
extern int emit_label_record();
extern int emit_line_comment();
extern int emit_line_directive();
extern int emit_line_directive_for_record();
extern int emit_line_directive_if_new();
extern int emit_listing_page_header();
extern int emit_literal_pool();
extern int emit_literal_pool_entry();
extern ushort emit_memory_operand();
extern int emit_object_header_and_tables();
extern int emit_object_module_header_record();
extern int emit_object_record_kind_table();
extern int emit_object_unit_record();
extern ushort emit_postincrement_operand();
extern ushort emit_predecrement_operand();
extern int emit_progress_banner();
extern ushort emit_register_operand();
extern int emit_relocation_expression();
extern int emit_relocation_symbol_term();
extern int emit_reserve_record();
extern int emit_runtime_routine_imports();
extern int emit_section_definition_record();
extern ushort emit_signed_imm8_operand();
extern int emit_spooled_tag38_records();
extern int emit_stack_offset_records();
extern int emit_string_data_record();
extern int emit_switch_table();
extern int emit_switch_table_entry();
extern ushort emit_trapa_imm8_operand();
extern ushort emit_unsigned_imm8_operand();
extern int entries_access_disjoint_memory();
extern int evaluate_label_expression();
extern int expand_call();
extern int expand_conditional_jump();
extern int expand_enter_prologue();
extern int expand_exit_epilogue();
extern int expand_extld_record();
extern int expand_extst_record();
extern int expand_fprset_record();
extern int expand_jump();
extern int expand_mov_to_r0_with_nop();
extern int expand_move_local();
extern int expand_movi_record();
extern int expand_movif_record();
extern int expand_mva_fc_record();
extern int expand_mva_lc_record();
extern int expand_mva_pc_record();
extern int expand_return();
extern int expand_switch_jump();
extern short find_basic_type_code();
extern short find_ctor_dtor_name_code();
extern short find_declarator_code();
extern int find_literal_pool_index();
extern short find_operator_name_code();
extern int find_path_file_name_offset();
extern int find_pool_literal();
extern int find_request_entry12_value();
extern request_section * find_section_by_id();
extern char * find_substring();
extern symbol * find_symbol_by_id();
extern symbol * find_symbol_entry_by_id();
extern short find_type_qualifier_code();
extern int findenv();
extern int finish_layout_passes();
extern int finish_object_record();
extern int flush_listing_entry();
extern int flush_listing_line();
extern int flush_output_line();
extern int flush_register_variable_map();
extern int flush_reloc_records();
extern int flush_source_line_ranges();
extern int flush_src_line();
extern short format_array_dimensions();
extern ushort format_class_scope_prefix();
extern short format_decimal();
extern int format_hex_digits();
extern int format_listing_location();
extern short format_listing_page_header();
extern int format_listing_section_column();
extern ushort format_mangled_type_list();
extern short format_member_pointer_class();
extern ushort format_placeholder_type();
extern short format_qualified_name();
extern short format_type_back_reference();
extern int frame_offset_to_sp_displacement();
extern int frame_offset_to_sp_displacement_for_pass();
extern int free_debug_location_table();
extern int free_debug_symbol_table();
extern int free_demangle_string_chunks();
extern int free_ea_operand();
extern int free_expno_register_variable_table();
extern int free_line_directive_list();
extern int free_size_decision_stream_buffer();
extern int free_to_pool_chunks();
extern int free_work_buffers();
extern undefined4 genfname();
extern int getSystemCP();
extern char * get_env_directory();
extern char * get_full_path();
extern int get_marked_symbol_attr_low_bits();
extern int get_module_name();
extern char * get_output_stream_path();
extern int get_source_file_basename();
extern int get_symbol_attribute_bits();
extern int handle_fault_signal();
extern int handle_interrupt_signal();
extern int immediate_bit_width();
extern int init_debug_info_state();
extern undefined4 init_namebuf();
extern int initialize_work_buffers();
extern int intern_placeholder_name();
extern int intern_token_text();
extern short is_unprintable_char();
extern int is_word_symbol_literal();
extern int issue_groups_conflict();
extern int layout_literal_pool();
extern char layout_next_ofb_record();
extern int list_object_code_byte();
extern int list_object_code_long();
extern int list_object_code_value();
extern int list_object_code_word();
extern int load_debug_symbol_tables();
extern int load_function_register_variable_map();
extern int load_intermediate_record_stream();
extern pipeline_entry * load_pipeline_window();
extern request * load_request_record_file();
extern char * make_temp_file_name();
extern int mark_pipeline_tail_barrier();
extern int month_name_to_digits();
extern alloc_chunk * new_pool_chunk();
extern int open_debug_scope_range();
extern int open_output_stream();
extern FILE * open_temp_file();
extern int operand_size_from_flags();
extern int pad_listing_page();
extern byte * parse_cmdline();
extern int parse_decimal_digits();
extern short parse_length_prefixed_name();
extern short parse_mangled_signature_kind();
extern int pipeline();
extern int pipeline_entry_uses_memory_stage();
extern int * pool_alloc();
extern int pool_free();
extern int pool_literal_matches();
extern int * pool_try_alloc();
extern int print_label_ref_expression();
extern int print_label_ref_expression_to_listing();
extern int print_label_sum_from_backend_stream();
extern int print_pc_relative_literal_comment();
extern int print_superscalar_entry_operands();
extern int push_demangle_token();
extern int push_type_piece();
extern int put_char_at_column();
extern int put_text_at_column();
extern int quicksort_range();
extern uint read_backend_record_payload();
extern uint read_backend_stream_bytes();
extern uint read_branch_label_operand();
extern uint read_file_bytes();
extern int read_intermediate_bytes();
extern char * read_intermediate_string();
extern int read_label_ref_list();
extern int read_next_backend_record();
extern psd * read_next_scheduled_pipeline_record();
extern psd * read_next_superscalar_scheduled_record();
extern layout_record * read_ofb_layout_record();
extern int read_operand_label_refs();
extern uint read_pseudo_op_record_payload();
extern uint read_record_operand();
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
extern short read_spool_byte();
extern int record_size_decision_byte();
extern int record_source_line_range();
extern int record_superscalar_entry_operands();
extern int refill_pipeline_when_drained();
extern int relax_call_record();
extern int relax_conditional_jump_record();
extern int relax_exit_record();
extern int relax_fprset_record();
extern int relax_inline_asm_record();
extern int relax_jump_record();
extern int relax_movi_record();
extern int relax_movif_record();
extern int relax_mv_loc_record();
extern int relax_mva_fc_record();
extern int relax_mva_lc_record();
extern int relax_mva_pc_record();
extern int relax_return_record();
extern int relax_switch_jump_record();
extern int relax_unconditional_branch_record();
extern int release_pipeline_entry_successors();
extern int remember_argument_type();
extern char * replace_first_substring();
extern int report_message_at_source_line();
extern uint report_message_by_code();
extern int report_message_file_error_and_exit();
extern int reset_pipeline_state();
extern int reset_work_buffer();
extern int resize_case_table_record();
extern layout_record * resolve_layout_record();
extern int resolve_next_pending_layout_record();
extern ushort reverse_bits_16();
extern int rewind_size_decision_stream();
extern int rewrite_entry_expression_with_earlier_definitions();
extern int run_assembler_passes();
extern int run_layout_passes();
extern int run_superscalar_scheduler();
extern int save_request_trailer_to_temp();
extern int schedule_pipeline_window();
extern int schedule_superscalar_window();
extern int select_env_variable_names();
extern undefined4 setSBCS();
extern int set_psd_record();
extern int set_superscalar_entry_timing();
extern int shcasm_main();
extern uint siglookup();
extern int sort_array();
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
extern FILE * stock_fopen();
extern int stock_fptrap();
extern int stock_free();
extern int stock_free_osfhnd();
extern char * stock_fullpath();
extern undefined8 stock_get_int64_arg();
extern int stock_get_int_arg();
extern int stock_get_osfhandle();
extern ushort stock_get_short_arg();
extern char * stock_getcwd();
extern char * stock_getdcwd();
extern char * stock_getenv();
extern int * stock_heap_alloc();
extern int stock_heap_init();
extern int stock_initmbctable();
extern int stock_initterm();
extern int stock_ioinit();
extern uchar stock_isatty();
extern uint stock_lseek();
extern int * stock_malloc();
extern char * stock_mbsrchr();
extern int stock_memcmp();
extern int * stock_memcpy();
extern int * stock_nh_malloc();
extern int stock_read();
extern int * stock_realloc();
extern int stock_remove();
extern int stock_rmtmp();
extern int stock_setenvp();
extern int stock_setmbcp();
extern int stock_setmode();
extern uint stock_sopen();
extern uint * stock_strcat();
extern char * stock_strchr();
extern uint * stock_strcpy();
extern uint stock_strlen();
extern char * stock_strncat();
extern char * stock_strncpy();
extern uint stock_strtoxl();
extern int stock_unlink();
extern int stock_write();
extern int store_immediate_in_operand();
extern uint store_request_record_file();
extern int store_request_record_updates();
extern char * store_string_in_pool();
extern uint store_u16_big_endian();
extern uint store_u32_big_endian();
extern int switch_section();
extern int symbol_address_is_abs16();
extern int track_stack_pointer_offset();
extern int translate_debug_symbol_record();
extern int translate_scope_record();
extern int translate_short_tagged_record();
extern int translate_tag44_record();
extern int translate_tag4e_record();
extern int update_debug_info_for_record();
extern int update_register_variable_map();
extern int write_at_decimal();
extern int write_decimal();
extern int write_displacement_width_suffix();
extern uint write_file_bytes();
extern int write_hex_byte();
extern int write_hex_long();
extern int write_hex_word();
extern int write_immediate_with_size();
extern int write_label_name();
extern int write_listing_line();
extern int write_operand_offset();
extern int write_pool_flush_flag();
extern int write_register_name();
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
extern int write_size_suffix();
extern uint xtoa();

#define DAT_0043c7a0 (*(unsigned char *)(g_sd + 0x17a0))
#define DAT_0043cdfc (*(unsigned char *)(g_sd + 0x1dfc))
#define DAT_004419b8 (*(unsigned char *)(g_sd + 0x69b8))
#define DAT_004427d0 (*(unsigned char *)(g_sd + 0x77d0))
#define DAT_00443230 (*(int *)(g_sd + 0x8230))
#define DAT_00443234 (*(short *)(g_sd + 0x8234))
#define DAT_004435ec (*(int *)(g_sd + 0x85ec))
#define DAT_004435f0 (*(int *)(g_sd + 0x85f0))
#define DAT_00443604 (*(unsigned char *)(g_sd + 0x8604))
#define DAT_00443608 (*(unsigned char *)(g_sd + 0x8608))
#define DAT_00443610 (*(unsigned char *)(g_sd + 0x8610))
#define DAT_00443724 (*(int *)(g_sd + 0x8724))
#define DAT_00443728 (*(int *)(g_sd + 0x8728))
#define DAT_0044372c (*(int *)(g_sd + 0x872c))
#define DAT_00443aec (*(int *)(g_sd + 0x8aec))
#define DAT_00443ec0 (*(int *)(g_sd + 0x8ec0))
#define DAT_00443f7c (*(unsigned char *)(g_sd + 0x8f7c))
#define DAT_00443f80 (*(unsigned char *)(g_sd + 0x8f80))
#define DAT_0044bc68 (*(unsigned char *)(g_sd + 0x10c68))
#define DAT_0044f748 (*(unsigned char *)(g_sd + 0x14748))
#define DAT_0044f74c (*(unsigned char *)(g_sd + 0x1474c))
#define DAT_00450398 (*(unsigned char *)(g_sd + 0x15398))
#define DAT_0045039c (*(unsigned char *)(g_sd + 0x1539c))
#define DAT_00450bb4 (*(int *)(g_sd + 0x15bb4))
#define PTR_DAT_004419d0 (*(unsigned char * *)(g_sd + 0x69d0))
#define PTR_DAT_00441d98 (*(unsigned char * *)(g_sd + 0x6d98))
#define PTR_DAT_00441eb0 (*(unsigned char * *)(g_sd + 0x6eb0))
#define PTR_DAT_00441ee4 (*(char * *)(g_sd + 0x6ee4))
#define PTR_DAT_004429ec (*(char * *)(g_sd + 0x79ec))
#define PTR_DAT_00442a3c (*(char * *)(g_sd + 0x7a3c))
#define PTR_DAT_00443040 (*(char * *)(g_sd + 0x8040))
#define PTR_s_0123456789ABCDEF_0043cef0 (*(char * *)(g_sd + 0x1ef0))
#define PTR_s_SH_SERIES_C_Compiler__Ver__5_0_R_00443028 (*(char * *)(g_sd + 0x8028))
#define PTR_s_SH_SERIES_C___Compiler__Ver__5_0_00443058 (*(char * *)(g_sd + 0x8058))
#define PTR_s___block_00441f88 (*(unsigned char * *)(g_sd + 0x6f88))
#define PTR_s___case_label_00441ee8 (*(char * *)(g_sd + 0x6ee8))
#define PTR_s___default_label_00441eec (*(char * *)(g_sd + 0x6eec))
#define PTR_s___function__00441ee0 (*(char * *)(g_sd + 0x6ee0))
#define PTR_s___label__00441ef0 (*(char * *)(g_sd + 0x6ef0))
#define PTR_s___static__00441ef4 (*(char * *)(g_sd + 0x6ef4))
#define PTR_s__divbs_0043cb24 (*(char * *)(g_sd + 0x1b24))
#define PTR_s__sta_sftrl12_0043ccfc (*(unsigned char * *)(g_sd + 0x1cfc))
#define PTR_s_empty_string_00442bac (*(char * *)(g_sd + 0x7bac))
#define PTR_s_operator___00442a5c (*(char * *)(g_sd + 0x7a5c))
#define PTR_s_unsigned_004429cc (*(char * *)(g_sd + 0x79cc))
#define _g_current_aux_index (*(int *)(g_sd + 0xf8ec))
#define _stock_C_Exit_Done (*(int *)(g_sd + 0x81f4))
#define _stock_errno (*(int *)(g_sd + 0x81b0))
#define _stock_pgmptr (*(int *)(g_sd + 0x81e8))
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#define g_backend_continuation_opened (*(int *)(g_sd + 0xfb08))
#define g_backend_first_record (*(unsigned char *)(g_sd + 0x12ff0))
#define g_backend_op_payload_format (*(unsigned char *)(g_sd + 0x1048))
#define g_backend_record_input (*(unsigned char * *)(g_sd + 0xf6d4))
#define g_backend_stream (*(unsigned char * *)(g_sd + 0x8f98))
#define g_column_starts (*(char * (*)[4])(g_sd + 0xcf10))
#define g_created_symbol_chunks (*(int *)(g_sd + 0x6954))
#define g_current_aux_index (*(short *)(g_sd + 0xf8ec))
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#define g_current_section (*(request_section * *)(g_sd + 0x10b2c))
#define g_current_section_kind (*(short *)(g_sd + 0xcf2c))
#define g_debug_function_label (*(short *)(g_sd + 0x13148))
#define g_debug_group_depth (*(int *)(g_sd + 0x5cd0))
#define g_debug_location_hash (*(debug_location * (*)[127])(g_sd + 0xcf30))
#define g_debug_prev_op (*(unsigned char *)(g_sd + 0x696c))
#define g_debug_record_body (*(unsigned char (*)[253])(g_sd + 0x13042))
#define g_debug_record_cursor (*(int *)(g_sd + 0x13030))
#define g_debug_record_input (*(int *)(g_sd + 0xcf20))
#define g_debug_record_tag (*(unsigned char *)(g_sd + 0x13040))
#define g_debug_scope_depth (*(short *)(g_sd + 0xe742))
#define g_debug_symbol_hash (*(debug_symbol * (*)[127])(g_sd + 0xcd00))
#define g_debug_symbol_input (*(int *)(g_sd + 0xcf24))
#define g_debug_word_1001 (*(short *)(g_sd + 0x5cc4))
#define g_decimal_text (*(unsigned char *)(g_sd + 0xc4c8))
#define g_decimal_text_length (*(short *)(g_sd + 0xc4c0))
#define g_delay_slot_record (*(psd *)(g_sd + 0xdc70))
#define g_demangle_array_type_text (*(int *)(g_sd + 0x98b0))
#define g_demangle_back_reference_count (*(int *)(g_sd + 0x14f50))
#define g_demangle_back_references (*(demangle_entry (*)[256])(g_sd + 0x153a0))
#define g_demangle_backref_chunk_current (*(int *)(g_sd + 0x1473c))
#define g_demangle_backref_chunk_first (*(int *)(g_sd + 0x14738))
#define g_demangle_class_scope (*(unsigned char *)(g_sd + 0xaeb0))
#define g_demangle_cv_suffix (*(int *)(g_sd + 0xa4b0))
#define g_demangle_joined_tokens (*(unsigned char *)(g_sd + 0xb2b0))
#define g_demangle_member_class_text (*(unsigned char *)(g_sd + 0xbab0))
#define g_demangle_name_scratch (*(int *)(g_sd + 0x96b0))
#define g_demangle_piece_chunk_current (*(int *)(g_sd + 0x14734))
#define g_demangle_piece_chunk_first (*(int *)(g_sd + 0x14730))
#define g_demangle_placeholder_chunk_current (*(int *)(g_sd + 0x14f64))
#define g_demangle_placeholder_chunk_first (*(int *)(g_sd + 0x14f60))
#define g_demangle_placeholder_chunk_used (*(int *)(g_sd + 0x14f68))
#define g_demangle_placeholder_count (*(int *)(g_sd + 0x15ba0))
#define g_demangle_placeholder_name_pool (*(unsigned char *)(g_sd + 0x14fa0))
#define g_demangle_placeholder_name_pool_used (*(int *)(g_sd + 0x14740))
#define g_demangle_placeholder_types (*(demangle_entry (*)[256])(g_sd + 0x13f30))
#define g_demangle_qualified_component (*(int *)(g_sd + 0xa8b0))
#define g_demangle_token_pool (*(unsigned char *)(g_sd + 0x13330))
#define g_demangle_token_pool_used (*(int *)(g_sd + 0x14f54))
#define g_demangle_token_text (*(int *)(g_sd + 0xbcb0))
#define g_demangle_tokens (*(demangle_entry (*)[256])(g_sd + 0x13730))
#define g_demangle_type_piece (*(char (*)[1024])(g_sd + 0xaab0))
#define g_demangle_type_pieces (*(demangle_entry (*)[256])(g_sd + 0x14750))
#define g_demangle_type_text (*(int *)(g_sd + 0xa0b0))
#define g_drop_function_debug (*(int *)(g_sd + 0x5ccc))
#define g_env_directory (*(char (*)[118])(g_sd + 0xc4e0))
#define g_expanded_record_count (*(int *)(g_sd + 0x129a4))
#define g_expanded_record_read_index (*(int *)(g_sd + 0x6dd0))
#define g_expanded_records (*(psd (*)[48])(g_sd + 0xe2b0))
#define g_expno_register_variables (*(register_variable * * *)(g_sd + 0x13008))
#define g_expno_use_list (*(expno_use * *)(g_sd + 0x10c80))
#define g_export_symbol_count (*(short *)(g_sd + 0xf8ea))
#define g_extra_section_needed (*(char *)(g_sd + 0xfb15))
#define g_frame_offset_literal_table (*(literal_table *)(g_sd + 0xca90))
#define g_function_debug_loaded (*(int *)(g_sd + 0xccb4))
#define g_function_label (*(short *)(g_sd + 0xe740))
#define g_function_label_pass0 (*(short *)(g_sd + 0x129a0))
#define g_function_label_pass1 (*(short *)(g_sd + 0x13014))
#define g_held_section_record (*(psd *)(g_sd + 0x9430))
#define g_import_symbol_count (*(short *)(g_sd + 0x10c5c))
#define g_inc_env_name (*(char * *)(g_sd + 0x13314))
#define g_inline_asm_input (*(unsigned char * *)(g_sd + 0xf8f0))
#define g_inline_asm_needs_label (*(int *)(g_sd + 0xf6d0))
#define g_instruction_format_table (*(instruction_format (*)[182])(g_sd + 0x2a90))
#define g_intermediate_file (*(unsigned char * *)(g_sd + 0x9308))
#define g_intermediate_record_header (*(unsigned char (*)[8])(g_sd + 0x9208))
#define g_internal_error_text (*(char * *)(g_sd + 0x8110))
#define g_internal_file_error_text (*(unsigned char *)(g_sd + 0x4d70))
#define g_issue_group_names (*(unsigned char * *)(g_sd + 0x4298))
#define g_label_name_buffer (*(unsigned char *)(g_sd + 0x9328))
#define g_last_attributed_symbol (*(symbol * *)(g_sd + 0xfb1c))
#define g_last_label_number (*(short *)(g_sd + 0xccc0))
#define g_last_movi_immediate (*(int *)(g_sd + 0x9428))
#define g_last_was_delayed_branch (*(int *)(g_sd + 0x6dd8))
#define g_layout_pending_records (*(layout_record * *)(g_sd + 0xcca8))
#define g_layout_record_tail (*(layout_record * *)(g_sd + 0x13158))
#define g_layout_section_pass0 (*(request_section * *)(g_sd + 0xcc9c))
#define g_layout_section_pass1 (*(request_section * *)(g_sd + 0xcca4))
#define g_layout_shrink_pass0 (*(int *)(g_sd + 0x128d0))
#define g_layout_shrink_pass1 (*(int *)(g_sd + 0x128d4))
#define g_layout_symbol_labno_pass1 (*(short *)(g_sd + 0xccfc))
#define g_layout_symbol_pass0 (*(symbol * *)(g_sd + 0xccf8))
#define g_layout_symbol_pass1 (*(symbol * *)(g_sd + 0xccac))
#define g_layout_symbol_pending_records (*(layout_record * *)(g_sd + 0x13018))
#define g_lib_env_name_00 (*(char * *)(g_sd + 0x13300))
#define g_lib_env_name_04 (*(char * *)(g_sd + 0x13304))
#define g_lib_env_name_0c (*(char * *)(g_sd + 0x1330c))
#define g_lib_env_name_10 (*(char * *)(g_sd + 0x13310))
#define g_line_directive_prev_op (*(unsigned char *)(g_sd + 0x6970))
#define g_line_filno (*(short *)(g_sd + 0x9448))
#define g_line_linno (*(unsigned short *)(g_sd + 0x944c))
#define g_line_range_count (*(short *)(g_sd + 0x128e4))
#define g_line_range_temp (*(unsigned char * *)(g_sd + 0x128bc))
#define g_line_wrap_disabled (*(int *)(g_sd + 0x12974))
#define g_listing_blank_line (*(unsigned char *)(g_sd + 0x9450))
#define g_listing_code_column_pos (*(short *)(g_sd + 0x10b28))
#define g_listing_code_field (*(char * *)(g_sd + 0x13150))
#define g_listing_code_row_last (*(short *)(g_sd + 0x10c54))
#define g_listing_code_row_next (*(short *)(g_sd + 0xd230))
#define g_listing_code_rows (*(unsigned char *)(g_sd + 0xd240))
#define g_listing_continuation_mark (*(char * *)(g_sd + 0x128e0))
#define g_listing_header_buffer (*(unsigned char *)(g_sd + 0x9550))
#define g_listing_last_source_file (*(short *)(g_sd + 0x6e58))
#define g_listing_last_source_line (*(unsigned short *)(g_sd + 0x6e5c))
#define g_listing_location_field (*(char * *)(g_sd + 0xcc98))
#define g_listing_page_line_count (*(short *)(g_sd + 0x128d8))
#define g_listing_page_number (*(short *)(g_sd + 0x12980))
#define g_listing_section_field (*(char * *)(g_sd + 0x13140))
#define g_lit_input (*(unsigned char * *)(g_sd + 0x10c84))
#define g_literal_label_serial (*(short *)(g_sd + 0x718c))
#define g_literal_pool_label (*(short *)(g_sd + 0x12978))
#define g_loaded_aux_count (*(int *)(g_sd + 0xcf08))
#define g_loaded_request (*(request * *)(g_sd + 0x13320))
#define g_location_counter (*(int *)(g_sd + 0xccf0))
#define g_long_literal_table (*(literal_table *)(g_sd + 0xc880))
#define g_long_literal_table_pass1 (*(literal_table *)(g_sd + 0xf900))
#define g_mangle_basic_type_names (*(char * *)(g_sd + 0x79e8))
#define g_mangle_code_classes (*(char * *)(g_sd + 0x78c0))
#define g_mangle_ctor_dtor_names (*(char * *)(g_sd + 0x7ba8))
#define g_mangle_declarator_names (*(char * *)(g_sd + 0x7a38))
#define g_mangle_operator_names (*(char * *)(g_sd + 0x7a58))
#define g_mangle_qualifier_names (*(char * *)(g_sd + 0x79c8))
#define g_max_error_severity (*(int *)(g_sd + 0xe748))
#define g_message_number_text (*(unsigned char *)(g_sd + 0xc4b8))
#define g_module_header_record (*(unsigned char (*)[28])(g_sd + 0x91c8))
#define g_mv_loc_size_table (*(unsigned char *)(g_sd + 0x73b0))
#define g_name_chunk_cursor (*(char * *)(g_sd + 0x930c))
#define g_name_chunk_end (*(char * *)(g_sd + 0x9310))
#define g_new_register_variable_map (*(register_variable * *)(g_sd + 0x9318))
#define g_new_symbol_count (*(short *)(g_sd + 0xf6dc))
#define g_next_delay_slot_record (*(psd *)(g_sd + 0xccd0))
#define g_next_export_index (*(int *)(g_sd + 0xccec))
#define g_next_import_index (*(int *)(g_sd + 0xf6d8))
#define g_object_data_buffer (*(char * *)(g_sd + 0x10c7c))
#define g_object_data_cursor (*(char * *)(g_sd + 0x10c58))
#define g_object_data_end (*(char * *)(g_sd + 0x10c60))
#define g_object_expr_buffer (*(char * *)(g_sd + 0x128cc))
#define g_object_expr_cursor (*(char * *)(g_sd + 0x10ca8))
#define g_object_expr_end (*(int *)(g_sd + 0x128b0))
#define g_object_header_word (*(short *)(g_sd + 0x5cd4))
#define g_object_language_tag_c (*(char * *)(g_sd + 0x8030))
#define g_object_language_tag_cpp (*(char * *)(g_sd + 0x8060))
#define g_object_need_section_select (*(short *)(g_sd + 0xcce8))
#define g_object_record_break (*(int *)(g_sd + 0x1297c))
#define g_object_record_buffer (*(unsigned char (*)[256])(g_sd + 0xd130))
#define g_object_record_cursor (*(unsigned char * *)(g_sd + 0x13154))
#define g_object_record_tag (*(int *)(g_sd + 0x13010))
#define g_ofb_at_end (*(int *)(g_sd + 0xccc8))
#define g_ofb_current_label (*(short *)(g_sd + 0xdc60))
#define g_ofb_input (*(unsigned char * *)(g_sd + 0xd12c))
#define g_op_code_size_table (*(short (*)[256])(g_sd + 0x71b0))
#define g_op_names (*(unsigned char * *)(g_sd + 0x3e98))
#define g_opcode_format_index (*(opcode_format (*)[256])(g_sd + 0x2290))
#define g_operand1_register_class (*(unsigned char *)(g_sd + 0x8fc0))
#define g_operand2_register_class (*(unsigned char *)(g_sd + 0x8fa0))
#define g_output_channels (*(output_channel (*)[4])(g_sd + 0x1e80))
#define g_page_label_text (*(char (*)[8])(g_sd + 0x8130))
#define g_pid_digit_count (*(int *)(g_sd + 0x7420))
#define g_pipeline_active (*(int *)(g_sd + 0x6dd4))
#define g_pipeline_code_offset (*(char *)(g_sd + 0x1301c))
#define g_pipeline_drained_count (*(int *)(g_sd + 0x10b24))
#define g_pipeline_edge_count (*(int *)(g_sd + 0x128c4))
#define g_pipeline_edges (*(pipeline_edge (*)[992])(g_sd + 0xe750))
#define g_pipeline_end_of_stream (*(int *)(g_sd + 0x128b4))
#define g_pipeline_fdiv_busy (*(char *)(g_sd + 0x12971))
#define g_pipeline_first_scheduled (*(int *)(g_sd + 0x10c4c))
#define g_pipeline_fsqrt_busy (*(char *)(g_sd + 0x12970))
#define g_pipeline_hold (*(int *)(g_sd + 0xfb0c))
#define g_pipeline_input_exhausted (*(int *)(g_sd + 0xfb10))
#define g_pipeline_last_scheduled (*(int *)(g_sd + 0xe734))
#define g_pipeline_load_result_regs (*(unsigned int (*)[2])(g_sd + 0xe738))
#define g_pipeline_lookahead_record (*(psd *)(g_sd + 0x10c90))
#define g_pipeline_lookahead_valid (*(int *)(g_sd + 0x5d64))
#define g_pipeline_mac_busy (*(char *)(g_sd + 0xfb14))
#define g_pipeline_op_fpu_flags (*(unsigned char *)(g_sd + 0x3bc8))
#define g_pipeline_op_read_operands (*(unsigned char *)(g_sd + 0x39c8))
#define g_pipeline_op_t_bit_use (*(unsigned char *)(g_sd + 0x3ac8))
#define g_pipeline_op_written_operand (*(unsigned char *)(g_sd + 0x38c8))
#define g_pipeline_opcode_name_table (*(unsigned char * *)(g_sd + 0x5d88))
#define g_pipeline_reload_pending (*(int *)(g_sd + 0x128c8))
#define g_pipeline_window (*(pipeline_entry (*)[32])(g_sd + 0xdc90))
#define g_pipeline_window_ended_at_c_jmp (*(int *)(g_sd + 0x5d60))
#define g_pipeline_window_ends_block (*(int *)(g_sd + 0x10c6c))
#define g_pipeline_window_last_index (*(int *)(g_sd + 0x12984))
#define g_pool_carried_code_bytes (*(int *)(g_sd + 0x719c))
#define g_pool_carried_has_word (*(unsigned char *)(g_sd + 0x71a0))
#define g_pool_carried_literal_bytes (*(int *)(g_sd + 0x7198))
#define g_pool_code_bytes (*(int *)(g_sd + 0x7194))
#define g_pool_flush_pending (*(int *)(g_sd + 0x71a8))
#define g_pool_pending_literal_bytes (*(int *)(g_sd + 0x7190))
#define g_pool_segment_has_word (*(unsigned char *)(g_sd + 0x71a4))
#define g_pool_size_classes (*(alloc_class_table * *)(g_sd + 0x17ac))
#define g_process_id (*(int *)(g_sd + 0x7424))
#define g_program_size (*(int *)(g_sd + 0xcf04))
#define g_progress_banner_table (*(unsigned char * *)(g_sd + 0x7dd0))
#define g_record_kind_table_debug (*(unsigned char *)(g_sd + 0x5d00))
#define g_register_bit_masks (*(unsigned int (*)[32])(g_sd + 0x1e00))
#define g_register_candidates (*(register_candidate * *)(g_sd + 0xf8f8))
#define g_register_map_temp (*(unsigned char * *)(g_sd + 0x13020))
#define g_register_names (*(unsigned char * *)(g_sd + 0x3cc8))
#define g_register_sort_buffer (*(unsigned char *)(g_sd + 0x132e0))
#define g_register_variable_input (*(unsigned char * *)(g_sd + 0x128c0))
#define g_register_variable_map (*(register_variable * *)(g_sd + 0x931c))
#define g_request_being_loaded (*(request * *)(g_sd + 0xc4b0))
#define g_request_copy (*(request * *)(g_sd + 0x129a8))
#define g_request_cpp_block_size (*(short *)(g_sd + 0x13326))
#define g_request_record_path (*(int *)(g_sd + 0x13318))
#define g_request_record_size (*(short *)(g_sd + 0x13328))
#define g_request_trailer_file (*(unsigned char * *)(g_sd + 0x1331c))
#define g_request_version_mismatch (*(short *)(g_sd + 0x13324))
#define g_runtime_routine_import_index (*(unsigned char *)(g_sd + 0x129b0))
#define g_runtime_routine_imported (*(unsigned char *)(g_sd + 0xdc40))
#define g_runtime_routine_names (*(unsigned char *)(g_sd + 0x1b20))
#define g_runtime_routine_stack_adjust (*(unsigned char *)(g_sd + 0x1844))
#define g_runtime_routines_used (*(unsigned char *)(g_sd + 0xe290))
#define g_scope_saved_sibling (*(debug_scope * *)(g_sd + 0x9320))
#define g_scope_stack (*(debug_scope * (*)[71])(g_sd + 0x10b30))
#define g_scope_top (*(int *)(g_sd + 0x10c50))
#define g_section_count (*(short *)(g_sd + 0x12988))
#define g_section_data_bytes (*(short *)(g_sd + 0x1300c))
#define g_section_location_counters (*(unsigned char * *)(g_sd + 0x1ef8))
#define g_section_numbers (*(short (*)[4])(g_sd + 0x13028))
#define g_section_object_offsets (*(unsigned char *)(g_sd + 0x12990))
#define g_section_record (*(unsigned char (*)[16])(g_sd + 0x91e8))
#define g_source_line_list (*(source_line_range * *)(g_sd + 0x10c64))
#define g_source_listing_at_end (*(unsigned char *)(g_sd + 0xe730))
#define g_source_listing_file (*(unsigned short *)(g_sd + 0xccf4))
#define g_source_listing_input (*(unsigned char * *)(g_sd + 0xe744))
#define g_source_listing_line (*(int *)(g_sd + 0x128b8))
#define g_stack_adjust_list (*(stack_adjust_node * *)(g_sd + 0xcf28))
#define g_stack_offset_temp (*(unsigned char * *)(g_sd + 0xcefc))
#define g_stack_pointer_offset (*(int *)(g_sd + 0xfb20))
#define g_stage_pattern_names (*(unsigned char * *)(g_sd + 0x42f0))
#define g_string_pool_blocks (*(int *)(g_sd + 0x128dc))
#define g_string_pool_chunk (*(char * *)(g_sd + 0x9314))
#define g_string_pool_end (*(char * *)(g_sd + 0xfb18))
#define g_string_pool_pos (*(char * *)(g_sd + 0x13144))
#define g_superscalar_current_entry (*(char *)(g_sd + 0xf8e8))
#define g_superscalar_drain_count (*(int *)(g_sd + 0xcf00))
#define g_superscalar_drain_index (*(int *)(g_sd + 0xcca0))
#define g_superscalar_draining (*(int *)(g_sd + 0xccb0))
#define g_superscalar_dump_file (*(unsigned char * *)(g_sd + 0x1298c))
#define g_superscalar_dump_line (*(unsigned char *)(g_sd + 0x8fc8))
#define g_superscalar_entry_stage_pattern (*(unsigned char *)(g_sd + 0x128f0))
#define g_superscalar_lookahead_record (*(psd *)(g_sd + 0x8fa8))
#define g_superscalar_lookahead_valid (*(char *)(g_sd + 0x8fa4))
#define g_superscalar_order (*(superscalar_order_slot (*)[32])(g_sd + 0x13160))
#define g_superscalar_records_read (*(int *)(g_sd + 0x10c78))
#define g_superscalar_stream_ended (*(int *)(g_sd + 0x13024))
#define g_superscalar_window (*(superscalar_entry (*)[32])(g_sd + 0x10cb0))
#define g_suppress_debug_record (*(int *)(g_sd + 0x5cc8))
#define g_symbol_base (*(symbol * *)(g_sd + 0x1314c))
#define g_symbol_hash (*(symbol * (*)[1021])(g_sd + 0xfb30))
#define g_symbol_ordinal (*(int *)(g_sd + 0x9200))
#define g_symbol_table (*(symbol * *)(g_sd + 0xf8f4))
#define g_symbol_table_next (*(symbol * *)(g_sd + 0x10c70))
#define g_temp_file_count (*(int *)(g_sd + 0x9654))
#define g_temp_files (*(temp_file (*)[8])(g_sd + 0x9658))
#define g_temp_name_buffer (*(char * *)(g_sd + 0x741c))
#define g_temp_name_counter (*(int *)(g_sd + 0x7428))
#define g_temp_path_in_progress (*(char * *)(g_sd + 0x96ac))
#define g_temp_record_length (*(unsigned char *)(g_sd + 0x13041))
#define g_tmp_env_name (*(char * *)(g_sd + 0x13308))
#define g_unit_record (*(unsigned char (*)[7])(g_sd + 0x91f8))
#define g_window_entry_bit_masks (*(unsigned char *)(g_sd + 0x4348))
#define g_word_literal_table (*(literal_table *)(g_sd + 0xc670))
#define g_word_literal_table_pass1 (*(literal_table *)(g_sd + 0xf6e0))
#define g_work_buffer_a (*(int *)(g_sd + 0x14f70))
#define g_work_buffer_a_capacity (*(int *)(g_sd + 0x14f74))
#define g_work_buffer_a_length (*(int *)(g_sd + 0x14f78))
#define g_work_buffer_b (*(int *)(g_sd + 0x14f80))
#define g_work_buffer_b_capacity (*(int *)(g_sd + 0x14f84))
#define g_work_buffer_b_length (*(int *)(g_sd + 0x14f88))
#define g_work_buffer_c (*(int *)(g_sd + 0x14f90))
#define g_work_buffer_c_capacity (*(int *)(g_sd + 0x14f94))
#define g_work_buffer_c_length (*(int *)(g_sd + 0x14f98))
#define g_zero_psd (*(psd *)(g_sd + 0x12db0))
#define s_012345678901234567890123456789_0043c490 (*(char (*)[32])(g_sd + 0x1490))
#define s_CODE__02x_Offset__08x_004420bc (*(char (*)[23])(g_sd + 0x70bc))
#define s_Count_Cycle_Node_Instruction_0043c410 (*(char (*)[49])(g_sd + 0x1410))
#define s_Data_Dependency_List_0043c248 (*(char (*)[22])(g_sd + 0x1248))
#define s_FILE_NAME__00442108 (*(char (*)[12])(g_sd + 0x7108))
#define s_FlowChild_AntiChild_AmbiChild_Ki_0043c2a0 (*(char (*)[61])(g_sd + 0x12a0))
#define s_FlowParent_AntiParent_AmbiParent_0043c320 (*(char (*)[61])(g_sd + 0x1320))
#define s_H_apos_0043c7bc (*(char (*)[1])(g_sd + 0x17bc))
#define s_H_apos_0043c7c0 (*(char (*)[1])(g_sd + 0x17c0))
#define s_H_apos_00441e70 (*(char (*)[1])(g_sd + 0x6e70))
#define s_H_apos_00441e74 (*(char (*)[1])(g_sd + 0x6e74))
#define s_H_apos_00441e78 (*(char (*)[1])(g_sd + 0x6e78))
#define s_H_apos_00441e7c (*(char (*)[1])(g_sd + 0x6e7c))
#define s_H_apos_00441e80 (*(char (*)[1])(g_sd + 0x6e80))
#define s_H_apos_00441e84 (*(char (*)[1])(g_sd + 0x6e84))
#define s_H_apos_00441e88 (*(char (*)[1])(g_sd + 0x6e88))
#define s_H_apos_00441e8c (*(char (*)[1])(g_sd + 0x6e8c))
#define s_H_apos_00441e90 (*(char (*)[1])(g_sd + 0x6e90))
#define s_H_apos_00441e94 (*(char (*)[1])(g_sd + 0x6e94))
#define s_H_apos_00441ea0 (*(char (*)[1])(g_sd + 0x6ea0))
#define s_H_apos_00441eac (*(char (*)[1])(g_sd + 0x6eac))
#define s_H_apos_0044209c (*(char (*)[1])(g_sd + 0x709c))
#define s_H_apos_004420a0 (*(char (*)[1])(g_sd + 0x70a0))
#define s_H_apos_004420ac (*(char (*)[1])(g_sd + 0x70ac))
#define s_H_apos_004420b0 (*(char (*)[1])(g_sd + 0x70b0))
#define s_IMM_0043c748 (*(char (*)[1])(g_sd + 0x1748))
#define s_INSTRUCTION_OPERAND_COMMENT_00442148 (*(char (*)[36])(g_sd + 0x7148))
#define s_Line_00442068 (*(char (*)[6])(g_sd + 0x7068))
#define s_Microsoft_Visual_C___Runtime_Lib_00443ac4 (*(char (*)[37])(g_sd + 0x8ac4))
#define s_NON_00441940 (*(char (*)[1])(g_sd + 0x6940))
#define s_No_0043c458 (*(char (*)[49])(g_sd + 0x1458))
#define s_No_Instruction_Read_0043c260 (*(char (*)[57])(g_sd + 0x1260))
#define s_Original_Easy_View_0043c3e0 (*(char (*)[20])(g_sd + 0x13e0))
#define s_PCDB_00442078 (*(char (*)[1])(g_sd + 0x7078))
#define s_Pipeline_0043c448 (*(char (*)[10])(g_sd + 0x1448))
#define s_R0___DISP_GBR___0043c58c (*(char (*)[16])(g_sd + 0x158c))
#define s_Runtime_Error__Program__00443af0 (*(char (*)[28])(g_sd + 0x8af0))
#define s_SHCPP_INC_0044318c (*(char (*)[10])(g_sd + 0x818c))
#define s_SHCPP_LIB_00443180 (*(char (*)[10])(g_sd + 0x8180))
#define s_SHCPP_TMP_00443174 (*(char (*)[10])(g_sd + 0x8174))
#define s_SHC_INC_004431a8 (*(char (*)[8])(g_sd + 0x81a8))
#define s_SHC_LIB_004431a0 (*(char (*)[8])(g_sd + 0x81a0))
#define s_SHC_TMP_00443198 (*(char (*)[8])(g_sd + 0x8198))
#define s_Scheduled_Easy_View_0043c3f8 (*(char (*)[21])(g_sd + 0x13f8))
#define s_Write_0043c2e0 (*(char (*)[57])(g_sd + 0x12e0))
#define s__00442118 (*(char (*)[12])(g_sd + 0x7118))
#define s__0____0044311c (*(char (*)[7])(g_sd + 0x811c))
#define s__1_____0043c5cc (*(char (*)[7])(g_sd + 0x15cc))
#define s__2147483648_00441dc0 (*(char (*)[12])(g_sd + 0x6dc0))
#define s__2_____0043c5c4 (*(char (*)[7])(g_sd + 0x15c4))
#define s__2d__5s_0043c644 (*(char (*)[14])(g_sd + 0x1644))
#define s__4_____0043c5bc (*(char (*)[7])(g_sd + 0x15bc))
#define s__4s_0043c688 (*(char (*)[7])(g_sd + 0x1688))
#define s__5d__5d__5d__5s_0043c6e0 (*(char (*)[21])(g_sd + 0x16e0))
#define s__8____0043c530 (*(char (*)[6])(g_sd + 0x1530))
#define s__ALIGN_00441f7c (*(char (*)[7])(g_sd + 0x6f7c))
#define s__ALIGN_00442070 (*(char (*)[7])(g_sd + 0x7070))
#define s__ALIGN_16_00441e20 (*(char (*)[10])(g_sd + 0x6e20))
#define s__ALIGN_32_00441e30 (*(char (*)[10])(g_sd + 0x6e30))
#define s__ALIGN_4_00441e00 (*(char (*)[9])(g_sd + 0x6e00))
#define s__ALIGN_8_00441e10 (*(char (*)[9])(g_sd + 0x6e10))
#define s__DATAB_00441ddc (*(char (*)[7])(g_sd + 0x6ddc))
#define s__DATA_00441958 (*(char (*)[6])(g_sd + 0x6958))
#define s__DATA_00441de4 (*(char (*)[6])(g_sd + 0x6de4))
#define s__DATA_00442094 (*(char (*)[6])(g_sd + 0x7094))
#define s__DATA_004420a4 (*(char (*)[6])(g_sd + 0x70a4))
#define s__DATA_B_00441e98 (*(char (*)[8])(g_sd + 0x6e98))
#define s__DATA_B_00441ea4 (*(char (*)[8])(g_sd + 0x6ea4))
#define s__EXPORT_0043c03c (*(char (*)[8])(g_sd + 0x103c))
#define s__IMM__0043c61c (*(char (*)[6])(g_sd + 0x161c))
#define s__IMPORT_0043c034 (*(char (*)[8])(g_sd + 0x1034))
#define s__LINE_00441e50 (*(char (*)[6])(g_sd + 0x6e50))
#define s__SDATA_00441df4 (*(char (*)[7])(g_sd + 0x6df4))
#define s__SECTION_00441e40 (*(char (*)[9])(g_sd + 0x6e40))
#define s__STARTOF_004419bc (*(char (*)[10])(g_sd + 0x69bc))
#define s___DISP_GBR__R0_0043c5ec (*(char (*)[15])(g_sd + 0x15ec))
#define s___DISP__0043c5fc (*(char (*)[8])(g_sd + 0x15fc))
#define s___File_0044205c (*(char (*)[8])(g_sd + 0x705c))
#define s___Line_0043c7b0 (*(char (*)[8])(g_sd + 0x17b0))
#define s___R0__0043c544 (*(char (*)[6])(g_sd + 0x1544))
#define s___R0__0043c5e0 (*(char (*)[6])(g_sd + 0x15e0))
#define s___R0__s__0043c724 (*(char (*)[9])(g_sd + 0x1724))
#define s____2d_00441948 (*(char (*)[6])(g_sd + 0x6948))
#define s____DISP__0043c59c (*(char (*)[9])(g_sd + 0x159c))
#define s____R0__0043c520 (*(char (*)[7])(g_sd + 0x1520))
#define s____R0__0043c580 (*(char (*)[7])(g_sd + 0x1580))
#define s____R0__s__0043c778 (*(char (*)[10])(g_sd + 0x1778))
#define s________________________________0043c4e8 (*(char (*)[32])(g_sd + 0x14e8))
#define s__________________________________0043c360 (*(char (*)[57])(g_sd + 0x1360))
#define s__________________________________0043c3a0 (*(char (*)[61])(g_sd + 0x13a0))
#define s__________________________________0043c4b0 (*(char (*)[49])(g_sd + 0x14b0))
#define s_____s_0043c75c (*(char (*)[6])(g_sd + 0x175c))
#define s_____s_GBR__0043c794 (*(char (*)[11])(g_sd + 0x1794))
#define s____disp_GBR__0043c784 (*(char (*)[13])(g_sd + 0x1784))
#define s____disp_PC__0043c5ac (*(char (*)[12])(g_sd + 0x15ac))
#define s____disp__s__0043c76c (*(char (*)[12])(g_sd + 0x176c))
#define s____s_GBR__0043c73c (*(char (*)[10])(g_sd + 0x173c))
#define s____s__0043c764 (*(char (*)[6])(g_sd + 0x1764))
#define s___disp_GBR__0043c730 (*(char (*)[12])(g_sd + 0x1730))
#define s___disp__s__0043c718 (*(char (*)[11])(g_sd + 0x1718))
#define s___frame_size__00441f48 (*(char (*)[14])(g_sd + 0x6f48))
#define s___used_runtime_library_name__00441f58 (*(char (*)[29])(g_sd + 0x6f58))
#define s__s_d__d_00442438 (*(char (*)[8])(g_sd + 0x7438))
#define s_ab_00443114 (*(char (*)[1])(g_sd + 0x8114))
#define s_argument_separator (*(unsigned char *)(g_sd + 0x7bd4))
#define s_at_lp_0043c53c (*(char (*)[1])(g_sd + 0x153c))
#define s_at_lp_0043c5d8 (*(char (*)[1])(g_sd + 0x15d8))
#define s_at_minus_0043c7c4 (*(char (*)[1])(g_sd + 0x17c4))
#define s_at_minus_pct_s_0043c708 (*(char (*)[1])(g_sd + 0x1708))
#define s_at_pct_s_0043c704 (*(char (*)[1])(g_sd + 0x1704))
#define s_at_pct_s_plus_0043c710 (*(char (*)[1])(g_sd + 0x1710))
#define s_close_paren (*(int *)(g_sd + 0x7bc8))
#define s_colon_0043c574 (*(char (*)[1])(g_sd + 0x1574))
#define s_colon_16_00441db4 (*(char (*)[1])(g_sd + 0x6db4))
#define s_colon_32_00441db8 (*(char (*)[1])(g_sd + 0x6db8))
#define s_colon_4_00441dbc (*(char (*)[1])(g_sd + 0x6dbc))
#define s_colon_8_00441db0 (*(char (*)[1])(g_sd + 0x6db0))
#define s_comma_0_00441e6c (*(char (*)[1])(g_sd + 0x6e6c))
#define s_comma_at_pct_s_0043c754 (*(char (*)[1])(g_sd + 0x1754))
#define s_comma_pct_s_0043c750 (*(char (*)[1])(g_sd + 0x1750))
#define s_comma_pct_s_0043c7a4 (*(char (*)[1])(g_sd + 0x17a4))
#define s_comma_sp_00442064 (*(char (*)[1])(g_sd + 0x7064))
#define s_const_suffix (*(char (*)[8])(g_sd + 0x7bd8))
#define s_depend___00441928 (*(char (*)[24])(g_sd + 0x6928))
#define s_dollar_G0_004419c8 (*(char (*)[1])(g_sd + 0x69c8))
#define s_dollar_G0_00442080 (*(char (*)[1])(g_sd + 0x7080))
#define s_dollar_G1_00442084 (*(char (*)[1])(g_sd + 0x7084))
#define s_dot_END_00440d50 (*(char (*)[1])(g_sd + 0x5d50))
#define s_dot_END_00441e60 (*(char (*)[1])(g_sd + 0x6e60))
#define s_dot_RES_00441960 (*(char (*)[1])(g_sd + 0x6960))
#define s_dot_RES_00441dec (*(char (*)[1])(g_sd + 0x6dec))
#define s_dot_RES_0044208c (*(char (*)[1])(g_sd + 0x708c))
#define s_dot_dot_0043c654 (*(char (*)[1])(g_sd + 0x1654))
#define s_dot_dot_0043c664 (*(char (*)[1])(g_sd + 0x1664))
#define s_dot_dot_0043c670 (*(char (*)[1])(g_sd + 0x1670))
#define s_dot_dot_0043c67c (*(char (*)[1])(g_sd + 0x167c))
#define s_dot_dot_0043c6a0 (*(char (*)[1])(g_sd + 0x16a0))
#define s_dot_dot_0043c6b0 (*(char (*)[1])(g_sd + 0x16b0))
#define s_dot_dot_0043c6bc (*(char (*)[1])(g_sd + 0x16bc))
#define s_dot_dot_0043c6c8 (*(char (*)[1])(g_sd + 0x16c8))
#define s_empty_string (*(unsigned char *)(g_sd + 0x7440))
#define s_enum_prefix (*(char (*)[8])(g_sd + 0x7bf0))
#define s_eq_0043c510 (*(char (*)[1])(g_sd + 0x1510))
#define s_eq_0043c52c (*(char (*)[1])(g_sd + 0x152c))
#define s_eq_0043c550 (*(char (*)[1])(g_sd + 0x1550))
#define s_eq_0043c55c (*(char (*)[1])(g_sd + 0x155c))
#define s_eq_0043c5b8 (*(char (*)[1])(g_sd + 0x15b8))
#define s_eq_0043c60c (*(char (*)[1])(g_sd + 0x160c))
#define s_eq_0043c614 (*(char (*)[1])(g_sd + 0x1614))
#define s_eq_0043c624 (*(char (*)[1])(g_sd + 0x1624))
#define s_eq_0043c62c (*(char (*)[1])(g_sd + 0x162c))
#define s_eq_0043c634 (*(char (*)[1])(g_sd + 0x1634))
#define s_eq_0043c63c (*(char (*)[1])(g_sd + 0x163c))
#define s_eq_1_plus_0043c570 (*(char (*)[1])(g_sd + 0x1570))
#define s_eq_2_plus_0043c56c (*(char (*)[1])(g_sd + 0x156c))
#define s_eq_4_plus_0043c568 (*(char (*)[1])(g_sd + 0x1568))
#define s_eq_IMM_0043c554 (*(char (*)[1])(g_sd + 0x1554))
#define s_eq_at_lp_0043c508 (*(char (*)[1])(g_sd + 0x1508))
#define s_eq_at_lp_0043c518 (*(char (*)[1])(g_sd + 0x1518))
#define s_eq_at_lp_0043c560 (*(char (*)[1])(g_sd + 0x1560))
#define s_eq_at_lp_0043c578 (*(char (*)[1])(g_sd + 0x1578))
#define s_flags__04x__count__d__next__d_004418f8 (*(char (*)[46])(g_sd + 0x68f8))
#define s_lt_pct_s_gt_0043c658 (*(char (*)[1])(g_sd + 0x1658))
#define s_lt_pct_s_gt_0043c6a4 (*(char (*)[1])(g_sd + 0x16a4))
#define s_member_pointer_suffix (*(int *)(g_sd + 0x7bd0))
#define s_minus_0043c630 (*(char (*)[1])(g_sd + 0x1630))
#define s_minus_0043c638 (*(char (*)[1])(g_sd + 0x1638))
#define s_minus_0043c640 (*(char (*)[1])(g_sd + 0x1640))
#define s_nl_00441950 (*(char (*)[1])(g_sd + 0x6950))
#define s_nl_0044313c (*(unsigned char *)(g_sd + 0x813c))
#define s_nl_nl_0043c6dc (*(char (*)[1])(g_sd + 0x16dc))
#define s_nl_sp_sp_00443124 (*(char (*)[1])(g_sd + 0x8124))
#define s_object_listing_banner (*(char (*)[41])(g_sd + 0x70d8))
#define s_object_listing_header (*(char (*)[32])(g_sd + 0x7128))
#define s_object_program_empty (*(char (*)[25])(g_sd + 0x7170))
#define s_open_paren (*(int *)(g_sd + 0x7bc4))
#define s_operator_prefix (*(char (*)[10])(g_sd + 0x7bb8))
#define s_pct_2d_00441944 (*(char (*)[1])(g_sd + 0x6944))
#define s_pct_2d_nl_0043c694 (*(char (*)[1])(g_sd + 0x1694))
#define s_pct_4d_nl_0043c6d4 (*(char (*)[1])(g_sd + 0x16d4))
#define s_pct_d_00440ce0 (*(char (*)[1])(g_sd + 0x5ce0))
#define s_pct_d_00440ce4 (*(char (*)[1])(g_sd + 0x5ce4))
#define s_pct_d_00440ce8 (*(char (*)[1])(g_sd + 0x5ce8))
#define s_pct_d_00440cec (*(char (*)[1])(g_sd + 0x5cec))
#define s_pct_d_00440cf0 (*(char (*)[1])(g_sd + 0x5cf0))
#define s_pct_d_00440cf4 (*(char (*)[1])(g_sd + 0x5cf4))
#define s_pct_d_00440cf8 (*(char (*)[1])(g_sd + 0x5cf8))
#define s_pct_d_00440cfc (*(char (*)[1])(g_sd + 0x5cfc))
#define s_pct_d_00443128 (*(char (*)[1])(g_sd + 0x8128))
#define s_pct_d_colon_0043c668 (*(char (*)[1])(g_sd + 0x1668))
#define s_pct_d_colon_0043c674 (*(char (*)[1])(g_sd + 0x1674))
#define s_pct_d_colon_0043c680 (*(char (*)[1])(g_sd + 0x1680))
#define s_pct_d_colon_0043c6b4 (*(char (*)[1])(g_sd + 0x16b4))
#define s_pct_d_colon_0043c6c0 (*(char (*)[1])(g_sd + 0x16c0))
#define s_pct_d_colon_0043c6cc (*(char (*)[1])(g_sd + 0x16cc))
#define s_pct_s_0043c700 (*(char (*)[1])(g_sd + 0x1700))
#define s_pct_s_0043c74c (*(char (*)[1])(g_sd + 0x174c))
#define s_pct_s_nl_0043c6fc (*(char (*)[1])(g_sd + 0x16fc))
#define s_pipetbl_dump_after_pipeline (*(char (*)[32])(g_sd + 0x5d68))
#define s_placeholder_name_format (*(char (*)[7])(g_sd + 0x7bf8))
#define s_plus_0043c610 (*(char (*)[1])(g_sd + 0x1610))
#define s_plus_0043c618 (*(char (*)[1])(g_sd + 0x1618))
#define s_plus_0043c628 (*(char (*)[1])(g_sd + 0x1628))
#define s_plus_8_0043c514 (*(char (*)[1])(g_sd + 0x1514))
#define s_rb_00440cd8 (*(char (*)[1])(g_sd + 0x5cd8))
#define s_rb_00440cdc (*(char (*)[1])(g_sd + 0x5cdc))
#define s_rb_00440d40 (*(char (*)[1])(g_sd + 0x5d40))
#define s_rb_00440d44 (*(char (*)[1])(g_sd + 0x5d44))
#define s_rb_00440d48 (*(char (*)[1])(g_sd + 0x5d48))
#define s_rb_00440d4c (*(char (*)[1])(g_sd + 0x5d4c))
#define s_rb_00440d58 (*(char (*)[1])(g_sd + 0x5d58))
#define s_rb_00441974 (*(char (*)[1])(g_sd + 0x6974))
#define s_rb_00441e68 (*(char (*)[1])(g_sd + 0x6e68))
#define s_rb_004420b4 (*(char (*)[1])(g_sd + 0x70b4))
#define s_rb_004420b8 (*(char (*)[1])(g_sd + 0x70b8))
#define s_rb_00442c5c (*(char (*)[1])(g_sd + 0x7c5c))
#define s_request_compiler_version (*(char (*)[44])(g_sd + 0x17c8))
#define s_request_copyright (*(char (*)[76])(g_sd + 0x17f8))
#define s_rp_0043c51c (*(char (*)[1])(g_sd + 0x151c))
#define s_rp_0043c528 (*(char (*)[1])(g_sd + 0x1528))
#define s_rp_0043c57c (*(char (*)[1])(g_sd + 0x157c))
#define s_rp_0043c588 (*(char (*)[1])(g_sd + 0x1588))
#define s_rp_0043c5a8 (*(char (*)[1])(g_sd + 0x15a8))
#define s_rp_004419cc (*(char (*)[1])(g_sd + 0x69cc))
#define s_rp_colon_0043c50c (*(char (*)[1])(g_sd + 0x150c))
#define s_rp_colon_0043c564 (*(char (*)[1])(g_sd + 0x1564))
#define s_rp_eq_0043c538 (*(char (*)[1])(g_sd + 0x1538))
#define s_rp_eq_0043c540 (*(char (*)[1])(g_sd + 0x1540))
#define s_rp_eq_0043c54c (*(char (*)[1])(g_sd + 0x154c))
#define s_rp_eq_0043c5d4 (*(char (*)[1])(g_sd + 0x15d4))
#define s_rp_eq_0043c5dc (*(char (*)[1])(g_sd + 0x15dc))
#define s_rp_eq_0043c5e8 (*(char (*)[1])(g_sd + 0x15e8))
#define s_rp_eq_R0_0043c604 (*(char (*)[1])(g_sd + 0x1604))
#define s_scope_separator (*(int *)(g_sd + 0x7bcc))
#define s_semi_sp_0043c7b8 (*(char (*)[1])(g_sd + 0x17b8))
#define s_sp_0043c660 (*(char (*)[1])(g_sd + 0x1660))
#define s_sp_0043c66c (*(char (*)[1])(g_sd + 0x166c))
#define s_sp_0043c678 (*(char (*)[1])(g_sd + 0x1678))
#define s_sp_0043c684 (*(char (*)[1])(g_sd + 0x1684))
#define s_sp_0043c690 (*(char (*)[1])(g_sd + 0x1690))
#define s_sp_0043c69c (*(char (*)[1])(g_sd + 0x169c))
#define s_sp_0043c6ac (*(char (*)[1])(g_sd + 0x16ac))
#define s_sp_0043c6b8 (*(char (*)[1])(g_sd + 0x16b8))
#define s_sp_0043c6c4 (*(char (*)[1])(g_sd + 0x16c4))
#define s_sp_0043c6d0 (*(char (*)[1])(g_sd + 0x16d0))
#define s_sp_0043c6f8 (*(char (*)[1])(g_sd + 0x16f8))
#define s_sp_0043c7a8 (*(char (*)[1])(g_sd + 0x17a8))
#define s_sp_00442088 (*(char (*)[1])(g_sd + 0x7088))
#define s_sp_00443118 (*(unsigned char *)(g_sd + 0x8118))
#define s_sp_sp_00443140 (*(unsigned char *)(g_sd + 0x8140))
#define s_sp_us_00441f78 (*(char (*)[1])(g_sd + 0x6f78))
#define s_space (*(int *)(g_sd + 0x7bec))
#define s_str_00443b0c (*(char (*)[24])(g_sd + 0x8b0c))
#define s_tbl__d___s__refreg__08x__08x__se_004418c8 (*(char (*)[48])(g_sd + 0x68c8))
#define s_tmp_suffix (*(int *)(g_sd + 0x7430))
#define s_volatile_suffix (*(char (*)[12])(g_sd + 0x7be0))
#define s_wb_00442e24 (*(char (*)[1])(g_sd + 0x7e24))
#define s_wb_plus (*(unsigned char *)(g_sd + 0x742c))
#define stock_XcptActTab (*(unsigned char *)(g_sd + 0x8730))
#define stock_XcptActTabCount (*(int *)(g_sd + 0x87b0))
#define stock_acmdln (*(int *)(g_sd + 0x16cc0))
#define stock_adbgmsg (*(int *)(g_sd + 0x8ac0))
#define stock_aenvptr (*(int *)(g_sd + 0x81f8))
#define stock_aexit_rtn (*(char * *)(g_sd + 0x8200))
#define stock_app_type (*(int *)(g_sd + 0x8208))
#define stock_argc (*(int *)(g_sd + 0x81cc))
#define stock_argv (*(int *)(g_sd + 0x81d0))
#define stock_commode (*(int *)(g_sd + 0x8c90))
#define stock_crtheap (*(int *)(g_sd + 0x15cb0))
#define stock_doserrno (*(int *)(g_sd + 0x81b4))
#define stock_environ (*(int *)(g_sd + 0x81d8))
#define stock_error_mode (*(int *)(g_sd + 0x8204))
#define stock_errtable (*(int *)(g_sd + 0x8b28))
#define stock_exitflag (*(unsigned char *)(g_sd + 0x81f0))
#define stock_fSystemSet (*(int *)(g_sd + 0x85f4))
#define stock_f_use_CompareString (*(int *)(g_sd + 0x8f88))
#define stock_f_use_GetEnvironmentStrings (*(int *)(g_sd + 0x87c0))
#define stock_f_use_GetStringType (*(int *)(g_sd + 0x8f78))
#define stock_f_use_LCMapString (*(int *)(g_sd + 0x8f90))
#define stock_fmode (*(int *)(g_sd + 0x8f70))
#define stock_fpinit (*(int *)(g_sd + 0x16cc8))
#define stock_initenv (*(int *)(g_sd + 0x81dc))
#define stock_lc_codepage (*(int *)(g_sd + 0x8ed0))
#define stock_mb_cur_max (*(int *)(g_sd + 0x8eac))
#define stock_mbcodepage (*(int *)(g_sd + 0x85dc))
#define stock_mbctype (*(int *)(g_sd + 0x84d8))
#define stock_mblcid (*(int *)(g_sd + 0x85e0))
#define stock_mbulinfo (*(int *)(g_sd + 0x85e8))
#define stock_namebuf0 (*(unsigned char *)(g_sd + 0x8210))
#define stock_namebuf1 (*(unsigned char *)(g_sd + 0x8220))
#define stock_newmode (*(int *)(g_sd + 0x86f0))
#define stock_nhandle (*(int *)(g_sd + 0x15ba4))
#define stock_nstream (*(int *)(g_sd + 0x15cb4))
#define stock_onexitbegin (*(int *)(g_sd + 0x16ccc))
#define stock_onexitend (*(int *)(g_sd + 0x16cc4))
#define stock_pctype (*(char * *)(g_sd + 0x8ca0))
#define stock_pgmname (*(unsigned char *)(g_sd + 0xc568))
#define stock_piob (*(int *)(g_sd + 0x15cb8))
#define stock_pioinfo (*(int *)(g_sd + 0x15bb0))
#define stock_pnhHeap (*(int *)(g_sd + 0xc560))
#define stock_rgcode_page_info (*(int *)(g_sd + 0x8600))
#define stock_rgctypeflag (*(unsigned char *)(g_sd + 0x85f8))
#define stock_rterrs (*(int *)(g_sd + 0x8a38))
#define stock_stderr (*(unsigned char *)(g_sd + 0x8290))
#define stock_stdout (*(unsigned char *)(g_sd + 0x8270))
#define stock_umaskval (*(int *)(g_sd + 0x81b8))
#define stock_wenviron (*(int *)(g_sd + 0x81e0))
#define stock_xc_a (*(unsigned char *)(g_sd + 0x1000))
#define stock_xc_z (*(unsigned char *)(g_sd + 0x1004))
#define stock_xi_a (*(unsigned char *)(g_sd + 0x1008))
#define stock_xi_z (*(unsigned char *)(g_sd + 0x1010))
#define stock_xp_a (*(unsigned char *)(g_sd + 0x1014))
#define stock_xp_z (*(unsigned char *)(g_sd + 0x1020))
#define stock_xt_a (*(unsigned char *)(g_sd + 0x1024))
#define stock_xt_z (*(unsigned char *)(g_sd + 0x1028))

#endif
