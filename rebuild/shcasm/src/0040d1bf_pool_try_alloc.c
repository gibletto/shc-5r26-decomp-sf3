#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_pool_size_classes
#define g_pool_size_classes (*(alloc_class_table * *)(g_sd + 0x17ac))


// entry: 0040d1bf
// name : pool_try_alloc
// size : 649
// sig  : void * pool_try_alloc(uint size)


int * __cdecl pool_try_alloc(uint size)

{
  unsigned char _frec_18[24];
#define table (*(alloc_class_table * *)(_frec_18 + 0))
#define class_no (*(int *)(_frec_18 + 12))
#define mem (*(void * *)(_frec_18 + 16))
  short size16;
  alloc_class_table *new_table;
  uint sign;
  bool found;
  
  mem = (void *)0x0;
  if ((((int)size < 0x401) && (0 < (int)size)) &&
     (sign = (int)size >> 0x1f, ((size ^ sign) - sign & 3 ^ sign) == sign)) {
    size16 = (short)size;
    if (g_pool_size_classes == (alloc_class_table *)0x0) {
      new_table = stock_malloc(0x108);
      g_pool_size_classes = new_table;
      if (new_table == (alloc_class_table *)0x0) {
        mem = (void *)0x0;
      }
      else {
        new_table->count = 1;
        new_table->next = (alloc_class_table *)0x0;
        new_table->cls[0].size = size16;
        new_table->cls[0].chunks = (alloc_chunk *)0x0;
        mem = alloc_from_pool_chunks(&new_table->cls[0].chunks,size);
      }
    }
    else {
      found = false;
      for (table = g_pool_size_classes; table != (alloc_class_table *)0x0; table = table->next) {
        for (class_no = 0; class_no < table->count; class_no = class_no + 1) {
          if ((int)table->cls[class_no].size == size) {
            found = true;
            break;
          }
        }
        if (found) break;
      }
      if (!found) {
        for (table = g_pool_size_classes; table->next != (alloc_class_table *)0x0;
            table = table->next) {
        }
        if (table->count < 0x20) {
          class_no = (int)table->count;
          table->count = table->count + 1;
          table->cls[class_no].size = size16;
          table->cls[class_no].chunks = (alloc_chunk *)0x0;
        }
        else {
          new_table = stock_malloc(0x108);
          if (new_table == (alloc_class_table *)0x0) {
            table = (alloc_class_table *)0x0;
          }
          else {
            table->next = new_table;
            new_table->count = 1;
            new_table->next = (alloc_class_table *)0x0;
            class_no = 0;
            new_table->cls[0].size = size16;
            new_table->cls[0].chunks = (alloc_chunk *)0x0;
            table = new_table;
          }
        }
      }
      if (table == (alloc_class_table *)0x0) {
        mem = (void *)0x0;
      }
      else {
        mem = alloc_from_pool_chunks(&table->cls[class_no].chunks,size);
      }
    }
  }
  if (mem != (void *)0x0) {
    for (class_no = 0; class_no < (int)size; class_no = class_no + 1) {
      *(undefined1 *)(class_no + (int)mem) = 0;
    }
  }
  return mem;
#undef table
#undef class_no
#undef mem
}



