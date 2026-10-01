#include "decls.h"
#include "imports.h"

// entry: 004205e0
// name : parse_cmdline
// size : 466
// sig  : void parse_cmdline(byte * cmdstart, undefined4 * argv, byte * args, int * numargs, int * numchars)


/* Library Function - Single Match
    _parse_cmdline
   
   Library: Visual Studio 1998 Release */

int __cdecl parse_cmdline(byte *cmdstart,undefined4 *argv,byte *args,int *numargs,int *numchars)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  byte *pbVar4;
  uint uVar5;
  byte *pbVar6;
  
  *numchars = 0;
  *numargs = 1;
  if (argv != (undefined4 *)0x0) {
    *argv = args;
    argv = argv + 1;
  }
  if (*cmdstart == 0x22) {
    pbVar6 = cmdstart + 1;
    bVar1 = *pbVar6;
    while ((bVar1 != 0x22 && (*pbVar6 != 0))) {
      if (((*(byte *)((int)&stock_mbctype + *pbVar6 + 1) & 4) != 0) &&
         (*numchars = *numchars + 1, args != (byte *)0x0)) {
        bVar1 = *pbVar6;
        pbVar6 = pbVar6 + 1;
        *args = bVar1;
        args = args + 1;
      }
      *numchars = *numchars + 1;
      if (args != (byte *)0x0) {
        *args = *pbVar6;
        args = args + 1;
      }
      pbVar6 = pbVar6 + 1;
      bVar1 = *pbVar6;
    }
    *numchars = *numchars + 1;
    if (args != (byte *)0x0) {
      *args = 0;
      args = args + 1;
    }
    if (*pbVar6 == 0x22) {
      pbVar6 = pbVar6 + 1;
    }
  }
  else {
    do {
      *numchars = *numchars + 1;
      if (args != (byte *)0x0) {
        *args = *cmdstart;
        args = args + 1;
      }
      bVar1 = *cmdstart;
      pbVar6 = cmdstart + 1;
      if ((*(byte *)((int)&stock_mbctype + bVar1 + 1) & 4) != 0) {
        *numchars = *numchars + 1;
        if (args != (byte *)0x0) {
          *args = *pbVar6;
          args = args + 1;
        }
        pbVar6 = cmdstart + 2;
      }
      if (bVar1 == 0x20) break;
      if (bVar1 == 0) goto LAB_00420650;
      cmdstart = pbVar6;
    } while (bVar1 != 9);
    if (bVar1 == 0) {
LAB_00420650:
      pbVar6 = pbVar6 + -1;
    }
    else if (args != (byte *)0x0) {
      args[-1] = 0;
    }
  }
  bVar3 = false;
  while (*pbVar6 != 0) {
    for (; (*pbVar6 == 0x20 || (*pbVar6 == 9)); pbVar6 = pbVar6 + 1) {
    }
    if (*pbVar6 == 0) break;
    if (argv != (undefined4 *)0x0) {
      *argv = args;
      argv = argv + 1;
    }
    *numargs = *numargs + 1;
    while( true ) {
      bVar2 = true;
      uVar5 = 0;
      bVar1 = *pbVar6;
      while (bVar1 == 0x5c) {
        pbVar6 = pbVar6 + 1;
        uVar5 = uVar5 + 1;
        bVar1 = *pbVar6;
      }
      if (*pbVar6 == 0x22) {
        pbVar4 = pbVar6;
        if ((uVar5 & 1) == 0) {
          if ((!bVar3) || (pbVar4 = pbVar6 + 1, *pbVar4 != 0x22)) {
            bVar2 = false;
            pbVar4 = pbVar6;
          }
          bVar3 = !bVar3;
        }
        uVar5 = uVar5 >> 1;
        pbVar6 = pbVar4;
      }
      while (uVar5 != 0) {
        uVar5 = uVar5 - 1;
        if (args != (byte *)0x0) {
          *args = 0x5c;
          args = args + 1;
        }
        *numchars = *numchars + 1;
      }
      bVar1 = *pbVar6;
      if ((bVar1 == 0) || ((!bVar3 && ((bVar1 == 0x20 || (bVar1 == 9)))))) break;
      if (bVar2) {
        if (args == (byte *)0x0) {
          if ((*(byte *)((int)&stock_mbctype + bVar1 + 1) & 4) != 0) {
            pbVar6 = pbVar6 + 1;
            *numchars = *numchars + 1;
          }
          *numchars = *numchars + 1;
          goto LAB_00420781;
        }
        pbVar4 = args;
        if ((*(byte *)((int)&stock_mbctype + bVar1 + 1) & 4) != 0) {
          *args = bVar1;
          pbVar6 = pbVar6 + 1;
          pbVar4 = args + 1;
          *numchars = *numchars + 1;
        }
        bVar1 = *pbVar6;
        args = pbVar4 + 1;
        pbVar6 = pbVar6 + 1;
        *pbVar4 = bVar1;
        *numchars = *numchars + 1;
      }
      else {
LAB_00420781:
        pbVar6 = pbVar6 + 1;
      }
    }
    if (args != (byte *)0x0) {
      *args = 0;
      args = args + 1;
    }
    *numchars = *numchars + 1;
  }
  if (argv != (undefined4 *)0x0) {
    *argv = 0;
  }
  *numargs = *numargs + 1;
  return;
}



