#include "decls.h"
#include "imports.h"

// entry: 00403c60
// name : cse_record_leaf_definition
// size : 74
// sig  : void cse_record_leaf_definition(il_node * node)


int __cdecl cse_record_leaf_definition(il_node *node)

{
  undefined4 *def_entry;
  ushort leafno;
  ushort sign;
  
  def_entry = pool_alloc(8);
  if (def_entry == (undefined4 *)0x0) {
    cse_abort_out_of_memory();
  }
  *(short *)(def_entry + 1) = node->nleaf;
  leafno = node->nleaf;
  sign = (short)leafno >> 0xf;
  *def_entry = (&g_leaf_def_hash)[(short)(((leafno ^ sign) - sign & 0x7f ^ sign) - sign)];
  (&g_leaf_def_hash)[(short)(((leafno ^ sign) - sign & 0x7f ^ sign) - sign)] = def_entry;
  *(undefined2 *)((int)def_entry + 6) = 1;
  return;
}



