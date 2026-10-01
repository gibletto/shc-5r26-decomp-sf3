#include "decls.h"
#include "imports.h"

// entry: 00405c60
// name : dump_block_list
// size : 37
// sig  : void dump_block_list(block_list * list)


int __cdecl dump_block_list(block_list *list)

{
  for (; list != (block_list *)0x0; list = list->next) {
    FID_conflict__wprintf(&g_str_block_number_comma,(int)list->block->number);
  }
  return;
}



