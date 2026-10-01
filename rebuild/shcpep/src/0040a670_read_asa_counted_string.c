#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_string_pool_block
#define g_string_pool_block (*(char * *)(g_sd + 0x5354))
#undef g_string_pool_cursor
#define g_string_pool_cursor (*(char * *)(g_sd + 0x534c))
#undef g_string_pool_end
#define g_string_pool_end (*(char * *)(g_sd + 0x5350))


// entry: 0040a670
// name : read_asa_counted_string
// size : 180
// sig  : char * read_asa_counted_string(void)


char * __cdecl read_asa_counted_string(void)

{
  unsigned char _frec_1[1];
#define str_len (*(byte *)(_frec_1 + 0))
  char *str;
  
  str = (char *)0x0;
  read_asa_bytes((char *)&str_len,1);
  if (str_len != 0) {
    if ((g_string_pool_block == (char *)0x0) ||
       (g_string_pool_end < g_string_pool_cursor + str_len + 1)) {
      g_string_pool_block = stock_malloc(0x100);
      if (g_string_pool_block == (char *)0x0) {
        report_compiler_message(0,0,0xbcd,(char *)0x0);
      }
      g_string_pool_cursor = g_string_pool_block;
      g_string_pool_end = g_string_pool_block + 0x100;
    }
    str = g_string_pool_cursor;
    read_asa_bytes(g_string_pool_cursor,(uint)str_len);
    g_string_pool_cursor = g_string_pool_cursor + str_len;
    *g_string_pool_cursor = '\0';
    g_string_pool_cursor = g_string_pool_cursor + 1;
  }
  return str;
#undef str_len
}



