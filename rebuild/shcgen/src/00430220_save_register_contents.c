#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_fpr_contents_stack
#define g_fpr_contents_stack (*(int * *)(g_sd + 0x1f998))
#undef g_gpr_contents_stack
#define g_gpr_contents_stack (*(int * *)(g_sd + 0x1fef0))


// entry: 00430220
// name : save_register_contents
// size : 248
// sig  : void save_register_contents(void)


int __cdecl save_register_contents(void)

{
  undefined4 *save_ptr;
  label_ref *labels;
  int ix;
  short i;
  
  i = 0;
  save_ptr = alloc_zeroed(0x44);
  *save_ptr = g_gpr_contents_stack;
  g_gpr_contents_stack = save_ptr;
  do {
    ix = (int)i;
    copy_words(g_gpr_contents_stack + ix * 4 + 1,(uint *)(g_gpr_contents + ix),4);
    if (((g_gpr_contents[ix].flags & 0x40) != 0) &&
       (g_gpr_contents[ix].u.labels != (label_ref *)0x0)) {
      save_ptr = g_gpr_contents_stack + ix * 4 + 2;
      labels = copy_label_ref_list((label_ref *)*save_ptr);
      *save_ptr = labels;
    }
    i = i + 1;
  } while (i < 4);
  i = 0;
  save_ptr = alloc_zeroed(0x44);
  *save_ptr = g_fpr_contents_stack;
  g_fpr_contents_stack = save_ptr;
  do {
    ix = (int)i;
    copy_words(g_fpr_contents_stack + ix * 4 + 1,(uint *)(g_fpr_contents + ix),4);
    if (((g_fpr_contents[ix].flags & 0x40) != 0) &&
       (g_fpr_contents[ix].u.labels != (label_ref *)0x0)) {
      save_ptr = g_fpr_contents_stack + ix * 4 + 2;
      labels = copy_label_ref_list((label_ref *)*save_ptr);
      *save_ptr = labels;
    }
    i = i + 1;
  } while (i < 4);
  return;
}



