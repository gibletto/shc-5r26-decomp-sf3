#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_pool_size_classes
#define g_pool_size_classes (*(alloc_class_table * *)(g_sd + 0x17ac))


// entry: 0040d5cb
// name : pool_free
// size : 190
// sig  : void __cdecl pool_free(void *ptr,int size)


int __cdecl pool_free(void *ptr,int size)

{
  unsigned char _frec_10[16];
#define table (*(alloc_class_table * *)(_frec_10 + 0))
#define class_no (*(int *)(_frec_10 + 8))
  bool found;
  
  table = g_pool_size_classes;
  found = false;
  do {
    if (table == (alloc_class_table *)0x0) {
LAB_0040d643:
      if (found) {
        free_to_pool_chunks(&table->cls[class_no].chunks,ptr,size);
      }
      else {
        report_message_at_source_line(0,0,0x12e8,(char *)0x0);
      }
      return;
    }
    for (class_no = 0; class_no < table->count; class_no = class_no + 1) {
      if (table->cls[class_no].size == size) {
        found = true;
        goto LAB_0040d643;
      }
    }
    table = table->next;
  } while( true );
#undef table
#undef class_no
}
