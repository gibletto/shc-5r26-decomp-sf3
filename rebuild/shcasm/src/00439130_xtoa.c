#include "decls.h"
#include "imports.h"

// entry: 00439130
// name : xtoa
// size : 96
// sig  : uint __cdecl xtoa(uint param_1,char *param_2,uint param_3,int param_4)


/* Library Function - Single Match
    _xtoa
   
   Library: Visual Studio 1998 Release */

uint __cdecl xtoa(uint param_1,char *param_2,uint param_3,int param_4)

{
  char cVar1;
  byte ch;
  byte *p;
  byte *next;
  ulonglong val;
  
  next = (byte *)param_2;
  if (param_4 != 0) {
    *param_2 = '-';
    param_2 = param_2 + 1;
    param_1 = -param_1;
    next = (byte *)param_2;
  }
  do {
    p = next;
    val = (ulonglong)param_1;
    param_1 = param_1 / param_3;
    cVar1 = (char)(val % (ulonglong)param_3);
    if ((uint)(val % (ulonglong)param_3) < 10) {
      ch = cVar1 + 0x30;
    }
    else {
      ch = cVar1 + 0x57;
    }
    *p = ch;
    next = p + 1;
  } while (param_1 != 0);
  p[1] = 0;
  do {
    ch = *p;
    *p = *param_2;
    p = p + -1;
    *param_2 = ch;
    param_2 = param_2 + 1;
  } while (param_2 < p);
  return (uint)ch;
}
