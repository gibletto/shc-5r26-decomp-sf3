#include "decls.h"
#include "imports.h"

// entry: 0043a300
// name : _strncnt
// size : 44
// sig  : size_t _strncnt(char * _String, size_t _Cnt)


/* Library Function - Single Match
    _strncnt
   
   Library: Visual Studio 1998 Release */

size_t __cdecl _strncnt(char *_String,size_t _Cnt)

{
  size_t left;
  char *scan;
  
  scan = _String;
  left = _Cnt;
  while (left != 0) {
    left = left - 1;
    if (*scan == '\0') goto LAB_0043a325;
    scan = scan + 1;
  }
  if (*scan == '\0') {
LAB_0043a325:
    _Cnt = (int)scan - (int)_String;
  }
  return _Cnt;
}



