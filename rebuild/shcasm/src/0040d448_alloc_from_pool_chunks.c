#include "decls.h"
#include "imports.h"

// entry: 0040d448
// name : alloc_from_pool_chunks
// size : 263
// sig  : void * alloc_from_pool_chunks(alloc_chunk * * chunks, int size)


int * __cdecl alloc_from_pool_chunks(alloc_chunk **chunks,int size)

{
  alloc_chunk *new_chunk;
  alloc_chunk *chunk;
  char *mem;
  
  mem = (char *)0x0;
  if (*chunks == (alloc_chunk *)0x0) {
    new_chunk = new_pool_chunk();
    *chunks = new_chunk;
  }
  if (*chunks == (alloc_chunk *)0x0) {
    mem = (char *)0x0;
  }
  else {
    for (chunk = *chunks; chunk != (alloc_chunk *)0x0; chunk = chunk->next) {
      if (chunk->cursor + size <= chunk->end) {
        mem = chunk->cursor;
        chunk->cursor = chunk->cursor + size;
        break;
      }
      if (chunk->free_list != (void *)0x0) {
        mem = chunk->free_list;
        chunk->free_list = *(void **)chunk->free_list;
        chunk->free_count = chunk->free_count + -1;
        break;
      }
    }
    if (mem == (char *)0x0) {
      new_chunk = new_pool_chunk();
      if (new_chunk == (alloc_chunk *)0x0) {
        mem = (char *)0x0;
      }
      else {
        new_chunk->next = *chunks;
        *chunks = new_chunk;
        mem = new_chunk->cursor;
        new_chunk->cursor = new_chunk->cursor + size;
      }
    }
  }
  return mem;
}



