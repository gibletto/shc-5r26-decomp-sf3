#include "decls.h"
#include "imports.h"

// entry: 0041ba90
// name : cut_r0_ranges_at_serials
// size : 65
// sig  : void cut_r0_ranges_at_serials(serial_block * list)


int __cdecl cut_r0_ranges_at_serials(serial_block *list)

{
  serial_block *slot;
  uint i;
  
  do {
    if (list == (serial_block *)0x0) {
      return;
    }
    i = 0;
    slot = list;
    do {
      slot = (serial_block *)slot->serial;
      if (*(uint *)slot == 0) break;
      i = i + 1;
      remove_serial_from_register_ranges(1,*(uint *)slot);
      g_used_gpr_mask = g_used_gpr_mask | 1;
    } while (i < 4);
    list = list->next;
  } while( true );
}



