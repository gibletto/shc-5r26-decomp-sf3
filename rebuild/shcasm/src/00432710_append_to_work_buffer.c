#include "decls.h"
#include "imports.h"

// entry: 00432710
// name : append_to_work_buffer
// size : 240
// sig  : int append_to_work_buffer(char * text, int buffer)


int __cdecl append_to_work_buffer(char *text,int buffer)

{
  char *pcVar1;
  uint uVar2;
  uint words;
  int iVar3;
  undefined4 *buf;
  char *pcVar4;
  char *pcVar5;
  char ch;
  int old_capacity;
  int text_len;
  
  if (buffer == 1) {
    buf = &g_work_buffer_a;
  }
  else {
    buf = &g_work_buffer_b;
    if (buffer != 2) {
      buf = &g_work_buffer_c;
    }
  }
  uVar2 = 0xffffffff;
  pcVar1 = text;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    ch = *pcVar1;
    pcVar1 = pcVar1 + 1;
  } while (ch != '\0');
  iVar3 = 0;
  text_len = ~uVar2 - 1;
  if ((int)buf[1] < buf[2] + text_len + 1) {
    do {
      old_capacity = buf[1];
      iVar3 = iVar3 + 1;
      buf[1] = old_capacity * 2;
    } while (old_capacity * 2 < buf[2] + text_len + 1);
  }
  if (iVar3 != 0) {
    pcVar1 = stock_malloc(buf[1]);
    if (pcVar1 == (char *)0x0) {
      return -1;
    }
    uVar2 = 0xffffffff;
    pcVar4 = (char *)*buf;
    do {
      pcVar5 = pcVar4;
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar5 = pcVar4 + 1;
      ch = *pcVar4;
      pcVar4 = pcVar5;
    } while (ch != '\0');
    uVar2 = ~uVar2;
    pcVar4 = pcVar5 + -uVar2;
    pcVar5 = pcVar1;
    for (words = uVar2 >> 2; words != 0; words = words - 1) {
      *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      pcVar5 = pcVar5 + 4;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *pcVar5 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      pcVar5 = pcVar5 + 1;
    }
    stock_free((void *)*buf);
    *buf = pcVar1;
  }
  uVar2 = 0xffffffff;
  do {
    pcVar1 = text;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar1 = text + 1;
    ch = *text;
    text = pcVar1;
  } while (ch != '\0');
  uVar2 = ~uVar2;
  iVar3 = -1;
  pcVar4 = (char *)*buf;
  do {
    pcVar5 = pcVar4;
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar5 = pcVar4 + 1;
    ch = *pcVar4;
    pcVar4 = pcVar5;
  } while (ch != '\0');
  pcVar1 = pcVar1 + -uVar2;
  pcVar4 = pcVar5 + -1;
  for (words = uVar2 >> 2; words != 0; words = words - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar1;
    pcVar1 = pcVar1 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar4 = *pcVar1;
    pcVar1 = pcVar1 + 1;
    pcVar4 = pcVar4 + 1;
  }
  buf[2] = buf[2] + text_len;
  return 1;
}



