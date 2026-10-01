#include "decls.h"
#include "imports.h"

// entry: 00422ee9
// name : relax_unconditional_branch_record
// size : 74
// sig  : void __cdecl relax_unconditional_branch_record(layout_record *item,int pass)


int __cdecl relax_unconditional_branch_record(layout_record *item,int pass)

{
  if (pass == 0) {
    item->location = item->location - g_layout_shrink_pass0;
  }
  else {
    item->location = item->location - g_layout_shrink_pass1;
  }
  layout_literal_pool(item,pass);
  return;
}
