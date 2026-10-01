#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_alloc_size_classes
#define g_alloc_size_classes (*(alloc_class_table * *)(g_sd + 0x1318))


// entry: 00407c30
// name : pool_free
// size : 136
// sig  : void pool_free(void * ptr, int size)


int __cdecl pool_free(void *ptr,int size)

{
  int i;
  alloc_class_table *entry;
  bool found;
  alloc_class_table *table;
  
  found = false;
  table = g_alloc_size_classes;
  do {
    if (table == (alloc_class_table *)0x0) {
LAB_00407c7a:
      if (!found) {
        report_compiler_message(0,0,0x12e8,(char *)0x0);
        return;
      }
      pool_free_in_chunk_list(&table->cls[i].chunks,ptr,size);
      return;
    }
    i = 0;
    entry = table;
    if (0 < table->count) {
      do {
        if (entry->cls[0].size == size) {
          found = true;
          goto LAB_00407c7a;
        }
        i = i + 1;
        entry = (alloc_class_table *)entry->cls;
      } while (i < table->count);
    }
    table = table->next;
  } while( true );
}



