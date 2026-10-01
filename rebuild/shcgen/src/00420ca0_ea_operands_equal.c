#include "decls.h"
#include "imports.h"

// entry: 00420ca0
// name : ea_operands_equal
// size : 104
// sig  : short ea_operands_equal(ea * a, ea * b)


short __cdecl ea_operands_equal(ea *a,ea *b)

{
  short labels_equal;
  short equal;
  
  equal = 0;
  if ((a != (ea *)0x0) && (b != (ea *)0x0)) {
    if (((b->type == a->type) &&
        (((b->base == a->base && (b->index == a->index)) && (b->misc == a->misc)))) &&
       (((b->disp == a->disp && ((a->type & 0x80) == 0)) && ((b->type & 0x80) == 0)))) {
      labels_equal = label_lists_equal(a->labels,b->labels);
      if (labels_equal != 0) {
        equal = 1;
      }
    }
  }
  return equal;
}



