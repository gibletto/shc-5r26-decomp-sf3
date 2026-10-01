#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_name_chunk_cursor
#define g_name_chunk_cursor (*(char * *)(g_sd + 0x930c))
#undef g_name_chunk_end
#define g_name_chunk_end (*(char * *)(g_sd + 0x9310))
#undef g_string_pool_chunk
#define g_string_pool_chunk (*(char * *)(g_sd + 0x9314))


// entry: 00414686
// name : read_intermediate_string
// size : 223
// sig  : char * read_intermediate_string(void)


char * __cdecl read_intermediate_string(void)

{
  unsigned char _frec_c[12];
#define str_start (*(char * *)(_frec_c + 0))
#define text_len (*(byte (*)[4])(_frec_c + 4))
  
  str_start = (char *)0x0;
  read_intermediate_bytes((char *)text_len,1);
  if (text_len[0] != 0) {
    if ((g_string_pool_chunk == (char *)0x0) ||
       (g_name_chunk_end < g_name_chunk_cursor + text_len[0] + 1)) {
      g_string_pool_chunk = stock_malloc(0x100);
      if (g_string_pool_chunk == (char *)0x0) {
        report_message_at_source_line(0,0,0xbcd,(char *)0x0);
      }
      g_name_chunk_cursor = g_string_pool_chunk;
      g_name_chunk_end = g_string_pool_chunk + 0x100;
    }
    str_start = g_name_chunk_cursor;
    read_intermediate_bytes(g_name_chunk_cursor,(uint)text_len[0]);
    g_name_chunk_cursor = g_name_chunk_cursor + text_len[0];
    *g_name_chunk_cursor = '\0';
    g_name_chunk_cursor = g_name_chunk_cursor + 1;
  }
  return str_start;
#undef str_start
#undef text_len
}



