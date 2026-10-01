#include "decls.h"
#include "imports.h"

// entry: 00403b30
// name : cse_join_value_class
// size : 83
// sig  : void cse_join_value_class(il_node * head, il_node * node)


int __cdecl cse_join_value_class(il_node *head,il_node *node)

{
  byte type_class;
  ushort value_no;
  
  node->cse_head = head;
  node->cse_next = head->cse_next;
  head->cse_next = node;
  node->refcnt = 0;
  value_no = head->pp;
  if (head->pp == 0) {
    if (node->cse_next == (il_node *)0x0) {
      g_value_number = g_value_number + 1;
      value_no = g_value_number;
    }
    else {
      value_no = node->cse_next->pp;
    }
  }
  node->pp = value_no;
  type_class = head->type & 0xf0;
  if ((type_class != 0x60) && (type_class != 0x70)) {
    head->refcnt = head->refcnt + 1;
  }
  return;
}



