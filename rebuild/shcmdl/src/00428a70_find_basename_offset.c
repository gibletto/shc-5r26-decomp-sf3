#include "decls.h"
#include "imports.h"

// entry: 00428a70
// name : find_basename_offset
// size : 44
// sig  : int find_basename_offset(char * path)


int __cdecl find_basename_offset(char *path)

{
  int i;
  char ch;
  
  i = 0;
  ch = *path;
  while (ch != '\0') {
    i = i + 1;
    ch = path[i];
  }
  for (; (((-1 < i && (ch = path[i], ch != '\\')) && (ch != ':')) && (ch != '/')); i = i + -1) {
  }
  return i + 1;
}



