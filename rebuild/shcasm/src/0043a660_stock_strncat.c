#include "decls.h"
#include "imports.h"

// entry: 0043a660
// name : stock_strncat
// size : 49
// sig  : char * stock_strncat(char * front, char * back, int count)


char * __cdecl stock_strncat(char *front,char *back,int count)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  bool at_nul;
  char ch;
  
  iVar1 = -1;
  pcVar3 = front;
  do {
    pcVar2 = pcVar3;
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    pcVar2 = pcVar3 + 1;
    ch = *pcVar3;
    pcVar3 = pcVar2;
  } while (ch != '\0');
  at_nul = pcVar2 + -1 == (char *)0x0;
  iVar1 = count;
  pcVar3 = back;
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    at_nul = *pcVar3 == '\0';
    pcVar3 = pcVar3 + 1;
  } while (!at_nul);
  if (at_nul) {
    iVar1 = iVar1 + 1;
  }
  pcVar3 = pcVar2 + -1;
  for (iVar1 = -(iVar1 - count); iVar1 != 0; iVar1 = iVar1 + -1) {
    *pcVar3 = *back;
    back = back + 1;
    pcVar3 = pcVar3 + 1;
  }
  *pcVar3 = '\0';
  return front;
}



