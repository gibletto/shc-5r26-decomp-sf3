#include "decls.h"
#include "imports.h"

// entry: 00416200
// name : find_previous_slot_candidate
// size : 231
// sig  : psd * find_previous_slot_candidate(code_node * node, psd * rec)


psd * __cdecl find_previous_slot_candidate(code_node *node,psd *rec)

{
  psd_op op;
  ea *opnd;
  
  if (rec != (psd *)0x0) {
    while (node->psd != rec) {
      op = rec->op;
      if ((((((op != OP_ADD) || (opnd = rec->ea1, opnd->labels != (label_ref *)0x0)) ||
            ((opnd->type & 0x1f) != 7)) || (opnd->disp != 0)) &&
          ((op != OP_CASEJMP && (op != OP_LINE)))) &&
         ((((op != OP_DUMMY && ((op != OP_CTBL && (op != OP_CENT)))) && (op != OP_SWBGN)) &&
          (((op != OP_SWEND && (op != OP_ENTER)) && ((op < OP_LABEL || (OP_FLABEL < op)))))))) {
        op = rec->op;
        if ((((op == OP_JSR) || (op == OP_BSR)) || (op == OP_CALL)) || (op == OP_BSRF)) {
          rec = (psd *)0x0;
        }
        break;
      }
      rec = find_previous_psd_record(node,rec);
      if (rec == (psd *)0x0) break;
    }
    if ((rec != (psd *)0x0) &&
       ((((op = rec->op, op == OP_CASEJMP || (op == OP_LINE)) ||
         ((op == OP_DUMMY || ((op == OP_CTBL || (op == OP_CENT)))))) ||
        ((op == OP_SWBGN ||
         ((((op == OP_SWEND || (op == OP_JSR)) || (op == OP_BSR)) ||
          (((op == OP_CALL || (op == OP_BSRF)) ||
           ((op == OP_ENTER || ((OP_BEND < op && (op < OP_NON_1C)))))))))))))) {
      rec = (psd *)0x0;
    }
  }
  return rec;
}



