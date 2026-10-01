#include "decls.h"
#include "imports.h"

// entry: 004234b0
// name : stock_strncat
// size : 49
// sig  : char * stock_strncat(char * front, char * back, int count)


char * __cdecl stock_strncat(char *front,char *back,int count)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  bool bVar5;
  
  iVar2 = -1;
  pcVar4 = front;
  do {
    pcVar3 = pcVar4;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar3 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar3;
  } while (cVar1 != '\0');
  bVar5 = pcVar3 + -1 == (char *)0x0;
  iVar2 = count;
  pcVar4 = back;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar5 = *pcVar4 == '\0';
    pcVar4 = pcVar4 + 1;
  } while (!bVar5);
  if (bVar5) {
    iVar2 = iVar2 + 1;
  }
  pcVar4 = pcVar3 + -1;
  for (iVar2 = -(iVar2 - count); iVar2 != 0; iVar2 = iVar2 + -1) {
    *pcVar4 = *back;
    back = back + 1;
    pcVar4 = pcVar4 + 1;
  }
  *pcVar4 = '\0';
  return front;
}



