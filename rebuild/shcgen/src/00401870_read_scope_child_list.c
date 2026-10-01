#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x1f99c))


// entry: 00401870
// name : read_scope_child_list
// size : 291
// sig  : void * read_scope_child_list(void)


int * __cdecl read_scope_child_list(void)

{
  unsigned char _frec_a[10];
#define remaining (*(short *)(_frec_a + 0))
#define blocks (*(uint * *)(_frec_a + 2))
#define block_entries (*(uint * *)(_frec_a + 6))
  uint *puVar1;
  uint *index_cursor;
  int block_count;
  
  blocks = (uint *)0x0;
  read_bytes_or_fail((char *)&remaining,2,g_sym_file);
  if (remaining != 0) {
    blocks = stock_malloc((remaining + 5) / 6 << 4);
    if (blocks == (uint *)0x0) {
      report_codegen_message(0xbcd,1,0,0,(char *)0x0);
    }
    else {
      block_count = 0;
      zero_words(blocks,((remaining + 5) / 6 & 0xfffffffU) << 2);
      puVar1 = block_entries;
      if (remaining != 0) {
        block_entries = blocks + 1;
        do {
          puVar1 = (uint *)0x0;
          index_cursor = block_entries;
          do {
            if (remaining == 0) break;
            puVar1 = (uint *)((int)puVar1 + 1);
            read_bytes_or_fail((char *)index_cursor,2,g_sym_file);
            *(short *)index_cursor = (short)*index_cursor + 0xb6;
            remaining = remaining + -1;
            index_cursor = (uint *)((int)index_cursor + 2);
          } while (puVar1 < 6);
          block_count = block_count + 1;
          block_entries = block_entries + 4;
        } while (remaining != 0);
      }
      block_count = block_count + -1;
      if (puVar1 < 6) {
        *(undefined2 *)((int)blocks + ((int)puVar1 + block_count * 8) * 2 + 4) = 0xffff;
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
#undef block_entries
}



