#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_last_block
#define g_last_block (*(code_node * *)(g_sd + 0x5bc4))


// entry: 00409b70
// name : find_preceding_nonempty_block
// size : 112
// sig  : code_node * find_preceding_nonempty_block(code_node * block)


code_node * __cdecl find_preceding_nonempty_block(code_node *block)

{
  psd *final_rec;
  code_node *next;
  code_node *scan;
  code_node *prev;
  
  scan = (code_node *)0x0;
  if ((block != (code_node *)0x0) && (block != g_current_node_list)) {
    do {
      next = g_current_node_list;
      prev = scan;
      if (g_current_node_list == (code_node *)0x0) {
LAB_00409bac:
        if (g_last_block == scan) {
          final_rec = find_block_final_record(g_last_block);
          block = g_last_block;
          if (final_rec != (psd *)0x0) {
            return g_last_block;
          }
        }
      }
      else {
        do {
          scan = next;
          if (block == scan) {
            final_rec = find_block_final_record(prev);
            block = prev;
            next = scan;
            scan = prev;
            if (final_rec != (psd *)0x0) {
              return prev;
            }
            break;
          }
          next = scan->next_block;
          prev = scan;
        } while (next != (code_node *)0x0);
        if (next == (code_node *)0x0) goto LAB_00409bac;
      }
    } while (block != g_current_node_list);
  }
  return (code_node *)0x0;
}



