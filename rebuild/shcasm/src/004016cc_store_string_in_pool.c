#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_string_pool_blocks
#define g_string_pool_blocks (*(int * *)(g_sd + 0x128dc))
#undef g_string_pool_end
#define g_string_pool_end (*(char * *)(g_sd + 0xfb18))
#undef g_string_pool_pos
#define g_string_pool_pos (*(char * *)(g_sd + 0x13144))


// entry: 004016cc
// name : store_string_in_pool
// size : 207
// sig  : char * store_string_in_pool(char len, char * text)


char * __cdecl store_string_in_pool(char len,char *text)

{
  int *new_block;
  char *stored;
  
  stored = (char *)0x0;
  if (len != '\0') {
    if ((g_string_pool_blocks == (int *)0x0) || (g_string_pool_end < g_string_pool_pos + len + 1)) {
      new_block = pool_alloc(0x104);
      *new_block = (int)g_string_pool_blocks;
      g_string_pool_pos = (char *)(new_block + 1);
      g_string_pool_end = (char *)(new_block + 0x41);
      g_string_pool_blocks = new_block;
    }
    stored = g_string_pool_pos;
    while( true ) {
      if (len == '\0') break;
      *g_string_pool_pos = *text;
      text = text + 1;
      g_string_pool_pos = g_string_pool_pos + 1;
      len = len + -1;
    }
    *g_string_pool_pos = '\0';
    g_string_pool_pos = g_string_pool_pos + 1;
  }
  return stored;
}



