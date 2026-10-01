#include "decls.h"
#include "imports.h"

// entry: 00409340
// name : dump_block_numbers
// size : 79
// sig  : void dump_block_numbers(block_list * list)


int __cdecl dump_block_numbers(block_list *list)

{
  int col;
  
  col = 0;
  while (list != (block_list *)0x0) {
    col = col + 1;
    FID_conflict__wprintf(&g_str_percent_5d_colon,(int)list->block->number);
    list = list->next;
    if (10 < col) {
      if (list == (block_list *)0x0) break;
      col = 0;
      FID_conflict__wprintf(s___00434f48);
    }
  }
  FID_conflict__wprintf(&g_str_newline);
  return;
}



