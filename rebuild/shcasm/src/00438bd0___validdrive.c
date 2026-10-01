#include "decls.h"
#include "imports.h"

// entry: 00438bd0
// name : __validdrive
// size : 76
// sig  : int __validdrive(uint param_1)


/* Library Function - Single Match
    __validdrive
   
   Library: Visual Studio 1998 Release */

int __cdecl __validdrive(uint param_1)

{
  unsigned char _frec_4[4];
#define rootpath (*(char (*)[4])(_frec_4 + 0))
  UINT drive_type;
  
  if (param_1 == 0) {
    return 1;
  }
  rootpath[1] = 0x3a;
  rootpath[2] = 0x5c;
  rootpath[3] = 0;
  rootpath[0] = (char)param_1 + '@';
  drive_type = GetDriveTypeA(rootpath);
  if ((drive_type != 0) && (drive_type != 1)) {
    return 1;
  }
  return 0;
#undef rootpath
}



