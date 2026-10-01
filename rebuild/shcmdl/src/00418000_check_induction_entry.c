#include "decls.h"
#include "imports.h"

// entry: 00418000
// name : check_induction_entry
// size : 60
// sig  : int __cdecl check_induction_entry(iv_entry *entry)


int __cdecl check_induction_entry(iv_entry *entry)

{
  bool no_plain_use;
  uint result;
  iv_use *use;
  
  result = 0;
  use = entry->uses;
  if ((use != (iv_use *)0x0) && (entry->step != (il_node *)0x0)) {
    no_plain_use = true;
    for (; use != (iv_use *)0x0; use = use->next) {
      if (use->expr == use->id) {
        no_plain_use = false;
        break;
      }
    }
    result = 0;
    if (no_plain_use) {
      result = check_loop_test_replacement(entry);
    }
  }
  return result;
}
