#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_pool_classes
#define g_pool_classes (*(pool_class * *)(g_sd + 0x39f4))


// entry: 00417120
// name : pool_alloc
// size : 174
// sig  : void * pool_alloc(uint size)


int * __cdecl pool_alloc(uint size)

{
  pool_class *cls;
  char *dst;
  pool_class *new_head;
  pool_class *prev;
  pool_class *succ;
  
  cls = g_pool_classes;
  prev = g_pool_classes;
  while ((succ = cls, succ != (pool_class *)0x0 && ((int)succ->size <= (int)size))) {
    prev = succ;
    cls = succ->next;
  }
  if (((prev == (pool_class *)0x0) ||
      (cls = prev, new_head = g_pool_classes, (int)prev->size != size)) &&
     (cls = stock_malloc(0xc), new_head = g_pool_classes, cls != (pool_class *)0x0)) {
    cls->size = (short)size;
    cls->next = succ;
    cls->free_list = (void *)0x0;
    new_head = cls;
    if (succ != g_pool_classes) {
      prev->next = cls;
      new_head = g_pool_classes;
    }
  }
  g_pool_classes = new_head;
  if (cls == (pool_class *)0x0) {
    return (void *)0x0;
  }
  dst = cls->free_list;
  if (dst == (char *)0x0) {
    dst = stock_malloc(size);
    if (dst == (char *)0x0) {
      pool_release_free_lists();
      dst = stock_malloc(size);
      goto LAB_004171b4;
    }
  }
  else {
    cls->free_list = *(void **)dst;
LAB_004171b4:
    if (dst == (char *)0x0) goto LAB_004171c2;
  }
  clear_bytes(dst,size);
LAB_004171c2:
  g_pool_bytes_in_use = g_pool_bytes_in_use + size;
  return dst;
}



