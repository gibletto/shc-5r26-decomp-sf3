#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0040ef41
// name : store_request_record_updates
// size : 186
// sig  : void __cdecl store_request_record_updates(char *request_path)


int __cdecl store_request_record_updates(char *request_path)

{
  uint uVar1;
  request_section *cur_section;
  request_section *next_section;
  
  g_current_request->label_count = (int)g_new_symbol_count;
  cur_section = g_current_request->sections;
  while (cur_section != (request_section *)0x0) {
    next_section = cur_section->next;
    pool_free(cur_section->layout,0x30);
    cur_section->layout = (section_layout *)0x0;
    cur_section = next_section;
  }
  g_current_request->extern_ref_count = (int)g_import_symbol_count;
  g_current_request->extern_def_count = (int)g_export_symbol_count;
  uVar1 = store_request_record_file(4,request_path);
  if ((short)uVar1 == -1) {
    report_message_at_source_line(0,0,0x1325,(char *)0x0);
  }
  return;
}
