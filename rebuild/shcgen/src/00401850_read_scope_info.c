#include "decls.h"
#include "imports.h"

// entry: 00401850
// name : read_scope_info
// size : 23
// sig  : void read_scope_info(sym_entry * sym)


int __cdecl read_scope_info(sym_entry *sym)

{
  void *list;
  
  list = read_scope_child_list();
  sym->size = (int)list;
  list = read_scope_member_list();
  sym->list_10 = list;
  return;
}



