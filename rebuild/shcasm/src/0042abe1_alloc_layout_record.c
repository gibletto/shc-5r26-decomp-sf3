#include "decls.h"
#include "imports.h"

// entry: 0042abe1
// name : alloc_layout_record
// size : 86
// sig  : layout_record * alloc_layout_record(void)


layout_record * alloc_layout_record(void)

{
  layout_record *new_item;
  int resolved;
  
  while (new_item = stock_calloc(1,0x20), new_item == (layout_record *)0x0) {
    resolved = resolve_next_pending_layout_record();
    if (resolved == 0) {
      report_message_at_source_line(0,0,0xbcd,(char *)0x0);
    }
  }
  return new_item;
}



