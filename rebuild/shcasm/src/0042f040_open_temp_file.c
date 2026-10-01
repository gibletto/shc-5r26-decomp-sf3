#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_temp_path_in_progress
#define g_temp_path_in_progress (*(char * *)(g_sd + 0x96ac))


// entry: 0042f040
// name : open_temp_file
// size : 296
// sig  : FILE * open_temp_file(void)


FILE * open_temp_file(void)

{
  char cVar1;
  char *pcVar2;
  FILE *fp;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  
  if (7 < g_temp_file_count) {
    return (FILE *)0x0;
  }
  pcVar2 = make_temp_file_name();
  uVar3 = 0xffffffff;
  pcVar6 = pcVar2;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  g_temp_path_in_progress = stock_malloc(~uVar3 + 4);
  if (g_temp_path_in_progress == (char *)0x0) {
    report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
    stock_exit(9);
  }
  uVar3 = 0xffffffff;
  pcVar6 = pcVar2;
  do {
    pcVar8 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar8;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar6 = pcVar8 + -uVar3;
  pcVar8 = g_temp_path_in_progress;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
  stock_free(pcVar2);
  pcVar6 = g_temp_path_in_progress;
  uVar3 = 0xffffffff;
  pcVar2 = (char *)&s_tmp_suffix;
  do {
    pcVar8 = pcVar2;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar8;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar5 = -1;
  pcVar2 = g_temp_path_in_progress;
  do {
    pcVar7 = pcVar2;
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar7 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar7;
  } while (cVar1 != '\0');
  pcVar2 = pcVar8 + -uVar3;
  pcVar8 = pcVar7 + -1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar8 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    pcVar8 = pcVar8 + 1;
  }
  fp = stock_fopen(pcVar6,&s_wb_plus);
  if (fp == (FILE *)0x0) {
    report_message_by_code((char *)0x0,0,0xce4,(char *)0x0);
    stock_exit(9);
  }
  pcVar6 = g_temp_path_in_progress;
  g_temp_path_in_progress = (char *)0x0;
  g_temp_files[g_temp_file_count].path = pcVar6;
  g_temp_files[g_temp_file_count].file = fp;
  g_temp_file_count = g_temp_file_count + 1;
  return fp;
}



