#include "decls.h"
#include "imports.h"

// entry: 004280f6
// name : get_symbol_attribute_bits
// size : 67
// sig  : int get_symbol_attribute_bits(short labno)


int __cdecl get_symbol_attribute_bits(short labno)

{
  symbol *sym;
  uint attr_bits;
  
  attr_bits = 0;
  if (0xb6 < labno) {
    sym = find_symbol_by_id(labno);
    attr_bits = (int)(char)sym->attr & 3;
  }
  return attr_bits;
}



