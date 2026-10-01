#include "decls.h"
#include "imports.h"

// entry: 00432660
// name : remember_argument_type
// size : 45
// sig  : void __cdecl remember_argument_type(char *text)


int __cdecl remember_argument_type(char *text)

{
  char *copy;
  
  copy = alloc_back_reference_string(text);
  g_demangle_back_references[g_demangle_back_reference_count].text = copy;
  g_demangle_back_references[g_demangle_back_reference_count].kind = 1;
  g_demangle_back_reference_count = g_demangle_back_reference_count + 1;
  return;
}
