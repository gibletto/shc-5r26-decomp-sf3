#include "decls.h"
#include "imports.h"

// entry: 0042cb30
// name : get_marked_symbol_kind
// size : 36
// sig  : int get_marked_symbol_kind(label_ref * labels)


int __cdecl get_marked_symbol_kind(label_ref *labels)

{
  uchar low_bits;
  int kind;
  undefined3 extraout_var = 0;
  
  kind = 0;
  if (((labels != (label_ref *)0x0) && (labels->labno2 == -0x8000)) &&
     (labels->next == (label_ref *)0x0)) {
    low_bits = get_symbol_attr_low_bits(labels->labno1);
    kind = CONCAT31(extraout_var,low_bits);
  }
  return kind;
}



