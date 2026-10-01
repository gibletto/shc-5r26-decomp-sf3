#include "decls.h"
#include "imports.h"

// entry: 00406a40
// name : pool_new_chunk
// size : 43
// sig  : alloc_chunk * pool_new_chunk(void)


alloc_chunk * pool_new_chunk(void)

{
  alloc_chunk *chunk;
  
  chunk = stock_malloc(0x414);
  if (chunk != (alloc_chunk *)0x0) {
    chunk->next = (alloc_chunk *)0x0;
    chunk->cursor = (char *)chunk->data;
    chunk->end = (char *)(chunk + 1);
    chunk->free_list = (void *)0x0;
    chunk->free_count = 0;
  }
  return chunk;
}



