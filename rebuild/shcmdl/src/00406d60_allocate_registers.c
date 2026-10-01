#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_candidate_list_tail
#define g_candidate_list_tail (*(lreg * *)(g_sd + 0x1626c))
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_loop_tree
#define g_loop_tree (*(loop * *)(g_sd + 0x267f0))
#undef g_lreg_list
#define g_lreg_list (*(lreg * *)(g_sd + 0x16264))
#undef g_mem_freq_list
#define g_mem_freq_list (*(mem_freq * *)(g_sd + 0x164a0))
#undef g_noalloc_leaf_regs
#define g_noalloc_leaf_regs (*(void * *)(g_sd + 0x16488))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00406d60
// name : allocate_registers
// size : 538
// sig  : void allocate_registers(void)


int __cdecl allocate_registers(void)

{
  void *rec;
  
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 4) == 0) {
    if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 3) != 0) {
      FID_conflict__wprintf(&g_str_target_function_name,g_symtab[g_func_node->symx].name);
    }
    build_dag_chains('\x01');
    compute_dataflow('\x03');
    if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
      dump_tree(g_func_node,0,s_register_allocation_before_tree_00434418);
    }
    link_def_use_webs();
    g_lreg_list = (lreg *)0x0;
    g_candidate_list_tail = (lreg *)0x0;
    prepare_register_allocation();
    g_regalloc_phase = 1;
    weigh_common_expression_candidates();
    compute_lreg_priorities_and_life_areas();
    build_lreg_clash_lists();
    coalesce_copy_webs();
    compute_lreg_profits();
    sort_lregs_by_profit();
    assign_argument_registers();
    assign_parameter_registers();
    g_regalloc_phase = 2;
    assign_physical_registers();
    if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
      dump_block_table(g_f_chain,s_after_physicalreg_00434404);
    }
    g_regalloc_phase = 3;
    allocate_block_registers();
    collect_memory_frequencies();
    clear_unlinked_block_statements();
    if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 3) != 0) {
      dump_tree(g_func_node,0,s_register_allocation_after_tree_004343e4);
    }
    if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
      dump_loop_tree_titled(g_loop_tree,s_register_allocation_after_loop_t_004343bc);
      dump_leaf_table();
      dump_logical_register_list(s_after_blockreg_004343ac);
    }
    remove_unused_parameter_assignments();
    g_expp_counter = 1;
    number_expps(g_func_node);
    if (g_mem_freq_list != (mem_freq *)0x0) {
      reflect_register_numbers();
    }
    write_register_allocation_table();
    free_register_allocation_tables();
    free_du_tables();
  }
  else {
    FID_conflict__wprintf(s______REGISTER_ALLOCATION_NOT_RUN_00434460);
    write_reg_header(g_func_node->symx,1,1);
    g_lreg_count = 1;
    g_noalloc_leaf_regs = (void *)0x0;
    g_int_reg_count = 0xe;
    assign_registers_without_allocation(g_func_node);
    write_reg_trailer(g_func_node->symx);
    if (g_noalloc_leaf_regs != (void *)0x0) {
      do {
        rec = g_noalloc_leaf_regs;
        g_noalloc_leaf_regs = *(void **)((int)g_noalloc_leaf_regs + 0xc);
        pool_free(rec,0x10);
      } while (g_noalloc_leaf_regs != (void *)0x0);
      return;
    }
  }
  return;
}



