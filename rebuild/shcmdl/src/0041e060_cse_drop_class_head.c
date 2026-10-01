#include "decls.h"
#include "imports.h"

// entry: 0041e060
// name : cse_drop_class_head
// size : 91
// sig  : il_node * __cdecl cse_drop_class_head(il_node *head)


il_node * __cdecl cse_drop_class_head(il_node *head)

{
  il_node *last;
  il_node *member;
  il_node *next;
  
  next = head;
  do {
    last = next;
    member = head;
    if (last == (il_node *)0x0) break;
    next = last->cse_next;
  } while (last->cse_next != (il_node *)0x0);
  for (; member != (il_node *)0x0; member = member->cse_next) {
    member->cse_head = last;
    if (member->cse_next == last) {
      member->cse_next = (il_node *)0x0;
    }
  }
  last->cse_next = head->cse_next;
  last->cse_head = last;
  last->refcnt = head->refcnt - 1;
  head->cse_next = (il_node *)0x0;
  head->cse_head = (il_node *)0x0;
  head->refcnt = 0;
  return last;
}
