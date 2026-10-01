#include "decls.h"
#include "imports.h"

// entry: 00437d70
// name : parse_cmdline
// size : 466
// sig  : byte * __cdecl parse_cmdline(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5)


/* Library Function - Single Match
    _parse_cmdline
   
   Library: Visual Studio 1998 Release */

byte * __cdecl parse_cmdline(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5)

{
  byte *next;
  uint numslash;
  byte *p;
  byte ch;
  bool copychar;
  bool inquote;
  
  *param_5 = 0;
  *param_4 = 1;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = param_3;
    param_2 = param_2 + 1;
  }
  if (*param_1 == 0x22) {
    p = param_1 + 1;
    ch = *p;
    while ((ch != 0x22 && (*p != 0))) {
      if (((*(byte *)((int)&stock_mbctype + *p + 1) & 4) != 0) &&
         (*param_5 = *param_5 + 1, param_3 != (byte *)0x0)) {
        ch = *p;
        p = p + 1;
        *param_3 = ch;
        param_3 = param_3 + 1;
      }
      *param_5 = *param_5 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *p;
        param_3 = param_3 + 1;
      }
      p = p + 1;
      ch = *p;
    }
    *param_5 = *param_5 + 1;
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    if (*p == 0x22) {
      p = p + 1;
    }
  }
  else {
    do {
      *param_5 = *param_5 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *param_1;
        param_3 = param_3 + 1;
      }
      ch = *param_1;
      p = param_1 + 1;
      if ((*(byte *)((int)&stock_mbctype + ch + 1) & 4) != 0) {
        *param_5 = *param_5 + 1;
        if (param_3 != (byte *)0x0) {
          *param_3 = *p;
          param_3 = param_3 + 1;
        }
        p = param_1 + 2;
      }
      if (ch == 0x20) break;
      if (ch == 0) goto LAB_00437de0;
      param_1 = p;
    } while (ch != 9);
    if (ch == 0) {
LAB_00437de0:
      p = p + -1;
    }
    else if (param_3 != (byte *)0x0) {
      param_3[-1] = 0;
    }
  }
  inquote = false;
  while (*p != 0) {
    for (; (*p == 0x20 || (*p == 9)); p = p + 1) {
    }
    if (*p == 0) break;
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = param_3;
      param_2 = param_2 + 1;
    }
    *param_4 = *param_4 + 1;
    while( true ) {
      copychar = true;
      numslash = 0;
      ch = *p;
      while (ch == 0x5c) {
        p = p + 1;
        numslash = numslash + 1;
        ch = *p;
      }
      if (*p == 0x22) {
        next = p;
        if ((numslash & 1) == 0) {
          if ((!inquote) || (next = p + 1, *next != 0x22)) {
            copychar = false;
            next = p;
          }
          inquote = !inquote;
        }
        numslash = numslash >> 1;
        p = next;
      }
      while (numslash != 0) {
        numslash = numslash - 1;
        if (param_3 != (byte *)0x0) {
          *param_3 = 0x5c;
          param_3 = param_3 + 1;
        }
        *param_5 = *param_5 + 1;
      }
      ch = *p;
      if ((ch == 0) || ((!inquote && ((ch == 0x20 || (ch == 9)))))) break;
      if (copychar) {
        if (param_3 == (byte *)0x0) {
          if ((*(byte *)((int)&stock_mbctype + ch + 1) & 4) != 0) {
            p = p + 1;
            *param_5 = *param_5 + 1;
          }
          *param_5 = *param_5 + 1;
          goto LAB_00437f11;
        }
        next = param_3;
        if ((*(byte *)((int)&stock_mbctype + ch + 1) & 4) != 0) {
          *param_3 = ch;
          p = p + 1;
          next = param_3 + 1;
          *param_5 = *param_5 + 1;
        }
        ch = *p;
        param_3 = next + 1;
        p = p + 1;
        *next = ch;
        *param_5 = *param_5 + 1;
      }
      else {
LAB_00437f11:
        p = p + 1;
      }
    }
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    *param_5 = *param_5 + 1;
  }
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = 0;
  }
  *param_4 = *param_4 + 1;
  return param_3;
}
