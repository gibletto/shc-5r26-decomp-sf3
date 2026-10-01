#include "decls.h"
#include "imports.h"

// entry: 0040479a
// name : compare_order_entries_by_index
// size : 97
// sig  : int compare_order_entries_by_index(superscalar_order_slot * a, superscalar_order_slot * b)


int __cdecl compare_order_entries_by_index(superscalar_order_slot *a,superscalar_order_slot *b)

{
  int result;
  
  if (b->entry == a->entry) {
    result = 0;
  }
  else if ((char)a->entry < (char)b->entry) {
    result = -1;
  }
  else {
    result = 1;
  }
  return result;
}



