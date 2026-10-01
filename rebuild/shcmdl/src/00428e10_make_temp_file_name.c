#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_env_tmp_name
#define g_env_tmp_name (*(char * *)(g_sd + 0x27318))
#undef g_temp_name_buffer
#define g_temp_name_buffer (*(char * *)(g_sd + 0x403c))


// entry: 00428e10
// name : make_temp_file_name
// size : 285
// sig  : char * make_temp_file_name(void)


char * __cdecl make_temp_file_name(void)

{
  unsigned char _frec_4[4];
#define ok (*(int *)(_frec_4 + 0))
  char *dir;
  DWORD pid;
  int iVar1;
  char *p;
  uint len;
  char ch;
  
  dir = get_env_directory(g_env_tmp_name,&ok);
  if (dir == (char *)0x0) {
    if (ok == 0) {
      write_error_record((char *)0x0,0,0xcf9,(char *)0x0);
      stock_exit(9);
    }
    else {
      dir = &g_str_empty;
    }
  }
  if (g_temp_pid == 0) {
    pid = GetCurrentProcessId();
    g_temp_pid = (pid ^ (int)pid >> 0x1f) - ((int)pid >> 0x1f);
    for (iVar1 = g_temp_pid; iVar1 != 0; iVar1 = iVar1 / 10) {
      g_pid_digit_count = g_pid_digit_count + 1;
    }
  }
  len = 0xffffffff;
  p = dir;
  do {
    if (len == 0) break;
    len = len - 1;
    ch = *p;
    p = p + 1;
  } while (ch != '\0');
  iVar1 = 0;
  if (~len != 1) {
    iVar1 = ~len - 2;
  }
  p = _tmpnam((char *)0x0);
  if (p != (char *)0x0) {
    len = 0xffffffff;
    do {
      if (len == 0) break;
      len = len - 1;
      ch = *p;
      p = p + 1;
    } while (ch != '\0');
    g_temp_name_buffer = stock_malloc(g_pid_digit_count + ~len + iVar1);
    if (g_temp_name_buffer != (char *)0x0) goto LAB_00428ef9;
  }
  write_error_record((char *)0x0,0,0xbcd,(char *)0x0);
  stock_exit(9);
LAB_00428ef9:
  iVar1 = g_temp_counter;
  g_temp_counter = g_temp_counter + 1;
  _sprintf(g_temp_name_buffer,s__s_d__d_00436058,dir,g_temp_pid,iVar1);
  return g_temp_name_buffer;
#undef ok
}



