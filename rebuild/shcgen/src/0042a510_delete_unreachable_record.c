#include "decls.h"
#include "imports.h"

// entry: 0042a510
// name : delete_unreachable_record
// size : 160
// sig  : void delete_unreachable_record(psd * rec)


int __cdecl delete_unreachable_record(psd *rec)

{
  char reach_class;
  
  reach_class = (&g_op_reachability_class)[rec->op];
  if (reach_class == '\0') {
    report_compiler_message(0,0,0x12ec,(char *)0x0);
  }
  if (g_in_unreachable_code == 1) {
    if (reach_class == '\x02') {
      g_in_unreachable_code = 0;
      return;
    }
    if (reach_class != '\x01') {
      if (rec->ea1 != (ea *)0x0) {
        free_ea(rec->ea1);
      }
      if (rec->ea2 != (ea *)0x0) {
        free_ea(rec->ea2);
      }
      rec->op = OP_DUMMY;
      rec->flg = '\0';
      rec->filno = 0;
      rec->misc = '\0';
      rec->linno = 0;
      rec->tmp = '\0';
      rec->sptravel = 0;
      rec->expno = 0;
      rec->ea2 = (ea *)0x0;
      rec->ea1 = (ea *)0x0;
      return;
    }
  }
  else if (reach_class == '\x03') {
    g_in_unreachable_code = 1;
  }
  return;
}



