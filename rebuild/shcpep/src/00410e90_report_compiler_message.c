#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x6e34))


// entry: 00410e90
// name : report_compiler_message
// size : 126
// sig  : void report_compiler_message(short filno, uint linno, short msgno, char * text)


int __cdecl report_compiler_message(short filno,uint linno,short msgno,char *text)

{
  request_source_file *src_file;
  char *file_name;
  
  file_name = (char *)0x0;
  if ((g_loaded_request != (request *)0x0) &&
     (src_file = g_loaded_request->source_files, src_file != (request_source_file *)0x0)) {
    do {
      if (src_file->filno == filno) break;
      src_file = src_file->next;
    } while (src_file != (request_source_file *)0x0);
    if (src_file != (request_source_file *)0x0) {
      file_name = src_file->name;
    }
  }
  report_message_by_code(file_name,linno & 0xffff,(int)msgno,text);
  if (2999 < msgno) {
    close_and_delete_temp_files();
    if (3999 < msgno) {
      stock_exit(0xb);
      return;
    }
    stock_exit(9);
  }
  return;
}



