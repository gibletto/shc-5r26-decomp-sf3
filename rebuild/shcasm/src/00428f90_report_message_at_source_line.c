#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x13320))


// entry: 00428f90
// name : report_message_at_source_line
// size : 204
// sig  : void __cdecl report_message_at_source_line(short filno,uint linno,short msg_code,char *text)


int __cdecl report_message_at_source_line(short filno,uint linno,short msg_code,char *text)

{
  request_source_file *src_file;
  char *file_name;
  
  file_name = (char *)0x0;
  if (g_loaded_request != (request *)0x0) {
    for (src_file = g_loaded_request->source_files;
        (src_file != (request_source_file *)0x0 && (src_file->filno != filno));
        src_file = src_file->next) {
    }
    if (src_file != (request_source_file *)0x0) {
      file_name = src_file->name;
    }
  }
  report_message_by_code(file_name,linno & 0xffff,(int)msg_code,text);
  if (2999 < msg_code) {
    close_and_delete_temp_files();
    if (msg_code < 4000) {
      stock_exit(9);
    }
    else {
      stock_exit(0xb);
    }
  }
  return;
}
