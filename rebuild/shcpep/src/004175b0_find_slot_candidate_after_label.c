#include "decls.h"
#include "imports.h"

// entry: 004175b0
// name : find_slot_candidate_after_label
// size : 328
// sig  : psd * find_slot_candidate_after_label(code_node * block, psd * label_rec)


psd * __cdecl find_slot_candidate_after_label(code_node *block,psd *label_rec)

{
  psd *next_rec;
  int feeds_add;
  psd *found;
  psd *rec;
  psd_op op;
  ea *opnd;
  
  found = (psd *)0x0;
  if ((label_rec == (psd *)0x0) || (block == (code_node *)0x0)) {
    return (psd *)0x0;
  }
  next_rec = find_next_psd_record(block,label_rec);
  if (next_rec != (psd *)0x0) {
    while (rec = next_rec, found == (psd *)0x0) {
      op = rec->op;
      if ((((((op == OP_ADD) && (opnd = rec->ea1, opnd->labels == (label_ref *)0x0)) &&
            ((opnd->type & 0x1f) == 7)) && (opnd->disp == 0)) ||
          (((op == OP_DUMMY || (op == OP_LINE)) ||
           ((op == OP_CTBL || ((op == OP_CENT || (op == OP_SWBGN)))))))) || (op == OP_SWEND)) {
        next_rec = find_next_psd_record(block,rec);
        rec = found;
      }
      else {
        if (op == OP_JSR) {
          return (psd *)0x0;
        }
        if (op == OP_BSR) {
          return (psd *)0x0;
        }
        if (op == OP_RTE) {
          return (psd *)0x0;
        }
        if (op == OP_CALL) {
          return (psd *)0x0;
        }
        if (op == OP_BSRF) {
          return (psd *)0x0;
        }
        if ((OP_CALL < op) && (op < OP_MOV_LOC)) {
          return (psd *)0x0;
        }
        if (op == OP_EXIT) {
          return (psd *)0x0;
        }
        if (op == OP_RETURN) {
          return (psd *)0x0;
        }
        if ((OP_SETT < op) && (op < OP_BSR)) {
          return (psd *)0x0;
        }
        if (op == OP_JMP) {
          return (psd *)0x0;
        }
        if ((OP_JSR < op) && (op < OP_BSRF)) {
          return (psd *)0x0;
        }
        if (op == OP_BRAF) {
          return (psd *)0x0;
        }
        if (op == OP_RTE) {
          return (psd *)0x0;
        }
        if (op == OP_NON_A0) {
          return (psd *)0x0;
        }
        if (op == OP_CASEJMP) {
          return (psd *)0x0;
        }
        if (op == OP_ENTER) {
          return (psd *)0x0;
        }
        if (op == OP_NON_30) {
          return (psd *)0x0;
        }
        if (op == OP_NON_31) {
          return (psd *)0x0;
        }
        next_rec = rec;
        if (op == OP_MOVI) {
          feeds_add = is_movi_feeding_stack_add(block,rec);
          if (feeds_add != 0) {
            return (psd *)0x0;
          }
          if (((rec->op == OP_MOVI) && (rec->ea1->labels == (label_ref *)0x0)) &&
             (found = find_next_psd_record(block,rec), found == (psd *)0x0)) {
            return (psd *)0x0;
          }
        }
      }
      found = rec;
      if (next_rec == (psd *)0x0) {
        return rec;
      }
    }
  }
  return found;
}



