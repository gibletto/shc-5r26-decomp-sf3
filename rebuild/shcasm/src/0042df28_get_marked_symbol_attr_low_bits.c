#include "decls.h"
#include "imports.h"

// entry: 0042df28
// name : get_marked_symbol_attr_low_bits
// size : 88
// sig  : int get_marked_symbol_attr_low_bits(label_ref * labels)


int __cdecl get_marked_symbol_attr_low_bits(label_ref *labels)

{
  int attr_bits;
  
  attr_bits = 0;
  if (((labels != (label_ref *)0x0) && (labels->labno2 == -0x8000)) &&
     (labels->next == (label_ref *)0x0)) {
    attr_bits = get_symbol_attribute_bits(labels->labno1);
  }
  return attr_bits;
}



