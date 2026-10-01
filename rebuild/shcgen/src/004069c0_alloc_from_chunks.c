#include "decls.h"
#include "imports.h"

// entry: 004069c0
// name : alloc_from_chunks
// size : 122
// sig  : void * alloc_from_chunks(alloc_chunk * * head, int size)


int * __cdecl alloc_from_chunks(alloc_chunk **head,int size)

{
  alloc_chunk *chunk;
  char *mem;
  
  mem = (char *)0x0;
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
      mem = chunk->cursor;
      chunk->cursor = mem + size;
      goto LAB_00406a13;
    }
    if (chunk->free_list != (void *)0x0) break;
    chunk = chunk->next;
    if (chunk == (alloc_chunk *)0x0) {
LAB_00406a13:
      if (mem == (char *)0x0) {
        chunk = pool_new_chunk();
        if (chunk == (alloc_chunk *)0x0) {
          return (void *)0x0;
        }
        chunk->next = *head;
        *head = chunk;
        mem = chunk->cursor;
        chunk->cursor = mem + size;
      }
      return mem;
    }
  }
  mem = chunk->free_list;
  chunk->free_list = *(void **)mem;
  chunk->free_count = chunk->free_count + -1;
  goto LAB_00406a13;
}



