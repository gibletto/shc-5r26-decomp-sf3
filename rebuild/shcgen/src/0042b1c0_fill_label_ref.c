#include "decls.h"
#include "imports.h"

// entry: 0042b1c0
// name : fill_label_ref
// size : 29
// sig  : void fill_label_ref(label_ref * ref, short labno1, short labno2)


int __cdecl fill_label_ref(label_ref *ref,short labno1,short labno2)

{
  ref->next = (label_ref *)0x0;
  ref->labno1 = labno1;
  ref->labno2 = labno2;
  return;
}



