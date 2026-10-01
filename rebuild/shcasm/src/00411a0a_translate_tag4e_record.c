#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_record_cursor
#define g_debug_record_cursor (*(unsigned int * *)(g_sd + 0x13030))
#undef g_object_record_cursor
#define g_object_record_cursor (*(unsigned char * *)(g_sd + 0x13154))


// entry: 00411a0a
// name : translate_tag4e_record
// size : 339
// sig  : void translate_tag4e_record(void)


int __cdecl translate_tag4e_record(void)

{
  uchar *puVar1;
  int entry_count;
  
  store_u32_big_endian(g_debug_record_cursor,(uint *)g_object_record_cursor);
  g_debug_record_cursor = g_debug_record_cursor + 1;
  g_object_record_cursor[4] = (uchar)*g_debug_record_cursor;
  g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 1);
  puVar1 = g_object_record_cursor + 4;
  g_object_record_cursor = g_object_record_cursor + 5;
  entry_count = (int)(char)*puVar1;
  while( true ) {
    if (entry_count == 0) break;
    *g_object_record_cursor = (uchar)*g_debug_record_cursor;
    g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 1);
    g_object_record_cursor = g_object_record_cursor + 1;
    *g_object_record_cursor = *(uchar *)g_debug_record_cursor;
    g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 1);
    g_object_record_cursor = g_object_record_cursor + 1;
    store_u32_big_endian(g_debug_record_cursor,(uint *)g_object_record_cursor);
    g_debug_record_cursor = g_debug_record_cursor + 1;
    g_object_record_cursor = g_object_record_cursor + 4;
    *g_object_record_cursor = (uchar)*g_debug_record_cursor;
    g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 1);
    g_object_record_cursor = g_object_record_cursor + 1;
    store_u32_big_endian(g_debug_record_cursor,(uint *)g_object_record_cursor);
    g_debug_record_cursor = g_debug_record_cursor + 1;
    g_object_record_cursor = g_object_record_cursor + 4;
    entry_count = entry_count + -1;
  }
  store_u16_big_endian((ushort *)g_debug_record_cursor,(ushort *)g_object_record_cursor);
  puVar1 = g_object_record_cursor;
  g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 2);
  g_object_record_cursor = g_object_record_cursor + 2;
  if (g_suppress_debug_record == 0) {
    append_object_record_bytes
              (g_object_record_buffer,(int)(puVar1 + -SD(0x0044812e)),(uint)g_debug_record_tag);
  }
  return;
}
