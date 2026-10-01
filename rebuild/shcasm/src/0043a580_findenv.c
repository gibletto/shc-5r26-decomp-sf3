#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_environ
#define stock_environ (*(int * *)(g_sd + 0x81d8))


// entry: 0043a580
// name : findenv
// size : 92
// sig  : int findenv(uchar * param_1, size_t param_2)


/* Library Function - Single Match
    _findenv
   
   Library: Visual Studio 1998 Release */

int __cdecl findenv(uchar *param_1,size_t param_2)

{
  int iVar1;
  int *env;
  
  iVar1 = *stock_environ;
  env = stock_environ;
  while( true ) {
    if (iVar1 == 0) {
      return -((int)env - (int)stock_environ >> 2);
    }
    iVar1 = __mbsnbicoll(param_1,(uchar *)*env,param_2);
    if ((iVar1 == 0) && ((*(char *)(*env + param_2) == '=' || (*(char *)(*env + param_2) == '\0'))))
    break;
    env = env + 1;
    iVar1 = *env;
  }
  return (int)env - (int)stock_environ >> 2;
}



