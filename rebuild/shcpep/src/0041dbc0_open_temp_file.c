#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_temp_path_in_progress
#define g_temp_path_in_progress (*(char * *)(g_sd + 0x53cc))


// entry: 0041dbc0
// name : open_temp_file
// size : 296
// sig  : FILE * open_temp_file(void)


FILE * open_temp_file(void)

{
  char *pcVar1;
  FILE *fp;
  uint uVar2;
  uint n_words;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char ch;
  
  if (7 < g_temp_file_count) {
    return (FILE *)0x0;
  }
  pcVar1 = make_temp_file_name();
  uVar2 = 0xffffffff;
  pcVar4 = pcVar1;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    ch = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (ch != '\0');
  g_temp_path_in_progress = stock_malloc(~uVar2 + 4);
  if (g_temp_path_in_progress == (char *)0x0) {
    report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
    stock_exit(9);
  }
  uVar2 = 0xffffffff;
  pcVar4 = pcVar1;
  do {
    pcVar6 = pcVar4;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar6 = pcVar4 + 1;
    ch = *pcVar4;
    pcVar4 = pcVar6;
  } while (ch != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar6 + -uVar2;
  pcVar6 = g_temp_path_in_progress;
  for (n_words = uVar2 >> 2; n_words != 0; n_words = n_words - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar6 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar6 = pcVar6 + 1;
  }
  stock_free(pcVar1);
  pcVar4 = g_temp_path_in_progress;
  uVar2 = 0xffffffff;
  pcVar1 = s_dot_tmp_00428320;
  do {
    pcVar6 = pcVar1;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar6 = pcVar1 + 1;
    ch = *pcVar1;
    pcVar1 = pcVar6;
  } while (ch != '\0');
  uVar2 = ~uVar2;
  iVar3 = -1;
  pcVar1 = g_temp_path_in_progress;
  do {
    pcVar5 = pcVar1;
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar5 = pcVar1 + 1;
    ch = *pcVar1;
    pcVar1 = pcVar5;
  } while (ch != '\0');
  pcVar1 = pcVar6 + -uVar2;
  pcVar6 = pcVar5 + -1;
  for (n_words = uVar2 >> 2; n_words != 0; n_words = n_words - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar1;
    pcVar1 = pcVar1 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar6 = *pcVar1;
    pcVar1 = pcVar1 + 1;
    pcVar6 = pcVar6 + 1;
  }
  fp = open_shared_file(pcVar4,s_wb_plus_0042831c);
  if (fp == (FILE *)0x0) {
    report_message_by_code((char *)0x0,0,0xce4,(char *)0x0);
    stock_exit(9);
  }
  pcVar4 = g_temp_path_in_progress;
  g_temp_path_in_progress = (char *)0x0;
  g_temp_files[g_temp_file_count].path = pcVar4;
  g_temp_files[g_temp_file_count].file = fp;
  g_temp_file_count = g_temp_file_count + 1;
  return fp;
}



