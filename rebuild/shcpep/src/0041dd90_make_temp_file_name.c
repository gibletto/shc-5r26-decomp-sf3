#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_temp_name_buffer
#define g_temp_name_buffer (*(char * *)(g_sd + 0x430c))
#undef g_tmp_env_name
#define g_tmp_env_name (*(char * *)(g_sd + 0x6e1c))


// entry: 0041dd90
// name : make_temp_file_name
// size : 285
// sig  : char * make_temp_file_name(void)


char * __cdecl make_temp_file_name(void)

{
  unsigned char _frec_4[4];
#define env_ok (*(int *)(_frec_4 + 0))
  char *dir;
  DWORD pid;
  int iVar1;
  char *tmp_name;
  uint remaining;
  char ch;
  
  dir = get_env_directory(g_tmp_env_name,&env_ok);
  if (dir == (char *)0x0) {
    if (env_ok == 0) {
      report_message_by_code((char *)0x0,0,0xcf9,(char *)0x0);
      stock_exit(9);
    }
    else {
      dir = s_empty_004281bc;
    }
  }
  if (g_process_id == 0) {
    pid = GetCurrentProcessId();
    g_process_id = (pid ^ (int)pid >> 0x1f) - ((int)pid >> 0x1f);
    for (iVar1 = g_process_id; iVar1 != 0; iVar1 = iVar1 / 10) {
      g_pid_digit_count = g_pid_digit_count + 1;
    }
  }
  remaining = 0xffffffff;
  tmp_name = dir;
  do {
    if (remaining == 0) break;
    remaining = remaining - 1;
    ch = *tmp_name;
    tmp_name = tmp_name + 1;
  } while (ch != '\0');
  iVar1 = 0;
  if (~remaining != 1) {
    iVar1 = ~remaining - 2;
  }
  tmp_name = _tmpnam((char *)0x0);
  if (tmp_name != (char *)0x0) {
    remaining = 0xffffffff;
    do {
      if (remaining == 0) break;
      remaining = remaining - 1;
      ch = *tmp_name;
      tmp_name = tmp_name + 1;
    } while (ch != '\0');
    g_temp_name_buffer = stock_malloc(g_pid_digit_count + ~remaining + iVar1);
    if (g_temp_name_buffer != (char *)0x0) goto LAB_0041de79;
  }
  report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
  stock_exit(9);
LAB_0041de79:
  iVar1 = g_temp_name_counter;
  g_temp_name_counter = g_temp_name_counter + 1;
  _sprintf(g_temp_name_buffer,s__s_d__d_00428328,dir,g_process_id,iVar1);
  return g_temp_name_buffer;
#undef env_ok
}



