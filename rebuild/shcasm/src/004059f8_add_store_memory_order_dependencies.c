#include "decls.h"
#include "imports.h"

// entry: 004059f8
// name : add_store_memory_order_dependencies
// size : 451
// sig  : void add_store_memory_order_dependencies(void)


int __cdecl add_store_memory_order_dependencies(void)

{
  char other;
  char store_entry;
  
  for (store_entry = (char)g_pipeline_window_last_index; -1 < store_entry;
      store_entry = store_entry + -1) {
    if (('\x10' < g_superscalar_window[store_entry].issue_group) &&
       (g_superscalar_window[store_entry].issue_group < '\x16')) {
      for (other = '\0'; other <= g_pipeline_window_last_index; other = other + '\x01') {
        if ((('\x06' < g_superscalar_window[other].issue_group) &&
            (g_superscalar_window[other].issue_group < '\x16')) && (other != store_entry)) {
          if (other < store_entry) {
            g_superscalar_window[other].ambi_children =
                 g_superscalar_window[other].ambi_children |
                 *(uint *)(&g_window_entry_bit_masks + store_entry * 4);
            g_superscalar_window[other].ambi_child_count =
                 g_superscalar_window[other].ambi_child_count + '\x01';
            g_superscalar_window[store_entry].ambi_parents =
                 g_superscalar_window[store_entry].ambi_parents |
                 *(uint *)(&g_window_entry_bit_masks + other * 4);
            g_superscalar_window[store_entry].ambi_parent_count =
                 g_superscalar_window[store_entry].ambi_parent_count + '\x01';
          }
          else {
            g_superscalar_window[store_entry].ambi_children =
                 g_superscalar_window[store_entry].ambi_children |
                 *(uint *)(&g_window_entry_bit_masks + other * 4);
            g_superscalar_window[store_entry].ambi_child_count =
                 g_superscalar_window[store_entry].ambi_child_count + '\x01';
            g_superscalar_window[other].ambi_parents =
                 g_superscalar_window[other].ambi_parents |
                 *(uint *)(&g_window_entry_bit_masks + store_entry * 4);
            g_superscalar_window[other].ambi_parent_count =
                 g_superscalar_window[other].ambi_parent_count + '\x01';
          }
        }
      }
    }
  }
  return;
}
