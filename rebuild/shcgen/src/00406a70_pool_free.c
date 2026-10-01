#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_alloc_size_classes
#define g_alloc_size_classes (*(short * *)(g_sd + 0x17b0))


// entry: 00406a70
// name : pool_free
// size : 136
// sig  : void pool_free(void * ptr, int size)


int __cdecl pool_free(void *ptr,int size)

{
  int slot;
  short *block;
  short *class_entry;
  bool found;
  
  found = false;
  block = g_alloc_size_classes;
  do {
    if (block == (short *)0x0) {
LAB_00406aba:
      if (!found) {
        report_compiler_message(0,0,0x12e8,(char *)0x0);
        return;
      }
      pool_free_in_chunk_list((alloc_chunk **)(block + slot * 4 + 6),ptr,size);
      return;
    }
    slot = 0;
    class_entry = block;
    if (0 < *block) {
      do {
        if (class_entry[4] == size) {
          found = true;
          goto LAB_00406aba;
        }
        slot = slot + 1;
        class_entry = class_entry + 4;
      } while (slot < *block);
    }
    block = *(short **)(block + 2);
  } while( true );
}



