#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x13320))


// entry: 004348a0
// name : format_listing_page_header
// size : 821
// sig  : short format_listing_page_header(char * line, short page_no)


/* WARNING: Removing unreachable block (ram,0x00434aa4) */

short __cdecl format_listing_page_header(char *line,short page_no)

{
  short title_width;
  uint uVar1;
  uint uVar2;
  int scan_count;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char ch;
  
  if (page_no < 0) {
    report_message_by_code((char *)0x0,0,0x1309,(char *)0x0);
    stock_exit(0xb);
  }
  pcVar4 = PTR_s_SH_SERIES_C_Compiler__Ver__5_0_R_00443028;
  if ((g_loaded_request != (request *)0x0) &&
     (g_loaded_request->cpp_block != (request_cpp_block *)0x0)) {
    pcVar4 = PTR_s_SH_SERIES_C___Compiler__Ver__5_0_00443058;
  }
  uVar1 = 0xffffffff;
  do {
    pcVar6 = pcVar4;
    if (uVar1 == 0) break;
    uVar1 = uVar1 - 1;
    pcVar6 = pcVar4 + 1;
    ch = *pcVar4;
    pcVar4 = pcVar6;
  } while (ch != '\0');
  uVar1 = ~uVar1;
  pcVar4 = pcVar6 + -uVar1;
  pcVar6 = line;
  for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *pcVar6 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar6 = pcVar6 + 1;
  }
  if (line == (char *)0x0) {
    report_message_by_code((char *)0x0,0,0x1309,(char *)0x0);
    stock_exit(0xb);
  }
  if (g_loaded_request->list_width == 0) {
    title_width = 0x61;
  }
  else {
    title_width = (short)g_loaded_request->list_width + -0x1f;
  }
  iVar3 = 0;
  ch = *line;
  while (ch != '\0') {
    iVar3 = iVar3 + 1;
    ch = line[iVar3];
  }
  if (iVar3 <= (short)(title_width + -1)) {
    uVar2 = ((short)(title_width + -1) - iVar3) + 1;
    uVar1 = uVar2 >> 2;
    pcVar4 = line + iVar3;
    while (uVar1 != 0) {
      uVar1 = uVar1 - 1;
      builtin_strncpy(pcVar4,"    ",4);
      pcVar4 = pcVar4 + 4;
    }
    for (uVar1 = uVar2 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
      *pcVar4 = ' ';
      pcVar4 = pcVar4 + 1;
    }
    iVar3 = iVar3 + uVar2;
  }
  line[iVar3] = '\0';
  uVar1 = 0xffffffff;
  pcVar4 = g_loaded_request->compile_date;
  do {
    pcVar6 = pcVar4;
    if (uVar1 == 0) break;
    uVar1 = uVar1 - 1;
    pcVar6 = pcVar4 + 1;
    ch = *pcVar4;
    pcVar4 = pcVar6;
  } while (ch != '\0');
  uVar1 = ~uVar1;
  iVar3 = -1;
  pcVar4 = line;
  do {
    pcVar5 = pcVar4;
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar5 = pcVar4 + 1;
    ch = *pcVar4;
    pcVar4 = pcVar5;
  } while (ch != '\0');
  pcVar4 = pcVar6 + -uVar1;
  pcVar6 = pcVar5 + -1;
  for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *pcVar6 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar6 = pcVar6 + 1;
  }
  if (line == (char *)0x0) {
    report_message_by_code((char *)0x0,0,0x1309,(char *)0x0);
    stock_exit(0xb);
  }
  uVar1 = 0xffffffff;
  pcVar4 = &s_sp_sp_00443140;
  do {
    pcVar6 = pcVar4;
    if (uVar1 == 0) break;
    uVar1 = uVar1 - 1;
    pcVar6 = pcVar4 + 1;
    ch = *pcVar4;
    pcVar4 = pcVar6;
  } while (ch != '\0');
  uVar1 = ~uVar1;
  iVar3 = -1;
  pcVar4 = line;
  do {
    pcVar5 = pcVar4;
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar5 = pcVar4 + 1;
    ch = *pcVar4;
    pcVar4 = pcVar5;
  } while (ch != '\0');
  pcVar4 = pcVar6 + -uVar1;
  pcVar6 = pcVar5 + -1;
  for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *pcVar6 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar6 = pcVar6 + 1;
  }
  if (line == (char *)0x0) {
    report_message_by_code((char *)0x0,0,0x1309,(char *)0x0);
    stock_exit(0xb);
  }
  title_width = format_decimal((int)page_no);
  if (title_width == -1) {
    report_message_by_code((char *)0x0,0,0x1309,(char *)0x0);
    stock_exit(0xb);
  }
  iVar3 = 4 - title_width;
  if (0 < iVar3) {
    do {
      uVar1 = 0xffffffff;
      pcVar4 = &s_sp_00443118;
      do {
        pcVar6 = pcVar4;
        if (uVar1 == 0) break;
        uVar1 = uVar1 - 1;
        pcVar6 = pcVar4 + 1;
        ch = *pcVar4;
        pcVar4 = pcVar6;
      } while (ch != '\0');
      uVar1 = ~uVar1;
      scan_count = -1;
      pcVar4 = g_page_label_text;
      do {
        pcVar5 = pcVar4;
        if (scan_count == 0) break;
        scan_count = scan_count + -1;
        pcVar5 = pcVar4 + 1;
        ch = *pcVar4;
        pcVar4 = pcVar5;
      } while (ch != '\0');
      pcVar4 = pcVar6 + -uVar1;
      pcVar6 = pcVar5 + -1;
      for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar6 = pcVar6 + 4;
      }
      for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
        *pcVar6 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar6 = pcVar6 + 1;
      }
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  uVar1 = 0xffffffff;
  pcVar4 = g_page_label_text;
  do {
    pcVar6 = pcVar4;
    if (uVar1 == 0) break;
    uVar1 = uVar1 - 1;
    pcVar6 = pcVar4 + 1;
    ch = *pcVar4;
    pcVar4 = pcVar6;
  } while (ch != '\0');
  uVar1 = ~uVar1;
  iVar3 = -1;
  pcVar4 = line;
  do {
    pcVar5 = pcVar4;
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar5 = pcVar4 + 1;
    ch = *pcVar4;
    pcVar4 = pcVar5;
  } while (ch != '\0');
  pcVar4 = pcVar6 + -uVar1;
  pcVar6 = pcVar5 + -1;
  for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *pcVar6 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar6 = pcVar6 + 1;
  }
  if (line == (char *)0x0) {
    report_message_by_code((char *)0x0,0,0x1309,(char *)0x0);
    stock_exit(0xb);
  }
  uVar1 = 0xffffffff;
  pcVar4 = &g_decimal_text;
  do {
    pcVar6 = pcVar4;
    if (uVar1 == 0) break;
    uVar1 = uVar1 - 1;
    pcVar6 = pcVar4 + 1;
    ch = *pcVar4;
    pcVar4 = pcVar6;
  } while (ch != '\0');
  uVar1 = ~uVar1;
  iVar3 = -1;
  pcVar4 = line;
  do {
    pcVar5 = pcVar4;
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar5 = pcVar4 + 1;
    ch = *pcVar4;
    pcVar4 = pcVar5;
  } while (ch != '\0');
  pcVar4 = pcVar6 + -uVar1;
  pcVar6 = pcVar5 + -1;
  for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *pcVar6 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar6 = pcVar6 + 1;
  }
  if (line == (char *)0x0) {
    report_message_by_code((char *)0x0,0,0x1309,(char *)0x0);
    stock_exit(0xb);
  }
  uVar1 = 0xffffffff;
  pcVar4 = &s_nl_0044313c;
  do {
    pcVar6 = pcVar4;
    if (uVar1 == 0) break;
    uVar1 = uVar1 - 1;
    pcVar6 = pcVar4 + 1;
    ch = *pcVar4;
    pcVar4 = pcVar6;
  } while (ch != '\0');
  uVar1 = ~uVar1;
  iVar3 = -1;
  pcVar4 = line;
  do {
    pcVar5 = pcVar4;
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar5 = pcVar4 + 1;
    ch = *pcVar4;
    pcVar4 = pcVar5;
  } while (ch != '\0');
  pcVar4 = pcVar6 + -uVar1;
  pcVar6 = pcVar5 + -1;
  for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *pcVar6 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar6 = pcVar6 + 1;
  }
  if (line == (char *)0x0) {
    report_message_by_code((char *)0x0,0,0x1309,(char *)0x0);
    stock_exit(0xb);
  }
  iVar3 = -1;
  g_page_label_text[5] = '\0';
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    ch = *line;
    line = line + 1;
  } while (ch != '\0');
  return ~(ushort)iVar3 - 2;
}



