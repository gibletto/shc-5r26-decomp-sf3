#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_alloc_size_classes
#define g_alloc_size_classes (*(alloc_class_table * *)(g_sd + 0x1318))


// entry: 00407890
// name : alloc_zeroed
// size : 392
// sig  : void * alloc_zeroed(uint size)


int * __cdecl alloc_zeroed(uint size)

{
  alloc_class_table *paVar1;
  alloc_chunk **head;
  uint uVar2;
  int i;
  short class_size;
  alloc_class_table *table;
  undefined4 *dst;
  undefined4 *new_block;
  bool found;
  short used_count;
  
  found = false;
  new_block = (undefined4 *)0x0;
  if (((0x400 < (int)size) || ((int)size < 1)) ||
     (uVar2 = (int)size >> 0x1f, ((size ^ uVar2) - uVar2 & 3 ^ uVar2) != uVar2)) goto LAB_004079d6;
  class_size = (short)size;
  table = g_alloc_size_classes;
  if (g_alloc_size_classes == (alloc_class_table *)0x0) {
    table = stock_malloc(0x108);
    g_alloc_size_classes = table;
    if (table == (alloc_class_table *)0x0) goto LAB_004079c1;
    table->count = 1;
    head = &table->cls[0].chunks;
    table->next = (alloc_class_table *)0x0;
    table->cls[0].size = class_size;
    *head = (alloc_chunk *)0x0;
  }
  else {
    do {
      i = 0;
      paVar1 = table;
      if (0 < table->count) {
        do {
          if ((int)paVar1->cls[0].size == size) {
            found = true;
            break;
          }
          i = i + 1;
          paVar1 = (alloc_class_table *)paVar1->cls;
        } while (i < table->count);
      }
    } while ((!found) && (table = table->next, table != (alloc_class_table *)0x0));
    if (!found) {
      paVar1 = g_alloc_size_classes->next;
      table = g_alloc_size_classes;
      while (paVar1 != (alloc_class_table *)0x0) {
        table = table->next;
        paVar1 = table->next;
      }
      used_count = table->count;
      if (used_count < 0x20) {
        i = (int)used_count;
        table->count = used_count + 1;
        table->cls[i].size = class_size;
        table->cls[i].chunks = (alloc_chunk *)0x0;
      }
      else {
        paVar1 = stock_malloc(0x108);
        if (paVar1 == (alloc_class_table *)0x0) {
          table = (alloc_class_table *)0x0;
        }
        else {
          i = 0;
          table->next = paVar1;
          paVar1->count = 1;
          paVar1->next = (alloc_class_table *)0x0;
          paVar1->cls[0].size = class_size;
          paVar1->cls[0].chunks = (alloc_chunk *)0x0;
          table = paVar1;
        }
      }
    }
    if (table == (alloc_class_table *)0x0) {
LAB_004079c1:
      report_compiler_message(0,0,0xbcd,(char *)0x0);
      goto LAB_004079d6;
    }
    head = &table->cls[i].chunks;
  }
  new_block = alloc_from_chunks(head,size);
LAB_004079d6:
  if (new_block == (undefined4 *)0x0) {
    report_compiler_message(0,0,0xbcd,(char *)0x0);
  }
  else if (0 < (int)size) {
    dst = new_block;
    for (uVar2 = size >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *dst = 0;
      dst = dst + 1;
    }
    for (uVar2 = size & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)dst = 0;
      dst = (undefined4 *)((int)dst + 1);
    }
  }
  return new_block;
}



