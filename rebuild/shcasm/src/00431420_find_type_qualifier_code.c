#include "decls.h"
#include "imports.h"

// entry: 00431420
// name : find_type_qualifier_code
// size : 52
// sig  : short find_type_qualifier_code(char * mangled)


short __cdecl find_type_qualifier_code(char *mangled)

{
  short i;
  bool found;
  
  i = 0;
  found = false;
  do {
    if (*(&g_mangle_qualifier_names)[i * 2] == *mangled) {
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



