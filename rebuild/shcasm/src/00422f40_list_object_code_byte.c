#include "decls.h"
#include "imports.h"

// entry: 00422f40
// name : list_object_code_byte
// size : 31
// sig  : void __cdecl list_object_code_byte(char value,short relocatable)


int __cdecl list_object_code_byte(char value,short relocatable)

{
  append_listing_object_code((int)value,1,relocatable);
  return;
}
