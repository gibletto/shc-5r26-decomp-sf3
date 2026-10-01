#include "decls.h"
#include "imports.h"

// entry: 004231d7
// name : list_object_code_value
// size : 135
// sig  : void __cdecl list_object_code_value(int *value,short size_kind,short relocatable)


int __cdecl list_object_code_value(int *value,short size_kind,short relocatable)

{
  if (size_kind == 0) {
    list_object_code_byte((char)*value,relocatable);
  }
  else if (size_kind == 1) {
    list_object_code_word((short)*value,relocatable);
  }
  else if (size_kind == 2) {
    list_object_code_long(*value,relocatable);
  }
  return;
}
