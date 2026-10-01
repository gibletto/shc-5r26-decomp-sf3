#include "decls.h"
#include "imports.h"

// entry: 004059d0
// name : register_referenced_between
// size : 172
// sig  : uchar register_referenced_between(code_node * node, psd * from, psd * to, uchar reg)


uchar __cdecl register_referenced_between(code_node *node,psd *from,psd *to,uchar reg)

{
  byte used;
  byte used2;
  code_node *from_node;
  psd *rec;
  
  used = 0;
  from_node = find_node_containing_record(node,from);
  rec = find_next_psd_record(from_node,from);
  while( true ) {
    if (rec == to) {
      if ((((rec != (psd *)0x0) && (rec == to)) && (rec->ea1 != (ea *)0x0)) &&
         ((rec->ea1->type & 0x1f) != 7)) {
        used = operand_uses_register(rec,reg,'\x01');
      }
      return used;
    }
    if (rec->ea1 != (ea *)0x0) {
      used = operand_uses_register(rec,reg,'\x01');
    }
    if (rec->ea2 != (ea *)0x0) {
      used2 = operand_uses_register(rec,reg,'\x02');
      used = used | used2;
    }
    if (used != 0) break;
    rec = find_next_psd_record(from_node,rec);
  }
  return used;
}



