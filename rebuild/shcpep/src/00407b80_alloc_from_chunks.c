#include "decls.h"
#include "imports.h"

// entry: 00407b80
// name : alloc_from_chunks
// size : 122
// sig  : void * alloc_from_chunks(alloc_chunk * * head, int size)


int * __cdecl alloc_from_chunks(alloc_chunk **head,int size)

{
  alloc_chunk *chunk;
  char *block;
  
  block = (char *)0x0;
  if (*head == (alloc_chunk *)0x0) {
    chunk = pool_new_chunk();
    *head = chunk;
  }
  chunk = *head;
  if (chunk == (alloc_chunk *)0x0) {
    return (void *)0x0;
  }
  while( true ) {
    if (chunk->cursor + size <= chunk->end) {
      block = chunk->cursor;
      chunk->cursor = block + size;
      goto LAB_00407bd3;
    }
    if (chunk->free_list != (void *)0x0) break;
    chunk = chunk->next;
    if (chunk == (alloc_chunk *)0x0) {
LAB_00407bd3:
      if (block == (char *)0x0) {
        chunk = pool_new_chunk();
        if (chunk == (alloc_chunk *)0x0) {
          return (void *)0x0;
        }
        chunk->next = *head;
        *head = chunk;
        block = chunk->cursor;
        chunk->cursor = block + size;
      }
      return block;
    }
  }
  block = chunk->free_list;
  chunk->free_list = *(void **)block;
  chunk->free_count = chunk->free_count + -1;
  goto LAB_00407bd3;
}



