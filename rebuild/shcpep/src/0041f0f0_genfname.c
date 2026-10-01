#include "decls.h"
#include "imports.h"

// entry: 0041f0f0
// name : genfname
// size : 115
// sig  : int genfname(byte * fname)


/* Library Function - Single Match
    _genfname
   
   Library: Visual Studio 1998 Release */

int __cdecl genfname(byte *fname)

{
  unsigned char _frec_4[4];
#define local_4 (*(char (*)[4])(_frec_4 + 0))
  char cVar1;
  char *pcVar2;
  ulong uVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  
  pcVar2 = stock_mbsrchr(fname,0x2e);
  uVar3 = _strtoul(pcVar2 + 1,(char **)0x0,0x20);
  if (0x7ffe < uVar3 + 1) {
    return -1;
  }
  pcVar4 = __ultoa(uVar3 + 1,local_4,0x20);
  uVar5 = 0xffffffff;
  do {
    pcVar7 = pcVar4;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar7 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar7;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar4 = pcVar7 + -uVar5;
  pcVar2 = pcVar2 + 1;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar2 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar2 = pcVar2 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar2 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar2 = pcVar2 + 1;
  }
  return 0;
#undef local_4
}



