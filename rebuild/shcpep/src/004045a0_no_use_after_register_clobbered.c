#include "decls.h"
#include "imports.h"

// entry: 004045a0
// name : no_use_after_register_clobbered
// size : 230
// sig  : char no_use_after_register_clobbered(code_node * node, psd * start, uchar used_reg, uchar clobbered_reg)


char __cdecl no_use_after_register_clobbered(code_node *node,psd *start,uchar used_reg,uchar clobbered_reg)

{
  uchar changed;
  char result;
  psd *rec;
  bool used;
  
  used = false;
  for (; start != (psd *)0x0; start = find_next_psd_record(node,start)) {
    changed = record_changes_register(start,clobbered_reg);
    if ((changed != '\0') || (result = call_register_effect(start,clobbered_reg,0), result != '\0'))
    {
      for (rec = find_next_psd_record(node,start); rec != (psd *)0x0;
          rec = find_next_psd_record(node,rec)) {
        if (((rec->ea1 != (ea *)0x0) &&
            (result = operand_uses_register(rec,used_reg,'\x01'), result != '\0')) ||
           ((rec->ea2 != (ea *)0x0 &&
            (result = operand_uses_register(rec,used_reg,'\x02'), result != '\0')))) {
          used = true;
          break;
        }
      }
    }
    if (used) break;
  }
  return !used;
}



