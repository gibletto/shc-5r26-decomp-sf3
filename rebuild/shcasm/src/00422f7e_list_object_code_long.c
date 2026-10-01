#include "decls.h"
#include "imports.h"

// entry: 00422f7e
// name : list_object_code_long
// size : 30
// sig  : void __cdecl list_object_code_long(int value,short relocatable)


int __cdecl list_object_code_long(int value,short relocatable)

{
  append_listing_object_code(value,4,relocatable);
  return;
}
