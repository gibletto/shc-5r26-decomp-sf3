#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x10b2c))
#undef g_line_range_temp
#define g_line_range_temp (*(FILE * *)(g_sd + 0x128bc))
#undef g_register_map_temp
#define g_register_map_temp (*(FILE * *)(g_sd + 0x13020))
#undef g_register_variable_input
#define g_register_variable_input (*(FILE * *)(g_sd + 0x128c0))
#undef g_stack_offset_temp
#define g_stack_offset_temp (*(FILE * *)(g_sd + 0xcefc))


// entry: 0041e360
// name : init_debug_info_state
// size : 341
// sig  : void init_debug_info_state(void)


int __cdecl init_debug_info_state(void)

{
  debug_scope *scope;
  
  g_line_range_count = 0;
  g_scope_top = 0;
  scope = pool_alloc(0x10);
  g_scope_stack[g_scope_top] = scope;
  g_scope_top = g_scope_top + 1;
  scope = pool_alloc(0x10);
  g_scope_stack[g_scope_top] = scope;
  (&g_current_section)[g_scope_top]->size[1] = (int)g_scope_stack[g_scope_top];
  g_scope_stack[g_scope_top]->start = 0;
  if (g_current_request->optimize != 0) {
    g_register_variable_input = stock_fopen(g_current_request->reg_path,&s_rb_00441974);
    if (g_register_variable_input == (FILE *)0x0) {
      report_message_at_source_line(0,0,0xce4,(char *)0x0);
    }
  }
  g_line_range_temp = open_temp_file();
  if (g_line_range_temp == (FILE *)0x0) {
    report_message_at_source_line(0,0,0xce4,(char *)0x0);
  }
  g_stack_offset_temp = open_temp_file();
  if (g_stack_offset_temp == (FILE *)0x0) {
    report_message_at_source_line(0,0,0xce4,(char *)0x0);
  }
  g_register_map_temp = open_temp_file();
  if (g_register_map_temp == (FILE *)0x0) {
    report_message_at_source_line(0,0,0xce4,(char *)0x0);
  }
  return;
}
