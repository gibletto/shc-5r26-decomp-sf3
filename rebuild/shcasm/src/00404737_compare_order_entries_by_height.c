#include "decls.h"
#include "imports.h"

// entry: 00404737
// name : compare_order_entries_by_height
// size : 89
// sig  : int compare_order_entries_by_height(superscalar_order_slot * a, superscalar_order_slot * b)


int __cdecl compare_order_entries_by_height(superscalar_order_slot *a,superscalar_order_slot *b)

{
  int result;
  
  if (b->path_length == a->path_length) {
    result = 0;
  }
  else if (b->path_length < a->path_length) {
    result = -1;
  }
  else {
    result = 1;
  }
  return result;
}



