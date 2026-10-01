#include "decls.h"
#include "imports.h"

// entry: 0040b970
// name : free_node_list
// size : 208
// sig  : void free_node_list(code_node * node)


int __cdecl free_node_list(code_node *node)

{
  int i;
  psd *rec;
  code_node *next_node;
  psd_op op;
  
  do {
    if (node == (code_node *)0x0) {
      return;
    }
    next_node = node->next;
    rec = node->psd;
    i = 0;
    do {
      op = rec->op;
      if (op != OP_DUMMY) {
        if ((((((op != OP_CASEJMP) && (op != OP_CTBL)) && (op != OP_CENT)) &&
             ((op != OP_LINE && (op != OP_BBGN)))) &&
            ((op != OP_BEND && ((op != OP_NON_10 && (op != OP_PROGRAM)))))) &&
           (((char)op < '\x18' || ('\x1b' < (char)op)))) {
          if (rec->ea1 != (ea *)0x0) {
            free_ea(rec->ea1);
            rec->ea1 = (ea *)0x0;
          }
          if (rec->ea2 != (ea *)0x0) {
            free_ea(rec->ea2);
            rec->ea2 = (ea *)0x0;
          }
        }
        op = rec->op;
        if (((((OP_CALL < op) && (op < OP_MOV_LOC)) || (op == OP_EXIT)) ||
            ((op == OP_RETURN || ((OP_SETT < op && (op < OP_BSR)))))) ||
           ((op == OP_JMP ||
            (((OP_JSR < op && (op < OP_BSRF)) || ((op == OP_BRAF || (op == OP_RTE)))))))) break;
      }
      i = i + 1;
      rec = rec + 1;
    } while (i < 0xf);
    pool_free(node,0x178);
    node = next_node;
  } while( true );
}



