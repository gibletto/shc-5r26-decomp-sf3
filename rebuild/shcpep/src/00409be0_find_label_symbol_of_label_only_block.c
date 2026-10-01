#include "decls.h"
#include "imports.h"

// entry: 00409be0
// name : find_label_symbol_of_label_only_block
// size : 112
// sig  : symbol * find_label_symbol_of_label_only_block(code_node * block)


symbol * __cdecl find_label_symbol_of_label_only_block(code_node *block)

{
  symbol *sym;
  psd *rec;
  int i;
  psd_op op;
  
  sym = (symbol *)0x0;
  if (block == (code_node *)0x0) {
    return (symbol *)0x0;
  }
  do {
    rec = block->psd;
    i = 0;
    do {
      if (rec == (psd *)0x0) break;
      op = rec->op;
      if ((((op == OP_DUMMY) || (op == OP_LINE)) || (op == OP_BBGN)) || (op == OP_BEND)) {
LAB_00409c1a:
        if ((op == OP_LABEL) || ((op == OP_DLABEL || (op == OP_CLABEL)))) goto LAB_00409c29;
      }
      else {
        if (op != OP_LABEL) {
          if ((op != OP_DLABEL) && (op != OP_CLABEL)) {
            return (symbol *)0x0;
          }
          goto LAB_00409c1a;
        }
LAB_00409c29:
        sym = find_label_symbol(*(short *)&rec->ea1);
      }
      i = i + 1;
      rec = rec + 1;
    } while (i < 0xf);
    block = block->next;
    if (block == (code_node *)0x0) {
      return sym;
    }
  } while( true );
}



