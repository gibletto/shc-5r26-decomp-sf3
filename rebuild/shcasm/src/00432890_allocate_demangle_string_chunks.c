#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_demangle_backref_chunk_current
#define g_demangle_backref_chunk_current (*(int * *)(g_sd + 0x1473c))
#undef g_demangle_backref_chunk_first
#define g_demangle_backref_chunk_first (*(int * *)(g_sd + 0x14738))
#undef g_demangle_piece_chunk_current
#define g_demangle_piece_chunk_current (*(int * *)(g_sd + 0x14734))
#undef g_demangle_piece_chunk_first
#define g_demangle_piece_chunk_first (*(int * *)(g_sd + 0x14730))


// entry: 00432890
// name : allocate_demangle_string_chunks
// size : 109
// sig  : void allocate_demangle_string_chunks(void)


int __cdecl allocate_demangle_string_chunks(void)

{
  undefined4 *chunk;
  
  if (g_demangle_piece_chunk_first == (undefined4 *)0x0) {
    chunk = stock_malloc(0x808);
    if (chunk == (undefined4 *)0x0) {
      free_demangle_string_chunks();
      return;
    }
    *chunk = 0;
    chunk[1] = 0;
    g_demangle_piece_chunk_first = chunk;
    g_demangle_piece_chunk_current = chunk;
  }
  if (g_demangle_backref_chunk_first == (undefined4 *)0x0) {
    chunk = stock_malloc(0x808);
    if (chunk == (undefined4 *)0x0) {
      free_demangle_string_chunks();
      return;
    }
    *chunk = 0;
    chunk[1] = 0;
    g_demangle_backref_chunk_first = chunk;
    g_demangle_backref_chunk_current = chunk;
  }
  return;
}
