#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_source_line_list
#define g_source_line_list (*(source_line_range * *)(g_sd + 0x10c64))


// entry: 00420565
// name : free_line_directive_list
// size : 166
// sig  : void __cdecl free_line_directive_list(int free_all)


int __cdecl free_line_directive_list(int free_all)

{
  bool more;
  source_line_range *range_node;
  source_line_range *next_range;
  
  if (g_source_line_list != (source_line_range *)0x0) {
    range_node = g_source_line_list;
    while( true ) {
      if (free_all == 0) {
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
      pool_free(range_node,0x18);
      range_node = next_range;
    }
    g_source_line_list = range_node;
  }
  return;
}
