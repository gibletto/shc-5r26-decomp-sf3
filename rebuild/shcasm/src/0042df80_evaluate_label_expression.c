#include "decls.h"
#include "imports.h"

// entry: 0042df80
// name : evaluate_label_expression
// size : 228
// sig  : int evaluate_label_expression(int value, label_ref * labels)


int __cdecl evaluate_label_expression(int value,label_ref *labels)

{
  symbol *sym;
  int result_value;
  label_ref *cur_ref;
  
  result_value = value;
  for (cur_ref = labels; cur_ref != (label_ref *)0x0; cur_ref = cur_ref->next) {
    if (cur_ref->labno1 < 1) {
      if (cur_ref->labno1 != 0) {
        sym = find_symbol_by_id(cur_ref->labno1);
        result_value = result_value - sym->value;
      }
    }
    else {
      sym = find_symbol_by_id(cur_ref->labno1);
      result_value = result_value + sym->value;
    }
    if (cur_ref->labno2 < 1) {
      if (cur_ref->labno2 != 0) {
        sym = find_symbol_by_id(cur_ref->labno2);
        result_value = result_value - sym->value;
      }
    }
    else {
      sym = find_symbol_by_id(cur_ref->labno2);
      result_value = result_value + sym->value;
    }
  }
  return result_value;
}



