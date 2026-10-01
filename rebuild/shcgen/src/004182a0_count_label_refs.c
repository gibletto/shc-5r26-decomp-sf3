#include "decls.h"
#include "imports.h"

// entry: 004182a0
// name : count_label_refs
// size : 18
// sig  : int count_label_refs(label_ref * list)


int __cdecl count_label_refs(label_ref *list)

{
  int count;
  
  count = 0;
  for (; list != (label_ref *)0x0; list = list->next) {
    count = count + 1;
  }
  return count;
}



