#include "decls.h"
#include "imports.h"

// entry: 00420c50
// name : label_lists_equal
// size : 70
// sig  : short label_lists_equal(label_ref * a, label_ref * b)


short __cdecl label_lists_equal(label_ref *a,label_ref *b)

{
  short equal;
  
  equal = 0;
  if ((a == (label_ref *)0x0) || (b == (label_ref *)0x0)) {
    if ((a == (label_ref *)0x0) && (b == (label_ref *)0x0)) {
      equal = 1;
    }
  }
  else if ((b->labno1 == a->labno1) && (b->labno2 == a->labno2)) {
    equal = label_lists_equal(a->next,b->next);
    return equal;
  }
  return equal;
}



