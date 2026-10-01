#include "decls.h"
#include "imports.h"

// entry: 00412eef
// name : copy_to_counted_string
// size : 80
// sig  : void __cdecl copy_to_counted_string(char *out,char *text)


int __cdecl copy_to_counted_string(char *out,char *text)

{
  char *src;
  char *dst;
  char len;
  
  len = '\0';
  dst = out;
  for (src = text; dst = dst + 1, *src != '\0'; src = src + 1) {
    *dst = *src;
    len = len + '\x01';
  }
  *out = len;
  return;
}
