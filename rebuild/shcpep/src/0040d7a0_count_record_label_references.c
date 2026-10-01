#include "decls.h"
#include "imports.h"

// entry: 0040d7a0
// name : count_record_label_references
// size : 151
// sig  : void count_record_label_references(psd * rec)


int __cdecl count_record_label_references(psd *rec)

{
  label_ref *lref;
  psd_op op;
  
  op = rec->op;
  if (((op == OP_EXPORT) || (op == OP_INPORT)) || ((OP_BEND < op && (op < OP_NON_1C)))) {
    count_label_reference((int)*(short *)&rec->ea1);
  }
  else if ((rec->ea1 != (ea *)0x0) && (lref = rec->ea1->labels, lref != (label_ref *)0x0)) {
    do {
      count_label_reference((int)lref->labno1);
      if (lref->labno2 != 0) {
        count_label_reference((int)lref->labno2);
      }
      lref = lref->next;
    } while (lref != (label_ref *)0x0);
    return;
  }
  return;
}



