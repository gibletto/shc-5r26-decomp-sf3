#include "decls.h"
#include "imports.h"

// entry: 0040dc10
// name : clear_psd_record
// size : 269
// sig  : void clear_psd_record(psd * rec)


int __cdecl clear_psd_record(psd *rec)

{
  psd_op op;
  
  if (rec->op != OP_DUMMY) {
    rec->flg = '\0';
    rec->misc = '\0';
    rec->tmp = -1;
    rec->sptravel = 0;
    rec->expno = 0;
    op = rec->op;
    if (op == OP_CASEJMP) {
      rec->filno = 0;
      rec->linno = 0;
      rec->ea1 = (ea *)0x0;
      rec->ea2 = (ea *)0x0;
      rec->op = OP_DUMMY;
      return;
    }
    if (op == OP_LINE) {
      rec->filno = 0;
      rec->linno = 0;
      *(undefined1 *)&rec->ea1 = 0;
      *(undefined1 *)((int)&rec->ea1 + 1) = 0;
      *(undefined2 *)((int)&rec->ea1 + 2) = 0;
      rec->ea2 = (ea *)0x0;
      rec->op = OP_DUMMY;
      return;
    }
    if ((OP_BEND < op) && (op < OP_NON_1C)) {
      rec->filno = 0;
      rec->linno = 0;
      *(undefined2 *)&rec->ea1 = 0;
      *(undefined2 *)((int)&rec->ea1 + 2) = 0;
      rec->ea2 = (ea *)0x0;
      rec->op = OP_DUMMY;
      return;
    }
    if ((op == OP_CTBL) || (op == OP_CENT)) {
      rec->filno = 0;
      rec->linno = 0;
      *(undefined2 *)&rec->ea1 = 0;
      *(undefined2 *)((int)&rec->ea1 + 2) = 0;
      rec->ea2 = (ea *)0x0;
    }
    else {
      if (op == OP_NON_10) {
        rec->filno = 0;
        rec->linno = 0;
        rec->ea1 = (ea *)0x0;
        rec->ea2 = (ea *)0x0;
        rec->op = OP_DUMMY;
        return;
      }
      if (op == OP_PROGRAM) {
        rec->filno = 0;
        rec->linno = 0;
        rec->ea1 = (ea *)0x0;
        rec->ea2 = (ea *)0x0;
        rec->op = OP_DUMMY;
        return;
      }
      rec->filno = 0;
      rec->linno = 0;
      if (rec->ea1 != (ea *)0x0) {
        free_ea(rec->ea1);
        rec->ea1 = (ea *)0x0;
      }
      if (rec->ea2 != (ea *)0x0) {
        free_ea(rec->ea2);
        rec->ea2 = (ea *)0x0;
        rec->op = OP_DUMMY;
        return;
      }
    }
  }
  rec->op = OP_DUMMY;
  return;
}



