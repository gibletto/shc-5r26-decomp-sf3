#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0042b270
// name : report_codegen_message
// size : 256
// sig  : void report_codegen_message(int msgno, short filno, uint linno, int listno, char * text)


int __cdecl report_codegen_message(int msgno,short filno,uint linno,int listno,char *text)

{
  char *file_name;
  bool found;
  request_source_file *src_file;
  
  found = false;
  file_name = g_request->source_name;
  src_file = g_request->source_files;
  while ((src_file != (request_source_file *)0x0 && (!found))) {
    found = src_file->filno == filno;
    if (found) {
      file_name = src_file->name;
    }
    src_file = src_file->next;
  }
  report_message_by_code(file_name,linno & 0xffff,msgno,text);
  if (2999 < msgno) {
    if (g_close_status == 0) {
      close_stage_files();
    }
    if ((2999 < msgno) && (msgno < 4000)) {
      stock_exit(9);
    }
  }
  if ((3999 < msgno) && (msgno < 5000)) {
    stock_exit(0xb);
  }
  if (((1999 < msgno) && (msgno < 3000)) && (g_message_severity < 4)) {
    g_message_severity = 3;
  }
  if (((999 < msgno) && (msgno < 2000)) && (g_message_severity < 3)) {
    g_message_severity = 2;
  }
  if (((0 < msgno) && (msgno < 1000)) && (g_message_severity < 2)) {
    g_message_severity = 1;
  }
  return;
}



