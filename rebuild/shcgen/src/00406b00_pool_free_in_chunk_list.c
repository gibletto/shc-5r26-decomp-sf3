#include "decls.h"
#include "imports.h"

// entry: 00406b00
// name : pool_free_in_chunk_list
// size : 177
// sig  : void pool_free_in_chunk_list(alloc_chunk * * chunk_list, void * ptr, int size)


int __cdecl pool_free_in_chunk_list(alloc_chunk **chunk_list,void *ptr,int size)

{
  alloc_chunk *block;
  int iVar1;
  undefined4 *free_entry;
  alloc_chunk *prev;
  
  iVar1 = -1;
  prev = (alloc_chunk *)0x0;
  block = *chunk_list;
  while( true ) {
    if (block == (alloc_chunk *)0x0) goto LAB_00406b93;
    if ((block->end + -0x400 <= ptr) && (ptr < block->end)) break;
    prev = block;
    block = block->next;
  }
  for (free_entry = block->free_list; free_entry != (undefined4 *)0x0;
      free_entry = (undefined4 *)*free_entry) {
    if (ptr == free_entry) {
      report_compiler_message(0,0,0x12eb,(char *)0x0);
    }
  }
  *(void **)ptr = block->free_list;
  block->free_list = ptr;
  iVar1 = block->free_count + 1;
  block->free_count = iVar1;
  if ((int)(0x400 / (longlong)size) == iVar1) {
    if (*chunk_list == block) {
      *chunk_list = block->next;
    }
    else {
      prev->next = block->next;
    }
    stock_free(block);
  }
  iVar1 = 0;
LAB_00406b93:
  if (iVar1 != 0) {
    report_compiler_message(0,0,0x12ea,(char *)0x0);
  }
  return;
}



