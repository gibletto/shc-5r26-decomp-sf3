#include "decls.h"
#include "imports.h"

// entry: 00407cc0
// name : pool_free_in_chunk_list
// size : 177
// sig  : void pool_free_in_chunk_list(alloc_chunk * * chunk_list, void * ptr, int size)


int __cdecl pool_free_in_chunk_list(alloc_chunk **chunk_list,void *ptr,int size)

{
  alloc_chunk *p;
  int iVar1;
  undefined4 *free_item;
  alloc_chunk *prev;
  
  iVar1 = -1;
  prev = (alloc_chunk *)0x0;
  p = *chunk_list;
  while( true ) {
    if (p == (alloc_chunk *)0x0) goto LAB_00407d53;
    if ((p->end + -0x400 <= ptr) && (ptr < p->end)) break;
    prev = p;
    p = p->next;
  }
  for (free_item = p->free_list; free_item != (undefined4 *)0x0;
      free_item = (undefined4 *)*free_item) {
    if (ptr == free_item) {
      report_compiler_message(0,0,0x12eb,(char *)0x0);
    }
  }
  *(void **)ptr = p->free_list;
  p->free_list = ptr;
  iVar1 = p->free_count + 1;
  p->free_count = iVar1;
  if ((int)(0x400 / (longlong)size) == iVar1) {
    if (*chunk_list == p) {
      *chunk_list = p->next;
    }
    else {
      prev->next = p->next;
    }
    stock_free(p);
  }
  iVar1 = 0;
LAB_00407d53:
  if (iVar1 != 0) {
    report_compiler_message(0,0,0x12ea,(char *)0x0);
  }
  return;
}



