#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_assigned_symbol_count
#define g_assigned_symbol_count (*(short *)(g_sd + 0x1ee98))
#undef g_lreg_entry_count
#define g_lreg_entry_count (*(short *)(g_sd + 0x1fa4e))
#undef g_lreg_table
#define g_lreg_table (*(short * *)(g_sd + 0x1fa10))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 004160f0
// name : assign_function_storage
// size : 788
// sig  : void assign_function_storage(gen_node * func)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl assign_function_storage(gen_node *func)

{
  short *psVar1;
  int iVar2;
  uint uVar3;
  byte bVar4;
  short *entry_reg;
  uint uVar5;
  ushort gpr_mask;
  ushort fpr_mask;
  int ofs;
  undefined4 *item;
  undefined4 *next;
  short reg;
  
  g_frame_end = -4;
  gpr_mask = 0;
  g_used_gpr_mask = 0;
  g_var_gpr_mask = 0;
  g_mac_regs_used = '\0';
  g_used_fpr_mask = 0;
  g_saved_sys_mask = '\0';
  g_var_fpr_mask = 0;
  g_sptravel = 0;
  g_stmt_temp_regs = 0;
  g_local_frame_size = 0;
  _g_lreg_entry_count = 0;
  g_max_sptravel = 0;
  fpr_mask = 0;
  g_max_temp_frame = 0;
  _g_assigned_symbol_count = 0;
  g_stmt_serial = 0;
  g_gpr_contents_stack = 0;
  g_last_chosen_reg = -1;
  g_fpscr_pr_stack = 0;
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\x02')) {
    g_fpscr_pr = '\x01';
  }
  else {
    g_fpscr_pr = '\0';
  }
  ofs = 0;
  do {
    item = *(undefined4 **)(g_gpr_contents[0].unknown_0a + ofs + 6);
    while (item != (undefined4 *)0x0) {
      next = (undefined4 *)*item;
      pool_free(item,0xc);
      item = next;
    }
    zero_words((uint *)(g_gpr_contents[0].unknown_0a + ofs + -10),6);
    item = *(undefined4 **)(g_fpr_contents[0].unknown_0a + ofs + 6);
    while (item != (undefined4 *)0x0) {
      next = (undefined4 *)*item;
      pool_free(item,0xc);
      item = next;
    }
    iVar2 = ofs + -10;
    ofs = ofs + 0x18;
    zero_words((uint *)(g_fpr_contents[0].unknown_0a + iVar2),6);
  } while (ofs < 0x60);
  if (((*(short *)g_request->unknown_004 != 0) &&
      (read_reg_file_lreg_table(), g_no_reg_ranges == '\0')) && (*g_lreg_table != 0)) {
    entry_reg = g_lreg_table + 1;
    do {
      reg = *entry_reg;
      bVar4 = (byte)reg;
      if ((reg < 0x10) && (3 < reg)) {
        gpr_mask = gpr_mask | 1 << (bVar4 & 0x1f);
      }
      else if ((reg < 0x20) && (0x13 < reg)) {
        fpr_mask = fpr_mask | 1 << (bVar4 - 0x10 & 0x1f);
      }
      else if ((reg < 0x2f) && (0x23 < reg)) {
        fpr_mask = fpr_mask | 1 << (bVar4 - 0x1f & 0x1f) | 1 << (bVar4 - 0x20 & 0x1f);
      }
      psVar1 = entry_reg + 0x11;
      entry_reg = entry_reg + 0x12;
    } while (*psVar1 != 0);
  }
  uVar3 = (int)func->symx + 0xb6;
  uVar5 = (int)uVar3 >> 0x1f;
  g_used_fpr_mask = fpr_mask;
  g_used_gpr_mask = gpr_mask;
  if ((g_symbol_table[(uVar3 ^ uVar5) - uVar5].attr & 0x18) != 0) {
    g_used_gpr_mask = 0x7f00;
    g_used_fpr_mask =
         (1 << (0xcU - g_request->scratch_bank_reg_count & 0x1f)) + -1 <<
         (g_request->scratch_bank_reg_count + 4U & 0x1f);
  }
  g_used_gpr_mask = g_used_gpr_mask | (ushort)g_request->reg_mask_150 & 0x7f00;
  g_var_gpr_mask = g_used_gpr_mask;
  g_used_fpr_mask =
       g_used_fpr_mask |
       (1 << (0xcU - g_request->scratch_bank_reg_count & 0x1f)) + -1 <<
       (g_request->scratch_bank_reg_count + 4U & 0x1f) & (ushort)(g_request->reg_mask_150 >> 0x10);
  g_var_fpr_mask = g_used_fpr_mask;
  assign_parameter_storage(func);
  g_used_gpr_mask = g_used_gpr_mask | gpr_mask;
  g_var_gpr_mask = g_used_gpr_mask;
  g_used_fpr_mask = g_used_fpr_mask | fpr_mask;
  g_var_fpr_mask = g_used_fpr_mask;
  assign_block_local_storage(func->child->symx + 0xb6,g_frame_end);
  uVar3 = g_frame_end >> 0x1f;
  if (((g_frame_end ^ uVar3) - uVar3 & 3 ^ uVar3) != uVar3) {
    g_frame_end = g_frame_end & 0xfffffffc;
  }
  if ((*(short *)g_request->unknown_004 != 0) && (g_no_reg_ranges == '\0')) {
    assign_lreg_storage();
    g_current_function = func->symx + 0xb6;
    mark_arg_register_lregs_holding_parameters();
  }
  g_local_frame_size = -4 - g_frame_end;
  return;
}



