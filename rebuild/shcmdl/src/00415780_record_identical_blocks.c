#include "decls.h"
#include "imports.h"

// entry: 00415780
// name : record_identical_blocks
// size : 164
// sig  : void record_identical_blocks(bblock * a, bblock * b)


int __cdecl record_identical_blocks(bblock *a,bblock *b)

{
  undefined4 *entry;
  uint slot;
  undefined4 *bucket;
  undefined4 *cur;
  undefined4 *next;
  undefined4 *prev;
  
  entry = pool_alloc(0x14);
  if (entry == (undefined4 *)0x0) {
    free_merge_tables_and_abort();
  }
  slot = g_merge_pair_count & 0xf;
  entry[2] = a;
  bucket = &g_identical_block_buckets + slot;
  entry[3] = b;
  entry[4] = g_merge_pair_count;
  prev = (undefined4 *)*bucket;
  if (prev == (undefined4 *)0x0) {
    *entry = 0;
    *bucket = entry;
  }
  else {
    next = prev;
    if (*(short *)prev[2] == a->number) {
      entry[1] = prev;
      *entry = *(undefined4 *)*bucket;
      *(undefined4 *)*bucket = 0;
      *bucket = entry;
      return;
    }
    while (cur = next, cur != (undefined4 *)0x0) {
      if (*(short *)cur[2] == a->number) {
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



