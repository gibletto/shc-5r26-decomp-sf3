#include "decls.h"
#include "imports.h"

// entry: 00408a40
// name : dump_qualify_fields
// size : 52
// sig  : void dump_qualify_fields(il_node * node)


int __cdecl dump_qualify_fields(il_node *node)

{
  FID_conflict__wprintf(s_ofst__d_00434a38,node->val2);
  if (node->op == IL_B_QUALIFY) {
    FID_conflict__wprintf(s_boff__d_bsiz__d_00434a24,(int)(char)node->boff,(int)(char)node->bsiz);
  }
  return;
}



