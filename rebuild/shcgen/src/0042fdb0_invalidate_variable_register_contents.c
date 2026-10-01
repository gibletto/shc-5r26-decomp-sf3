#include "decls.h"
#include "imports.h"

// entry: 0042fdb0
// name : invalidate_variable_register_contents
// size : 197
// sig  : void invalidate_variable_register_contents(uint mask)


int __cdecl invalidate_variable_register_contents(uint mask)

{
  short i;
  short bit;
  uint pending;
  
  bit = 1;
  pending = mask & 0xf;
  for (i = 0; (pending != 0 && (i < 4)); i = i + 1) {
    if ((((int)bit & pending) != 0) &&
       (((g_gpr_contents[i].flags & 0x40) == 0 && ((g_gpr_contents[i].type & 0xe0) != 0x80)))) {
      g_gpr_contents[i].value = 0;
      g_gpr_contents[i].flags = '\0';
      pending = pending ^ (int)bit;
    }
    bit = bit * 2;
  }
  bit = 1;
  pending = (mask & 0xf0000) >> 0x10;
  for (i = 0; (pending != 0 && (i < 4)); i = i + 1) {
    if ((((int)bit & pending) != 0) &&
       (((g_fpr_contents[i].flags & 0x40) == 0 && ((g_fpr_contents[i].type & 0xe0) != 0x80)))) {
      pending = pending ^ (int)bit;
      g_fpr_contents[i].value = 0;
      g_fpr_contents[i].flags = '\0';
    }
    bit = bit * 2;
  }
  return;
}



