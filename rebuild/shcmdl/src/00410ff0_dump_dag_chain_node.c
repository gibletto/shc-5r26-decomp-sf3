#include "decls.h"
#include "imports.h"

// entry: 00410ff0
// name : dump_dag_chain_node
// size : 79
// sig  : void dump_dag_chain_node(il_node * node)


int __cdecl dump_dag_chain_node(il_node *node)

{
  il_node *sub;
  
  FID_conflict__wprintf
            (s__8X__8d__8X__8X__8X__8d__s_00435464,node,(int)(short)node->pp,node->cmnexp,
             node->refchn,(uint)node->refcnt,node->duptr,(&g_op_names_upper)[(char)node->op]);
  for (sub = node->child; sub != (il_node *)0x0; sub = sub->next) {
    dump_dag_chain_node(sub);
  }
  return;
}



