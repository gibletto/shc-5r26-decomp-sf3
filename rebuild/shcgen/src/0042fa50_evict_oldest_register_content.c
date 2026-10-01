#include "decls.h"
#include "imports.h"

// entry: 0042fa50
// name : evict_oldest_register_content
// size : 157
// sig  : void evict_oldest_register_content(reg_content * contents)


int __cdecl evict_oldest_register_content(reg_content *contents)

{
  ushort oldest;
  ushort i;
  int used;
  
  oldest = 0xffff;
  i = 3;
  used = 0;
  do {
    if (((contents[(short)i].flags & 0x40) != 0) || (contents[(short)i].value != 0)) {
      if ((oldest == 0xffff) || (contents[(short)i].stamp < contents[(short)oldest].stamp)) {
        oldest = i;
      }
      used = used + 1;
    }
    i = i - 1;
  } while (-1 < (short)i);
  if (used == 2) {
    if (contents == g_fpr_contents) {
      oldest = (ushort)(byte)((char)oldest + 0x10);
    }
    invalidate_register_contents(1 << ((byte)oldest & 0x1f));
    return;
  }
  if (2 < used) {
    report_codegen_message(0x123b,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  }
  return;
}



