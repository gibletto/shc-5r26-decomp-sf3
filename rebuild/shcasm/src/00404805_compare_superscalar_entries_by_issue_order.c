#include "decls.h"
#include "imports.h"

// entry: 00404805
// name : compare_superscalar_entries_by_issue_order
// size : 97
// sig  : int compare_superscalar_entries_by_issue_order(superscalar_entry * a, superscalar_entry * b)


int __cdecl compare_superscalar_entries_by_issue_order(superscalar_entry *a,superscalar_entry *b)

{
  int result;
  
  if (b->order == a->order) {
    result = 0;
  }
  else if ((char)a->order < (char)b->order) {
    result = -1;
  }
  else {
    result = 1;
  }
  return result;
}



