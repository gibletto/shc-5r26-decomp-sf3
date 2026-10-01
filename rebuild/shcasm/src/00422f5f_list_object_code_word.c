#include "decls.h"
#include "imports.h"

// entry: 00422f5f
// name : list_object_code_word
// size : 31
// sig  : void __cdecl list_object_code_word(short value,short relocatable)


int __cdecl list_object_code_word(short value,short relocatable)

{
  append_listing_object_code((int)value,2,relocatable);
  return;
}
