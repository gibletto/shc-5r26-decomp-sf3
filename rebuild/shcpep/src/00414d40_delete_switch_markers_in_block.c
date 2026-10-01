#include "decls.h"
#include "imports.h"

// entry: 00414d40
// name : delete_switch_markers_in_block
// size : 159
// sig  : void delete_switch_markers_in_block(code_node * block)


int __cdecl delete_switch_markers_in_block(code_node *block)

{
  short i;
  psd *rec;
  psd_op op;
  
  do {
    if (block == (code_node *)0x0) {
      return;
    }
    i = 0;
    rec = block->psd;
    do {
      if (((rec->op == OP_SWBGN) || (rec->op == OP_SWEND)) &&
         (delete_switch_marker_pair(rec), rec->op == OP_SWEND)) {
        g_after_switch_end = 1;
      }
      if (((g_after_switch_end == 1) && ('\x17' < (char)rec->op)) && ((char)rec->op < '\x1c')) {
        delete_switch_marker_pair(rec);
      }
      op = rec->op;
      if ((((OP_CALL < op) && (op < OP_MOV_LOC)) || ((op == OP_EXIT || (op == OP_RETURN)))) ||
         ((((((OP_SETT < op && (op < OP_BSR)) || (op == OP_JMP)) ||
            ((OP_JSR < op && (op < OP_BSRF)))) || (op == OP_BRAF)) || (op == OP_RTE)))) break;
      i = i + 1;
      rec = rec + 1;
    } while (i < 0xf);
    block = block->next;
  } while( true );
}



