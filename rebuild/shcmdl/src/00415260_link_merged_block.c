#include "decls.h"
#include "imports.h"

// entry: 00415260
// name : link_merged_block
// size : 57
// sig  : void link_merged_block(bblock * into, bblock * block)


int __cdecl link_merged_block(bblock *into,bblock *block)

{
  bblock *cur;
  bblock *next;
  
  next = into->merge_next;
  if (next != (bblock *)0x0) {
    while (cur = next, next = cur, block->number <= cur->number) {
      if ((cur->number == block->number) ||
         (next = cur->merge_next, into = cur, next == (bblock *)0x0)) goto LAB_0041528f;
    }
    block->merge_next = cur;
    into->merge_next = block;
  }
LAB_0041528f:
  if (next == (bblock *)0x0) {
    into->merge_next = block;
  }
  return;
}



