#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_record_cursor
#define g_debug_record_cursor (*(unsigned short * *)(g_sd + 0x13030))
#undef g_object_record_cursor
#define g_object_record_cursor (*(unsigned char * *)(g_sd + 0x13154))


// entry: 00411c45
// name : translate_short_tagged_record
// size : 255
// sig  : void __cdecl translate_short_tagged_record(uint tag)


int __cdecl translate_short_tagged_record(uint tag)

{
  uint tag_kind;
  
  tag_kind = tag & 0x7f;
  if (tag_kind != 0x50) {
    *g_object_record_cursor = (uchar)*g_debug_record_cursor;
    g_debug_record_cursor = (ushort *)((int)g_debug_record_cursor + 1);
    g_object_record_cursor = g_object_record_cursor + 1;
    if (((int)(char)g_object_record_buffer[0] & 0x80U) != 0) goto LAB_00411cdc;
  }
  if (tag_kind == 0x48) {
    *g_object_record_cursor = (uchar)*g_debug_record_cursor;
    g_debug_record_cursor = (ushort *)((int)g_debug_record_cursor + 1);
    g_object_record_cursor = g_object_record_cursor + 1;
  }
  store_u16_big_endian(g_debug_record_cursor,(ushort *)g_object_record_cursor);
  g_debug_record_cursor = g_debug_record_cursor + 1;
  g_object_record_cursor = g_object_record_cursor + 2;
LAB_00411cdc:
  if (g_suppress_debug_record == 0) {
    append_object_record_bytes(g_object_record_buffer,(int)(g_object_record_cursor + -SD(0x00448130)),tag)
    ;
  }
  if (tag_kind == 0x36) {
    if (g_object_record_buffer[0] == '\0') {
      g_debug_group_depth = g_debug_group_depth + 1;
    }
    else {
      g_debug_group_depth = g_debug_group_depth + -1;
      if (g_debug_group_depth == 0) {
        g_suppress_debug_record = 0;
      }
    }
  }
  return;
}
