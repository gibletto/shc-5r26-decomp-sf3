#include "decls.h"
#include "imports.h"

// entry: 00430320
// name : restore_register_contents
// size : 191
// sig  : void restore_register_contents(void)


int __cdecl restore_register_contents(void)

{
  label_ref *labels;
  int ix;
  short i;
  
  i = 0;
  do {
    ix = (int)i;
    copy_words((uint *)(g_gpr_contents + ix),(uint *)(ix * 0x10 + g_gpr_contents_stack + 4),4);
    if (((g_gpr_contents[ix].flags & 0x40) != 0) &&
       (g_gpr_contents[ix].u.labels != (label_ref *)0x0)) {
      labels = copy_label_ref_list(g_gpr_contents[ix].u.labels);
      g_gpr_contents[ix].u.labels = labels;
    }
    i = i + 1;
  } while (i < 4);
  i = 0;
  do {
    ix = (int)i;
    copy_words((uint *)(g_fpr_contents + ix),(uint *)(ix * 0x10 + g_fpr_contents_stack + 4),4);
    if (((g_fpr_contents[ix].flags & 0x40) != 0) &&
       (g_fpr_contents[ix].u.labels != (label_ref *)0x0)) {
      labels = copy_label_ref_list(g_fpr_contents[ix].u.labels);
      g_fpr_contents[ix].u.labels = labels;
    }
    i = i + 1;
  } while (i < 4);
  return;
}



