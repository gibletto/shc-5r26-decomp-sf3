#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x1f99c))


// entry: 00401670
// name : read_function_scope_list
// size : 270
// sig  : void * read_function_scope_list(void)


int * __cdecl read_function_scope_list(void)

{
  unsigned char _frec_a[10];
#define remaining (*(short *)(_frec_a + 0))
#define blocks (*(uint * *)(_frec_a + 2))
#define block_entries (*(uint * *)(_frec_a + 6))
  uint *cursor;
  uint slot;
  int block_count;
  
  slot = 0;
  blocks = (uint *)0x0;
  read_bytes_or_fail((char *)&remaining,2,g_sym_file);
  if (remaining != 0) {
    blocks = stock_malloc((remaining + 1) / 2 << 3);
    if (blocks == (uint *)0x0) {
      report_codegen_message(0xbcd,1,0,0,(char *)0x0);
    }
    else {
      block_count = 0;
      zero_words(blocks,((uint)((remaining + 1) - (remaining + 1 >> 0x1f)) >> 1 & 0x1fffffff) * 2);
      if (remaining != 0) {
        block_entries = blocks + 1;
        do {
          slot = 0;
          cursor = block_entries;
          do {
            if (remaining == 0) break;
            slot = slot + 1;
            read_bytes_or_fail((char *)cursor,2,g_sym_file);
            *(short *)cursor = (short)*cursor + 0xb6;
            remaining = remaining + -1;
            cursor = (uint *)((int)cursor + 2);
          } while (slot < 2);
          block_count = block_count + 1;
          block_entries = block_entries + 2;
        } while (remaining != 0);
      }
      block_count = block_count + -1;
      if (slot < 2) {
        *(undefined2 *)((int)blocks + (slot + block_count * 4) * 2 + 4) = 0xffff;
      }
      cursor = blocks;
      if (0 < block_count) {
        do {
          block_count = block_count + -1;
          *cursor = (uint)(cursor + 2);
          cursor = cursor + 2;
        } while (block_count != 0);
      }
    }
  }
  return blocks;
#undef remaining
#undef blocks
#undef block_entries
}



