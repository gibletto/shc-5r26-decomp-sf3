#include "decls.h"
#include "imports.h"

// entry: 00402374
// name : append_object_record_bytes
// size : 759
// sig  : void __cdecl append_object_record_bytes(uchar *data,int len,uint tag)


int __cdecl append_object_record_bytes(uchar *data,int len,uint tag)

{
  int iVar1;
  bool bVar2;
  short room;
  
  if ((g_object_record_tag != tag) || (g_object_record_break == 1)) {
    if (((g_object_record_tag ^ tag & 0x7f) & 0x7f) != 0) {
      *g_output_channels[1].buffer = *g_output_channels[1].buffer | 0x80;
    }
    finish_object_record(g_object_record_tag);
    g_object_record_break = 0;
    g_object_record_tag = tag;
  }
  while (0 < len) {
    if (g_output_channels[1].cursor == g_output_channels[1].buffer) {
      if ((((byte)tag == 0x1c) || ((byte)tag == 0x9c)) && (g_object_need_section_select == 1)) {
        iVar1 = build_section_select_record((uchar *)g_output_channels[1].cursor);
        g_output_channels[1].cursor = g_output_channels[1].cursor + iVar1;
        finish_object_record(0x1a);
        g_object_need_section_select = 0;
      }
      *g_output_channels[1].cursor = (byte)tag & 0x7f;
      g_output_channels[1].cursor = g_output_channels[1].cursor + 2;
      if (tag == 0x1c) {
        *g_output_channels[1].cursor = -0x80;
        g_output_channels[1].cursor = g_output_channels[1].cursor + 1;
        store_u32_big_endian
                  ((uint *)(&g_section_object_offsets + g_current_section_kind * 4),
                   (uint *)g_output_channels[1].cursor);
        g_output_channels[1].cursor = g_output_channels[1].cursor + 5;
      }
    }
    room = (short)g_output_channels[1].end - (short)g_output_channels[1].cursor;
    if (room < len) {
      if (((((tag != 0x1c) || (4 < len)) && ((tag != 0x30 && ((tag != 0x34 && (tag != 0x40)))))) &&
          (tag != 0x38)) && (tag != 0x3a)) {
        len = len - room;
        while (room != 0) {
          *g_output_channels[1].cursor = *data;
          data = data + 1;
          g_output_channels[1].cursor = g_output_channels[1].cursor + 1;
          room = room + -1;
        }
      }
      finish_object_record(tag);
    }
    else {
      while (iVar1 = len + -1, bVar2 = len != 0, len = iVar1, bVar2) {
        *g_output_channels[1].cursor = *data;
        data = data + 1;
        g_output_channels[1].cursor = g_output_channels[1].cursor + 1;
      }
    }
  }
  return;
}
