#include "decls.h"
#include "imports.h"

// entry: 0041d890
// name : cse_join_class
// size : 83
// sig  : void cse_join_class(il_node * head, il_node * node)


int __cdecl cse_join_class(il_node *head,il_node *node)

{
  byte kind;
  ushort vn;
  
  node->cse_head = head;
  node->cse_next = head->cse_next;
  head->cse_next = node;
  node->refcnt = 0;
  vn = head->pp;
  if (head->pp == 0) {
    if (node->cse_next == (il_node *)0x0) {
      g_value_number = g_value_number + 1;
      vn = g_value_number;
    }
    else {
      vn = node->cse_next->pp;
    }
  }
  node->pp = vn;
  kind = head->type & 0xf0;
  if ((kind != 0x60) && (kind != 0x70)) {
    head->refcnt = head->refcnt + 1;
  }
  return;
}



