#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_temp_name_pending
#define g_temp_name_pending (*(char * *)(g_sd + 0xdd0c))


// entry: 00428c40
// name : open_temp_file
// size : 296
// sig  : FILE * open_temp_file(void)


FILE * open_temp_file(void)

{
  char *pcVar1;
  FILE *fp;
  uint len;
  uint words;
  int remaining;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char ch;
  
  if (7 < g_temp_file_count) {
    return (FILE *)0x0;
  }
  pcVar1 = make_temp_file_name();
  len = 0xffffffff;
  pcVar2 = pcVar1;
  do {
    if (len == 0) break;
    len = len - 1;
    ch = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (ch != '\0');
  g_temp_name_pending = stock_malloc(~len + 4);
  if (g_temp_name_pending == (char *)0x0) {
    write_error_record((char *)0x0,0,0xbcd,(char *)0x0);
    stock_exit(9);
  }
  len = 0xffffffff;
  pcVar2 = pcVar1;
  do {
    pcVar4 = pcVar2;
    if (len == 0) break;
    len = len - 1;
    pcVar4 = pcVar2 + 1;
    ch = *pcVar2;
    pcVar2 = pcVar4;
  } while (ch != '\0');
  len = ~len;
  pcVar2 = pcVar4 + -len;
  pcVar4 = g_temp_name_pending;
  for (words = len >> 2; words != 0; words = words - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (len = len & 3; len != 0; len = len - 1) {
    *pcVar4 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    pcVar4 = pcVar4 + 1;
  }
  stock_free(pcVar1);
  pcVar2 = g_temp_name_pending;
  len = 0xffffffff;
  pcVar1 = (char *)&g_str_dot_tmp;
  do {
    pcVar4 = pcVar1;
    if (len == 0) break;
    len = len - 1;
    pcVar4 = pcVar1 + 1;
    ch = *pcVar1;
    pcVar1 = pcVar4;
  } while (ch != '\0');
  len = ~len;
  remaining = -1;
  pcVar1 = g_temp_name_pending;
  do {
    pcVar3 = pcVar1;
    if (remaining == 0) break;
    remaining = remaining + -1;
    pcVar3 = pcVar1 + 1;
    ch = *pcVar1;
    pcVar1 = pcVar3;
  } while (ch != '\0');
  pcVar1 = pcVar4 + -len;
  pcVar4 = pcVar3 + -1;
  for (words = len >> 2; words != 0; words = words - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar1;
    pcVar1 = pcVar1 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (len = len & 3; len != 0; len = len - 1) {
    *pcVar4 = *pcVar1;
    pcVar1 = pcVar1 + 1;
    pcVar4 = pcVar4 + 1;
  }
  fp = stock_fopen(pcVar2,&g_str_mode_wbplus);
  if (fp == (FILE *)0x0) {
    write_error_record((char *)0x0,0,0xce4,(char *)0x0);
    stock_exit(9);
  }
  pcVar2 = g_temp_name_pending;
  g_temp_name_pending = (char *)0x0;
  (&g_temp_files)[g_temp_file_count * 2] = pcVar2;
  (&DAT_0043fcbc)[g_temp_file_count * 2] = fp;
  g_temp_file_count = g_temp_file_count + 1;
  return fp;
}



