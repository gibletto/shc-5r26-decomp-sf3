#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_aux_record
#define g_current_aux_record (*(unsigned int * *)(g_sd + 0x1f950))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_sptravel
#define g_sptravel (*(short *)(g_sd + 0x1f944))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0040ad10
// name : end_function_code
// size : 950
// sig  : void end_function_code(gen_node * node)


int __cdecl end_function_code(gen_node *node)

{
  byte fpu_mode;
  uint uVar1;
  uint uVar2;
  uint uVar3;
  ushort saved_gpr_mask;
  
  if ((g_return_label != 0) && (g_return_label_used != '\0')) {
    fill_label_record((psd *)&g_psd_scratch,OP_LABEL,g_return_label,(short)g_sptravel);
    emit_psd_record((psd *)&g_psd_scratch,0);
  }
  *(undefined1 *)(g_current_aux_record + 10) = 0xff;
  if ((*(short *)g_request->unknown_004 != 0) && (g_no_reg_ranges == '\0')) {
    remap_register_variables_to_scratch_registers();
    g_used_gpr_mask = g_used_gpr_mask | g_stmt_temp_regs & 0xf0U;
  }
  saved_gpr_mask = g_used_gpr_mask;
  uVar3 = g_max_temp_frame + g_local_frame_size;
  if ((0x7f < uVar3) && (g_used_gpr_mask = g_used_gpr_mask | 2, 0x80 < uVar3)) {
    (*(unsigned char *)((char *)&g_used_gpr_mask + 1)) = SUB21(saved_gpr_mask,1);
    g_used_gpr_mask = CONCAT11((*(unsigned char *)((char *)&g_used_gpr_mask + 1)),(undefined1)g_used_gpr_mask) | 1;
  }
  uVar1 = (uint)(short)(node->symx + 0xb6);
  uVar2 = (int)uVar1 >> 0x1f;
  if ((g_symbol_table[(uVar1 ^ uVar2) - uVar2].sym_flags & 0x10) == 0) {
    g_used_gpr_mask = g_used_gpr_mask & 0x7f00;
    g_used_fpr_mask =
         g_used_fpr_mask &
         (1 << (0xcU - g_request->scratch_bank_reg_count & 0x1f)) + -1 <<
         (g_request->scratch_bank_reg_count + 4U & 0x1f);
  }
  uVar1 = (uint)(short)(node->symx + 0xb6);
  uVar2 = (int)uVar1 >> 0x1f;
  if ((g_symbol_table[(uVar1 ^ uVar2) - uVar2].attr & 0x10) == 0) {
    if ((g_symbol_table[(uVar1 ^ uVar2) - uVar2].attr & 0xc) != 0) {
      g_used_gpr_mask = g_used_gpr_mask & 0x80ff;
      g_mac_regs_used = g_mac_regs_used & 0xfc;
      g_saved_sys_mask = g_saved_sys_mask & 0xfc;
      g_used_fpr_mask =
           g_used_fpr_mask &
           ~((1 << (0xcU - g_request->scratch_bank_reg_count & 0x1f)) + -1 <<
            (g_request->scratch_bank_reg_count + 4U & 0x1f));
    }
  }
  else {
    g_used_gpr_mask = g_used_gpr_mask | 0x7f00;
    g_mac_regs_used = g_mac_regs_used | 3;
    g_saved_sys_mask = g_saved_sys_mask | 3;
    g_used_fpr_mask =
         g_used_fpr_mask |
         (1 << (0xcU - g_request->scratch_bank_reg_count & 0x1f)) + -1 <<
         (g_request->scratch_bank_reg_count + 4U & 0x1f);
  }
  g_used_gpr_mask = g_used_gpr_mask & (~(ushort)g_request->reg_mask_150 | 0x80ff);
  g_used_fpr_mask =
       g_used_fpr_mask &
       ~((1 << (0xcU - g_request->scratch_bank_reg_count & 0x1f)) + -1 <<
         (g_request->scratch_bank_reg_count + 4U & 0x1f) & (ushort)(g_request->reg_mask_150 >> 0x10)
        );
  uVar1 = (uint)(short)(node->symx + 0xb6);
  uVar2 = (int)uVar1 >> 0x1f;
  if (((g_symbol_table[(uVar1 ^ uVar2) - uVar2].sym_flags & 0x10) == 0) &&
     (g_request->macsave == '\0')) {
    g_mac_regs_used = g_mac_regs_used & 0xfc;
  }
  uVar1 = (uint)(short)(node->symx + 0xb6);
  uVar2 = (int)uVar1 >> 0x1f;
  if ((g_symbol_table[(uVar1 ^ uVar2) - uVar2].sym_flags & 0x10) == 0) {
    g_saved_sys_mask = '\0';
  }
  if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
    fpu_mode = 1;
  }
  else {
    fpu_mode = -(g_request->cpu == 4) & 2;
  }
  if (fpu_mode == 0) {
    g_used_fpr_mask = 0;
    g_saved_sys_mask = '\0';
  }
  *g_current_aux_record = uVar3;
  *(ushort *)(g_current_aux_record + 1) = g_used_gpr_mask;
  *(ushort *)((int)g_current_aux_record + 6) = g_used_fpr_mask;
  *(uchar *)((int)g_current_aux_record + 0x17) = g_mac_regs_used;
  *(uchar *)(g_current_aux_record + 2) = g_saved_sys_mask;
  g_current_aux_record[3] = g_max_sptravel + g_max_temp_frame + g_local_frame_size;
  uVar3 = 0;
  do {
    uVar1 = uVar3 + 1;
    (&g_used_routine_bits)[uVar3] =
         (&g_used_routine_bits)[uVar3] | *(byte *)((int)g_current_aux_record + uVar3 + 0x2c);
    uVar3 = uVar1;
  } while (uVar1 < 0x17);
  if (((int)*g_current_aux_record < 0) || ((int)g_current_aux_record[3] < 0)) {
    report_codegen_message(0xc84,node->filn,(uint)node->line,(int)node->listno,(char *)0x0);
  }
  g_current_aux_record[8] = g_stmt_serial;
  fill_psd_record((psd *)&g_psd_scratch,OP_EXIT,'\x02','\0',g_stmt_serial,g_msg_filn,g_msg_line,
                  (ea *)0x0,(ea *)0x0,0,'\0');
  emit_psd_record((psd *)&g_psd_scratch,0);
  if (g_exit_record_dropped != '\0') {
    *(undefined2 *)(g_current_aux_record + 1) = 0;
    *(undefined2 *)((int)g_current_aux_record + 6) = 0;
    *(undefined1 *)((int)g_current_aux_record + 0x17) = 0;
    *(undefined1 *)(g_current_aux_record + 2) = 0;
    *(ushort *)((int)g_current_aux_record + 10) =
         *(ushort *)((int)g_current_aux_record + 10) | 0x8000;
  }
  return;
}



