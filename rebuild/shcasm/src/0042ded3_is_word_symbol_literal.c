#include "decls.h"
#include "imports.h"

// entry: 0042ded3
// name : is_word_symbol_literal
// size : 85
// sig  : int is_word_symbol_literal(int value, label_ref * labels)


int __cdecl is_word_symbol_literal(int value,label_ref *labels)

{
  int is_abs16;
  int result;
  
  result = 0;
  if ((labels != (label_ref *)0x0) && (labels->labno2 == 0)) {
    is_abs16 = symbol_address_is_abs16(labels->labno1);
    if (is_abs16 != 0) {
      result = 1;
    }
  }
  return result;
}



