#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x1f99c))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 004019a0
// name : read_scope_member_list
// size : 378
// sig  : void * read_scope_member_list(void)


int * __cdecl read_scope_member_list(void)

{
  unsigned char _frec_e[14];
#define remaining (*(short *)(_frec_e + 0))
#define blocks (*(uint * *)(_frec_e + 2))
#define block_count (*(int *)(_frec_e + 6))
#define block_entries (*(uint * *)(_frec_e + 10))
  uint *index_cursor;
  int block_offset;
  uint *puVar1;
  char *flag_byte;
  
  blocks = (uint *)0x0;
  read_bytes_or_fail((char *)&remaining,2,g_sym_file);
  if (remaining != 0) {
    blocks = stock_malloc(((int)(remaining + 3 + (remaining + 3 >> 0x1f & 3U)) >> 2) << 4);
    if (blocks == (uint *)0x0) {
      report_codegen_message(0xbcd,1,0,0,(char *)0x0);
    }
    else {
      zero_words(blocks,(remaining + 3 + (remaining + 3 >> 0x1f & 3U) >> 2 & 0xfffffff) << 2);
      block_count = 0;
      puVar1 = block_entries;
      if (remaining != 0) {
        block_offset = 0;
        block_entries = blocks + 2;
        do {
          puVar1 = (uint *)0x0;
          index_cursor = block_entries;
          do {
            if (remaining == 0) break;
            read_bytes_or_fail((char *)index_cursor,2,g_sym_file);
            *(short *)index_cursor = (short)*index_cursor + 0xb6;
            flag_byte = (char *)((int)blocks + block_offset + (int)puVar1 + 4U);
            read_bytes_or_fail(flag_byte,1,g_sym_file);
            if (*flag_byte != '\0') {
              g_symbol_table[(short)*index_cursor].flags =
                   g_symbol_table[(short)*index_cursor].flags | 0x20;
            }
            remaining = remaining + -1;
            index_cursor = (uint *)((int)index_cursor + 2);
            puVar1 = (uint *)((int)puVar1 + 1);
          } while (puVar1 < 4);
          block_offset = block_offset + 0x10;
          block_count = block_count + 1;
          block_entries = block_entries + 4;
        } while (remaining != 0);
      }
      block_count = block_count + -1;
      if (puVar1 < 4) {
        *(undefined2 *)((int)blocks + ((int)puVar1 + block_count * 8) * 2 + 8) = 0xffff;
      }
      puVar1 = blocks;
      if (0 < block_count) {
        do {
          block_count = block_count + -1;
          *puVar1 = (uint)(puVar1 + 4);
          puVar1 = puVar1 + 4;
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



