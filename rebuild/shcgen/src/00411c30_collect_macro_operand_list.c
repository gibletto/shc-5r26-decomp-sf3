#include "decls.h"
#include "imports.h"

// entry: 00411c30
// name : collect_macro_operand_list
// size : 122
// sig  : int collect_macro_operand_list(gen_node * node, tmpl_entry * entries, ea * * out, ea * * operands)


int __cdecl collect_macro_operand_list(gen_node *node,tmpl_entry *entries,ea **out,ea **operands)

{
  ea *opnd;
  int n_out;
  int next_out;
  int entry_count;
  
  n_out = 0;
  entry_count = 0;
  do {
    if (entries->op != 0x2200) {
      return entry_count;
    }
    next_out = n_out;
    if (entries->opnd[0] != 0xfa) {
      next_out = n_out + 1;
      opnd = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
      out[n_out] = opnd;
    }
    n_out = next_out;
    if (entries->opnd[1] != 0xfa) {
      n_out = next_out + 1;
      opnd = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
      out[next_out] = opnd;
    }
    entries = entries + 1;
    entry_count = entry_count + 1;
  } while (n_out == 0);
  return entry_count;
}



