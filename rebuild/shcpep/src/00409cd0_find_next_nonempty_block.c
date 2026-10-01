#include "decls.h"
#include "imports.h"

// entry: 00409cd0
// name : find_next_nonempty_block
// size : 91
// sig  : code_node * __cdecl find_next_nonempty_block(code_node *block)


code_node * __cdecl find_next_nonempty_block(code_node *block)

{
  psd *rec;
  int i;
  code_node *cand;
  code_node *node;
  psd_op op;
  
  cand = block->next_block;
  do {
    if (((cand == (code_node *)0x0) || (cand->labno != 0)) || (node = cand, cand->target_labno != 0)
       ) {
      return cand;
    }
    for (; node != (code_node *)0x0; node = node->next) {
      rec = node->psd;
      i = 0;
      do {
        if (rec == (psd *)0x0) break;
        op = rec->op;
        if (((op != OP_DUMMY) && (op != OP_LINE)) && ((op != OP_BBGN && (op != OP_BEND)))) {
          return cand;
        }
        i = i + 1;
        rec = rec + 1;
      } while (i < 0xf);
    }
    cand = cand->next_block;
  } while( true );
}
