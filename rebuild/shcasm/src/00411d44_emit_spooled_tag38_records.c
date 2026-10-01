#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_line_range_temp
#define g_line_range_temp (*(FILE * *)(g_sd + 0x128bc))


// entry: 00411d44
// name : emit_spooled_tag38_records
// size : 331
// sig  : void emit_spooled_tag38_records(void)


int __cdecl emit_spooled_tag38_records(void)

{
  unsigned char _frec_10[16];
#define pair_count (*(ushort (*)[2])(_frec_10 + 0))
#define ranges_left (*(short *)(_frec_10 + 4))
#define pair_count_hi (*(uchar *)(_frec_10 + 8))
#define pair_count_lo (*(uchar *)(_frec_10 + 9))
  ushort uVar1;
  uint read_status;
  bool bVar2;
  
  ranges_left = g_line_range_count;
  store_u16_big_endian((ushort *)&g_line_range_count,(ushort *)g_object_record_buffer);
  append_object_record_bytes(g_object_record_buffer,2,0x38);
  while (ranges_left != 0) {
    ranges_left = ranges_left + -1;
    read_status = read_file_bytes(g_line_range_temp,(char *)g_object_record_buffer,0x10);
    if (read_status == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    pair_count_hi = g_object_record_buffer[0xe];
    pair_count_lo = g_object_record_buffer[0xf];
    store_u16_big_endian((ushort *)&pair_count_hi,pair_count);
    append_object_record_bytes(g_object_record_buffer,0x10,0x38);
    while (uVar1 = pair_count[0] - 1, bVar2 = pair_count[0] != 0, pair_count[0] = uVar1, bVar2) {
      read_status = read_file_bytes(g_line_range_temp,(char *)g_object_record_buffer,4);
      if (read_status == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      append_object_record_bytes(g_object_record_buffer,4,0x38);
    }
  }
  ranges_left = ranges_left + -1;
  store_u16_big_endian((ushort *)&g_debug_word_1001,(ushort *)g_object_record_buffer);
  append_object_record_bytes(g_object_record_buffer,2,0x38);
  return;
#undef pair_count
#undef ranges_left
#undef pair_count_hi
#undef pair_count_lo
}
