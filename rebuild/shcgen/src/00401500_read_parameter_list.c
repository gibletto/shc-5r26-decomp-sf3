#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x1f99c))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00401500
// name : read_parameter_list
// size : 361
// sig  : void * read_parameter_list(void)


int * __cdecl read_parameter_list(void)

{
  unsigned char _frec_d[13];
#define remaining (*(byte *)(_frec_d + 0))
#define blocks (*(uint * *)(_frec_d + 1))
#define block_count (*(int *)(_frec_d + 5))
#define block_entries (*(uint * *)(_frec_d + 9))
  char *buf;
  uint slot;
  int block_offset;
  uint *cursor;
  
  slot = 0;
  blocks = (uint *)0x0;
  read_bytes_or_fail((char *)&remaining,1,g_sym_file);
  if (remaining != 0) {
    blocks = stock_malloc(((int)(remaining + 3) >> 2) * 0x24);
    if (blocks == (uint *)0x0) {
      report_codegen_message(0xbcd,1,0,0,(char *)0x0);
    }
    else {
      zero_words(blocks,(remaining + 3 & 0xfffffffc) * 9 >> 2);
      block_count = 0;
      if (remaining != 0) {
        block_offset = 0;
        block_entries = blocks + 2;
        do {
          slot = 0;
          cursor = block_entries;
          do {
            if (remaining == 0) break;
            read_bytes_or_fail((char *)cursor,2,g_sym_file);
            *(short *)cursor = (short)*cursor + 0xb6;
            buf = (char *)((int)blocks + block_offset + slot + 4);
            read_bytes_or_fail(buf,1,g_sym_file);
            if (*buf != '\0') {
              g_symbol_table[(short)*cursor].flags = g_symbol_table[(short)*cursor].flags | 0x20;
            }
            cursor = (uint *)((int)cursor + 2);
            slot = slot + 1;
            remaining = remaining - 1;
          } while (slot < 4);
          block_offset = block_offset + 0x24;
          block_count = block_count + 1;
          block_entries = block_entries + 9;
        } while (remaining != 0);
      }
      block_count = block_count + -1;
      if (slot < 4) {
        *(undefined2 *)((int)blocks + (block_count * 0x12 + slot) * 2 + 8) = 0xffff;
      }
      cursor = blocks;
      if (0 < block_count) {
        do {
          block_count = block_count + -1;
          *cursor = (uint)(cursor + 9);
          cursor = cursor + 9;
        } while (block_count != 0);
      }
    }
  }
  return blocks;
#undef remaining
#undef blocks
#undef block_count
#undef block_entries
}



