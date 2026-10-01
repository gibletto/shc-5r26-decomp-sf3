#include "decls.h"
#include "imports.h"

// entry: 004182c0
// name : free_label_ref_list
// size : 33
// sig  : void free_label_ref_list(label_ref * list)


int __cdecl free_label_ref_list(label_ref *list)

{
  if (list != (label_ref *)0x0) {
    free_label_ref_list(list->next);
    pool_free(list,8);
  }
  return;
}



