#include "decls.h"
#include "imports.h"

// entry: 004314a0
// name : find_declarator_code
// size : 52
// sig  : short find_declarator_code(char * mangled)


short __cdecl find_declarator_code(char *mangled)

{
  short i;
  bool found;
  
  i = 0;
  found = false;
  do {
    if (*(&g_mangle_declarator_names)[i * 2] == *mangled) {
      found = true;
      break;
    }
    i = i + 1;
  } while (i < 4);
  if (!found) {
    i = -1;
  }
  return i;
}



