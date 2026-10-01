#include "decls.h"
#include "imports.h"

// entry: 00435a70
// name : stock_fullpath
// size : 183
// sig  : char * stock_fullpath(char * abs_path, char * rel_path, uint max_length)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char * __cdecl stock_fullpath(char *abs_path,char *rel_path,uint max_length)

{
  unsigned char _frec_4[4];
#define file_part (*(LPSTR *)(_frec_4 + 0))
  DWORD path_len;
  char *result;
  
  if ((rel_path == (char *)0x0) || (*rel_path == '\0')) {
    result = stock_getcwd(abs_path,max_length);
    return result;
  }
  if (abs_path == (char *)0x0) {
    abs_path = stock_malloc(0x104);
    if (abs_path == (LPSTR)0x0) {
      _stock_errno = 0xc;
      return (char *)0x0;
    }
    max_length = 0x104;
  }
  path_len = GetFullPathNameA(rel_path,max_length,abs_path,&file_part);
  if (path_len < max_length) {
    if (path_len != 0) {
      return abs_path;
    }
    path_len = GetLastError();
    stock_dosmaperr(path_len);
    return (char *)0x0;
  }
  _stock_errno = 0x22;
  return (char *)0x0;
#undef file_part
}



