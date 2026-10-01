#include "decls.h"
#include "imports.h"

// entry: 00408a80
// name : dump_constant_value
// size : 151
// sig  : void dump_constant_value(il_node * node)


int __cdecl dump_constant_value(il_node *node)

{
  byte type_class;
  
  type_class = node->type;
  if ((type_class & 0xe0) == 0) {
    if ((type_class & 4) != 0) {
      FID_conflict__wprintf(s_val__u__00434a64,node->val);
      return;
    }
    FID_conflict__wprintf(s_val__d__00434a58,node->val);
    return;
  }
  if ((type_class & 0xe0) != 0x20) {
    if ((type_class & 0xe0) == 0x40) {
      FID_conflict__wprintf(s_tend__d_offs__d_00434a44,node->val2,node->val);
    }
    return;
  }
  type_class = type_class & 0x18;
  if (type_class != 8) {
    if (type_class == 0x10) {
      dump_value_bytes((uchar *)&node->val,8);
      return;
    }
    if (type_class != 0x18) {
      return;
    }
    dump_value_bytes((uchar *)&node->val,0xc);
    return;
  }
  dump_value_bytes((uchar *)&node->val,4);
  return;
}



