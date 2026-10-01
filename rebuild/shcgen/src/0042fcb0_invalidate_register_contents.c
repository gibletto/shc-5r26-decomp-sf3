#include "decls.h"
#include "imports.h"

// entry: 0042fcb0
// name : invalidate_register_contents
// size : 255
// sig  : void invalidate_register_contents(uint mask)


int __cdecl invalidate_register_contents(uint mask)

{
  short bit;
  uint pending;
  short i;
  
  bit = 1;
  pending = mask & 0xf;
  for (i = 0; (pending != 0 && (i < 4)); i = i + 1) {
    if (((int)bit & pending) != 0) {
      g_gpr_contents[i].value = 0;
      if (((g_gpr_contents[i].flags & 0x40) != 0) &&
         (g_gpr_contents[i].u.labels != (label_ref *)0x0)) {
        free_label_ref_list(g_gpr_contents[i].u.labels);
        g_gpr_contents[i].u.labels = (label_ref *)0x0;
      }
      g_gpr_contents[i].flags = '\0';
      pending = pending ^ (int)bit;
    }
    bit = bit * 2;
  }
  bit = 1;
  pending = (mask & 0xf0000) >> 0x10;
  for (i = 0; (pending != 0 && (i < 4)); i = i + 1) {
    if (((int)bit & pending) != 0) {
      g_fpr_contents[i].value = 0;
      if (((g_fpr_contents[i].flags & 0x40) != 0) &&
         (g_fpr_contents[i].u.labels != (label_ref *)0x0)) {
        free_label_ref_list(g_fpr_contents[i].u.labels);
        g_fpr_contents[i].u.labels = (label_ref *)0x0;
      }
      g_fpr_contents[i].flags = '\0';
      pending = pending ^ (int)bit;
    }
    bit = bit * 2;
  }
  return;
}



