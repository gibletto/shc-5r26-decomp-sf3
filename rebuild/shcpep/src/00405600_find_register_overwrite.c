#include "decls.h"
#include "imports.h"

// entry: 00405600
// name : find_register_overwrite
// size : 200
// sig  : psd * find_register_overwrite(code_node * node, psd * start, uchar reg, char call_mode, char * in_block)


psd * __cdecl
find_register_overwrite(code_node *node,psd *start,uchar reg,char call_mode,char *in_block)

{
  uchar changed;
  char effect;
  psd *overwrite;
  psd_op op;
  
  if (in_block != (char *)0x0) {
    *in_block = '\x01';
  }
  if (start != (psd *)0x0) {
    while( true ) {
      if (start->op == OP_TRAPA) {
        return (psd *)0x0;
      }
      changed = record_changes_register(start,reg);
      if (changed != '\0') break;
      op = start->op;
      if ((((op == OP_CALL) || (op == OP_JSR)) || (op == OP_BSR)) || (op == OP_BSRF)) {
        overwrite = psd_overwrites_register(start,reg);
        if (overwrite == (psd *)0x0) {
          return (psd *)0x0;
        }
        effect = call_register_effect(start,reg,(int)call_mode);
        if (effect == '\x01') {
          return start;
        }
        if (effect == -1) {
          return (psd *)0x0;
        }
      }
      start = find_next_psd_record(node,start);
      if (start == (psd *)0x0) {
        if (in_block != (char *)0x0) {
          *in_block = '\0';
        }
        return (psd *)0x0;
      }
    }
    overwrite = psd_overwrites_register(start,reg);
    if (overwrite == (psd *)0x0) {
      return (psd *)0x0;
    }
  }
  return start;
}



