#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x13320))
#undef g_request_being_loaded
#define g_request_being_loaded (*(request * *)(g_sd + 0xc4b0))
#undef g_request_record_path
#define g_request_record_path (*(char * *)(g_sd + 0x13318))


// entry: 00432a10
// name : load_request_record_file
// size : 404
// sig  : request * load_request_record_file(short stage, char * path)


request * __cdecl load_request_record_file(short stage,char *path)

{
  unsigned char _frec_2[2];
#define record_size (*(short *)(_frec_2 + 0))
  FILE *in;
  uint len;
  int close_result;
  uint words;
  char *pcVar1;
  char *dst;
  char ch;
  
  in = stock_fopen(path,&s_rb_00442c5c);
  if (in == (FILE *)0x0) {
    report_message_by_code((char *)0x0,0,0xce4,(char *)0x0);
    stock_exit(9);
  }
  len = read_file_bytes(in,(char *)&record_size,2);
  check_request_read_result(len);
  g_request_record_size = record_size;
  g_request_being_loaded = stock_malloc((int)record_size);
  if (g_request_being_loaded == (request *)0x0) {
    report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
    stock_exit(9);
  }
  read_request_fixed_part(g_request_being_loaded,in);
  read_request_variable_part(g_request_being_loaded,in);
  select_env_variable_names((uint)(g_request_being_loaded->cpp_block != (request_cpp_block *)0x0));
  save_request_trailer_to_temp(in,stage);
  close_result = _fclose(in);
  if (close_result == -1) {
    report_message_by_code(g_request_being_loaded->source_name,0,0xce5,(char *)0x0);
    stock_exit(9);
  }
  g_loaded_request = g_request_being_loaded;
  g_request_being_loaded->stage = (int)stage;
  if (g_request_version_mismatch == 1) {
    report_message_by_code(g_request_being_loaded->source_name,0,0xceb,(char *)0x0);
    stock_exit(9);
  }
  len = 0xffffffff;
  pcVar1 = path;
  do {
    if (len == 0) break;
    len = len - 1;
    ch = *pcVar1;
    pcVar1 = pcVar1 + 1;
  } while (ch != '\0');
  g_request_record_path = stock_malloc(~len);
  len = 0xffffffff;
  do {
    pcVar1 = path;
    if (len == 0) break;
    len = len - 1;
    pcVar1 = path + 1;
    ch = *path;
    path = pcVar1;
  } while (ch != '\0');
  len = ~len;
  pcVar1 = pcVar1 + -len;
  dst = g_request_record_path;
  for (words = len >> 2; words != 0; words = words - 1) {
    *(undefined4 *)dst = *(undefined4 *)pcVar1;
    pcVar1 = pcVar1 + 4;
    dst = dst + 4;
  }
  for (len = len & 3; len != 0; len = len - 1) {
    *dst = *pcVar1;
    pcVar1 = pcVar1 + 1;
    dst = dst + 1;
  }
  return g_request_being_loaded;
#undef record_size
}



