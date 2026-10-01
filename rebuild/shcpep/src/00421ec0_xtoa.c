#include "decls.h"
#include "imports.h"

// entry: 00421ec0
// name : xtoa
// size : 96
// sig  : void xtoa(uint val, char * buf, uint radix, int is_neg)


/* Library Function - Single Match
    _xtoa
   
   Library: Visual Studio 1998 Release */

int __cdecl xtoa(uint val,char *buf,uint radix,int is_neg)

{
  ulonglong uVar1;
  char *pcVar2;
  char cVar3;
  char *pcVar4;
  
  pcVar2 = buf;
  if (is_neg != 0) {
    *buf = '-';
    buf = buf + 1;
    val = -val;
    pcVar2 = buf;
  }
  do {
    pcVar4 = pcVar2;
    uVar1 = (ulonglong)val;
    val = val / radix;
    cVar3 = (char)(uVar1 % (ulonglong)radix);
    if ((uint)(uVar1 % (ulonglong)radix) < 10) {
      cVar3 = cVar3 + '0';
    }
    else {
      cVar3 = cVar3 + 'W';
    }
    *pcVar4 = cVar3;
    pcVar2 = pcVar4 + 1;
  } while (val != 0);
  pcVar4[1] = '\0';
  do {
    cVar3 = *pcVar4;
    *pcVar4 = *buf;
    pcVar4 = pcVar4 + -1;
    *buf = cVar3;
    buf = buf + 1;
  } while (buf < pcVar4);
  return;
}



