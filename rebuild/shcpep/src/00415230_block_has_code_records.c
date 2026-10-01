#include "decls.h"
#include "imports.h"

// entry: 00415230
// name : block_has_code_records
// size : 78
// sig  : char block_has_code_records(code_node * block)


char __cdecl block_has_code_records(code_node *block)

{
  int i;
  psd *rec;
  psd_op op;
  
  do {
    if (block == (code_node *)0x0) {
      return '\0';
    }
    rec = block->psd;
    i = 0;
    do {
      if (rec == (psd *)0x0) break;
      op = rec->op;
      if ((((op != OP_DUMMY) && (op != OP_SWBGN)) && (op != OP_SWEND)) &&
         (((op != OP_LINE && (op != OP_LABEL)) && ((op != OP_CLABEL && (op != OP_DLABEL)))))) {
        return '\x01';
      }
      i = i + 1;
      rec = rec + 1;
    } while (i < 0xf);
    block = block->next;
  } while( true );
}



