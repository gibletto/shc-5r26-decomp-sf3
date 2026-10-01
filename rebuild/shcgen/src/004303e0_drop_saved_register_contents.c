#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_fpr_contents_stack
#define g_fpr_contents_stack (*(int * *)(g_sd + 0x1f998))
#undef g_gpr_contents_stack
#define g_gpr_contents_stack (*(int * *)(g_sd + 0x1fef0))


// entry: 004303e0
// name : drop_saved_register_contents
// size : 165
// sig  : void drop_saved_register_contents(void)


int __cdecl drop_saved_register_contents(void)

{
  short i;
  undefined4 *block;
  
  block = g_gpr_contents_stack;
  i = 0;
  do {
    if (((*(byte *)((int)g_gpr_contents_stack + i * 0x10 + 0xd) & 0x40) != 0) &&
       ((label_ref *)g_gpr_contents_stack[i * 4 + 2] != (label_ref *)0x0)) {
      free_label_ref_list((label_ref *)g_gpr_contents_stack[i * 4 + 2]);
    }
    i = i + 1;
  } while (i < 4);
  i = 0;
  g_gpr_contents_stack = (undefined4 *)*g_gpr_contents_stack;
  pool_free(block,0x44);
  block = g_fpr_contents_stack;
  do {
    if (((*(byte *)((int)g_fpr_contents_stack + i * 0x10 + 0xd) & 0x40) != 0) &&
       ((label_ref *)g_fpr_contents_stack[i * 4 + 2] != (label_ref *)0x0)) {
      free_label_ref_list((label_ref *)g_fpr_contents_stack[i * 4 + 2]);
    }
    i = i + 1;
  } while (i < 4);
  g_fpr_contents_stack = (undefined4 *)*g_fpr_contents_stack;
  pool_free(block,0x44);
  return;
}



