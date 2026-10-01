#include "decls.h"
#include "imports.h"

// entry: 00414f00
// name : block_has_non_marker_records
// size : 63
// sig  : char block_has_non_marker_records(code_node * block)


char __cdecl block_has_non_marker_records(code_node *block)

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
      if ((((op != OP_DUMMY) && (op != OP_LINE)) && (op != OP_SWBGN)) && (op != OP_SWEND)) {
        return '\x01';
      }
      i = i + 1;
      rec = rec + 1;
    } while (i < 0xf);
    block = block->next;
  } while( true );
}



