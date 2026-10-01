#include "decls.h"
#include "imports.h"

// entry: 0040a380
// name : link_common_chain
// size : 83
// sig  : void link_common_chain(il_node * head, il_node * node)


int __cdecl link_common_chain(il_node *head,il_node *node)

{
  byte type_class;
  ushort value_no;
  
  node->cmnexp = head;
  node->refchn = head->refchn;
  head->refchn = node;
  node->refcnt = 0;
  value_no = head->pp;
  if (head->pp == 0) {
    if (node->refchn == (il_node *)0x0) {
      g_value_number = g_value_number + 1;
      value_no = g_value_number;
    }
    else {
      value_no = node->refchn->pp;
    }
  }
  node->pp = value_no;
  type_class = head->type & 0xf0;
  if ((type_class != 0x60) && (type_class != 0x70)) {
    head->refcnt = head->refcnt + 1;
  }
  return;
}



