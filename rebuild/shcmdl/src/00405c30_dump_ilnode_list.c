#include "decls.h"
#include "imports.h"

// entry: 00405c30
// name : dump_ilnode_list
// size : 45
// sig  : void dump_ilnode_list(node_list * list)


int __cdecl dump_ilnode_list(node_list *list)

{
  for (; list != (node_list *)0x0; list = list->next) {
    FID_conflict__wprintf(&g_str_percent_s_comma,(&g_op_names_upper)[list->node->op]);
  }
  return;
}



