#include "decls.h"
#include "imports.h"

// entry: 00435bc0
// name : init_namebuf
// size : 131
// sig  : undefined4 __cdecl init_namebuf(int param_1)


/* Library Function - Single Match
    _init_namebuf
   
   Library: Visual Studio 1998 Release */

undefined4 __cdecl init_namebuf(int param_1)

{
  char *pcVar1;
  DWORD pid;
  uint len;
  uint n;
  char *namebuf;
  char *pcVar2;
  int iVar3;
  char ch;
  
  namebuf = &stock_namebuf0;
  if (param_1 != 0) {
    namebuf = &stock_namebuf1;
  }
  *(undefined2 *)namebuf = DAT_00443234;
  pcVar1 = namebuf + 1;
  if ((*namebuf != '\\') && (*namebuf != '/')) {
    *pcVar1 = '\\';
    pcVar1 = namebuf + 2;
  }
  if (param_1 == 0) {
    *pcVar1 = 's';
  }
  else {
    *pcVar1 = 't';
  }
  pcVar1 = pcVar1 + 1;
  iVar3 = 0x20;
  pid = GetCurrentProcessId();
  __ultoa(pid,pcVar1,iVar3);
  len = 0xffffffff;
  pcVar1 = (char *)&DAT_00443230;
  do {
    pcVar2 = pcVar1;
    if (len == 0) break;
    len = len - 1;
    pcVar2 = pcVar1 + 1;
    ch = *pcVar1;
    pcVar1 = pcVar2;
  } while (ch != '\0');
  len = ~len;
  iVar3 = -1;
  do {
    pcVar1 = namebuf;
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar1 = namebuf + 1;
    ch = *namebuf;
    namebuf = pcVar1;
  } while (ch != '\0');
  namebuf = pcVar2 + -len;
  pcVar1 = pcVar1 + -1;
  for (n = len >> 2; n != 0; n = n - 1) {
    *(undefined4 *)pcVar1 = *(undefined4 *)namebuf;
    namebuf = namebuf + 4;
    pcVar1 = pcVar1 + 4;
  }
  for (len = len & 3; len != 0; len = len - 1) {
    *pcVar1 = *namebuf;
    namebuf = namebuf + 1;
    pcVar1 = pcVar1 + 1;
  }
  return 0;
}
