#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sptravel
#define g_sptravel (*(short *)(g_sd + 0x1f944))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0040a3f0
// name : begin_function_code
// size : 387
// sig  : void begin_function_code(gen_node * node)


int __cdecl begin_function_code(gen_node *node)

{
  int unreserved;
  uint sym_index;
  uint uVar1;
  
  g_continue_label = 0;
  g_exit_record_dropped = '\0';
  g_break_label = 0;
  g_return_label = 0;
  unreserved = is_unreserved_function_name(node->symx + 0xb6);
  if ((short)unreserved == 0) {
    sym_index = (uint)(short)(node->symx + 0xb6);
    uVar1 = (int)sym_index >> 0x1f;
    report_codegen_message
              (0x7e4,node->filn,(uint)node->line,(int)node->listno,
               g_symbol_table[(sym_index ^ uVar1) - uVar1].name);
  }
  else {
    fill_label_record((psd *)&g_psd_scratch,OP_FLABEL,node->symx + 0xb6,(short)g_sptravel);
    emit_psd_record((psd *)&g_psd_scratch,0);
    sym_index = (int)node->symx + 0xb6;
    uVar1 = (int)sym_index >> 0x1f;
    if ((g_symbol_table[(sym_index ^ uVar1) - uVar1].sym_flags & 0x40) == 0) {
      fill_psd_record((psd *)&g_psd_scratch,OP_ENTER,'\x02','\0',g_stmt_serial,g_msg_filn,g_msg_line
                      ,(ea *)0x0,(ea *)0x0,0,'\0');
      emit_psd_record((psd *)&g_psd_scratch,0);
    }
    move_parameters_to_storage(node);
  }
  sym_index = (uint)(short)(node->symx + 0xb6);
  uVar1 = (int)sym_index >> 0x1f;
  if ((g_symbol_table[(sym_index ^ uVar1) - uVar1].sym_flags & 4) != 0) {
    *(ushort *)(g_current_aux_record + 10) = *(ushort *)(g_current_aux_record + 10) | 0x8000;
  }
  sym_index = (uint)(short)(node->symx + 0xb6);
  uVar1 = (int)sym_index >> 0x1f;
  if ((g_symbol_table[(sym_index ^ uVar1) - uVar1].sym_flags & 0x10) != 0) {
    *(byte *)(g_current_aux_record + 0xb) = *(byte *)(g_current_aux_record + 0xb) | 0x40;
  }
  g_current_function = node->symx + 0xb6;
  return;
}



