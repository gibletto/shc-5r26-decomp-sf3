#include "decls.h"
#include "imports.h"

// entry: 0042efd0
// name : find_substring
// size : 104
// sig  : char * find_substring(char * haystack, char * needle)


char * __cdecl find_substring(char *haystack,char *needle)

{
  char cVar1;
  uint needle_len;
  uint uVar2;
  int positions;
  int pos;
  int *piVar3;
  int *piVar4;
  char *pcVar5;
  int *piVar6;
  int *piVar7;
  bool bVar8;
  bool bVar9;
  
  needle_len = 0xffffffff;
  pcVar5 = needle;
  do {
    if (needle_len == 0) break;
    needle_len = needle_len - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  needle_len = ~needle_len - 1;
  uVar2 = 0xffffffff;
  pcVar5 = haystack;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  positions = ~uVar2 - needle_len;
  if (((0 < positions) && (needle_len != 0)) && (pos = 0, 0 < positions)) {
    do {
      uVar2 = needle_len >> 2;
      bVar8 = uVar2 == 0;
      piVar3 = (int *)(haystack + pos);
      piVar6 = (int *)needle;
      do {
        piVar4 = piVar3;
        piVar7 = piVar6;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        piVar7 = piVar6 + 1;
        piVar4 = piVar3 + 1;
        bVar8 = *piVar3 == *piVar6;
        piVar3 = piVar4;
        piVar6 = piVar7;
      } while (bVar8);
      bVar9 = false;
      if (bVar8) {
        uVar2 = needle_len & 3;
        bVar9 = uVar2 == 0;
        do {
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          bVar9 = (char)*piVar4 == (char)*piVar7;
          piVar4 = (int *)((int)piVar4 + 1);
          piVar7 = (int *)((int)piVar7 + 1);
        } while (bVar9);
      }
      if (bVar9) {
        return haystack + pos;
      }
      pos = pos + 1;
    } while (pos < positions);
  }
  return (char *)0x0;
}



