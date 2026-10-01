#include "decls.h"
#include "imports.h"

// entry: 00419030
// name : get_marked_symbol_kind
// size : 36
// sig  : int __cdecl get_marked_symbol_kind(label_ref *labels)


int __cdecl get_marked_symbol_kind(label_ref *labels)

{
  uint kind;
  
  kind = 0;
  if (((labels != (label_ref *)0x0) && (labels->labno2 == -0x8000)) &&
     (labels->next == (label_ref *)0x0)) {
    kind = get_symbol_attr_low_bits(labels->labno1);
  }
  return kind;
}
