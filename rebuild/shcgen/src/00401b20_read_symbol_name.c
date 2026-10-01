#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_string_pool_block
#define g_string_pool_block (*(char * *)(g_sd + 0x1fa40))
#undef g_string_pool_cursor
#define g_string_pool_cursor (*(char * *)(g_sd + 0x1fa48))
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x1f99c))


// entry: 00401b20
// name : read_symbol_name
// size : 224
// sig  : char * read_symbol_name(void)


char * __cdecl read_symbol_name(void)

{
  unsigned char _frec_fd[253];
#define name_length (*(byte *)(_frec_fd + 0))
#define name_buf (*(char (*)[252])(_frec_fd + 1))
  int i;
  char *copy;
  char *src;
  
  copy = (char *)0x0;
  read_bytes_or_fail((char *)&name_length,1,g_sym_file);
  if (name_length != 0) {
    read_bytes_or_fail(name_buf,(uint)name_length,g_sym_file);
    if (((g_string_pool_block == (char *)0x0) ||
        (copy = g_string_pool_cursor,
        g_string_pool_block + 0x100 < g_string_pool_cursor + name_length + 1)) &&
       (g_string_pool_block = stock_malloc(0x100), copy = g_string_pool_block,
       g_string_pool_block == (char *)0x0)) {
      report_codegen_message(0xbcd,1,0,0,(char *)0x0);
      copy = g_string_pool_cursor;
    }
    g_string_pool_cursor = copy;
    copy = g_string_pool_cursor;
    i = 0;
    if (name_length != 0) {
      do {
        src = name_buf + i;
        i = i + 1;
        *g_string_pool_cursor = *src;
        g_string_pool_cursor = g_string_pool_cursor + 1;
      } while (i < (int)(uint)name_length);
    }
    *g_string_pool_cursor = '\0';
    g_string_pool_cursor = g_string_pool_cursor + 1;
  }
  return copy;
#undef name_length
#undef name_buf
}



