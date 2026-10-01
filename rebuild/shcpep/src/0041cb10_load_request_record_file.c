#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x6e34))
#undef g_request_being_loaded
#define g_request_being_loaded (*(request * *)(g_sd + 0x5368))
#undef g_request_record_path
#define g_request_record_path (*(char * *)(g_sd + 0x6e2c))


// entry: 0041cb10
// name : load_request_record_file
// size : 404
// sig  : request * load_request_record_file(short stage, char * path)


request * __cdecl load_request_record_file(short stage,char *path)

{
  unsigned char _frec_2[2];
#define fixed_size (*(short *)(_frec_2 + 0))
  FILE *in;
  uint uVar1;
  int close_result;
  uint n_words;
  char *src;
  char *dst;
  char ch;
  
  in = open_shared_file(path,&s_open_mode_rb);
  if (in == (FILE *)0x0) {
    report_message_by_code((char *)0x0,0,0xce4,(char *)0x0);
    stock_exit(9);
  }
  uVar1 = read_file_bytes(in,(char *)&fixed_size,2);
  check_request_read_result(uVar1);
  g_request_fixed_size = fixed_size;
  g_request_being_loaded = stock_malloc((int)fixed_size);
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
  uVar1 = 0xffffffff;
  src = path;
  do {
    if (uVar1 == 0) break;
    uVar1 = uVar1 - 1;
    ch = *src;
    src = src + 1;
  } while (ch != '\0');
  g_request_record_path = stock_malloc(~uVar1);
  uVar1 = 0xffffffff;
  do {
    src = path;
    if (uVar1 == 0) break;
    uVar1 = uVar1 - 1;
    src = path + 1;
    ch = *path;
    path = src;
  } while (ch != '\0');
  uVar1 = ~uVar1;
  src = src + -uVar1;
  dst = g_request_record_path;
  for (n_words = uVar1 >> 2; n_words != 0; n_words = n_words - 1) {
    *(undefined4 *)dst = *(undefined4 *)src;
    src = src + 4;
    dst = dst + 4;
  }
  for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *dst = *src;
    src = src + 1;
    dst = dst + 1;
  }
  return g_request_being_loaded;
#undef fixed_size
}



