#include "decls.h"
#include "imports.h"

// entry: 00434e20
// name : _strcmp
// size : 129
// sig  : int _strcmp(char * _Str1, char * _Str2)


/* Library Function - Single Match
    _strcmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl _strcmp(char *_Str1,char *_Str2)

{
  byte ch;
  bool less;
  undefined2 half;
  byte last_ch;
  undefined4 quad;
  
  if (((uint)_Str1 & 3) != 0) {
    if (((uint)_Str1 & 1) != 0) {
      ch = *_Str1;
      _Str1 = _Str1 + 1;
      less = ch < (byte)*_Str2;
      if (ch != *_Str2) goto LAB_00434e64;
      _Str2 = _Str2 + 1;
      if (ch == 0) {
        return 0;
      }
      if (((uint)_Str1 & 2) == 0) goto LAB_00434e30;
    }
    half = *(undefined2 *)_Str1;
    _Str1 = _Str1 + 2;
    ch = (byte)half;
    less = ch < (byte)*_Str2;
    if (ch != *_Str2) goto LAB_00434e64;
    if (ch == 0) {
      return 0;
    }
    ch = (byte)((ushort)half >> 8);
    less = ch < (byte)_Str2[1];
    if (ch != _Str2[1]) goto LAB_00434e64;
    if (ch == 0) {
      return 0;
    }
    _Str2 = _Str2 + 2;
  }
LAB_00434e30:
  while( true ) {
    quad = *(undefined4 *)_Str1;
    ch = (byte)quad;
    less = ch < (byte)*_Str2;
    if (ch != *_Str2) break;
    if (ch == 0) {
      return 0;
    }
    ch = (byte)((uint)quad >> 8);
    less = ch < (byte)_Str2[1];
    if (ch != _Str2[1]) break;
    if (ch == 0) {
      return 0;
    }
    ch = (byte)((uint)quad >> 0x10);
    less = ch < (byte)_Str2[2];
    if (ch != _Str2[2]) break;
    last_ch = (byte)((uint)quad >> 0x18);
    if (ch == 0) {
      return 0;
    }
    less = last_ch < (byte)_Str2[3];
    if (last_ch != _Str2[3]) break;
    _Str2 = _Str2 + 4;
    _Str1 = _Str1 + 4;
    if (last_ch == 0) {
      return 0;
    }
  }
LAB_00434e64:
  return (uint)less * -2 + 1;
}



