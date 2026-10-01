#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_pool_classes
#define g_pool_classes (*(pool_class * *)(g_sd + 0x39f4))


// entry: 004171d0
// name : pool_release_free_lists
// size : 53
// sig  : void pool_release_free_lists(void)


int __cdecl pool_release_free_lists(void)

{
  undefined4 *ptr;
  pool_class *cls;
  undefined4 *next;
  
  for (cls = g_pool_classes; cls != (pool_class *)0x0; cls = cls->next) {
    ptr = cls->free_list;
    while (ptr != (undefined4 *)0x0) {
      next = (undefined4 *)*ptr;
      stock_free(ptr);
      ptr = next;
    }
    cls->free_list = (void *)0x0;
  }
  return;
}



