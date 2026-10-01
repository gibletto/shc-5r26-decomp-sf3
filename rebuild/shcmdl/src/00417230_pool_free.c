#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_pool_classes
#define g_pool_classes (*(pool_class * *)(g_sd + 0x39f4))


// entry: 00417230
// name : pool_free
// size : 53
// sig  : void pool_free(void * block, int size)


int __cdecl pool_free(void *block,int size)

{
  pool_class *cls;
  
  for (cls = g_pool_classes; (cls != (pool_class *)0x0 && (cls->size != size)); cls = cls->next) {
  }
  if (cls != (pool_class *)0x0) {
    *(void **)block = cls->free_list;
    cls->free_list = block;
    g_pool_bytes_in_use = g_pool_bytes_in_use - size;
  }
  return;
}



