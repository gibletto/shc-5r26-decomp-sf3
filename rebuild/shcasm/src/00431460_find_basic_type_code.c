#include "decls.h"
#include "imports.h"

// entry: 00431460
// name : find_basic_type_code
// size : 52
// sig  : short find_basic_type_code(char * mangled)


short __cdecl find_basic_type_code(char *mangled)

{
  short i;
  bool found;
  
  i = 0;
  found = false;
  do {
    if (*(&g_mangle_basic_type_names)[i * 2] == *mangled) {
      found = true;
      break;
    }
    i = i + 1;
  } while (i < 10);
  if (!found) {
    i = -1;
  }
  return i;
}



