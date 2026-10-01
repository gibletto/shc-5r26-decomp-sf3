#include "decls.h"
#include "imports.h"

// entry: 00403f90
// name : cse_single_definition_status
// size : 125
// sig  : short cse_single_definition_status(il_node * node)


short __cdecl cse_single_definition_status(il_node *node)

{
  int *def_entry;
  short status;
  il_node *child;
  ushort leafno;
  ushort sign;
  
  status = 0;
  if (node->op == IL_ID) {
    leafno = node->nleaf;
    sign = (short)leafno >> 0xf;
    def_entry = (int *)(&g_leaf_def_hash)[(short)(((leafno ^ sign) - sign & 0x7f ^ sign) - sign)];
    if (def_entry != (int *)0x0) {
      do {
        if (*(ushort *)(def_entry + 1) == leafno) {
          return *(short *)((int)def_entry + 6);
        }
        def_entry = (int *)*def_entry;
      } while (def_entry != (int *)0x0);
      return 0;
    }
  }
  else {
    if (node->op == IL_CONST) {
      return 1;
    }
    child = node->child;
    while ((child != (il_node *)0x0 && (status = cse_single_definition_status(child), status == 1)))
    {
      child = child->next;
    }
  }
  return status;
}



