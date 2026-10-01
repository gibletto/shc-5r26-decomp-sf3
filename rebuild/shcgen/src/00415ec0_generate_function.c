#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x1f9b8))
#undef g_ilb_file
#define g_ilb_file (*(FILE * *)(g_sd + 0x1f980))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00415ec0
// name : generate_function
// size : 558
// sig  : void generate_function(gen_node * func)


int __cdecl generate_function(gen_node *func)

{
  uint uVar1;
  gen_node *next_node;
  uint uVar2;
  
  g_msg_filn = func->filn;
  g_msg_line = func->line;
  uVar1 = (int)func->symx + 0xb6;
  uVar2 = (int)uVar1 >> 0x1f;
  g_current_aux_record = g_symbol_table[(uVar1 ^ uVar2) - uVar2].func_index * 0x44 + g_aux_records;
  uVar1 = (int)func->symx + 0xb6;
  uVar2 = (int)uVar1 >> 0x1f;
  if (g_current_section->id != g_symbol_table[(uVar1 ^ uVar2) - uVar2].short_06) {
    g_current_section =
         find_section_record(g_request,g_symbol_table[(uVar1 ^ uVar2) - uVar2].short_06);
    uVar1 = (int)func->symx + 0xb6;
    uVar2 = (int)uVar1 >> 0x1f;
    fill_section_record((psd *)&g_psd_scratch,OP_PROGRAM,
                        g_symbol_table[(uVar1 ^ uVar2) - uVar2].short_06);
    emit_psd_record((psd *)&g_psd_scratch,0);
    g_avoid_reg_mask = 0;
  }
  fill_line_record((psd *)&g_psd_scratch,OP_LINE,func->filn,func->line,'\0');
  emit_psd_record((psd *)&g_psd_scratch,0);
  if (*(short *)g_request->unknown_004 == 0) {
    fill_psd_record((psd *)&g_psd_scratch,OP_BBGN,'\x02','\0',g_stmt_serial,g_msg_filn,g_msg_line,
                    (ea *)0x0,(ea *)0x0,0,'\0');
    emit_psd_record((psd *)&g_psd_scratch,0);
  }
  next_node = read_ilb_node(g_ilb_file);
  if (next_node == (gen_node *)0x0) {
    report_codegen_message(0xce6,func->filn,(uint)func->line,(int)func->listno,(char *)0x0);
  }
  assign_function_storage(func);
  if (*(short *)(g_request->unknown_004 + 0x12) != 0) {
    write_db2_function_locations(func);
  }
  begin_function_code(func);
  generate_statement(func->child);
  unlink_and_free_subtree(func->child);
  end_function_code(func);
  if (*(short *)(g_request->unknown_004 + 0x12) != 0) {
    write_db2_lreg_table();
  }
  if (*(short *)g_request->unknown_004 == 0) {
    fill_psd_record((psd *)&g_psd_scratch,OP_BEND,'\x02','\0',g_stmt_serial,g_msg_filn,g_msg_line,
                    (ea *)0x0,(ea *)0x0,0,'\0');
    emit_psd_record((psd *)&g_psd_scratch,0);
  }
  return;
}



