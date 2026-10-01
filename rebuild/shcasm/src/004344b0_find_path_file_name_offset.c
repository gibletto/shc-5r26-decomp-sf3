#include "decls.h"
#include "imports.h"

// entry: 004344b0
// name : find_path_file_name_offset
// size : 44
// sig  : int find_path_file_name_offset(char * path)


int __cdecl find_path_file_name_offset(char *path)

{
  int pos;
  char ch;
  
  pos = 0;
  ch = *path;
  while (ch != '\0') {
    pos = pos + 1;
    ch = path[pos];
  }
  for (; (((-1 < pos && (ch = path[pos], ch != '\\')) && (ch != ':')) && (ch != '/'));
      pos = pos + -1) {
  }
  return pos + 1;
}



