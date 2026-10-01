#include "decls.h"
#include "imports.h"

// entry: 0040d689
// name : free_to_pool_chunks
// size : 326
// sig  : void __cdecl free_to_pool_chunks(alloc_chunk **chunks,void *ptr,int size)


int __cdecl free_to_pool_chunks(alloc_chunk **chunks,void *ptr,int size)

{
  alloc_chunk *chunk;
  int failed;
  undefined4 *free_item;
  alloc_chunk *prev_chunk;
  
  failed = -1;
  prev_chunk = (alloc_chunk *)0x0;
  chunk = *chunks;
  while( true ) {
    if (chunk == (alloc_chunk *)0x0) goto LAB_0040d7a6;
    if ((chunk->end + -0x400 <= ptr) && (ptr < chunk->end)) break;
    prev_chunk = chunk;
    chunk = chunk->next;
  }
  for (free_item = chunk->free_list; free_item != (undefined4 *)0x0;
      free_item = (undefined4 *)*free_item) {
    if (free_item == ptr) {
      report_message_at_source_line(0,0,0x12eb,(char *)0x0);
    }
  }
  *(void **)ptr = chunk->free_list;
  chunk->free_list = ptr;
  chunk->free_count = chunk->free_count + 1;
  if (chunk->free_count == (int)(0x400 / (longlong)size)) {
    if (*chunks == chunk) {
      *chunks = chunk->next;
    }
    else {
      prev_chunk->next = chunk->next;
    }
    stock_free(chunk);
  }
  failed = 0;
LAB_0040d7a6:
  if (failed != 0) {
    report_message_at_source_line(0,0,0x12ea,(char *)0x0);
  }
  return;
}
