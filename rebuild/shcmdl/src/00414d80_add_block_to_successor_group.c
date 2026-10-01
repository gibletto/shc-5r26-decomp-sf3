#include "decls.h"
#include "imports.h"

// entry: 00414d80
// name : add_block_to_successor_group
// size : 164
// sig  : void add_block_to_successor_group(bblock * block, bblock * succ)


int __cdecl add_block_to_successor_group(bblock *block,bblock *succ)

{
  undefined4 *entry;
  undefined4 *bucket;
  undefined4 *cur;
  undefined4 *next;
  undefined4 *prev;
  ushort sign;
  
  entry = pool_alloc(0x10);
  if (entry == (undefined4 *)0x0) {
    free_merge_tables_and_abort();
  }
  sign = succ->number >> 0xf;
  bucket = &g_successor_groups + (short)(((succ->number ^ sign) - sign & 0xf ^ sign) - sign);
  entry[2] = block;
  *(short *)(entry + 3) = succ->number;
  prev = (undefined4 *)*bucket;
  if (prev == (undefined4 *)0x0) {
    *entry = 0;
    *bucket = entry;
  }
  else {
    next = prev;
    if (*(short *)(prev + 3) == succ->number) {
      entry[1] = prev;
      *entry = *(undefined4 *)*bucket;
      *(undefined4 *)*bucket = 0;
      *bucket = entry;
      return;
    }
    while (cur = next, cur != (undefined4 *)0x0) {
      if (*(short *)(cur + 3) == succ->number) {
        entry[1] = cur;
        *entry = *cur;
        *prev = entry;
        *cur = 0;
        break;
      }
      prev = cur;
      next = (undefined4 *)*cur;
    }
    if (cur == (undefined4 *)0x0) {
      *entry = *bucket;
      *bucket = entry;
      return;
    }
  }
  return;
}



