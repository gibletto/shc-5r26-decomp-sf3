#include "decls.h"
#include "imports.h"

// entry: 00409980
// name : record_has_memory_source
// size : 111
// sig  : char record_has_memory_source(psd * rec)


char __cdecl record_has_memory_source(psd *rec)

{
  byte kind;
  bool rc;
  psd_op op;
  
  op = rec->op;
  if (((((op == OP_CASEJMP) || (op == OP_CTBL)) || (op == OP_CENT)) ||
      ((op == OP_LINE || (op == OP_BBGN)))) ||
     (((op == OP_BEND || (op == OP_NON_10)) || ((OP_BEND < op && (op < OP_NON_1C)))))) {
    rc = false;
  }
  else {
    if ((op == OP_MOVA) || (op == OP_MOVA_LC)) {
      return '\0';
    }
    rc = op == OP_NON_2C;
    if ((rec->ea1 != (ea *)0x0) &&
       (((kind = rec->ea1->type & 0x1f, 1 < kind && (kind < 5)) || ((7 < kind && (kind < 0xd)))))) {
      return '\x01';
    }
  }
  return rc;
}



