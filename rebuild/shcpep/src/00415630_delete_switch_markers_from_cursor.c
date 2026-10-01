#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_switch_scan_block
#define g_switch_scan_block (*(code_node * *)(g_sd + 0x5c04))


// entry: 00415630
// name : delete_switch_markers_from_cursor
// size : 95
// sig  : void delete_switch_markers_from_cursor(void)


int __cdecl delete_switch_markers_from_cursor(void)

{
  code_node *block;
  code_node *next_node;
  
  if (g_switch_scan_block == (code_node *)0x0) {
    g_switch_scan_block = g_current_node_list;
  }
  else {
    g_switch_scan_block = g_switch_scan_block->next_block;
  }
  if (g_switch_scan_single_block == 0) {
    g_switch_scan_single_block = 0;
    next_node = g_switch_scan_block;
    while (block = next_node, block != (code_node *)0x0) {
      delete_switch_markers_in_block(block);
      g_switch_scan_block = block;
      next_node = block->next_block;
    }
    return;
  }
  delete_switch_markers_in_block(g_switch_scan_block);
  return;
}



