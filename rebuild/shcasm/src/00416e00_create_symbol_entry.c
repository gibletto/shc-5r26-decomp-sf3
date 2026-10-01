#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_created_symbol_chunks
#define g_created_symbol_chunks (*(short * *)(g_sd + 0x6954))


// entry: 00416e00
// name : create_symbol_entry
// size : 482
// sig  : symbol * create_symbol_entry(uchar kind, uchar flags, short id)


symbol * __cdecl create_symbol_entry(uchar kind,uchar flags,short id)

{
  void *new_chunk;
  symbol *new_sym;
  short *chunk;
  uint i;
  symbol *tail_sym;
  short slot;
  
  if (g_created_symbol_chunks == (short *)0x0) {
    chunk = stock_malloc(0x588);
    g_created_symbol_chunks = chunk;
    if (chunk == (short *)0x0) {
      report_message_at_source_line(0,0,0xbcd,(char *)0x0);
    }
    for (i = 0; i < 0x588; i = i + 1) {
      *(undefined1 *)(i + (int)chunk) = 0;
    }
  }
  else {
    for (chunk = g_created_symbol_chunks; *(int *)(chunk + 2) != 0; chunk = *(short **)(chunk + 2))
    {
    }
    if (0x1f < *chunk) {
      new_chunk = stock_malloc(0x588);
      *(void **)(chunk + 2) = new_chunk;
      if (*(int *)(chunk + 2) == 0) {
        report_message_at_source_line(0,0,0xbcd,(char *)0x0);
      }
      chunk = *(short **)(chunk + 2);
      for (i = 0; i < 0x588; i = i + 1) {
        *(undefined1 *)(i + (int)chunk) = 0;
      }
    }
  }
  slot = *chunk;
  new_sym = (symbol *)(chunk + slot * 0x16 + 4);
  new_sym->kind = kind;
  *(uchar *)((int)chunk + slot * 0x2c + 9) = flags;
  chunk[slot * 0x16 + 7] = id;
  if (g_symbol_hash[(int)id % 0x3fd] == (symbol *)0x0) {
    g_symbol_hash[(int)id % 0x3fd] = new_sym;
  }
  else {
    for (tail_sym = g_symbol_hash[(int)id % 0x3fd]; tail_sym->hash_next != (symbol *)0x0;
        tail_sym = tail_sym->hash_next) {
    }
    tail_sym->hash_next = new_sym;
  }
  *chunk = *chunk + 1;
  g_created_symbol_chunks[1] = g_created_symbol_chunks[1] + 1;
  return new_sym;
}



