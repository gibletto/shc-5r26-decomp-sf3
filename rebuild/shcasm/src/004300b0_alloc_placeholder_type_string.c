#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_demangle_placeholder_chunk_current
#define g_demangle_placeholder_chunk_current (*(int * *)(g_sd + 0x14f64))
#undef g_demangle_placeholder_chunk_first
#define g_demangle_placeholder_chunk_first (*(int * *)(g_sd + 0x14f60))


// entry: 004300b0
// name : alloc_placeholder_type_string
// size : 205
// sig  : char * alloc_placeholder_type_string(char * text)


char * __cdecl alloc_placeholder_type_string(char *text)

{
  char cVar1;
  undefined4 *new_chunk;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  int text_start;
  
  uVar2 = 0xffffffff;
  pcVar5 = text;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  if (0x800 < (int)(g_demangle_placeholder_chunk_used + ~uVar2)) {
    new_chunk = stock_malloc(0x804);
    if (new_chunk == (undefined4 *)0x0) {
      while (g_demangle_placeholder_chunk_first != (undefined4 *)0x0) {
        g_demangle_placeholder_chunk_current = (undefined4 *)*g_demangle_placeholder_chunk_first;
        stock_free(g_demangle_placeholder_chunk_first);
        g_demangle_placeholder_chunk_first = g_demangle_placeholder_chunk_current;
      }
      return (char *)0x0;
    }
    *g_demangle_placeholder_chunk_current = new_chunk;
    *new_chunk = 0;
    g_demangle_placeholder_chunk_used = 0;
    g_demangle_placeholder_chunk_current = new_chunk;
  }
  text_start = g_demangle_placeholder_chunk_used;
  uVar3 = 0xffffffff;
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
  pcVar6 = (char *)(g_demangle_placeholder_chunk_used + 4 +
                   (int)g_demangle_placeholder_chunk_current);
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  g_demangle_placeholder_chunk_used = g_demangle_placeholder_chunk_used + ~uVar2;
  return (char *)((int)g_demangle_placeholder_chunk_current + text_start + 4);
}



