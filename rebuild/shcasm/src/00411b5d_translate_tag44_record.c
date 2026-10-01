#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_record_cursor
#define g_debug_record_cursor (*(unsigned int * *)(g_sd + 0x13030))
#undef g_object_record_cursor
#define g_object_record_cursor (*(unsigned char * *)(g_sd + 0x13154))


// entry: 00411b5d
// name : translate_tag44_record
// size : 232
// sig  : void translate_tag44_record(void)


int __cdecl translate_tag44_record(void)

{
  uint *puVar1;
  uchar *puVar2;
  
  g_object_record_buffer[0] = *(uchar *)g_debug_record_cursor;
  g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 1);
  store_u32_big_endian(g_debug_record_cursor,(uint *)(g_object_record_buffer + 1));
  puVar1 = g_debug_record_cursor;
  g_debug_record_cursor = g_debug_record_cursor + 1;
  g_object_record_buffer[5] = (uchar)*g_debug_record_cursor;
  g_debug_record_cursor = (uint *)((int)puVar1 + 5);
  g_object_record_cursor = g_object_record_cursor + 6;
  if ((g_object_record_buffer[0] == '\n') || (g_object_record_buffer[0] == '\v')) {
    store_u16_big_endian((ushort *)g_debug_record_cursor,(ushort *)g_object_record_cursor);
    g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 2);
    g_object_record_cursor = g_object_record_cursor + 2;
  }
  store_u16_big_endian((ushort *)g_debug_record_cursor,(ushort *)g_object_record_cursor);
  puVar2 = g_object_record_cursor;
  g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 2);
  g_object_record_cursor = g_object_record_cursor + 2;
  if (g_suppress_debug_record == 0) {
    append_object_record_bytes
              (g_object_record_buffer,(int)(puVar2 + -SD(0x0044812e)),(uint)g_debug_record_tag);
  }
  return;
}
