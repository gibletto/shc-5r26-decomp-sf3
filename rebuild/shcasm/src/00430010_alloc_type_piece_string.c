#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_demangle_piece_chunk_current
#define g_demangle_piece_chunk_current (*(int * *)(g_sd + 0x14734))


// entry: 00430010
// name : alloc_type_piece_string
// size : 146
// sig  : char * alloc_type_piece_string(char * text)


char * __cdecl alloc_type_piece_string(char *text)

{
  char cVar1;
  undefined4 *new_chunk;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  undefined4 *chunk;
  
  chunk = g_demangle_piece_chunk_current;
  uVar2 = 0xffffffff;
  pcVar6 = text;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  if (0x800 < (int)(g_demangle_piece_chunk_current[1] + ~uVar2)) {
    new_chunk = stock_malloc(0x808);
    if (new_chunk == (undefined4 *)0x0) {
      free_demangle_string_chunks();
      return (char *)0x0;
    }
    *new_chunk = 0;
    new_chunk[1] = 0;
    *chunk = new_chunk;
    g_demangle_piece_chunk_current = new_chunk;
  }
  chunk = g_demangle_piece_chunk_current;
  uVar3 = 0xffffffff;
  pcVar6 = (char *)(g_demangle_piece_chunk_current[1] + 8 + (int)g_demangle_piece_chunk_current);
  do {
    pcVar5 = text;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = text + 1;
    cVar1 = *text;
    text = pcVar5;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar5 + -uVar3;
  pcVar7 = pcVar6;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar7 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar7 = pcVar7 + 1;
  }
  chunk[1] = chunk[1] + ~uVar2;
  return pcVar6;
}



