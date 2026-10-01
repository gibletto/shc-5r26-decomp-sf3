#include "decls.h"
#include "imports.h"

// entry: 00403cb0
// name : cse_count_leaf_redefinition
// size : 55
// sig  : void cse_count_leaf_redefinition(il_node * node)


int __cdecl cse_count_leaf_redefinition(il_node *node)

{
  int *def_entry;
  ushort leafno;
  ushort sign;
  
  leafno = node->nleaf;
  sign = (short)leafno >> 0xf;
  def_entry = (int *)(&g_leaf_def_hash)[(short)(((leafno ^ sign) - sign & 0x7f ^ sign) - sign)];
  if (def_entry != (int *)0x0) {
    while (*(ushort *)(def_entry + 1) != leafno) {
      def_entry = (int *)*def_entry;
      if (def_entry == (int *)0x0) {
        return;
      }
    }
    *(short *)((int)def_entry + 6) = *(short *)((int)def_entry + 6) + 1;
  }
  return;
}



