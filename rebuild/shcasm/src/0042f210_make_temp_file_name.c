#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_temp_name_buffer
#define g_temp_name_buffer (*(char * *)(g_sd + 0x741c))
#undef g_tmp_env_name
#define g_tmp_env_name (*(char * *)(g_sd + 0x13308))


// entry: 0042f210
// name : make_temp_file_name
// size : 285
// sig  : char * make_temp_file_name(void)


char * __cdecl make_temp_file_name(void)

{
  unsigned char _frec_4[4];
#define local_4 (*(int *)(_frec_4 + 0))
  char cVar1;
  char *tmp_dir;
  DWORD pid;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  
  tmp_dir = get_env_directory(g_tmp_env_name,&local_4);
  if (tmp_dir == (char *)0x0) {
    if (local_4 == 0) {
      report_message_by_code((char *)0x0,0,0xcf9,(char *)0x0);
      stock_exit(9);
    }
    else {
      tmp_dir = &s_empty_string;
    }
  }
  if (g_process_id == 0) {
    pid = GetCurrentProcessId();
    g_process_id = (pid ^ (int)pid >> 0x1f) - ((int)pid >> 0x1f);
    for (iVar2 = g_process_id; iVar2 != 0; iVar2 = iVar2 / 10) {
      g_pid_digit_count = g_pid_digit_count + 1;
    }
  }
  uVar4 = 0xffffffff;
  pcVar3 = tmp_dir;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  iVar2 = 0;
  if (~uVar4 != 1) {
    iVar2 = ~uVar4 - 2;
  }
  pcVar3 = _tmpnam((char *)0x0);
  if (pcVar3 != (char *)0x0) {
    uVar4 = 0xffffffff;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    g_temp_name_buffer = stock_malloc(g_pid_digit_count + ~uVar4 + iVar2);
    if (g_temp_name_buffer != (char *)0x0) goto LAB_0042f2f9;
  }
  report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
  stock_exit(9);
LAB_0042f2f9:
  iVar2 = g_temp_name_counter;
  g_temp_name_counter = g_temp_name_counter + 1;
  _sprintf(g_temp_name_buffer,s__s_d__d_00442438,tmp_dir,g_process_id,iVar2);
  return g_temp_name_buffer;
#undef local_4
}



