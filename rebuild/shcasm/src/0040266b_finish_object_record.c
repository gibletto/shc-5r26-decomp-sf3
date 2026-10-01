#include "decls.h"
#include "imports.h"

// entry: 0040266b
// name : finish_object_record
// size : 369
// sig  : void __cdecl finish_object_record(int tag)


int __cdecl finish_object_record(int tag)

{
  short rec_len;
  short body_len;
  uint uVar1;
  char len_byte;
  char data_len_byte;
  
  if (g_output_channels[1].buffer < g_output_channels[1].cursor) {
    body_len = (short)g_output_channels[1].cursor - (short)g_output_channels[1].buffer;
    rec_len = body_len + 1;
    len_byte = (char)rec_len;
    g_output_channels[1].buffer[1] = len_byte;
    if (tag == 0x1c) {
      g_section_data_bytes = rec_len + g_section_data_bytes;
      body_len = body_len + -8;
      data_len_byte = (char)body_len;
      g_output_channels[1].buffer[7] = data_len_byte;
      *(int *)(&g_section_object_offsets + g_current_section_kind * 4) =
           *(int *)(&g_section_object_offsets + g_current_section_kind * 4) + (int)body_len;
    }
    uVar1 = compute_object_record_checksum();
    *g_output_channels[1].cursor = (char)uVar1;
    g_output_channels[1].cursor = g_output_channels[1].cursor + 1;
    uVar1 = write_file_bytes(g_output_channels[1].file,g_output_channels[1].buffer,(int)rec_len);
    if (uVar1 == 0xffffffff) {
      report_message_at_source_line(0,0,0xce7,(char *)0x0);
    }
    g_output_channels[1].cursor = g_output_channels[1].buffer;
  }
  return;
}
