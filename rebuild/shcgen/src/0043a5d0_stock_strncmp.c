#include "decls.h"
#include "imports.h"

// entry: 0043a5d0
// name : stock_strncmp
// size : 56
// sig  : int stock_strncmp(char * str1, char * str2, uint count)


/* Library Function - Single Match
    _strncmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl stock_strncmp(char *str1,char *str2,uint count)

{
  char cVar1;
  char cVar2;
  uint remaining;
  int n;
  uint result;
  char *pcVar3;
  char *pcVar4;
  
  result = 0;
  remaining = count;
  pcVar3 = str1;
  if (count != 0) {
    do {
      if (remaining == 0) break;
      remaining = remaining - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    n = count - remaining;
    do {
      pcVar3 = str2;
      pcVar4 = str1;
      if (n == 0) break;
      n = n + -1;
      pcVar4 = str1 + 1;
      pcVar3 = str2 + 1;
      cVar2 = *str1;
      cVar1 = *str2;
      str2 = pcVar3;
      str1 = pcVar4;
    } while (cVar1 == cVar2);
    result = 0;
    if ((byte)pcVar3[-1] <= (byte)pcVar4[-1]) {
      if (pcVar3[-1] == pcVar4[-1]) {
        return 0;
      }
      result = 0xfffffffe;
    }
    result = ~result;
  }
  return result;
}



