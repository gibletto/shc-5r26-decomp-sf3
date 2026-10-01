#include "decls.h"
#include "imports.h"

// entry: 0042bb3b
// name : copy_string_count
// size : 78
// sig  : short copy_string_count(char * src, char * dst)


short __cdecl copy_string_count(char *src,char *dst)

{
  short copied;
  
  copied = 0;
  for (; *src != '\0'; src = src + 1) {
    *dst = *src;
    dst = dst + 1;
    copied = copied + 1;
  }
  *dst = *src;
  return copied;
}



