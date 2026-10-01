#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_alloc_size_classes
#define g_alloc_size_classes (*(short * *)(g_sd + 0x17b0))


// entry: 00406830
// name : alloc_zeroed
// size : 392
// sig  : void * alloc_zeroed(uint size)


int * __cdecl alloc_zeroed(uint size)

{
  short *psVar1;
  alloc_chunk **head;
  uint uVar2;
  int slot;
  short short_size;
  short *block;
  undefined4 *fill;
  undefined4 *mem;
  short class_count;
  bool found;
  int next_link;
  
  found = false;
  mem = (undefined4 *)0x0;
  if (((0x400 < (int)size) || ((int)size < 1)) ||
     (uVar2 = (int)size >> 0x1f, ((size ^ uVar2) - uVar2 & 3 ^ uVar2) != uVar2)) goto LAB_00406976;
  short_size = (short)size;
  block = g_alloc_size_classes;
  if (g_alloc_size_classes == (short *)0x0) {
    block = stock_malloc(0x108);
    g_alloc_size_classes = block;
    if (block == (short *)0x0) goto LAB_00406961;
    *block = 1;
    head = (alloc_chunk **)(block + 6);
    block[2] = 0;
    block[3] = 0;
    block[4] = short_size;
    *head = (alloc_chunk *)0x0;
  }
  else {
    do {
      slot = 0;
      psVar1 = block;
      if (0 < *block) {
        do {
          if ((int)psVar1[4] == size) {
            found = true;
            break;
          }
          slot = slot + 1;
          psVar1 = psVar1 + 4;
        } while (slot < *block);
      }
    } while ((!found) && (block = *(short **)(block + 2), block != (short *)0x0));
    if (!found) {
      next_link = *(int *)(g_alloc_size_classes + 2);
      block = g_alloc_size_classes;
      while (next_link != 0) {
        block = *(short **)(block + 2);
        next_link = *(int *)(block + 2);
      }
      class_count = *block;
      if (class_count < 0x20) {
        slot = (int)class_count;
        *block = class_count + 1;
        block[slot * 4 + 4] = short_size;
        (block + slot * 4 + 6)[0] = 0;
        (block + slot * 4 + 6)[1] = 0;
      }
      else {
        psVar1 = stock_malloc(0x108);
        if (psVar1 == (short *)0x0) {
          block = (short *)0x0;
        }
        else {
          slot = 0;
          *(short **)(block + 2) = psVar1;
          *psVar1 = 1;
          psVar1[2] = 0;
          psVar1[3] = 0;
          psVar1[4] = short_size;
          psVar1[6] = 0;
          psVar1[7] = 0;
          block = psVar1;
        }
      }
    }
    if (block == (short *)0x0) {
LAB_00406961:
      report_compiler_message(0,0,0xbcd,(char *)0x0);
      goto LAB_00406976;
    }
    head = (alloc_chunk **)(block + slot * 4 + 6);
  }
  mem = alloc_from_chunks(head,size);
LAB_00406976:
  if (mem == (undefined4 *)0x0) {
    report_compiler_message(0,0,0xbcd,(char *)0x0);
  }
  else if (0 < (int)size) {
    fill = mem;
    for (uVar2 = size >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *fill = 0;
      fill = fill + 1;
    }
    for (uVar2 = size & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)fill = 0;
      fill = (undefined4 *)((int)fill + 1);
    }
  }
  return mem;
}



