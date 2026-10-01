#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_demangle_backref_chunk_first
#define g_demangle_backref_chunk_first (*(int * *)(g_sd + 0x14738))
#undef g_demangle_piece_chunk_first
#define g_demangle_piece_chunk_first (*(int * *)(g_sd + 0x14730))


// entry: 00432900
// name : free_demangle_string_chunks
// size : 57
// sig  : void free_demangle_string_chunks(void)


int __cdecl free_demangle_string_chunks(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = g_demangle_piece_chunk_first;
  while (puVar1 = g_demangle_backref_chunk_first, puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar2;
    stock_free(puVar2);
    puVar2 = puVar1;
  }
  while (puVar1 != (undefined4 *)0x0) {
    puVar2 = (undefined4 *)*puVar1;
    stock_free(puVar1);
    puVar1 = puVar2;
  }
  return;
}
