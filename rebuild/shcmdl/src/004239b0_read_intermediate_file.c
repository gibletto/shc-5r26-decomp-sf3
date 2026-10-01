#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_int_file_path
#define g_int_file_path (*(char * *)(g_sd + 0x27328))
#undef g_option_record
#define g_option_record (*(option_record * *)(g_sd + 0xdc20))
#undef g_options_for_errors
#define g_options_for_errors (*(option_record * *)(g_sd + 0x27330))


// entry: 004239b0
// name : read_intermediate_file
// size : 404
// sig  : option_record * read_intermediate_file(short phase, char * path)


option_record * __cdecl read_intermediate_file(short phase,char *path)

{
  unsigned char _frec_2[2];
#define record_size (*(short *)(_frec_2 + 0))
  FILE *fp;
  uint len;
  int status;
  uint words;
  char *src;
  char *dest;
  char ch;
  
  fp = stock_fopen(path,&g_mode_rb);
  if (fp == (FILE *)0x0) {
    write_error_record((char *)0x0,0,0xce4,(char *)0x0);
    stock_exit(9);
  }
  len = read_bytes(fp,(char *)&record_size,2);
  check_read_result(len);
  g_option_record_size = record_size;
  g_option_record = stock_malloc((int)record_size);
  if (g_option_record == (option_record *)0x0) {
    write_error_record((char *)0x0,0,0xbcd,(char *)0x0);
    stock_exit(9);
  }
  read_option_record((char *)g_option_record,fp);
  read_option_strings_and_lists((int *)g_option_record,fp);
  select_env_var_names((uint)(g_option_record->use_shcpp_env != 0));
  save_input_tail(fp,phase);
  status = _fclose(fp);
  if (status == -1) {
    write_error_record(g_option_record->source_name,0,0xce5,(char *)0x0);
    stock_exit(9);
  }
  g_options_for_errors = g_option_record;
  g_option_record->phase = (int)phase;
  if (g_version_mismatch == 1) {
    write_error_record(g_option_record->source_name,0,0xceb,(char *)0x0);
    stock_exit(9);
  }
  len = 0xffffffff;
  src = path;
  do {
    if (len == 0) break;
    len = len - 1;
    ch = *src;
    src = src + 1;
  } while (ch != '\0');
  g_int_file_path = stock_malloc(~len);
  len = 0xffffffff;
  do {
    src = path;
    if (len == 0) break;
    len = len - 1;
    src = path + 1;
    ch = *path;
    path = src;
  } while (ch != '\0');
  len = ~len;
  src = src + -len;
  dest = g_int_file_path;
  for (words = len >> 2; words != 0; words = words - 1) {
    *(undefined4 *)dest = *(undefined4 *)src;
    src = src + 4;
    dest = dest + 4;
  }
  for (len = len & 3; len != 0; len = len - 1) {
    *dest = *src;
    src = src + 1;
    dest = dest + 1;
  }
  return g_option_record;
#undef record_size
}



