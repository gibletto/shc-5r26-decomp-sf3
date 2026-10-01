#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_line_range_temp
#define g_line_range_temp (*(FILE * *)(g_sd + 0x128bc))
#undef g_source_line_list
#define g_source_line_list (*(source_line_range * *)(g_sd + 0x10c64))


// entry: 0041fcb9
// name : flush_source_line_ranges
// size : 512
// sig  : void __cdecl flush_source_line_ranges(int flush_all)


int __cdecl flush_source_line_ranges(int flush_all)

{
  unsigned char _frec_24[36];
#define range_node (*(source_line_range * *)(_frec_24 + 0))
#define out_buf (*(undefined4 *)(_frec_24 + 4))
#define out_section (*(ushort *)(_frec_24 + 8))
#define out_start (*(uint *)(_frec_24 + 10))
#define out_end (*(uint *)(_frec_24 + 14))
#define out_calls (*(ushort *)(_frec_24 + 18))
#define next_call (*(line_call_site * *)(_frec_24 + 20))
#define call_site (*(line_call_site * *)(_frec_24 + 24))
#define file_ix (*(ushort (*)[2])(_frec_24 + 28))
  uint nwritten;
  bool more;
  source_line_range *next_range;
  
  if (g_source_line_list != (source_line_range *)0x0) {
    range_node = g_source_line_list;
    while( true ) {
      if (flush_all == 0) {
        if (range_node->next == (source_line_range *)0x0) {
          more = false;
        }
        else {
          more = true;
        }
      }
      else {
        more = range_node != (source_line_range *)0x0;
      }
      if (!more) break;
      next_range = range_node->next;
      file_ix[0] = range_node->filno - 1;
      store_u16_big_endian(file_ix,(ushort *)&out_buf);
      store_u16_big_endian(&range_node->linno,(ushort *)((int)&out_buf + 2));
      store_u16_big_endian((ushort *)&range_node->section,&out_section);
      store_u32_big_endian((uint *)&range_node->start,&out_start);
      store_u32_big_endian((uint *)&range_node->end,&out_end);
      store_u16_big_endian((ushort *)&range_node->call_count,&out_calls);
      nwritten = write_file_bytes(g_line_range_temp,(char *)&out_buf,0x10);
      if (nwritten == 0xffffffff) {
        report_message_at_source_line(0,0,0xce7,(char *)0x0);
      }
      call_site = range_node->calls;
      while (call_site != (line_call_site *)0x0) {
        next_call = call_site->next;
        store_u32_big_endian((uint *)&call_site->address,&out_buf);
        nwritten = write_file_bytes(g_line_range_temp,(char *)&out_buf,4);
        if (nwritten == 0xffffffff) {
          report_message_at_source_line(0,0,0xce7,(char *)0x0);
        }
        pool_free(call_site,8);
        call_site = next_call;
      }
      pool_free(range_node,0x18);
      if (g_line_range_count == -1) {
        report_message_at_source_line(0,0,0xc82,(char *)0x0);
      }
      g_line_range_count = g_line_range_count + 1;
      range_node = next_range;
    }
    g_source_line_list = range_node;
  }
  return;
#undef range_node
#undef out_buf
#undef out_section
#undef out_start
#undef out_end
#undef out_calls
#undef next_call
#undef call_site
#undef file_ix
}
