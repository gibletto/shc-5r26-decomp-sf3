#include "decls.h"
#include "imports.h"

// entry: 0042cb00
// name : is_word_symbol_literal
// size : 43
// sig  : int is_word_symbol_literal(int value, label_ref * labels)


int __cdecl is_word_symbol_literal(int value,label_ref *labels)

{
  char attr_bit;
  undefined3 extraout_var = 0;
  int is_word;
  
  is_word = 0;
  if ((labels != (label_ref *)0x0) && (labels->labno2 == 0)) {
    attr_bit = get_symbol_attr_bit5_or_forced(labels->labno1);
    if (CONCAT31(extraout_var,attr_bit) != 0) {
      is_word = 1;
    }
  }
  return is_word;
}



