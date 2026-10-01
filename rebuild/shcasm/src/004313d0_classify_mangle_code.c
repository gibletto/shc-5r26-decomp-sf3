#include "decls.h"
#include "imports.h"

// entry: 004313d0
// name : classify_mangle_code
// size : 65
// sig  : short classify_mangle_code(char * mangled)


short __cdecl classify_mangle_code(char *mangled)

{
  short i;
  bool found;
  
  found = false;
  i = 0;
  do {
    if (*(&g_mangle_code_classes)[i * 2] == *mangled) {
      found = true;
      break;
    }
    i = i + 1;
  } while (i < 0x21);
  if (!found) {
    return -1;
  }
  return *(short *)(i * 8 + SD(0x004428c4));
}



