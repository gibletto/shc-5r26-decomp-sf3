#include "decls.h"
#include "imports.h"

// entry: 00409a70
// name : get_record_source_labno
// size : 89
// sig  : short get_record_source_labno(psd * rec)


short __cdecl get_record_source_labno(psd *rec)

{
  short labno;
  psd_op op;
  label_ref *ref;
  
  labno = 0;
  if ((((((rec != (psd *)0x0) && (op = rec->op, op != OP_DUMMY)) && (op != OP_CASEJMP)) &&
       ((op != OP_CTBL && (op != OP_CENT)))) &&
      (((op != OP_LINE && ((op < OP_LABEL || (OP_FLABEL < op)))) && (op != OP_NON_10)))) &&
     (((op != OP_SWBGN && (op != OP_SWEND)) &&
      ((rec->ea1 == (ea *)0x0 ||
       ((ref = rec->ea1->labels, ref == (label_ref *)0x0 || (labno = ref->labno1, labno == 0))))))))
  {
    labno = 0;
  }
  return labno;
}



