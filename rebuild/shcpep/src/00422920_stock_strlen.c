#include "decls.h"
#include "imports.h"

// entry: 00422920
// name : stock_strlen
// size : 119
// sig  : char * stock_strlen(uint * str)


char * __cdecl stock_strlen(uint *str)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar2 = str;
  do {
    if (((uint)puVar2 & 3) == 0) goto LAB_0042293c;
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
LAB_0042296f:
  return (char *)((int)puVar2 + (-1 - (int)str));
LAB_0042293c:
  do {
    do {
      puVar3 = puVar2;
      puVar2 = puVar3 + 1;
    } while (((*puVar3 ^ 0xffffffff ^ *puVar3 + 0x7efefeff) & 0x81010100) == 0);
    uVar1 = *puVar3;
    if ((char)uVar1 == '\0') {
      return (char *)((int)puVar3 - (int)str);
    }
    if ((char)(uVar1 >> 8) == '\0') {
      return (char *)((int)puVar3 + (1 - (int)str));
    }
    if ((uVar1 & 0xff0000) == 0) {
      return (char *)((int)puVar3 + (2 - (int)str));
    }
  } while ((uVar1 & 0xff000000) != 0);
  goto LAB_0042296f;
}



