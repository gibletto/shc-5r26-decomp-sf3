#include "decls.h"
#include "imports.h"

// entry: 00419000
// name : is_word_symbol_literal
// size : 43
// sig  : int is_word_symbol_literal(int value, label_ref * labels)


int __cdecl is_word_symbol_literal(int value,label_ref *labels)

{
  int is_word;
  int result;
  
  result = 0;
  if ((labels != (label_ref *)0x0) && (labels->labno2 == 0)) {
    is_word = get_symbol_attr_bit5_or_forced(labels->labno1);
    if (is_word != 0) {
      result = 1;
    }
  }
  return result;
}



